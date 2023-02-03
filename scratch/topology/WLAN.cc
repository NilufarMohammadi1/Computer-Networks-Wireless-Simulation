
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/mobility-module.h"
#include "ns3/applications-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/ssid.h"
#include "ns3/error-rate-model.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/yans-error-rate-model.h"
#include "ns3/gnuplot.h"
#include "load-balancer.h"


using namespace ns3;

std::string POSITION_MOBOLITY = "ns3::ConstantPositionMobilityModel";
int NODE_COUNT = 5; // node sender and reciver count
float RUN_TIME = 20.0; // life time of application
std::string IP = "10.10.10.1"; // ip address
std::string SUBNET_MASK = "255.255.255.0"; // subnet mask
uint16_t port = 8000; // run port
int PACKET_SIZE = 1024; // each packet send
float INTERVAL = 1.0; // interval between packaet
float MAX_PACKETS = 10.0; // max packet count

std::string ERRORRATE = "ErrorRate";
std::string WDTH = "ChannelWidth";
std::string STAWIFI = "ns3::StaWifiMac";
std::string APWIFI = "ns3::ApWifiMac";
std::string AARFWIFI = "ns3::AarfWifiManager";

WifiHelper wifi;
YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
YansWifiPhyHelper phy;
WifiMacHelper mac;

NetDeviceContainer staDeviceSender;
NetDeviceContainer staDeviceReceiver;
NetDeviceContainer apDeviceLoadBalancer;
MobilityHelper mobility;
Ipv4AddressHelper address;
Ipv4InterfaceContainer loadBalancerInterface;
Ipv4InterfaceContainer senderInterface, receiverInterface;
InternetStackHelper stack;

void
init_log ()
{ 
  //Predefined log statements 
  LogComponentEnable ("Scheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("PacketBurst", LOG_LEVEL_ALL);
  LogComponentEnable ("UdpSocket", LOG_LEVEL_ALL);
}

Ssid ssid;

NodeContainer node_sender;
NodeContainer node_reciever;
NodeContainer node_loadBalancer;

void runPre(){
  ssid = Ssid ("ns-3-ssid");
  mac.SetType (STAWIFI,"Ssid", SsidValue (ssid),"ActiveProbing", BooleanValue (false));
}


Ptr<RateErrorModel> em;
// set error rate
void nilufar(){
  em = CreateObject<RateErrorModel> ();
  em->SetAttribute (ERRORRATE, DoubleValue (0.000001));
}


void whatever(){
  phy.SetChannel (channel.Create ());
  phy.Set (WDTH, UintegerValue (20));

  wifi.SetStandard (WifiStandard::WIFI_STANDARD_80211a);   // set standard to 802.11
	wifi.SetRemoteStationManager (AARFWIFI);
}

void setIP(){
  address.SetBase ("10.1.1.0", "255.255.255.0");
}


void
checkMetrics (FlowMonitorHelper *fmhelper, Ptr<FlowMonitor> flowMon,Gnuplot2dDataset DataSet)
{
  double nilufar = 1.0;
  std::map<FlowId, FlowMonitor::FlowStats> flowStats = flowMon->GetFlowStats ();
  Ptr<Ipv4FlowClassifier> classing = DynamicCast<Ipv4FlowClassifier> (fmhelper->GetClassifier ());
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator stats = flowStats.begin (); stats != flowStats.end (); ++stats)
    {
      std::cout << "************************** OUTPUT METRIC RESULT *****************************" << std::endl;
      std::cout << "Duration of Flow: "<< (stats->second.timeLastRxPacket.GetSeconds () - stats->second.timeFirstTxPacket.GetSeconds ()) << " Sec";
      std::cout << std::endl;
      std::cout << "Throughput of Flow: " << stats->second.rxBytes * 8.0 / (stats->second.timeLastRxPacket.GetSeconds () - stats->second.timeFirstTxPacket.GetSeconds ()) / 1024 / 1024  << " Mbps" << std::endl;
      if (stats->first == 1) DataSet.Add ((double)Simulator::Now ().GetSeconds (),(double) nilufar); 
    }
  Simulator::Schedule (Seconds (RUN_TIME),&checkMetrics, fmhelper, flowMon,DataSet);
  flowMon->SerializeToXmlFile ("metricResults.xml", true, true);
}

Gnuplot2dDataset dataset;
Ptr<FlowMonitor> flowMonitor;
FlowMonitorHelper flowHelper;

void initThroughput(){

  dataset.SetTitle ("throughput");
  dataset.SetStyle (Gnuplot2dDataset::LINES_POINTS);
  flowMonitor = flowHelper.InstallAll ();
}


int main(int argc, char *argv[]) {

  init_log (); // init log for result
  
  node_sender.Create (NODE_COUNT);
  node_reciever.Create (NODE_COUNT);
  node_loadBalancer.Create (1);
 
  nilufar();

  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();

  whatever();
  runPre();

  staDeviceSender = wifi.Install (phy, mac, node_sender);
  staDeviceReceiver = wifi.Install (phy, mac, node_reciever);

  mac.SetType ("ns3::ApWifiMac", "Ssid", SsidValue (ssid));

  // NetDeviceContainer apDeviceLoadBalancer;
  apDeviceLoadBalancer = wifi.Install (phy, mac, node_loadBalancer);

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (node_sender);
  mobility.Install (node_reciever);
  mobility.Install (node_loadBalancer);

  stack.Install (node_loadBalancer);
  stack.Install (node_sender);
  stack.Install (node_reciever);

  setIP();

  //Senders
  loadBalancerInterface = address.Assign (apDeviceLoadBalancer);
  senderInterface = address.Assign (staDeviceSender);
  receiverInterface = address.Assign (staDeviceReceiver);
  UdpEchoClientHelper echoClient (loadBalancerInterface.GetAddress (0), port);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1000000000.0));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.0001)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
 
  ApplicationContainer clientApps = echoClient.Install (node_sender);
  clientApps.Start (Seconds(0.0));
  clientApps.Stop (Seconds(RUN_TIME));

  // Load Balancer
  Ptr<LoadBalancer> loadBalancerApp = CreateObject<LoadBalancer> (port, receiverInterface);
  node_loadBalancer.Get (0)->AddApplication (loadBalancerApp);
  loadBalancerApp->SetStartTime (Seconds (0.0));
  loadBalancerApp->SetStopTime (Seconds (RUN_TIME));


  // Receivers
  PacketSinkHelper sink ("ns3::TcpSocketFactory",InetSocketAddress (Ipv4Address::GetAny (), port));
  ApplicationContainer sinkApps = sink.Install (node_reciever);
  sinkApps.Start (Seconds (0.0));
  sinkApps.Stop (Seconds (RUN_TIME));

  // populate routing table
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  initThroughput();

  checkMetrics (&flowHelper, flowMonitor, dataset);

  // run til u hit run time = 20
  Simulator::Stop (Seconds (RUN_TIME));

	// run simulation
	Simulator::Run();
	Simulator::Destroy();

	return 0;
}
