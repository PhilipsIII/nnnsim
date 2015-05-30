/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-inf.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-inf.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-inf.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _NNN_INF_HEADER_H_
#define _NNN_INF_HEADER_H_

#include "../nnn-pdu.h"
#include "../../../nnn-naming.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn
     * @brief 3N INF PDU (wire formats are defined in wire)
     **/
    class INF : public NNNPDU
    {
    public:
      /**
       * \brief Constructor
       *
       * Creates a INF PDU
       **/
      INF ();

      /**
       * \brief Constructor
       *
       *
       * @param oldname Old 3N Address
       * @param newname New 3N Address
       **/
      INF(Ptr<NNNAddress> oldname, Ptr<NNNAddress> newname);

      /**
       * \brief Constructor
       *
       * Creates a INF PDU with payload
       *
       * @param oldname 3N name
       * @param newname 3N name
       **/
      INF(const NNNAddress &oldname, const NNNAddress &newname);

      /**
       * @brief Copy constructor
       */
      INF (const INF &inf_p);

      /**
       * \brief Get old 3N name
       *
       * Gets old 3N name.
       **/
      const NNNAddress&
      GetOldName () const;

      /**
       * @brief Get smart pointer to the 3N name (to avoid extra memory usage)
       */
      Ptr<const NNNAddress>
      GetOldNamePtr () const;

      /**
       * \brief Set Old 3N name
       *
       * @param name smart pointer to NNNAddress
       *
       **/
      void
      SetOldName (Ptr<NNNAddress> name);

      /**
       * \brief Another variant to set old 3N name
       *
       * @param name const reference to NNNAddress object
       *
       **/
      void
      SetOldName (const NNNAddress &name);

      /**
       * \brief Get new 3N name
       *
       * Gets 3N name
       **/
      const NNNAddress&
      GetNewName () const;

      /**
       * @brief Get smart pointer to the 3N name (to avoid extra memory usage)
       */
      Ptr<const NNNAddress>
      GetNewNamePtr () const;

      /**
       * \brief Set Old 3N name
       *
       * @param name smart pointer to NNNAddress
       *
       **/
      void
      SetNewName (Ptr<NNNAddress> name);

      /**
       * \brief Another variant to set old 3N name
       *
       * @param name const reference to NNNAddress object
       *
       **/
      void
      SetNewName (const NNNAddress &name);

      Time
      GetRemainLease () const;

      void
      SetRemainLease (Time ex_lease);

      /**
       * @brief Print INF in plain-text to the specified output stream
       */
      void
      Print (std::ostream &os) const;

    private:
      // NO_ASSIGN
      INF &
      operator = (const INF &other) { return *this; }

    private:
      Ptr<NNNAddress> m_old_name;  ///< @brief Old 3N name used in the packet
      Ptr<NNNAddress> m_new_name;  ///< @brief New 3N name used in the packet
      Time m_re_lease;             ///< @brief PDU Remaining lease time
    };

    inline std::ostream &
    operator << (std::ostream &os, const INF &i)
    {
      i.Print (os);
      return os;
    }

    /**
     * @brief Class for Interest parsing exception
     */
    class INFException {};

  } // namespace nnn
} // namespace ns3

#endif // _NNN_INF_HEADER_H_
