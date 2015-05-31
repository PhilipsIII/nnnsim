/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2011-2012 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author:  Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 * Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-l3-tracer.h"

#include "ns3/node.h"
#include "ns3/packet.h"
#include "ns3/config.h"
#include "ns3/names.h"
#include "ns3/callback.h"

#include "ns3/nnn-pdus.h"
#include "ns3/nnn-icn-pdus.h"
#include "ns3/nnn-forwarding-strategy.h"

#include <boost/lexical_cast.hpp>

#include "ns3/nnn-face.h"
#include "ns3/nnn-pit-entry.h"

using namespace std;

namespace ns3
{
  namespace nnn
  {

    L3Tracer::L3Tracer (Ptr<Node> node)
    : m_nodePtr (node)
    {
      m_node = boost::lexical_cast<string> (m_nodePtr->GetId ());

      Connect ();

      string name = Names::FindName (node);
      if (!name.empty ())
	{
	  m_node = name;
	}
    }

    L3Tracer::L3Tracer (const std::string &node)
    : m_node (node)
    {
      Connect ();
    }

    L3Tracer::~L3Tracer ()
    {
    };


    void
    L3Tracer::Connect ()
    {
      Ptr<ForwardingStrategy> fw = m_nodePtr->GetObject<ForwardingStrategy> ();

      fw->TraceConnectWithoutContext ("OutInterests",  MakeCallback (&L3Tracer::OutInterests, this));
      fw->TraceConnectWithoutContext ("InInterests",   MakeCallback (&L3Tracer::InInterests, this));
      fw->TraceConnectWithoutContext ("DropInterests", MakeCallback (&L3Tracer::DropInterests, this));

      fw->TraceConnectWithoutContext ("OutData",  MakeCallback (&L3Tracer::OutData, this));
      fw->TraceConnectWithoutContext ("InData",   MakeCallback (&L3Tracer::InData, this));
      fw->TraceConnectWithoutContext ("DropData", MakeCallback (&L3Tracer::DropData, this));

      // only for some strategies
      fw->TraceConnectWithoutContext ("OutNacks",  MakeCallback (&L3Tracer::OutNacks, this));
      fw->TraceConnectWithoutContext ("InNacks",   MakeCallback (&L3Tracer::InNacks, this));
      fw->TraceConnectWithoutContext ("DropNacks", MakeCallback (&L3Tracer::DropNacks, this));

      // satisfied/timed out PITs
      fw->TraceConnectWithoutContext ("SatisfiedInterests", MakeCallback (&L3Tracer::SatisfiedInterests, this));
      fw->TraceConnectWithoutContext ("TimedOutInterests", MakeCallback (&L3Tracer::TimedOutInterests, this));

      // Mechanism PDUs
      fw->TraceConnectWithoutContext ("OutAENs",  MakeCallback (&L3Tracer::OutAENs, this));
      fw->TraceConnectWithoutContext ("InAENs",   MakeCallback (&L3Tracer::InAENs, this));
      fw->TraceConnectWithoutContext ("DropAENs", MakeCallback (&L3Tracer::DropAENs, this));

      fw->TraceConnectWithoutContext ("OutDENs",  MakeCallback (&L3Tracer::OutDENs, this));
      fw->TraceConnectWithoutContext ("InDENs",   MakeCallback (&L3Tracer::InDENs, this));
      fw->TraceConnectWithoutContext ("DropDENs", MakeCallback (&L3Tracer::DropDENs, this));

      fw->TraceConnectWithoutContext ("OutENs",  MakeCallback (&L3Tracer::OutENs, this));
      fw->TraceConnectWithoutContext ("InENs",   MakeCallback (&L3Tracer::InENs, this));
      fw->TraceConnectWithoutContext ("DropENs", MakeCallback (&L3Tracer::DropENs, this));

      fw->TraceConnectWithoutContext ("OutOENs",  MakeCallback (&L3Tracer::OutOENs, this));
      fw->TraceConnectWithoutContext ("InOENs",   MakeCallback (&L3Tracer::InOENs, this));
      fw->TraceConnectWithoutContext ("DropOENs", MakeCallback (&L3Tracer::DropOENs, this));

      fw->TraceConnectWithoutContext ("OutRENs",  MakeCallback (&L3Tracer::OutRENs, this));
      fw->TraceConnectWithoutContext ("InRENs",   MakeCallback (&L3Tracer::InRENs, this));
      fw->TraceConnectWithoutContext ("DropRENs", MakeCallback (&L3Tracer::DropRENs, this));

      fw->TraceConnectWithoutContext ("OutINFs",  MakeCallback (&L3Tracer::OutINFs, this));
      fw->TraceConnectWithoutContext ("InINFs",   MakeCallback (&L3Tracer::InINFs, this));
      fw->TraceConnectWithoutContext ("DropINFs", MakeCallback (&L3Tracer::DropINFs, this));

      // Data Transfer PDUs
      fw->TraceConnectWithoutContext ("OutNULLps",  MakeCallback (&L3Tracer::OutNULLps, this));
      fw->TraceConnectWithoutContext ("InNULLps",   MakeCallback (&L3Tracer::InNULLps, this));
      fw->TraceConnectWithoutContext ("DropNULLps", MakeCallback (&L3Tracer::DropNULLps, this));

      fw->TraceConnectWithoutContext ("OutDOs",  MakeCallback (&L3Tracer::OutDOs, this));
      fw->TraceConnectWithoutContext ("InDOs",   MakeCallback (&L3Tracer::InDOs, this));
      fw->TraceConnectWithoutContext ("DropDOs", MakeCallback (&L3Tracer::DropDOs, this));

      fw->TraceConnectWithoutContext ("OutDUs",  MakeCallback (&L3Tracer::OutDUs, this));
      fw->TraceConnectWithoutContext ("InDUs",   MakeCallback (&L3Tracer::InDUs, this));
      fw->TraceConnectWithoutContext ("DropDUs", MakeCallback (&L3Tracer::DropDUs, this));

      fw->TraceConnectWithoutContext ("OutSOs",  MakeCallback (&L3Tracer::OutSOs, this));
      fw->TraceConnectWithoutContext ("InSOs",   MakeCallback (&L3Tracer::InSOs, this));
      fw->TraceConnectWithoutContext ("DropSOs", MakeCallback (&L3Tracer::DropSOs, this));
    }
  } /* namespace nnn */
} /* namespace ns3 */
