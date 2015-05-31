/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-pit-entry-outgoing-face.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-pit-entry-outgoing-face.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-pit-entry-outgoing-face.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-pit-entry-outgoing-face.h"

#include "ns3/simulator.h"

namespace ns3
{
  namespace nnn
  {
    namespace pit
    {
      OutgoingFace::OutgoingFace (Ptr<Face> face)
      : m_face (face)
      , m_sendTime (Simulator::Now ())
      , m_retxCount (0)
      , m_waitingInVain (false)
      {
      }

      OutgoingFace::OutgoingFace ()
      : m_face (0)
      , m_sendTime (0)
      , m_retxCount (0)
      , m_waitingInVain (false)
      {
      }

      OutgoingFace &
      OutgoingFace::operator = (const OutgoingFace &other)
      {
	m_face = other.m_face;
	m_sendTime = other.m_sendTime;
	m_retxCount = other.m_retxCount;
	m_waitingInVain = other.m_waitingInVain;

	return *this;
      }

      void
      OutgoingFace::UpdateOnRetransmit ()
      {
	m_sendTime = Simulator::Now ();
	m_retxCount++;
	m_waitingInVain = false;
      }
    } // namespace pit
  } // namespace nnn
} // namespace ns3
