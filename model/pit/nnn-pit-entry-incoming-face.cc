/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-pit-entry-incoming-face.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-pit-entry-incoming-face.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-pit-entry-incoming-face.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/simulator.h"

#include "nnn-pit-entry-incoming-face.h"

#include "../naming/nnn-address.h"

namespace ns3
{
  namespace nnn
  {
    namespace pit
    {
      IncomingFace::IncomingFace (Ptr<Face> face)
      : m_face (face)
      , m_arrivalTime (Simulator::Now ())
      , m_addrs (Create<NNNAddrAggregator> ())
      // , m_nonce (nonce)
      {
      }

      IncomingFace::IncomingFace (Ptr<Face> face, Ptr<const NNNAddress> addr)
      : m_face (face)
      , m_arrivalTime (Simulator::Now ())
      , m_addrs (Create<NNNAddrAggregator> ())
      {
	m_addrs->AddDestination(addr);
      }

      IncomingFace::IncomingFace ()
      : m_face (0)
      , m_arrivalTime (0)
      , m_addrs (Create<NNNAddrAggregator> ())
      {
      }

      void
      IncomingFace::AddDestination(Ptr<const NNNAddress> addr)
      {
	m_addrs->AddDestination(addr);
      }

      void
      IncomingFace::RemoveDestination(Ptr<const NNNAddress> addr)
      {
	m_addrs->RemoveDestination(addr);
      }

      bool
      IncomingFace::NoAddresses()
      {
	return m_addrs->isEmpty();
      }

      /**
       * @brie Copy operator
       */
      IncomingFace &
      IncomingFace::operator = (const IncomingFace &other)
      {
	m_face = other.m_face;
	m_addrs = other.m_addrs;
	m_arrivalTime = other.m_arrivalTime;
	return *this;
      }
    } // namespace pit
  } // namespace nnn
} // namespace ns3
