/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-header-helper.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-header-helper.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-header-helper.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _ICN_HEADER_HELPER_H_
#define _ICN_HEADER_HELPER_H_

#include "ns3/ptr.h"

namespace ns3
{
  class Header;
  class Packet;

  namespace icn
  {
    class Name;

    /**
     * @ingroup icn-helpers
     *
     * \brief Class implementing functionality to detect ICN header type and
     * create the corresponding object
     *
     * ICN doesn't really have a header, so we need this class to
     * determine type of ICN PDUs and return the header class,
     * Interest or Data
     *
     * Throws UnknownHeaderException if header type couldn't be determined
     */
    class HeaderHelper
    {
    public:
      /**
     @brief enum for ICN PDU types
       */
      enum Type {INTEREST_ICN, CONTENT_OBJECT_ICN};

      /**
       *	Packet ::= Version
       *		   PacketType
       *		   (Interest | Data)
       *
       *        0                   1
       *        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
       *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       *        |    Version    |   PacketType  |
       *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       *
       * For ccnb-encoding compatibility, ``Version`` / ``PacketType`` has two reserved values to denote ccnb-encoded packet:
       *
       * Version 0x01, PacketType 0xD2 --- ccnb-encoded ``Interest`` packet
       * Version 0x04, PacketType 0x82 --- ccnb-encoded ``Data`` packet
       *
       *
       * It peeks first 2 bytes of a packet.
       *
       *  All interests start with
       *   +-----------------+  +---+---------+-------+
       *   | 0 0 0 0 0 0 0 1 |  | 1 | 1 0 1 0 | 0 1 0 |   (0x01 0xD2)
       *   +-----------------+  +---+---------+-------+
       *
       *  All content objects start with
       *   +-----------------+  +---+---------+-------+
       *   | 0 0 0 0 0 1 0 0 |  | 1 | 0 0 0 0 | 0 1 0 |   (0x04 0x82)
       *   +-----------------+  +---+---------+-------+
       *                          ^             ^^^^^
       *                          |               |
       *                      terminator      DTAG (Dictionary TAG)
       *
       * \see http://www.ccnx.org/releases/latest/doc/technical/BinaryEncoding.html
       */

      static Type
      GetICNHeaderType (Ptr<const Packet> packet);
    };

    /**
     * \brief Exception thrown if NDN stack receives unrecognized message type
     */
    class UnknownHeaderException {};

  } // namespace icn
} // namespace ns3

#endif // _ICN_HEADER_HELPER_H_
