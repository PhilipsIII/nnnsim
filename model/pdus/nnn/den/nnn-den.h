/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-den.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-den.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-den.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *          Zhu Li <philipszhuli1990@ruri.waseda.jp>
 */

#ifndef _NNN_DEN_HEADER_H_
#define _NNN_DEN_HEADER_H_

#include "../nnn-pdu.h"
#include "../nnn-en-pdus.h"
#include "../../../nnn-naming.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn
     * @brief 3N DEN PDU (wire formats are defined in wire)
     **/
    class DEN : public ENPDU
    {
    public:
      /**
       * \brief Constructor
       *
       * Creates a DEN PDU
       **/
      DEN ();

      /**
       * \brief Constructor
       *
       *
       * @param name 3N Address Ptr
       **/
      DEN(Ptr<NNNAddress> name);

      /**
       * \brief Constructor
       *
       * Creates a DEN PDU with payload
       *
       * @param name 3N Address
       * @param payload Packet Ptr
       **/
      DEN(const NNNAddress &name);

      /**
       * @brief Copy constructor
       */
      DEN (const DEN &den_p);

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
       * @param name const reference to 3N name object
       *
       **/
      void
      SetName (const NNNAddress &name);

      /**
       * @brief Print DEN in plain-text to the specified output stream
       */
      void
      Print (std::ostream &os) const;

    private:
      // NO_ASSIGN
      DEN &
      operator = (const DEN &other) { return *this; }

    protected:
      Ptr<NNNAddress> m_name;   ///< @brief 3N Address used in the packet
    };

    inline std::ostream &
    operator << (std::ostream &os, const DEN &i)
    {
      i.Print (os);
      return os;
    }

    /**
     * @brief Class for Interest parsing exception
     */
    class DENException {};
  } //namespace nnn
} //namespace ns3

#endif // _NNN_DEN_HEADER_H_
