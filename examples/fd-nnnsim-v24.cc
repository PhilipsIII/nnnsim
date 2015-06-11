// Waseda University Sato Lab
// By Robin Wen
// nnnSim with FdNetDevice(File Descriptor Network Device)
// Broadcast nnn packet to ethernet
//
// +----------------------+     +-----------------------+
// |      client host     |     |      server host      |
// +----------------------+     +-----------------------+
// |     ns-3 Node 0      |     |      ns-3 Node 1      |
// |  +----------------+  |     |   +----------------+  |
// |  |    ns-3 TCP    |  |     |   |    ns-3 TCP    |  |
// |  +----------------+  |     |   +----------------+  |
// |  |    ns-3 IPv4   |  |     |   |    ns-3 IPv4   |  |
// |  +----------------+  |     |   +----------------+  |
// |  |   FdNetDevice  |  |     |   |   FdNetDevice  |  |
// |  |    10.1.1.1    |  |     |   |    10.1.1.2    |  |
// |  +----------------+  |     |   +----------------+  |
// |  |   raw socket   |  |     |   |   raw socket   |  |
// |  +----------------+  |     |   +----------------+  |
// |       | eth0 |       |     |        | eth0 |       |
// +-------+------+-------+     +--------+------+-------+
//
//             |                            |
//             +----------------------------+
//			   LAN
//
// To run this example you will need two hosts (client & server).
// Steps to run the experiment:
//
// 1 - Connect the 2 computers with an Ethernet cable.
// 2 - Set the IP addresses on both Ethernet devices. 
//  
// 3 - Set both Ethernet devices to promiscuous mode.
//	
//	sudo ip link set eth0 promisc on
//	//eth0 is Local Ehternet device
//
// 	both machines: $ sudo ip link set eth0 promisc on
//
// 4 - Give root suid to the raw socket creator binary.
//     If the --enable-sudo option was used to configure ns-3 with waf, then the following
//     step will not be necessary.
//
// both hosts: $ sudo chown root.root build/src/fd-net-device/ns3-dev-raw-sock-creator
// both hosts: $ sudo chmod 4755 build/src/fd-net-device/ns3-dev-raw-sock-creator
//
// 5 - Run the server side:
//
// server host: $ sudo ./waf --run="fd-nnnsim --deviceName=eth0 --serverMode=1"
//
// 6 - Run the client side:
//       
// client host: $ sudo ./waf --run="fd-nnnsim --deviceName=eth0"
//
// 7 - Run Wireshark
//
// Wireshark Filter
// Display Interests
// eth.src == 00:00:00:00:00:01
// Display Contents
// eth.src == 00:00:00:00:00:02 
// Display Both
// eth.src == 00:00:00:00:00:01 || eth.src == 00:00:00:00:00:02
//
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/config-store-module.h"
#include "ns3/point-to-point-module.h"

#include "ns3/fd-net-device-module.h" //fd netdevice

#include "ns3/nnnsim-module.h"//nnnsim


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("EmuFdNetDeviceSaturationExample");

int 
main (int argc, char *argv[])
{
  bool serverMode = false;

  std::string deviceName ("eth0");
  std::string macClient ("00:00:00:00:00:01"); //48:5a:b6:02:d2:80
  std::string macServer ("00:00:00:00:00:02"); //f8:b1:56:b5:08:34

  CommandLine cmd;
  cmd.AddValue ("deviceName", "Device name", deviceName);
  cmd.AddValue ("serverMode", "1:true, 0:false, default client", serverMode);
  cmd.AddValue ("mac-client", "Mac Address for Server Client : 00:00:00:00:00:01", macClient);
  cmd.AddValue ("mac-server", "Mac Address for Server Default : 00:00:00:00:00:02", macServer);
  cmd.Parse (argc, argv);

  Config::SetGlobal ("nnn::WireFormat", StringValue ("1"));

  Mac48AddressValue localMac;
  
  if (serverMode)
  {
     localMac = Mac48AddressValue (macServer.c_str ());
  }
  else
  {
     localMac =  Mac48AddressValue (macClient.c_str ());
  }
  
  GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));

  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

  NS_LOG_INFO ("Create Node");
  Ptr<Node> node = CreateObject<Node> ();

  NS_LOG_INFO ("Create Device");
  EmuFdNetDeviceHelper emu;
  emu.SetDeviceName (deviceName);
  NetDeviceContainer devices = emu.Install (node);
  Ptr<NetDevice> device = devices.Get (0);
  device->SetAttribute ("Address", localMac);

  nnn::NNNStackHelper nnnHelper;
  nnnHelper.SetDefaultRoutes (true);//broadcast nnn packet to LAN
  nnnHelper.InstallAll ();        

  if(serverMode)
  {
  nnn::AppHelper producerHelper ("ns3::nnn::Producer");
  producerHelper.SetPrefix ("/waseda/satolab");
  producerHelper.SetAttribute ("PayloadSize", StringValue("512"));
  producerHelper.Install (node);
  //emu.EnablePcap ("fd-server", device);
  }
  else
  {
  nnn::AppHelper consumerHelper ("ns3::nnn::ConsumerCbr");
  consumerHelper.SetPrefix ("/waseda/satolab");
  consumerHelper.SetAttribute ("Frequency", StringValue ("1")); // 10 interests a second
  consumerHelper.Install (node);
  //emu.EnablePcap ("fd-client", device);
  }

  Simulator::Stop (Seconds (100.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}

