/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011-2013 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-data.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-data.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-data.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Ilya Moiseenko <iliamo@cs.ucla.edu>
 *          Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *
 *   Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"

#include <boost/foreach.hpp>
#include "nnn-icn-data.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.icn.Data");

  namespace nnn
  {

    Data::Data (Ptr<Packet> payload/* = Create<Packet> ()*/)
    : m_name (Create<icn::Name> ())
    , m_signature (0)
    , m_payload (payload)
    , m_keyLocator (0)
    , m_wire (0)
    {
      if (m_payload == 0) // just in case
	{
	  m_payload = Create<Packet> ();
	}
    }

    Data::Data (const Data &other)
    : m_name (Create<icn::Name> (other.GetName ()))
    , m_freshness (other.GetFreshness ())
    , m_timestamp (other.GetTimestamp ())
    , m_signature (other.GetSignature ())
    , m_payload (other.GetPayload ()->Copy ())
    , m_wire (0)
    {
      if (other.GetKeyLocator ())
	{
	  m_keyLocator = Create<icn::Name> (*other.GetKeyLocator ());
	}
    }

    void
    Data::SetName (Ptr<icn::Name> name)
    {
      m_name = name;
      m_wire = 0;
    }

    void
    Data::SetName (const icn::Name &name)
    {
      m_name = Create<icn::Name> (name);
      m_wire = 0;
    }

    const icn::Name&
    Data::GetName () const
    {
      if (m_name==0) throw DataException();
      return *m_name;
    }

    Ptr<const icn::Name>
    Data::GetNamePtr () const
    {
      return m_name;
    }


    void
    Data::SetTimestamp (const Time &timestamp)
    {
      m_timestamp = timestamp;
      m_wire = 0;
    }

    Time
    Data::GetTimestamp () const
    {
      return m_timestamp;
    }

    void
    Data::SetFreshness (const Time &freshness)
    {
      m_freshness = freshness;
      m_wire = 0;
    }


    Time
    Data::GetFreshness () const
    {
      return m_freshness;
    }

    void
    Data::SetSignature (uint32_t signature)
    {
      m_signature = signature;
      m_wire = 0;
    }

    uint32_t
    Data::GetSignature () const
    {
      return m_signature;
    }

    void
    Data::SetKeyLocator (Ptr<icn::Name> keyLocator)
    {
      m_keyLocator = keyLocator;
    }

    Ptr<const icn::Name>
    Data::GetKeyLocator () const
    {
      return m_keyLocator;
    }

    void
    Data::Print (std::ostream &os) const
    {
      os << "D: " << GetName ();
      // os << "<Data><Name>" << GetName () << "</Name><Content>";
    }

    void
    Data::SetPayload (Ptr<Packet> payload)
    {
      m_payload = payload;
      m_wire = 0;
    }

    Ptr<const Packet>
    Data::GetPayload () const
    {
      return m_payload;
    }

  } // namespace icn
} // namespace ns3
