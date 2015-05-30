/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-consumer-cbr.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-consumer-cbr.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-consumer-cbr.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-icn-consumer-cbr.h"

#include "ns3/boolean.h"
#include "ns3/callback.h"
#include "ns3/double.h"
#include "ns3/integer.h"
#include "ns3/log.h"
#include "ns3/names.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/uinteger.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.ICNConsumerCbr");

  namespace nnn
  {
    NS_OBJECT_ENSURE_REGISTERED (ConsumerCbr);

    TypeId
    ConsumerCbr::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::nnn::ICNConsumerCbr")
	.SetGroupName ("Nnn")
	.SetParent<Consumer> ()
	.AddConstructor<ConsumerCbr> ()
	.AddAttribute ("Frequency", "Frequency of interest packets",
		       StringValue ("1.0"),
		       MakeDoubleAccessor (&ConsumerCbr::m_frequency),
		       MakeDoubleChecker<double> ())
	.AddAttribute ("Randomize", "Type of send time randomization: none (default), uniform, exponential",
		       StringValue ("none"),
		       MakeStringAccessor (&ConsumerCbr::SetRandomize, &ConsumerCbr::GetRandomize),
		       MakeStringChecker ())
	.AddAttribute ("MaxSeq",
		       "Maximum sequence number to request",
		       IntegerValue (std::numeric_limits<uint32_t>::max ()),
		       MakeIntegerAccessor (&ConsumerCbr::m_seqMax),
		       MakeIntegerChecker<uint32_t> ())
	;
      return tid;
    }

    ConsumerCbr::ConsumerCbr ()
    : m_frequency (1.0)
    , m_firstTime (true)
    , useUni      (false)
    , uniRandom   (CreateObject<UniformRandomVariable> ())
    , expRandom   (CreateObject<ExponentialRandomVariable> ())
    , m_randomType ("")
    {
      NS_LOG_FUNCTION_NOARGS ();
      m_seqMax = std::numeric_limits<uint32_t>::max ();
    }

    ConsumerCbr::~ConsumerCbr ()
    {
    }

    void
    ConsumerCbr::ScheduleNextPacket ()
    {
      if (m_firstTime)
	{
	  m_sendEvent = Simulator::Schedule (Seconds (0.0),
					     &Consumer::SendPacket, this);
	  m_firstTime = false;
	}
      else if (!m_sendEvent.IsRunning ())
	{
	  double sched;
	  if (useUni)
	    {
	      sched = uniRandom->GetValue();
	    }
	  else
	    {
	      sched = expRandom->GetValue ();
	    }

	  m_sendEvent = Simulator::Schedule (
	      (m_randomType == "none") ? Seconds (1.0 / m_frequency) : Seconds (sched),
		  &Consumer::SendPacket, this);
	}
    }

    void
    ConsumerCbr::SetRandomize (const std::string &value)
    {
      if (value == "uniform")
	{
	  uniRandom->SetAttribute ("Min", DoubleValue (0.0));
	  uniRandom->SetAttribute ("Max", DoubleValue (2 * 1.0 / m_frequency));
	  useUni = true;
	}
      else if (value == "exponential")
	{
	  expRandom->SetAttribute ("Mean", DoubleValue (1.0 / m_frequency));
	  expRandom->SetAttribute ("Bound", DoubleValue (50 * 1.0 / m_frequency));
	  useUni = false;
	}

      m_randomType = value;
    }

    std::string
    ConsumerCbr::GetRandomize () const
    {
      return m_randomType;
    }
  } // namespace nnn
} // namespace ns3
