/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-net-device-face.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-net-device-face.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-net-device-face.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Zhu Li <phillipszhuli1990@gmail.com>
 *          Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/channel.h"
#include "ns3/net-device.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/node.h"
#include "ns3/pointer.h"
#include "ns3/point-to-point-net-device.h"

#include "nnn-net-device-face.h"

#include "ns3/nnn-address.h"
#include "ns3/nnn-l3-protocol.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.NetDeviceFace");

  namespace nnn
  {
    NS_OBJECT_ENSURE_REGISTERED (NetDeviceFace);

    TypeId
    NetDeviceFace::GetTypeId ()
    {
      static TypeId tid = TypeId ("ns3::nnn::NetDeviceFace")
    		    .SetParent<Face> ()
    		    .SetGroupName ("Nnn")
    		    ;
      return tid;
    }

    /**
     * By default, Face are created in the "down" state.  Before
     * becoming useable, the user must invoke SetUp on the face
     */
    NetDeviceFace::NetDeviceFace (Ptr<Node> node, const Ptr<NetDevice> &netDevice)
    : Face (node)
    , m_netDevice (netDevice)
    {
      NS_LOG_FUNCTION (this << netDevice);

      SetMetric (1); // default metric
      SetAddress (m_netDevice->GetAddress());

      NS_ASSERT_MSG (m_netDevice != 0, "NetDeviceFace needs to be assigned a valid NetDevice");
    }

    NetDeviceFace::~NetDeviceFace ()
    {
      NS_LOG_FUNCTION_NOARGS ();
    }

    NetDeviceFace& NetDeviceFace::operator= (const NetDeviceFace &)
    {
      return *this;
    }

    Ptr<NetDevice>
    NetDeviceFace::GetNetDevice () const
    {
      return m_netDevice;
    }

    void
    NetDeviceFace::RegisterNNNProtocolHandlers (const NULLpHandler &NULLpHandler, const SOHandler &SOHandler,
                                                const DOHandler &DOHandler, const ENHandler &ENHandler,
                                                const AENHandler &AENHandler, const RENHandler &RENHandler,
                                                const DENHandler &DENHandler, const INFHandler &INFHandler,
						const DUHandler &DUHandler, const OENHandler &OENHandler)
    {
      NS_LOG_FUNCTION (this);

      Face::RegisterNNNProtocolHandlers (NULLpHandler, SOHandler, DOHandler, ENHandler, AENHandler,
					 RENHandler, DENHandler, INFHandler, DUHandler, OENHandler);

      m_node->RegisterProtocolHandler (MakeCallback (&NetDeviceFace::ReceiveFromNetDevice, this),
                                       L3Protocol::ETHERNET_FRAME_TYPE, m_netDevice, true/*promiscuous mode*/);
    }

    void
    NetDeviceFace:: UnRegisterNNNProtocolHandlers ()
    {
      m_node->UnregisterProtocolHandler (MakeCallback (&NetDeviceFace::ReceiveFromNetDevice, this));
      Face::UnRegisterNNNProtocolHandlers ();
    }

    bool
    NetDeviceFace::Send (Ptr<Packet> packet)
    {
      if (!Face::Send (packet))
	{
	  return false;
	}

      NS_LOG_FUNCTION (this << packet);

      NS_ASSERT_MSG (packet->GetSize () <= m_netDevice->GetMtu (),
                     "Packet size " << packet->GetSize () << " exceeds device MTU "
                     << m_netDevice->GetMtu ()
                     << " for Nnn; fragmentation not supported");

      bool ok = m_netDevice->Send (packet, m_netDevice->GetBroadcast (),
                                   L3Protocol::ETHERNET_FRAME_TYPE);
      return ok;
    }

    bool
    NetDeviceFace::Send (Ptr<Packet> packet, Address addr)
    {
      if (!Face::Send (packet, addr))
	{
	  return false;
	}

      NS_LOG_FUNCTION (this << packet << " going from " << m_netDevice->GetAddress() << " to " << addr);

      NS_ASSERT_MSG (packet->GetSize () <= m_netDevice->GetMtu (),
                     "Packet size " << packet->GetSize () << " exceeds device MTU "
                     << m_netDevice->GetMtu ()
                     << " for Nnn; fragmentation not supported");

      bool ok = m_netDevice->Send (packet, addr, L3Protocol::ETHERNET_FRAME_TYPE);
      return ok;
    }

    // callback
    void
    NetDeviceFace::ReceiveFromNetDevice (Ptr<NetDevice> device,
                                         Ptr<const Packet> p,
                                         uint16_t protocol,
                                         const Address &from,
                                         const Address &to,
                                         NetDevice::PacketType packetType)
    {
      NS_LOG_FUNCTION (device << p << protocol << from << to << packetType);
      Receive (p);
    }


    std::ostream&
    NetDeviceFace::Print (std::ostream& os) const
    {
#ifdef NS3_LOG_ENABLE
      os << "dev[" << GetNode ()->GetId () << "]=net(" << GetId ();

      if (DynamicCast<PointToPointNetDevice> (m_netDevice))
	{
	  // extra debugging information which available ONLY for PointToPointNetDevice's
	  os << ",";
	  os << DynamicCast<PointToPointNetDevice> (m_netDevice)->GetChannel ()->GetDevice (0)->GetNode ()->GetId ();
	  os << "-";
	  os << DynamicCast<PointToPointNetDevice> (m_netDevice)->GetChannel ()->GetDevice (1)->GetNode ()->GetId ();
	}
      os << ")";
#else
      os << "dev=net(" << GetId () << ")";
#endif
      return os;
    }

  } // namespace nnn
} // namespace ns3
