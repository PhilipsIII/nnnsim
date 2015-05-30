/* -*- Mode: C++; c-file-style: "gnu"; -*- */
/*
 * Copyright (c) 2011-2013 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-interest.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-interest.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-interest.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Ilya Moiseenko <iliamo@cs.ucla.edu>
 *          Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *
 *   Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-icn-interest.h"

#include "ns3/log.h"
#include "ns3/unused.h"
#include "ns3/packet.h"



namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.icn.Interest");

  namespace nnn
  {

    Interest::Interest (Ptr<Packet> payload/* = Create<Packet> ()*/)
    : m_name ()
    , m_scope (0xFF)
    , m_interestLifetime (Seconds (0))
    , m_nonce (0)
    , m_nackType (NORMAL_INTEREST)
    , m_exclude (0)
    , m_payload (payload)
    , m_wire (0)
    {
      if (m_payload == 0) // just in case
	{
	  m_payload = Create<Packet> ();
	}
    }

    Interest::Interest (const Interest &interest)
    : m_name             (Create<icn::Name> (interest.GetName ()))
    , m_scope            (interest.m_scope)
    , m_interestLifetime (interest.m_interestLifetime)
    , m_nonce            (interest.m_nonce)
    , m_nackType         (interest.m_nackType)
    , m_exclude          (interest.m_exclude ? Create<icn::Exclude> (*interest.GetExclude ()) : 0)
    , m_payload          (interest.GetPayload ()->Copy ())
    , m_wire             (0)
    {
      NS_LOG_FUNCTION ("correct copy constructor");
    }

    void
    Interest::SetName (Ptr<icn::Name> name)
    {
      m_name = name;
      m_wire = 0;
    }

    void
    Interest::SetName (const icn::Name &name)
    {
      m_name = Create<icn::Name> (name);
      m_wire = 0;
    }

    const icn::Name&
    Interest::GetName () const
    {
      if (m_name==0) throw InterestException();
      return *m_name;
    }

    Ptr<const icn::Name>
    Interest::GetNamePtr () const
    {
      return m_name;
    }

    void
    Interest::SetScope (int8_t scope)
    {
      m_scope = scope;
      m_wire = 0;
    }

    int8_t
    Interest::GetScope () const
    {
      return m_scope;
    }

    void
    Interest::SetInterestLifetime (Time lifetime)
    {
      m_interestLifetime = lifetime;
      m_wire = 0;
    }

    Time
    Interest::GetInterestLifetime () const
    {
      return m_interestLifetime;
    }

    void
    Interest::SetNonce (uint32_t nonce)
    {
      m_nonce = nonce;
      m_wire = 0;
    }

    uint32_t
    Interest::GetNonce () const
    {
      return m_nonce;
    }

    void
    Interest::SetNack (uint8_t nackType)
    {
      m_nackType = nackType;
      m_wire = 0;
    }

    uint8_t
    Interest::GetNack () const
    {
      return m_nackType;
    }

    void
    Interest::SetExclude (Ptr<icn::Exclude> exclude)
    {
      m_exclude = exclude;
      m_wire = 0;
    }

    Ptr<const icn::Exclude>
    Interest::GetExclude () const
    {
      return m_exclude;
    }

    void
    Interest::SetPayload (Ptr<Packet> payload)
    {
      m_payload = payload;
      m_wire = 0;
    }

    Ptr<const Packet>
    Interest::GetPayload () const
    {
      return m_payload;
    }

    void
    Interest::Print (std::ostream &os) const
    {
      os << "I: " << GetName ();

      return;
      os << "<Interest>\n  <Name>" << GetName () << "</Name>\n";
      if (GetNack ()>0)
	{
	  os << "  <NACK>";
	  switch (GetNack ())
	  {
	    case NACK_LOOP:
	      os << "loop";
	      break;
	    case NACK_CONGESTION:
	      os << "congestion";
	      break;
	    default:
	      os << "unknown";
	      break;
	  }
	  os << "</NACK>\n";
	}
      os << "  <Scope>" << GetScope () << "</Scope>\n";
      if ( !GetInterestLifetime ().IsZero() )
	os << "  <InterestLifetime>" << GetInterestLifetime () << "</InterestLifetime>\n";
      if (GetNonce ()>0)
	os << "  <Nonce>" << GetNonce () << "</Nonce>\n";
      os << "</Interest>";
    }
  } // namespace icn
} // namespace ns3
