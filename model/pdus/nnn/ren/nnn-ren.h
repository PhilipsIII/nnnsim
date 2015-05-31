/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-ren.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-ren.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-ren.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _NNN_REN_HEADER_H_
#define _NNN_REN_HEADER_H_

#include "ns3/nnn-pdu.h"
#include "ns3/nnn-en-pdus.h"
#include "ns3/nnn-naming.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn
     * @brief 3N REN PDU (wire formats are defined in wire)
     **/
    class REN : public ENPDU
    {
    public:
      /**
       * \brief Constructor
       *
       * Creates a REN PDU
       **/
      REN ();

      /**
       * \brief Constructor
       *
       *
       * @param name 3N name Ptr
       **/
      REN(Ptr<NNNAddress> name);

      /**
       * \brief Constructor
       *
       * Creates a REN PDU with payload
       *
       * @param name NNNAddress object
       **/
      REN(const NNNAddress &name);

      /**
       * @brief Copy constructor
       */
      REN (const REN &ren_p);

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
       * @param name smart pointer to 3N name
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
      GetRemainLease () const;

      void
      SetRemainLease (Time ex_lease);

      /**
       * @brief Print REN in plain-text to the specified output stream
       */
      void
      Print (std::ostream &os) const;

    private:
      // NO_ASSIGN
      REN &
      operator = (const REN &other) { return *this; }

      Time m_re_lease;          ///< @brief Lease absolute time for 3N name
      Ptr<NNNAddress> m_name;   ///< @brief Destination 3N name used in the PDU
    };

    inline std::ostream &
    operator << (std::ostream &os, const REN &i)
    {
      i.Print (os);
      return os;
    }

    /**
     * @brief Class for Interest parsing exception
     */
    class RENException {};

  } // namespace nnn
} // namespace ns3

#endif // _NNN_REN_HEADER_H_
