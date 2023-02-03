# **WirelessNetworkSimulation-NS3**


## Project Goal

In this project, we will try to build a Wireless network containing sender and reciever nodes on both sides and a load balancer in between. We will then try to simulate this wireless network using NS3. We will be using IEEE 802.11 standard for simulation.

## Install, Build and Test NS-3

ns-3 is a discrete-event network simulator for Internet systems, targeted primarily for research and educational use.

For linux, Mac OS and windows users, you can simply check out the ns-3 documentation page given below. Follow the instructions and you will be good to go!

    1. Downloading ns3
    2. Building ns3
    3. Testing ns3

    (https://www.nsnam.org/docs/release/3.37/tutorial/html/quick-start.html#downloading-ns-3)
    

## Project Description

    As mentioned before, we are going to build a wireless network and simulate it later on. The topology of the project is given in the description file. You can also see a demo below.
       
   
                [SenderA]|                                                                          |[ReceiverA]
                [SenderB]|                                                                          |[ReceiverB]
                [SenderC]|-----------(SEND through UDP) -- Load Balancer -- (Recieve through TCP)-->|[ReceiverC]
                [SenderD]|                                                                          |[ReceiverD]
                [SenderE]|                                                                          |[ReceiverE]

Senders in this wireless network will use UDP to send packets to the load balancer. The load balancer uses TCP to send packets to the receivers. The load balancer will randomly choose one reciever and sends the recieved packet to the corresponding reciever using TCP.

## How to Run?
    
   switch to the root directory of your ptoject and run the following commands. Remember that since we are using ns3 version 3.35, we will use the ./waf for running the project. In newer versions ./ns3 is used in most cases.
   
   1. ./waf configure
   2. ./waf build
   3. ./waf --run "WLAN"
   
  
## Results

    Metrics such as throughput and duration per flow is calculated and can be seen below.
    <img src=“https://imgur.com/a/kcdOtlS”>
    
    ************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 1.62937 Sec
Throughput of Flow: 0.000505703 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 1.11318 Sec
Throughput of Flow: 0.000740199 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 3.72455 Sec
Throughput of Flow: 0.000335939 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 1.04829 Sec
Throughput of Flow: 0.000786016 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 4.60836 Sec
Throughput of Flow: 0.000271511 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 19.9987 Sec
Throughput of Flow: 0.853232 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 19.9998 Sec
Throughput of Flow: 0.89452 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 19.6515 Sec
Throughput of Flow: 0.784581 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 19.9911 Sec
Throughput of Flow: 0.783296 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 19.9966 Sec
Throughput of Flow: 0.767027 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 16.9145 Sec
Throughput of Flow: 0.00737929 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 17.714 Sec
Throughput of Flow: 0.00653628 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 17.711 Sec
Throughput of Flow: 0.00290168 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 17.1628 Sec
Throughput of Flow: 0.00397944 Mbps
************************** OUTPUT METRIC RESULT *****************************
Duration of Flow: 16.1881 Sec
Throughput of Flow: 0.0223018 Mbps


## Project Developers

    Nilufar Mohammadi
    Sepehr Karimi

