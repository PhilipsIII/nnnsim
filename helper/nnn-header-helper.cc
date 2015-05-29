/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-header-helper.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-header-helper.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-header-helper.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Zhu Li <phillipszhuli1990@gmail.com>
 *          Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/header.h"
#include "ns3/object.h"

#include <iomanip>
#include "nnn-header-helper.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.HeaderHelper");

  namespace nnn
  {
    NNN_PDU_TYPE
    HeaderHelper::GetNNNHeaderType (Ptr<const Packet> packet)
    {
      // Our header ID is of 32 bits
      uint8_t type[4];
      uint32_t read = packet->CopyData (type, 4);

      if (read != 4) throw UnknownHeaderException();

      // Convert the bytes to a 32 bit unsigned integer
      uint32_t retval = 0;
      retval |= type[3];
      retval <<= 8;
      retval |= type[2];
      retval <<= 8;
      retval |= type[1];
      retval <<= 8;
      retval |= type[0];

      NS_LOG_DEBUG (*packet);

      switch (retval)
      {
	case 0:
	  return NULL_NNN;
	case 1:
	  return SO_NNN;
	case 2:
	  return DO_NNN;
	case 3:
	  return DU_NNN;
	case 4:
	  return EN_NNN;
	case 5:
	  return OEN_NNN;
	case 6:
	  return AEN_NNN;
	case 7:
	  return REN_NNN;
	case 8:
	  return DEN_NNN;
	case 9:
	  return INF_NNN;
      }

      NS_LOG_DEBUG (*packet);
      throw UnknownHeaderException();
    }
  } // namespace nnn
} // namespace ns3
