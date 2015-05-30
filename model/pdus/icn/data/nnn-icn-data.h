/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011-2013 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-data.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-data.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-data.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Ilya Moiseenko <iliamo@cs.ucla.edu>
 *          Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *
 *   Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _ICN_CONTENT_OBJECT_HEADER_H_
#define _ICN_CONTENT_OBJECT_HEADER_H_

#include "ns3/simple-ref-count.h"
#include "ns3/nstime.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

#include "../../../naming/nnn-icn-name.h"
#include "../../../nnn-naming.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup ndn
     * @brief Data header
     */
    class Data : public SimpleRefCount<Data>
    {
    public:
      /**
       * @brief Constructor
       *
       * Creates a null header
       **/
      Data (Ptr<Packet> payload = Create<Packet> ());

      /**
       * @brief Copy constructor
       */
      Data (const Data &other);

      /**
       * \brief Set content object name
       *
       * Sets name of the content object
       **/
      void
      SetName (Ptr<icn::Name> name);

      /**
       * @brief Another, less efficient, variant of setting content object name
       *
       * Sets name of the content object
       */
      void
      SetName (const icn::Name &name);

      /**
       * @brief Get name of the content object
       */
      const icn::Name&
      GetName () const;

      /**
       * @brief Get smart pointer to the interest name (to avoid extra memory usage)
       */
      Ptr<const icn::Name>
      GetNamePtr () const;

      /**
       * @brief Set content object timestamp
       * @param timestamp timestamp
       */
      void
      SetTimestamp (const Time &timestamp);

      /**
       * @brief Get timestamp of the content object
       */
      Time
      GetTimestamp () const;

      /**
       * @brief Set freshness of the content object
       * @param freshness Freshness, 0s means infinity
       */
      void
      SetFreshness (const Time &freshness);

      /**
       * @brief Get freshness of the content object
       */
      Time
      GetFreshness () const;

      /**
       * @brief Set "fake" signature on the content object
       * @param signature  uint32_t number, simulating content object signature
       *
       * Values for the signature totally depend on the application
       */
      void
      SetSignature (uint32_t signature);

      /**
       * @brief Get "fake" signature of the content object
       *
       * Values for the signature totally depend on the application
       */
      uint32_t
      GetSignature () const;

      /**
       * @brief Set key locator
       * @param keyLocator name of the key
       */
      void
      SetKeyLocator (Ptr<icn::Name> keyLocator);

      /**
       * @brief Get key locator
       *
       * Note that only <KeyName> option for the key locator is supported
       */
      Ptr<const icn::Name>
      GetKeyLocator () const;

      //////////////////////////////////////////////////////////////////
      /**
       * @brief Get payload of data packet
       *
       * This payload can also carry packet tags
       */
      void
      SetPayload (Ptr<Packet> payload);

      /**
       * @brief Set payload of data packet
       *
       * This payload can also carry packet tags
       */
      Ptr<const Packet>
      GetPayload () const;

      /**
       * @brief Get wire formatted packet
       *
       * If wire formatted packet has not been set before, 0 will be returned
       */
      inline Ptr<const Packet>
      GetWire () const;

      /**
       * @brief Set (cache) wire formatted packet
       */
      inline void
      SetWire (Ptr<const Packet> packet) const;

      /**
       * @brief Print Interest in plain-text to the specified output stream
       */
      void
      Print (std::ostream &os) const;

    private:
      // NO_ASSIGN
      Data &
      operator = (const Data &other) { return *this; }

    private:
      Ptr<icn::Name> m_name;
      Time m_freshness;
      Time m_timestamp;
      uint32_t m_signature; // 0, means no signature, any other value application dependent (not a real signature)
      Ptr<Packet> m_payload;
      Ptr<icn::Name> m_keyLocator;

      mutable Ptr<const Packet> m_wire;
    };

    inline std::ostream &
    operator << (std::ostream &os, const Data &d)
    {
      d.Print (os);
      return os;
    }

    /**
     * @brief Class for Data parsing exception
     */
    class DataException {};

    inline Ptr<const Packet>
    Data::GetWire () const
    {
      return m_wire;
    }

    inline void
    Data::SetWire (Ptr<const Packet> packet) const
    {
      m_wire = packet;
    }
  } // namespace nnn
} // namespace ns3

#endif // _ICN_CONTENT_OBJECT_HEADER_H_
