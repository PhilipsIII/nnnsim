/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-pdu.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-pdu.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-pdu.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/nstime.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "ns3/simple-ref-count.h"

#ifndef NNN_PACKET_H_
#define NNN_PACKET_H_

namespace ns3
{
  namespace nnn
  {
    /**
     * @brief enum for NNN PacketId for NNN Packets
     */
    enum NNN_PDU_TYPE { NULL_NNN = 0, SO_NNN, DO_NNN, DU_NNN, EN_NNN, OEN_NNN, AEN_NNN, REN_NNN, DEN_NNN, INF_NNN};

    /**
     * @brief enum for payload type the NNN data transmission packets are carrying
     */
    enum NNN_PDU_TRANS { ICN_NNN = 1 , NNN_NNN };

    /**
     * @brief enum for NNN version being used
     */
    enum NNN_VER { A_NNN = 0 };

    class NNNPDU : public SimpleRefCount<NNNPDU>
    {
    public:

      NNNPDU ();

      NNNPDU (uint32_t pkt_id, Time ttl);

      NNNPDU (uint32_t pkt_id, Time ttl, uint16_t ver);

      virtual
      ~NNNPDU ();

      /**
       * \brief Return Id of the packet
       *
       */
      inline uint32_t
      GetPacketId() const;

      /**
       * \brief Get the version of the packet
       */
      inline uint16_t
      GetVersion () const;

      /**
       * \brief Set the version of the packet
       * @param version Version number
       */
      inline void
      SetVersion (uint16_t version);

      /**
       * \brief Get time out value for NNN packets
       * Indicates the (approximate) time remaining before the packet times out.
       * The timeout is relative to the arrival time of the interest at the current node.
       * Based heavily on the NDN implementation for Interest Life time
       * \see http://www.ndn.org/releases/latest/doc/technical/InterestMessage.html for more information.
       */
      inline Time
      GetLifetime () const;

      /**
       * \brief Set time out for NNN packets
       * Indicates the (approximate) time remaining before the packet times out.
       * The timeout is relative to the arrival time of the interest at the current node.
       * Based heavily on the NDN implementation for Interest Life time
       * \see http://www.ndn.org/releases/latest/doc/technical/InterestMessage.html for more information.
       * @param[in] time interest lifetime
       */
      inline void
      SetLifetime (Time ttl);

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

      virtual void
      Print (std::ostream &os) const;

    protected:
      uint32_t m_packetid;              ///< @brief Packet Identifier
      Time m_ttl;                           ///< @brief Packet life time (TTL)
      uint16_t m_version;                   ///< @brief NNN Packet version
      mutable Ptr<const Packet> m_wire;
    };

    inline uint32_t
    NNNPDU::GetPacketId() const
    {
      return m_packetid;
    }

    inline uint16_t
    NNNPDU::GetVersion() const
    {
      return m_version;
    }

    inline void
    NNNPDU::SetVersion(uint16_t version)
    {
      m_version = version;
    }

    inline Time
    NNNPDU::GetLifetime () const
    {
      return m_ttl;
    }

    inline void
    NNNPDU::SetLifetime (Time ttl)
    {
      m_ttl = ttl;
      m_wire = 0;
    }

    inline Ptr<const Packet>
    NNNPDU::GetWire () const
    {
      return m_wire;
    }

    inline void
    NNNPDU::SetWire (Ptr<const Packet> packet) const
    {
      m_wire = packet;
    }
  } /* namespace nnn */
} /* namespace ns3 */

#endif /* NNN_PDUS_H_ */
