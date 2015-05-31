/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-nullp.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-nullp.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-nullp.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"

#include "nnn-nullp.h"

NS_LOG_COMPONENT_DEFINE ("nnn.NULLp");

namespace ns3
{
  namespace nnn
  {
    NULLp::NULLp ()
    : NNNPDU (NULL_NNN, Seconds (0))
    , DATAPDU ()
    {
    }

    NULLp::NULLp (Ptr<Packet> payload)
    : NNNPDU (NULL_NNN, Seconds (0))
    , DATAPDU ()
    {
      if (m_payload == 0)
	m_payload = Create<Packet> ();
      else
	m_payload = payload;
    }

    NULLp::NULLp (const NULLp &nullp)
    {
      NS_LOG_FUNCTION("NULLp correct copy constructor");
      NULLp ();
      SetVersion (nullp.GetVersion ());
      SetLifetime (nullp.GetLifetime ());
      SetPDUPayloadType (nullp.GetPDUPayloadType ());
      SetPayload (nullp.GetPayload()->Copy ());
      SetWire (nullp.GetWire ());
    }

    void
    NULLp::Print (std::ostream &os) const
    {
      os << "<NULLp>" << std::endl;
      NNNPDU::Print(os);
      DATAPDU::Print(os);
      os << "</NULLp>" << std::endl;
    }
  } // namespace nnn
} // namespace ns3
