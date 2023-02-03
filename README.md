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
    
    ![metric result for CN project 2](https://imgur.com/a/kcdOtlS)
    
## Project Developers

    Nilufar Mohammadi
    Sepehr Karimi

