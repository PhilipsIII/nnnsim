/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  content-store-nocache.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  content-store-nocache.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with content-store-nocache.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *  Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "content-store-nocache.h"

#include "ns3/log.h"
#include "ns3/packet.h"

#include "../naming/nnn-icn-name.h"
#include "../naming/nnn-icn-exclude.h"
#include "../nnn-icn-pdus.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.cs.Nocache");

  namespace nnn
  {
    namespace cs
    {
      NS_OBJECT_ENSURE_REGISTERED (Nocache);

      TypeId
      Nocache::GetTypeId (void)
      {
	static TypeId tid = TypeId ("ns3::nnn::cs::Nocache")
	.SetGroupName ("Nnn")
	.SetParent<ContentStore> ()
	.AddConstructor< Nocache > ()
	;

	return tid;
      }

      Nocache::Nocache ()
      {
      }

      Nocache::~Nocache ()
      {
      }

      Ptr<Data>
      Nocache::Lookup (Ptr<const Interest> interest)
      {
	this->m_cacheMissesTrace (interest);
	return 0;
      }

      bool
      Nocache::Add (Ptr<const Data> data)
      {
	return false;
      }

      void
      Nocache::Print (std::ostream &os) const
      {
      }

      uint32_t
      Nocache::GetSize () const
      {
	return 0;
      }

      Ptr<cs::Entry>
      Nocache::Begin ()
      {
	return 0;
      }

      Ptr<cs::Entry>
      Nocache::End ()
      {
	return 0;
      }

      Ptr<cs::Entry>
      Nocache::Next (Ptr<cs::Entry>)
      {
	return 0;
      }
    } // namespace cs
  } // namespace nnn
} // namespace ns3
