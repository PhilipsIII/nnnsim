/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-aen.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-aen.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-aen.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _NNN_AEN_HEADER_H_
#define _NNN_AEN_HEADER_H_

#include "../nnn-pdu.h"
#include "../nnn-en-pdus.h"
#include "../../../nnn-naming.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn
     * @brief 3N AEN packet (wire formats are defined in wire)
     **/
    class AEN : public ENPDU
    {
    public:
      /**
       * \brief Constructor
       *
       * Creates a AEN PDU
       **/
      AEN ();

      /**
       * \brief Constructor
       *
       *
       * @param name 3N name Ptr
       **/
      AEN(Ptr<NNNAddress> name);

      /**
       * \brief Constructor
       *
       * Creates a AEN PDU with payload
       *
       * @param name 3N name
       * @param payload Packet Ptr
       **/
      AEN(const NNNAddress &name);

      /**
       * @brief Copy constructor
       */
      AEN (const AEN &aen_p);

      /**
       * \brief Get 3N name
       *
       * Gets 3N name.
       **/
      const NNNAddress&
      GetName () const;

      /**
       * @brief Get smart pointer to the interest name (to avoid extra memory usage)
       */
      Ptr<const NNNAddress>
      GetNamePtr () const;

      /**
       * \brief Set 3N name
       *
       * @param name smart pointer to Name
       *
       **/

      void
      SetName (Ptr<NNNAddress> name);

      /**
       * \brief Another variant to set 3N name
       *
       * @param name const reference to Name object
       *
       **/
      void
      SetName (const NNNAddress &name);

      Time
      GetLeasetime() const;

      void
      SetLeasetime (Time lease);

      /**
       * @brief Print AEN in plain-text to the specified output stream
       */
      void
      Print (std::ostream &os) const;

    private:
      // NO_ASSIGN
      AEN &
      operator = (const AEN &other) { return *this; }

    private:
      Time m_lease;             ///< @brief Lease absolute time for 3N Address
      Ptr<NNNAddress> m_name;   ///< @brief Destination 3N Address

    };

    inline std::ostream &
    operator << (std::ostream &os, const AEN &i)
    {
      i.Print (os);
      return os;
    }

    /**
     * @brief Class for Interest parsing exception
     */
    class AENException {};

  } // namespace nnn
} // namespace ns3

#endif // _NNN_AEN_HEADER_H_
