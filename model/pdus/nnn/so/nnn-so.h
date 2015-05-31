/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-so.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-so.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-so.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _NNN_SO_HEADER_H_
#define _NNN_SO_HEADER_H_

#include "ns3/nnn-pdu.h"
#include "ns3/nnn-data-pdus.h"
#include "ns3/nnn-naming.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn
     * @brief 3N SO packet (wire formats are defined in wire)
     **/
    class SO : public DATAPDU
    {
    public:
      /**
       * \brief Constructor
       *
       * Creates a SO PDU with no payload
       **/
      SO ();

      /**
       * \brief Constructor
       *
       * Creates a SO PDU with payload
       *
       * @param name NNNAddress Ptr
       * @param payload Packet Ptr
       **/
      SO(Ptr<NNNAddress> name, Ptr<Packet> payload);

      /**
       * \brief Constructor
       *
       * Creates a SO PDU with payload
       *
       * @param name NNNAddress
       * @param payload Packet Ptr
       **/
      SO(const NNNAddress &name, Ptr<Packet> payload);

      /**
       * @brief Copy constructor
       */
      SO (const SO &so_p);

      /**
       * \brief Get 3N name
       *
       * Gets 3N name.
       **/
      const NNNAddress&
      GetName () const;

      /**
       * @brief Get smart pointer to the 3N name (to avoid extra memory usage)
       */
      Ptr<const NNNAddress>
      GetNamePtr () const;

      /**
       * \brief Set 3N name
       *
       * @param name smart pointer to 3N
       *
       **/
      void
      SetName (Ptr<NNNAddress> name);

      /**
       * \brief Another variant to set 3N name
       *
       * @param name const reference to NNNAddress object
       *
       **/
      void
      SetName (const NNNAddress &name);

      /**
       * @brief Print SO in plain-text to the specified output stream
       */
      void
      Print (std::ostream &os) const;

    private:
      // NO_ASSIGN
      SO &
      operator = (const SO &other) { return *this; }

    private:
      Ptr<NNNAddress> m_name;   ///< @brief Source 3N name used in the packet
    };

    inline std::ostream &
    operator << (std::ostream &os, const SO &i)
    {
      i.Print (os);
      return os;
    }

    /**
     * @brief Class for Interest parsing exception
     */
    class SOException {};

  } // namespace nnn
} // namespace ns3

#endif // _NNN_SO_HEADER_H_
