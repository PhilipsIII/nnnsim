/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-pdu.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-pdu.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-pdu.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-pdu.h"

namespace ns3
{
  namespace nnn
  {
    NNNPDU::NNNPDU ()
    {
    }

    NNNPDU::NNNPDU(uint32_t pkt_id, Time ttl)
    : m_packetid    (pkt_id)
    , m_ttl         (ttl)
    , m_version     (A_NNN)
    , m_wire        (0)
    {
    }

    NNNPDU::NNNPDU (uint32_t pkt_id, Time ttl, uint16_t ver)
    : m_packetid    (pkt_id)
    , m_ttl         (ttl)
    , m_version     (ver)
    , m_wire        (0)
    {
    }

    NNNPDU::~NNNPDU ()
    {
    }

    void
    NNNPDU::Print(std::ostream &os) const
    {
      os << "  <TTL>" << GetLifetime () << "</TTL>" << std::endl;
      os << "  <Version>" << GetVersion () << "</Version>" << std::endl;
    }
  } /* namespace nnn */
} /* namespace ns3 */
