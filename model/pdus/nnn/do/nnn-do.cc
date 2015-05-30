/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-do.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-do.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-do.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"

#include "nnn-do.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.DO");

  namespace nnn
  {
    DO::DO ()
    : NNNPDU (DO_NNN, Seconds (0))
    , DATAPDU ()
    , m_name (Create<NNNAddress> ())
    {
    }

    DO::DO (Ptr<NNNAddress> name, Ptr<Packet> payload)
    : NNNPDU (DO_NNN, Seconds (0))
    , DATAPDU ()
    , m_name (name)
    {
      if (m_payload == 0)
	m_payload = Create<Packet> ();
      else
	m_payload = payload;
    }

    DO::DO (const NNNAddress &name, Ptr<Packet> payload)
    : NNNPDU (DO_NNN, Seconds(0))
    , DATAPDU ()
    , m_name (Create<NNNAddress> (name))
    {
      if (m_payload == 0)
	m_payload = Create<Packet> ();
      else
	m_payload = payload;
    }

    DO::DO (const DO &do_p)
    {
      NS_LOG_FUNCTION("DO correct copy constructor");
      DO ();
      SetVersion (do_p.GetVersion ());
      SetLifetime (do_p.GetLifetime ());
      SetName (do_p.GetName());
      SetPDUPayloadType (do_p.GetPDUPayloadType ());
      SetPayload (do_p.GetPayload()->Copy ());
      SetWire (do_p.GetWire ());
    }

    const NNNAddress&
    DO::GetName () const
    {
      if (m_name == 0) throw DOException ();
      return *m_name;
    }

    Ptr<const NNNAddress>
    DO::GetNamePtr () const
    {
      return m_name;
    }

    void
    DO::SetName (Ptr<NNNAddress> name)
    {
      m_name = name;
      SetWire(0);
    }

    void
    DO::SetName (const NNNAddress &name)
    {
      m_name = Create<NNNAddress> (name);
      SetWire(0);
    }

    void
    DO::Print (std::ostream &os) const
    {
      os << "<DO>" << std::endl;
      NNNPDU::Print (os);
      os << "  <Name>" << GetName () << "</Name>" << std::endl;
      DATAPDU::Print (os);
      os << "</DO>" << std::endl;
    }
  } // namespace nnn
} // namespace ns3
