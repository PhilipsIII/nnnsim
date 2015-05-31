/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-pdu-buffer.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-pdu-buffer.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-pdu-buffer.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef PDU_BUFFER_H_
#define PDU_BUFFER_H_

#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/object.h"
#include "ns3/ptr.h"

#include "ns3/nnn-pdus.h"
#include "ns3/nnn-naming.h"
#include "ns3/nnn-trie.h"
#include "ns3/nnn-counting-policy.h"
#include "ns3/nnn-trie-with-policy.h"
#include "ns3/nnn-pdu-buffer-queue.h"

namespace ns3
{
  namespace nnn
  {
    class PDUBuffer : public Object,
    protected ns3::nnn::nnnSIM::trie_with_policy<
      NNNAddress,
      ns3::nnn::nnnSIM::smart_pointer_payload_traits<PDUQueue>,
      ns3::nnn::nnnSIM::counting_policy_traits
    >
    {
    public:
      typedef ns3::nnn::nnnSIM::trie_with_policy<
	  NNNAddress,
	  ns3::nnn::nnnSIM::smart_pointer_payload_traits<PDUQueue>,
	  ns3::nnn::nnnSIM::counting_policy_traits
      > super;

      static TypeId GetTypeId (void);

      PDUBuffer ();

      PDUBuffer (Time retx);

      virtual
      ~PDUBuffer ();

      void
      AddDestination (const NNNAddress &addr);

      void
      AddDestination (Ptr<NNNAddress> addr);

      void
      RemoveDestination (const NNNAddress &addr);

      void
      RemoveDestination (Ptr<NNNAddress> addr);

      bool
      DestinationExists (const NNNAddress &addr);

      bool
      DestinationExists (Ptr<NNNAddress> addr);

      void
      PushSO (const NNNAddress &addr, Ptr<const SO> so_p);

      void
      PushSO (Ptr<NNNAddress> addr, Ptr<const SO> so_p);

      void
      PushDO (const NNNAddress &addr, Ptr<const DO> do_p);

      void
      PushDO (Ptr<NNNAddress> addr, Ptr<const DO> do_p);

      void
      PushDU (const NNNAddress &addr, Ptr<const DU> du_p);

      void
      PushDU (Ptr<NNNAddress> addr, Ptr<const DU> du_p);

      std::queue<Ptr<Packet> >
      PopQueue (const NNNAddress &addr);

      std::queue<Ptr<Packet> >
      PopQueue (Ptr<NNNAddress> addr);

      uint
      QueueSize (const NNNAddress &addr);

      uint
      QueueSize (Ptr<NNNAddress> addr);

      void
      SetReTX (Time rtx);

      Time
      GetReTX () const;

    private:
      Time m_retx;
    };

    std::ostream& operator<< (std::ostream& os, const PDUBuffer &buffer);

  } /* namespace nnn */
} /* namespace ns3 */

#endif /* PDU_BUFFER_H_ */
