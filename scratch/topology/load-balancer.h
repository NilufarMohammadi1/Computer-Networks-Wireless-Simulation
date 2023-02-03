#include <iostream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

class LoadBalancer : public Application 
{
public:
  LoadBalancer (uint16_t m_port, Ipv4InterfaceContainer& receivers);
  virtual ~LoadBalancer ();

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void); 

  void HandleRead (Ptr<Socket> socket);

  uint16_t m_port;
  Ptr<Socket> m_socket;
  Ipv4InterfaceContainer m_receivers;
  std::vector<Ptr<Socket>> receiverSockets;
};
