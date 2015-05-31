/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-content-store.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-content-store.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-content-store.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-icn-content-store.h"

#include "ns3/log.h"
#include "ns3/packet.h"

#include "ns3/nnn-icn-naming.h"
#include "ns3/nnn-icn-pdus.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.cs.ContentStore");

  namespace nnn
  {
    NS_OBJECT_ENSURE_REGISTERED (ContentStore);

    TypeId
    ContentStore::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::nnn::ContentStore")
	.SetGroupName ("Nnn")
	.SetParent<Object> ()

	.AddTraceSource ("CacheHits", "Trace called every time there is a cache hit",
			 MakeTraceSourceAccessor (&ContentStore::m_cacheHitsTrace),
			 "ns3::nnn::ContentStore::CacheHitTracedCallback")

	.AddTraceSource ("CacheMisses", "Trace called every time there is a cache miss",
			 MakeTraceSourceAccessor (&ContentStore::m_cacheMissesTrace),
			 "ns3::nnn::ContentStore::CacheMissTracedCallback")
	;

      return tid;
    }

    ContentStore::~ContentStore ()
    {
    }

    namespace cs {

      //////////////////////////////////////////////////////////////////////

      Entry::Entry (Ptr<ContentStore> cs, Ptr<const Data> data)
      : m_cs (cs)
      , m_data (data)
      {
      }

      const icn::Name&
      Entry::GetName () const
      {
	return m_data->GetName ();
      }

      Ptr<const Data>
      Entry::GetData () const
      {
	return m_data;
      }

      Ptr<ContentStore>
      Entry::GetContentStore ()
      {
	return m_cs;
      }


    } // namespace cs
  } // namespace nnn
} // namespace ns3
