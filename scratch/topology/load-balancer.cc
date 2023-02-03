
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "load-balancer.h"


NS_LOG_COMPONENT_DEFINE ("LoadBalancer");

LoadBalancer::LoadBalancer (uint16_t m_port, Ipv4InterfaceContainer& receivers)
  : m_port (m_port),
    m_receivers (receivers)
{
  std::srand (time(0));
}

LoadBalancer::~LoadBalancer ()
{
}

void
LoadBalancer::StartApplication (void)
{
  m_socket = Socket::CreateSocket (GetNode (), UdpSocketFactory::GetTypeId ());
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), m_port);
  m_socket->Bind (local);
  m_socket->SetRecvCallback (MakeCallback (&LoadBalancer::HandleRead, this));

  for (uint32_t i = 0; i < m_receivers.GetN (); i++)
  {
    Ptr<Socket> sock = Socket::CreateSocket (GetNode (), TcpSocketFactory::GetTypeId ());
    InetSocketAddress sockAddr (m_receivers.GetAddress (i), m_port);
    sock->Connect (sockAddr);
    receiverSockets.push_back (sock);    
  }
  

}

void
LoadBalancer::StopApplication (void)
{
  m_socket->Close ();
}

void LoadBalancer::HandleRead (Ptr<Socket> socket)
{

  Ptr<Packet> packet;
  Address from;

  while ((packet = socket->RecvFrom (from)))
  {
    NS_LOG_INFO ("At time " << Simulator::Now ().As (Time::S) <<" loadbalancer received from "<< 
                  InetSocketAddress::ConvertFrom(from));
    if (packet->GetSize () == 0)
    { 
      break;
    }

    int receiverIndex = std::rand () % m_receivers.GetN ();

    receiverSockets[receiverIndex]->Send (packet);


    NS_LOG_INFO ("At time " << Simulator::Now().As (Time::S) << " loadbalancer redirect message to " <<
                 m_receivers.GetAddress (receiverIndex) << " port " << m_port);

  }
}
