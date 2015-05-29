/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-header-helper.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-header-helper.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-header-helper.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Zhu Li <phillipszhuli1990@gmail.com>
 *          Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _NNN_HEADER_HELPER_H_
#define _NNN_HEADER_HELPER_H_

#include "ns3/ptr.h"

#include "../model/pdus/nnn/nnn-pdu.h"

namespace ns3
{
  class Header;
  class Packet;

  namespace nnn
  {
    class NNNAddress;

    /**
     * @ingroup nnn-helpers
     *
     * \brief Class implementing functionality to detect 3N PDU type and
     * create the corresponding object
     *
     * Throws UnknownHeaderException if header type couldn't be determined
     */
    class HeaderHelper
    {
    public:
      static NNN_PDU_TYPE
      GetNNNHeaderType (Ptr<const Packet> packet);
    };

    /**
     * \brief Exception thrown if 3N stack receives unrecognized message type
     */
    class UnknownHeaderException {};

  } // namespace nnn
} // namespace ns3

#endif // _NNN_HEADER_HELPER_H_
