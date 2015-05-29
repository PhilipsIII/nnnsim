/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-app.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-app.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-app.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef NNN_APP_H
#define NNN_APP_H

#include "ns3/type-id.h"
#include "ns3/application.h"
#include "ns3/callback.h"
#include "ns3/traced-callback.h"
#include "ns3/ptr.h"

namespace ns3
{
  class Packet;

  namespace nnn
  {
    class NULLp;
    class SO;
    class DO;
    class DU;

    class Face;

    class NNNAddress;

    /**
     * \ingroup nnn
     * \defgroup nnn-apps 3N applications
     */
    /**
     * @ingroup nnn-apps
     * @brief Base class that all 3N applications should be derived from.
     *
     * The class implements virtual calls OnNULLp, OnSO, OnDO and OnDU
     */
    class App: public Application
    {
    public:
      static TypeId GetTypeId ();

      /**
       * @brief Default constructor
       */
      App ();
      virtual ~App ();

      /**
       * @brief Get application ID (ID of applications face)
       */
      uint32_t
      GetId () const;

      virtual void
      OnNULLp (Ptr<const NULLp> nullpObject);

      virtual void
      OnSO (Ptr<const SO> soObject);

      virtual void
      OnDO (Ptr<const DO> doObject);

      virtual void
      OnDU (Ptr<const DU> duObject);

      virtual void
      GotName ();

      virtual void
      NoName ();

      // typedefs for callbacks
      typedef void (* ReceivedNULLpTracedCallback)
	  (const Ptr<const NULLp>, const Ptr<App>, const Ptr<Face>);

      typedef void (* ReceivedSOTracedCallback)
	  (const Ptr<const SO>, const Ptr<App>, const Ptr<Face>);

      typedef void (* ReceivedDOTracedCallback)
	  (const Ptr<const DO>, const Ptr<App>, const Ptr<Face>);

      typedef void (* ReceivedDUTracedCallback)
	  (const Ptr<const DU>, const Ptr<App>, const Ptr<Face>);

      typedef void (* TransmittedNULLpTracedCallback)
	  (const Ptr<const NULLp>, const Ptr<App>, const Ptr<Face>);

      typedef void (* TransmittedSOTracedCallback)
     	  (const Ptr<const SO>, const Ptr<App>, const Ptr<Face>);

      typedef void (* TransmittedDOTracedCallback)
     	  (const Ptr<const DO>, const Ptr<App>, const Ptr<Face>);

      typedef void (* TransmittedDUTracedCallback)
     	  (const Ptr<const DU>, const Ptr<App>, const Ptr<Face>);

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
      bool m_active;  ///< @brief Flag to indicate that application is active (set by StartApplication and StopApplication)
      Ptr<Face> m_face;   ///< @brief automatically created application face through which application communicates
      Time m_3n_lifetime; ///< @brief Lifetime for 3N packets

      bool m_has3Nname; ///< @brief Flag to indicate that the underlying layer has a 3N name
      Ptr<const NNNAddress> m_current3Nname; ///< Keeps the current 3N name able to be used by the App
      bool m_isMobile; ///< @brief Flag to indicate that the App is of mobile type
      Ptr<const NNNAddress> m_possibleDestination; ///< @brief Keeps the possible destination 3N name

      TracedCallback<Ptr<const NULLp>,
      Ptr<App>, Ptr<Face> > m_receivedNULLps; ///< @brief App-level trace of received NULLp

      TracedCallback<Ptr<const SO>,
      Ptr<App>, Ptr<Face> > m_receivedSOs; ///< @brief App-level trace of received SO

      TracedCallback<Ptr<const DO>,
      Ptr<App>, Ptr<Face> > m_receivedDOs; ///< @brief App-level trace of received DO

      TracedCallback<Ptr<const DU>,
      Ptr<App>, Ptr<Face> > m_receivedDUs; ///< @brief App-level trace of received DU

      TracedCallback<Ptr<const NULLp>,
      Ptr<App>, Ptr<Face> > m_transmittedNULLps; ///< @brief App-level trace of transmitted SO

      TracedCallback<Ptr<const SO>,
      Ptr<App>, Ptr<Face> > m_transmittedSOs; ///< @brief App-level trace of transmitted SO

      TracedCallback<Ptr<const DO>,
      Ptr<App>, Ptr<Face> > m_transmittedDOs; ///< @brief App-level trace of transmitted DO

      TracedCallback<Ptr<const DU>,
      Ptr<App>, Ptr<Face> > m_transmittedDUs; ///< @brief App-level trace of transmitted DU
    };
  } // namespace nnn
} // namespace ns3

#endif // NNN_APP_H
