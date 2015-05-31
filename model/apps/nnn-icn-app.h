/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-app.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-app.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-app.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef NNN_ICN_APP_H
#define NNN_ICN_APP_H

#include "ns3/nnn-app.h"

#include "ns3/nnn-icn-name.h"
#include "ns3/nnn-icn-pdus.h"
#include "ns3/nnn-icn-wire.h"
#include "ns3/wire-nnnsim-icn.h"

namespace ns3
{
  class Packet;

  namespace nnn
  {
    class Data;
    class Interest;

    /**
     * \ingroup nnn
     * \defgroup nnn-icn-apps ICN applications
     */
    /**
     * @ingroup nnn-apps
     * @brief Base class that all ICN applications should be derived from.
     *
     * The class implements virtual calls onInterest, onNack, and onData
     */
    class ICNApp: public virtual App
    {
    public:
      static TypeId GetTypeId ();

      /**
       * @brief Default constructor
       */
      ICNApp ();
      virtual ~ICNApp ();

      /**
       * @brief Method that will be called every time new Interest arrives
       * @param interest Interest header
       * @param packet   "Payload" of the interests packet. The actual payload should be zero, but packet itself
       *                 may be useful to get packet tags
       */
      virtual void
      OnInterest (Ptr<const Interest> interest);

      /**
       * @brief Method that will be called every time new NACK arrives
       * @param interest Interest header
       */
      virtual void
      OnNack (Ptr<const Interest> interest);

      /**
       * @brief Method that will be called every time new Data arrives
       * @param contentObject Data header
       * @param payload payload (potentially virtual) of the Data packet (may include packet tags of original packet)
       */
      virtual void
      OnData (Ptr<const Data> contentObject);

      typedef void (* ReceivedInterestTracedCallback)
	  (const Ptr<const Interest>, const Ptr<App>, const Ptr<Face>);

      typedef void (* ReceivedNackTracedCallback)
	  (const Ptr<const Interest>, const Ptr<App>, const Ptr<Face>);

      typedef void (* ReceivedDataTracedCallback)
	  (const Ptr<const Data>, const Ptr<App>, const Ptr<Face>);

      typedef void (* TransmittedInterestTracedCallback)
	  (const Ptr<const Interest>, const Ptr<App>, const Ptr<Face>);

      typedef void (* TransmittedDataTracedCallback)
	  (const Ptr<const Data>, const Ptr<App>, const Ptr<Face>);

    protected:
      /**
       * @brief Do cleanup when application is destroyed
       */
      virtual void
      DoDispose ();

      // inherited from Application base class. Originally they were private
      virtual void
      StartApplication ();    ///< @brief Called at time specified by Start

      virtual void
      StopApplication ();     ///< @brief Called at time specified by Stop

    protected:
      TracedCallback<Ptr<const Interest>,
      Ptr<App>, Ptr<Face> > m_receivedInterests; ///< @brief App-level trace of received Interests

      TracedCallback<Ptr<const Interest>,
      Ptr<App>, Ptr<Face> > m_receivedNacks; ///< @brief App-level trace of received NACKs

      TracedCallback<Ptr<const Data>,
      Ptr<App>, Ptr<Face> > m_receivedDatas; ///< @brief App-level trace of received Data

      TracedCallback<Ptr<const Interest>,
      Ptr<App>, Ptr<Face> > m_transmittedInterests; ///< @brief App-level trace of transmitted Interests

      TracedCallback<Ptr<const Data>,
      Ptr<App>, Ptr<Face> > m_transmittedDatas; ///< @brief App-level trace of transmitted Data
    };
  } // namespace nnn
} // namespace ns3

#endif // NNN_APP_H
