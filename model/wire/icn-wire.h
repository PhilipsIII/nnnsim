/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  icn-wire.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  icn-wire.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with icn-wire.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef ICN_WIRE_H
#define ICN_WIRE_H

#include "ns3/buffer.h"

#include "../nnn-icn-common.h"

#include "../nnn-icn-naming.h"
#include "../nnn-icn-pdus.h"

ICN_NAMESPACE_BEGIN

struct Wire
{
  enum
  {
    WIRE_FORMAT_DEFAULT = -2,
    WIRE_FORMAT_AUTODETECT = -1,

    WIRE_FORMAT_NDNSIM = 0
  };

  static Ptr<Packet>
  FromInterest (Ptr<const nnn::Interest> interest, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<nnn::Interest>
  ToInterest (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromData (Ptr<const nnn::Data> data, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<nnn::Data>
  ToData (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);


  // Helper methods for Python
  static std::string
  FromInterestStr (Ptr<const nnn::Interest> interest, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<nnn::Interest>
  ToInterestStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromDataStr (Ptr<const nnn::Data> data, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<nnn::Data>
  ToDataStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  /**
   * @brief Convert name to wire format
   */
  static std::string
  FromName (Ptr<const Name> name, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  /**
   * @brief Convert name from wire format
   */
  static Ptr<Name>
  ToName (const std::string &wire, int8_t wireFormat = WIRE_FORMAT_DEFAULT);
};

inline std::string
PacketToBuffer (Ptr<const Packet> pkt)
{
  std::string buffer;
  buffer.resize (pkt->GetSize ());
  pkt->CopyData (reinterpret_cast<uint8_t*> (&buffer[0]), buffer.size ());

  return buffer;
}

inline Ptr<Packet>
BufferToPacket (const std::string &buffer)
{
  return Create<Packet> (reinterpret_cast<const uint8_t*> (&buffer[0]), buffer.size ());
}

ICN_NAMESPACE_END

#endif // ICN_WIRE_H
