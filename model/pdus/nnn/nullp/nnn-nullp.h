/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-nullp.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-nullp.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-nullp.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _NNN_NULLP_HEADER_H_
#define _NNN_NULLP_HEADER_H_

#include "../nnn-pdu.h"
#include "../nnn-data-pdus.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn
     * @brief 3N NULLp PDU (wire formats are defined in wire)
     **/
    class NULLp : public DATAPDU
    {
    public:
      /**
       * \brief Constructor
       *
       * Creates a NULLp PDU with no payload
       **/
      NULLp ();

      /**
       * \brief Constructor
       *
       * Creates a NULLp PDU with payload
       **/
      NULLp(Ptr<Packet> payload);

      /**
       * @brief Copy constructor
       */
      NULLp (const NULLp &nullp);

      /**
       * @brief Print NULLp in plain-text to the specified output stream
       */
      void
      Print (std::ostream &os) const;

    private:
      // NO_ASSIGN
      NULLp &
      operator = (const NULLp &other) { return *this; }
    };

    inline std::ostream &
    operator << (std::ostream &os, const NULLp &i)
    {
      i.Print (os);
      return os;
    }

    /**
     * @brief Class for Interest parsing exception
     */
    class NULLpException {};

  } // namespace nnn
} // namespace ns3

#endif // _NNN_NULLP_HEADER_H_
