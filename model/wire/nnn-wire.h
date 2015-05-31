/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-wire.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-wire.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-wire.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *          Zhu Li <phillipszhuli1990@gmail.com>
 */

#ifndef NNN_WIRE_H
#define NNN_WIRE_H

#include "ns3/buffer.h"

#include "ns3/nnn-common.h"
#include "ns3/nnn-naming.h"
#include "ns3/nnn-pdus.h"

NNN_NAMESPACE_BEGIN

struct Wire
{
  enum
  {
    WIRE_FORMAT_DEFAULT = -2,
    WIRE_FORMAT_AUTODETECT = -1,
    WIRE_FORMAT_NNNSIM = 0
  };

  static Ptr<Packet>
  FromNULLp (Ptr<const NULLp> n_o, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<NULLp>
  ToNULLp (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromSO (Ptr<const SO> so_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<SO>
  ToSO (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromDO (Ptr<const DO> do_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<DO>
  ToDO (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromEN (Ptr<const EN> n_o, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<EN>
  ToEN (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromAEN (Ptr<const AEN> n_o, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<AEN>
  ToAEN (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromREN (Ptr<const REN> n_o, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<REN>
  ToREN (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromDEN (Ptr<const DEN> n_o, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<DEN>
  ToDEN (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromINF (Ptr<const INF> n_o, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<INF>
  ToINF (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromDU (Ptr<const DU> du_o, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<DU>
  ToDU (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  static Ptr<Packet>
  FromOEN (Ptr<const OEN> du_o, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<OEN>
  ToOEN (Ptr<Packet> packet, int8_t type = WIRE_FORMAT_AUTODETECT);

  // Helper methods for Python
  static std::string
  FromNULLpStr (Ptr<const NULLp> so_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<NULLp>
  ToNULLpStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromSOStr (Ptr<const SO> so_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<SO>
  ToSOStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromDOStr (Ptr<const DO> do_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<DO>
  ToDOStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromDUStr (Ptr<const DU> du_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<DU>
  ToDUStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromENStr (Ptr<const EN> en_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<EN>
  ToENStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromAENStr (Ptr<const AEN> aen_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<AEN>
  ToAENStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromRENStr (Ptr<const REN> ren_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<REN>
  ToRENStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromDENStr (Ptr<const DEN> den_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<DEN>
  ToDENStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromINFStr (Ptr<const INF> inf_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<INF>
  ToINFStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  static std::string
  FromOENStr (Ptr<const OEN> du_p, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  static Ptr<OEN>
  ToOENStr (const std::string &wire, int8_t type = WIRE_FORMAT_AUTODETECT);

  // /*
  //  * @brief Get size of buffer to fit wire-formatted name object
  //  */
  // static uint32_t
  // FromNameSize (Ptr<const Name> name, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  /**
   * @brief Convert name to wire format
   */
  static std::string
  FromName (Ptr<const NNNAddress> name, int8_t wireFormat = WIRE_FORMAT_DEFAULT);

  /**
   * @brief Convert name from wire format
   */
  static Ptr<NNNAddress>
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

NNN_NAMESPACE_END

#endif // NNN_WIRE_H
