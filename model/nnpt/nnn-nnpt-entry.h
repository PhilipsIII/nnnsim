/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-nnpt-entry.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-nnpt-entry.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-nnpt-entry.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef NNN_NNPT_ENTRY_H_
#define NNN_NNPT_ENTRY_H_

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/tag.hpp>

#include "ns3/ptr.h"
#include "ns3/simple-ref-count.h"
#include "ns3/nstime.h"
#include "ns3/traced-value.h"

#include "ns3/nnn-naming.h"
#include "ns3/nnn-face.h"
#include "ns3/nnn-trie.h"
#include "ns3/nnn-counting-policy.h"
#include "ns3/nnn-trie-with-policy.h"
#include "ns3/nnn-face-container.h"
#include "ns3/nnn-naming.h"

namespace ns3
{
  namespace nnn
  {
    namespace nnpt
    {
      /**
       * @ingroup nnn-nnpt
       * @brief structure for NNPT entry
       *
       * All set-methods are virtual, in case index rearrangement is necessary in the derived classes
       */
      class Entry :  public SimpleRefCount<Entry>
      {
      public:
	Entry ();

	Entry (Ptr<const NNNAddress> oldName, Ptr<const NNNAddress> newName, Time lease_expire);

	virtual
	~Entry ();

	bool
	operator< (const Entry e) const { return m_lease_expire < e.m_lease_expire; }

	Ptr<const NNNAddress> m_oldName;
	Ptr<const NNNAddress> m_newName;
	Time m_lease_expire;
      };

      inline std::ostream &
      operator<< (std::ostream &os, const Entry &nnpt)
      {
	os << *nnpt.m_oldName << "\t" << *nnpt.m_newName  << "\t" << nnpt.m_lease_expire << std::endl;
	return os;
      }
    }
  } /* namespace nnn */
} /* namespace ns3 */

#endif /* NNN_NNPT_ENTRY_H_ */
