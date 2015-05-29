/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-pdu-buffer-queue.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-pdu-buffer-queue.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-pdu-buffer-queue.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef PDU_QUEUE_H_
#define PDU_QUEUE_H_

#include <queue>

#include "../nnn-nnnsim-wire.h"
#include "../nnn-pdus.h"

namespace ns3
{
  namespace nnn
  {
    class PDUQueue : public SimpleRefCount<PDUQueue>
    {
    public:
      PDUQueue ();
      virtual
      ~PDUQueue ();

      bool
      isEmpty();

      void
      clear ();

      Ptr<Packet>
      pop ();

      void
      push (Ptr<Packet> pdu, Time retx);

      void
      pushSO (Ptr<const SO> so_p, Time retx);

      void
      pushDO (Ptr<const DO> do_p, Time retx);

      void
      pushDU (Ptr<const DU> du_p, Time retx);

      std::queue<std::pair<Time, Ptr<Packet> > >
      popQueue ();

      uint
      size ();

    private:
      std::queue<std::pair<Time,Ptr<Packet> > > buffer;
    };
  } /* namespace nnn */
} /* namespace ns3 */

#endif /* PDU_QUEUE_H_ */
