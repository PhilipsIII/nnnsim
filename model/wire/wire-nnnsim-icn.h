/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  wire-nnnsim-icn.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  wire-nnnsim-icn.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with wire-nnnsim-icn.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef ICN_WIRE_NNNSIM_SYNTAX_H
#define ICN_WIRE_NNNSIM_SYNTAX_H

#include "ns3/buffer.h"
#include "ns3/nstime.h"
#include "ns3/ptr.h"

#include "ns3/nnn-icn-common.h"
#include "ns3/nnn-icn-naming.h"

ICN_NAMESPACE_BEGIN

namespace wire {

  /**
   * \brief Helper to encode nnnSIM wire elements
   */
  class IcnSim
  {
  public:
    /**
     * @brief Append Name in ICN encoding
     * @param start Buffer to store serialized Interest
     * @param name constant reference to Name object
     *
     * @returns written length
     */
    static size_t
    SerializeName (Buffer::Iterator &start, const Name &name);

    /**
     * @brief Estimate size of Name in ICN encoding
     * @param name constant reference to Name object
     * @returns estimated length
     */
    static size_t
    SerializedSizeName (const Name &name);

    /**
     * @brief Deserialize Name from ICN encodeing
     * @param start Buffer that stores serialized Interest
     * @param name Name object
     */
    static Ptr<Name>
    DeserializeName (Buffer::Iterator &start);


    enum Selectors {
      SelectorExclude = 0x01
    };

    enum ExcludeTypes {
      ExcludeNameType = 0x01,
      ExcludeAnyType = 0x02
    };

    /**
     * @brief Append Exclude in ICN encoding
     * @param start Buffer to store serialized Interest
     * @param exclude constant reference to Exclude object
     *
     * @returns written length
     */
    static size_t
    SerializeExclude (Buffer::Iterator &start, const Exclude &exclude);

    /**
     * @brief Estimate size of Exclude in ICN encoding
     * @param exclude constant reference to Exclude object
     * @returns estimated length
     */
    static size_t
    SerializedSizeExclude (const Exclude &exclude);

    /**
     * @brief Deserialize Exclude from ICN encodeing
     * @param start Buffer that stores serialized Interest
     * @param exclude Exclude object
     */
    static Ptr<Exclude>
    DeserializeExclude (Buffer::Iterator &start);
  };
} // wire

ICN_NAMESPACE_END

#endif // ICN_WIRE_NNNSIM_SYNTAX_H
