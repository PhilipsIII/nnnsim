/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnnsim-den.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnnsim-den.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnnsim-den.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "../../nnnsim-common-hdr.h"
#include "../../nnnsim-common.h"

NNN_NAMESPACE_BEGIN

/**
 * @brief Namespace encapsulating wire operations
 */
namespace wire {

  /**
   * @brief Namespace for nnnSIM wire format operations
   */
  namespace nnnSIM {

    class DEN : public CommonHeader<nnn::DEN>
    {
    public:
      DEN ();
      DEN (Ptr<nnn::DEN> den_p);

      static Ptr<Packet>
      ToWire (Ptr<const nnn::DEN> den_p);

      static Ptr<nnn::DEN>
      FromWire (Ptr<Packet> packet);

      // from Header
      static TypeId GetTypeId (void);
      TypeId GetInstanceTypeId (void) const;
      uint32_t GetSerializedSize (void) const;
      void Serialize (Buffer::Iterator start) const;
      uint32_t Deserialize (Buffer::Iterator start);
    };

  }
}

NNN_NAMESPACE_END
