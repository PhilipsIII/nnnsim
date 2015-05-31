/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-producer.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-producer.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-producer.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef NNN_PRODUCER_H
#define NNN_PRODUCER_H

#include "ns3/ptr.h"

#include "ns3/nnn-icn-app.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn-apps
     * @brief A simple Interest-sink application
     *
     * A simple Interest-sink application, which replying every incoming Interest with
     * Data PDU with a specified size and name same as in Interest.
     */
    class Producer : public ICNApp
    {
    public:
      static TypeId
      GetTypeId (void);

      Producer ();

      Ptr<Packet>
      CreateReturnData (Ptr<Interest> interest);

      // inherited from NnnApp
      void OnInterest (Ptr<const Interest> interest);

      // Essentially to de-encapsulate NULLp
      void OnNULLp (Ptr<const NULLp> nullpObject);

      // Essentially to de-encapsulate SO
      void OnSO (Ptr<const SO> soObject);

      // Essentially to de-encapsulate DO
      void OnDO (Ptr<const DO> doObject);

      // Essentially to de-encapsulate DU
      void OnDU (Ptr<const DU> duObject);

    protected:
      // inherited from Application base class.
      virtual void
      StartApplication ();    // Called at time specified by Start

      virtual void
      StopApplication ();     // Called at time specified by Stop

    private:
      icn::Name m_prefix;
      icn::Name m_postfix;
      uint32_t m_virtualPayloadSize;
      Time m_freshness;

      uint32_t m_signature;
      icn::Name m_keyLocator;
    };

  } // namespace nnn
} // namespace ns3

#endif // NNN_PRODUCER_H
