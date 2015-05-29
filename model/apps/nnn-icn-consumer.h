/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-consumer.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-consumer.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-consumer.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */
#ifndef NNN_CONSUMER_H
#define NNN_CONSUMER_H

#include "ns3/data-rate.h"
#include "ns3/nstime.h"
#include "ns3/random-variable-stream.h"

#include <set>
#include <map>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

#include "../../utils/nnn-rtt-estimator.h"
#include "nnn-icn-app.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn-apps
     * \brief NNN application for sending out Interest packets
     */
    class Consumer: public ICNApp
    {
    public:
      static TypeId GetTypeId ();

      /**
       * \brief Default constructor
       * Sets up randomizer function and packet sequence number
       */
      Consumer ();
      virtual ~Consumer () {};

      // From App
      // virtual void
      // OnInterest (const Ptr<const Interest> &interest);

      virtual void
      Deencapsulate3N(Ptr<Packet> packet);

      virtual void
      OnNack (Ptr<const Interest> interest);

      virtual void
      OnData (Ptr<const Data> contentObject);

      virtual void
      OnNULLp (Ptr<const NULLp> nullpObject);

      virtual void
      OnSO (Ptr<const SO> soObject);

      virtual void
      OnDO (Ptr<const DO> doObject);

      virtual void
      OnDU (Ptr<const DU> duObject);

      /**
       * @brief Timeout event
       * @param sequenceNumber time outed sequence number
       */
      virtual void
      OnTimeout (uint32_t sequenceNumber);

      /**
       * @brief Actually send packet
       */
      void
      SendPacket ();

      /**
       * @brief An event that is fired just before an Interest packet is actually send out (send is inevitable)
       *
       * The reason for "before" even is that in certain cases (when it is possible to satisfy from the local cache),
       * the send call will immediately return data, and if "after" even was used, this after would be called after
       * all processing of incoming data, potentially producing unexpected results.
       */
      virtual void
      WillSendOutInterest (uint32_t sequenceNumber);

    protected:
      // from App
      virtual void
      StartApplication ();

      virtual void
      StopApplication ();

      /**
       * \brief Constructs the Interest packet and sends it using a callback to the underlying NDN protocol
       */
      virtual void
      ScheduleNextPacket () = 0;

      /**
       * \brief Checks if the packet need to be retransmitted becuase of retransmission timer expiration
       */
      void
      CheckRetxTimeout ();

      /**
       * \brief Modifies the frequency of checking the retransmission timeouts
       * \param retxTimer Timeout defining how frequent retransmission timeouts should be checked
       */
      void
      SetRetxTimer (Time retxTimer);

      /**
       * \brief Returns the frequency of checking the retransmission timeouts
       * \return Timeout defining how frequent retransmission timeouts should be checked
       */
      Time
      GetRetxTimer () const;

      typedef void (* LastRetransmittedInterestDataDelayTracedCallback)
	  (const Ptr<App>, const uint32_t, const Time, const int32_t);

      typedef void (* FirstInterestDataDelayTracedCallback)
	  (const Ptr<App>, const uint32_t, const Time, const uint32_t);

    protected:
      Ptr<UniformRandomVariable> m_rand; ///< @brief nonce generator

      uint32_t        m_seq;  ///< @brief currently requested sequence number
      uint32_t        m_seqMax;    ///< @brief maximum number of sequence number
      EventId         m_sendEvent; ///< @brief EventId of pending "send packet" event
      Time            m_retxTimer; ///< @brief Currently estimated retransmission timer
      EventId         m_retxEvent; ///< @brief Event to check whether or not retransmission should be performed

      Ptr<RttEstimator> m_rtt; ///< @brief RTT estimator
      Time                   m_offTime;             ///< \brief Time interval between packets
      icn::Name              m_interestName;        ///< \brief NDN Name of the Interest (use Name)
      Time                   m_interestLifeTime;    ///< \brief LifeTime for interest packet
      /// @cond include_hidden
      /**
       * \struct This struct contains sequence numbers of packets to be retransmitted
       */
      struct RetxSeqsContainer :
	  public std::set<uint32_t> { };

      RetxSeqsContainer m_retxSeqs;             ///< \brief ordered set of sequence numbers to be retransmitted

      /**
       * \struct This struct contains a pair of packet sequence number and its timeout
       */
      struct SeqTimeout
      {
	SeqTimeout (uint32_t _seq, Time _time) : seq (_seq), time (_time) { }

	uint32_t seq;
	Time time;
      };
      /// @endcond

      /// @cond include_hidden
      class i_seq { };
      class i_timestamp { };
      /// @endcond

      /// @cond include_hidden
      /**
       * \struct This struct contains a multi-index for the set of SeqTimeout structs
       */
      struct SeqTimeoutsContainer :
	  public boost::multi_index::multi_index_container<
	  SeqTimeout,
	  boost::multi_index::indexed_by<
	  boost::multi_index::ordered_unique<
	  boost::multi_index::tag<i_seq>,
	  boost::multi_index::member<SeqTimeout, uint32_t, &SeqTimeout::seq>
      >,
      boost::multi_index::ordered_non_unique<
      boost::multi_index::tag<i_timestamp>,
      boost::multi_index::member<SeqTimeout, Time, &SeqTimeout::time>
      >
      >
      > { } ;

      SeqTimeoutsContainer m_seqTimeouts;       ///< \brief multi-index for the set of SeqTimeout structs

      SeqTimeoutsContainer m_seqLastDelay;
      SeqTimeoutsContainer m_seqFullDelay;
      std::map<uint32_t, uint32_t> m_seqRetxCounts;

      TracedCallback<Ptr<App> /* app */, uint32_t /* seqno */,
      Time /* delay */, int32_t /*hop count*/> m_lastRetransmittedInterestDataDelay;
      TracedCallback<Ptr<App> /* app */, uint32_t /* seqno */,
      Time /* delay */, uint32_t /*retx count*/,
      int32_t /*hop count*/> m_firstInterestDataDelay;

      /// @endcond
    };
  } // namespace nnn
} // namespace ns3

#endif
