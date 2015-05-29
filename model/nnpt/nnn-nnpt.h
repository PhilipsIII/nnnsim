/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-nnpt.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-nnpt.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-nnpt.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Takahiro Miyamoto <mt3.mos@gmail.com>
 *          Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef NNN_NNPT_H_
#define NNN_NNPT_H_

#include "ns3/node.h"
#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/simulator.h"

#include <ostream>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

#include "nnn-nnpt-entry.h"
#include "../nnn-naming.h"

using boost::multi_index_container;
using namespace ::boost::multi_index;

namespace ns3
{
  namespace nnn
  {
    namespace nnpt
    {
      class Entry;
    }

    class NNPT : public Object
    {
    public:
      struct PtrNNNComp
      {
	bool operator () (const Ptr<const NNNAddress> &lhs , const Ptr<const NNNAddress>  &rhs) const  {
	  return *lhs < *rhs;
	}
      };

      struct oldname {};
      struct newname {};
      struct st_lease {};

      typedef multi_index_container<
      	nnpt::Entry,
      	indexed_by<
          ordered_unique<
            tag<st_lease>,
      	    identity<nnpt::Entry>
          >,

          ordered_unique<
            tag<oldname>,
            member<nnpt::Entry,Ptr<const NNNAddress>,&nnpt::Entry::m_oldName>,
            PtrNNNComp
          >,

          ordered_unique<
            tag<newname>,
            member<nnpt::Entry,Ptr<const NNNAddress>,&nnpt::Entry::m_newName>,
            PtrNNNComp
          >
        >
      > pair_set;

      typedef pair_set::index<oldname>::type pair_set_by_oldname;
      typedef pair_set::index<newname>::type pair_set_by_newname;
      typedef pair_set::index<st_lease>::type pair_set_by_lease;

      static TypeId GetTypeId ();

      NNPT();

      virtual
      ~NNPT();

      void
      addEntry (Ptr<const NNNAddress> oldName, Ptr<const NNNAddress> newName, Time lease_expire);

      void
      deleteEntry (Ptr<const NNNAddress> oldName);

      void
      deleteEntry (nnpt::Entry nnptEntry);

      void
      deleteEntry (Ptr<const NNNAddress> oldName, Ptr<const NNNAddress> newName);

      bool
      foundOldName (Ptr<const NNNAddress> name);

      bool
      foundNewName (Ptr<const NNNAddress> name);

      const NNNAddress&
      findPairedName (Ptr<const NNNAddress> oldName);

      const NNNAddress&
      findPairedOldName (Ptr<const NNNAddress> newName);

      Ptr<const NNNAddress>
      findPairedNamePtr (Ptr<const NNNAddress> oldName);

      Ptr<const NNNAddress>
      findPairedOldNamePtr (Ptr<const NNNAddress> newName);

      nnpt::Entry
      findEntry (Ptr<const NNNAddress> name);

      void
      updateLeaseTime (Ptr<const NNNAddress> oldName, Time lease_expire);

      uint32_t
      size ();

      bool
      isEmpty ();

      Time
      findNameExpireTime (Ptr<const NNNAddress> name);

      Time
      findNameExpireTime (nnpt::Entry nnptEntry);

      void
      cleanExpired ();

      void
      Print (std::ostream &os) const;

      void
      printByAddress ();

      void
      printByLease ();

      pair_set container;
    };

    std::ostream& operator<< (std::ostream& os, const NNPT &nnpt);

  } /* namespace nnn */
} /* namespace ns3 */

#endif /* NNN_NNPT_H_ */
