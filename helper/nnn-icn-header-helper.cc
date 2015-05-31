/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-header-helper.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-header-helper.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-header-helper.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/header.h"
#include "ns3/object.h"

#include "ns3/nnn-icn-pdus.h"
#include <iomanip>
#include "nnn-icn-header-helper.h"

const uint8_t INTEREST_ICN_BYTES[]       = {0x80, 0x00};
const uint8_t CONTENT_OBJECT_ICN_BYTES[] = {0x80, 0x01};

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.icn.HeaderHelper");

  namespace icn
  {
    HeaderHelper::Type
    HeaderHelper::GetICNHeaderType (Ptr<const Packet> packet)
    {
      uint8_t type[2];
      uint32_t read=packet->CopyData (type,2);

      if (read!=2) throw UnknownHeaderException();

      NS_LOG_DEBUG (*packet);
      if (type[0] == INTEREST_ICN_BYTES[0] && type[1] == INTEREST_ICN_BYTES[1])
	{
	  return HeaderHelper::INTEREST_ICN;
	}
      else if (type[0] == CONTENT_OBJECT_ICN_BYTES[0] && type[1] == CONTENT_OBJECT_ICN_BYTES[1])
	{
	  return HeaderHelper::CONTENT_OBJECT_ICN;
	}

      NS_LOG_DEBUG (*packet);
      throw UnknownHeaderException();
    }
  } // namespace icn
} // namespace ns3
