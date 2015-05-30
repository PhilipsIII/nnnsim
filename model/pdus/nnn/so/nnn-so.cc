/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-so.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-so.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-so.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"

#include "nnn-so.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.SO");

  namespace nnn
  {
    SO::SO ()
    : NNNPDU (SO_NNN, Seconds (0))
    , DATAPDU ()
    , m_name (Create<NNNAddress> ())
    {
    }

    SO::SO (Ptr<NNNAddress> name, Ptr<Packet> payload)
    : NNNPDU (SO_NNN, Seconds (0))
    , DATAPDU ()
    , m_name (name)
    {
      if (m_payload == 0)
	m_payload = Create<Packet> ();
      else
	m_payload = payload;
    }

    SO::SO (const NNNAddress &name, Ptr<Packet> payload)
    : NNNPDU (SO_NNN, Seconds (0))
    , DATAPDU ()
    , m_name     (Create<NNNAddress> (name))
    {
      if (m_payload == 0)
	m_payload = Create<Packet> ();
      else
	m_payload = payload;
    }

    SO::SO (const SO &so_p)
    {
      NS_LOG_FUNCTION("SO correct copy constructor");
      SO ();
      SetVersion (so_p.GetVersion ());
      SetLifetime (so_p.GetLifetime ());
      SetName (so_p.GetName());
      SetPDUPayloadType (so_p.GetPDUPayloadType ());
      SetPayload (so_p.GetPayload()->Copy ());
      SetWire (so_p.GetWire ());
    }

    const NNNAddress&
    SO::GetName () const
    {
      if (m_name == 0) throw SOException ();
      return *m_name;
    }

    Ptr<const NNNAddress>
    SO::GetNamePtr () const
    {
      return m_name;
    }

    void
    SO::SetName (Ptr<NNNAddress> name)
    {
      m_name = name;
      m_wire = 0;
    }

    void
    SO::SetName (const NNNAddress &name)
    {
      m_name = Create<NNNAddress> (name);
      m_wire = 0;
    }

    void
    SO::Print (std::ostream &os) const
    {
      os << "<SO>" << std::endl;
      NNNPDU::Print (os);
      os << "  <Name>" << GetName () << "</Name>" << std::endl;
      DATAPDU::Print (os);
      os << "</SO>" << std::endl;
    }
  } // namespace nnn
} // namespace ns3
