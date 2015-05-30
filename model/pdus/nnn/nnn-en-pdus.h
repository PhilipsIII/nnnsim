/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-en-pdus.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-en-pdus.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-en-pdus.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _NNN_EN_PDUS_H_
#define _NNN_EN_PDUS_H_

#include <vector>
#include "ns3/nstime.h"
#include "ns3/address.h"

#include "nnn-pdu.h"

namespace ns3
{
  namespace nnn
  {
    class ENPDU : virtual public NNNPDU
    {
    public:
      ENPDU ();

      virtual
      ~ENPDU ();

      /**
       * \brief Get number of PoAs stored
       *
       * @param  const reference to Name object
       *
       **/
      uint32_t
      GetNumPoa () const;

      /**
       * \brief Get PoA names attached
       *
       **/
      std::vector<Address>
      GetPoas () const;

      Address
      GetOnePoa (uint32_t index) const;

      /**
       * \brief Add PoA name
       *
       * @param poa PoA name
       *
       **/
      void
      AddPoa (Address poa);

      /**
       * \brief Add PoA name
       *
       * @param poas Vector of PoA names
       *
       **/
      void
      AddPoa (std::vector<Address> poas);

      /**
       * @brief Print ENPDU in plain-text to the specified output stream
       */
      virtual void
      Print (std::ostream &os) const;

    protected:
      std::vector<Address> m_poas;  ///<@brief vector of PoA names
    };

  } /* namespace nnn */
} /* namespace ns3 */

#endif /* _NNN_EN_PDUS_H_ */
