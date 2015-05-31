/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-names-container.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-names-container.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-names-container.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef NNN_NAMES_CONTAINER_H_
#define NNN_NAMES_CONTAINER_H_

#include <ostream>

#include "ns3/ptr.h"
#include "ns3/node.h"
#include "ns3/object.h"
#include "ns3/simulator.h"
#include "ns3/simple-ref-count.h"

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

#include "ns3/nnn-names-container-entry.h"
#include "ns3/nnn-naming.h"

using boost::multi_index_container;
using namespace ::boost::multi_index;

namespace ns3
{
  namespace nnn
  {
    class NamesContainer : public Object
    {
    public:
      struct PtrNNNComp
      {
	bool operator () (const Ptr<const NNNAddress> &lhs , const Ptr<const NNNAddress>  &rhs) const  {
	  return *lhs < *rhs;
	}
      };

      struct address {};
      struct lease {};

      typedef multi_index_container<
	  NamesContainerEntry,
	  indexed_by<// sort by NamesContainer::operator<
	    ordered_unique<
	      tag<lease>,
	      identity<NamesContainerEntry>
            >,

            ordered_unique<
              tag<address>,
              member<NamesContainerEntry,Ptr<const NNNAddress>,&NamesContainerEntry::m_name>,
              PtrNNNComp
            >
          >
      > names_set;

      typedef names_set::index<address>::type names_set_by_name;
      typedef names_set::index<lease>::type names_set_by_lease;

      NamesContainer();

      virtual
      ~NamesContainer();

      void
      RegisterCallbacks (const Callback<void> renewal, const Callback<void> leaseagain);

      void
      SetDefaultRenewal (Time renew);

      Time
      GetDefaultRenewal ();

      void
      addEntry (Ptr<const NNNAddress> name, Time lease_expire, bool fixed);

      void
      deleteEntry (NamesContainerEntry nameEntry);

      void
      deleteEntry (Ptr<const NNNAddress> name);

      bool
      foundName (Ptr<const NNNAddress> name);

      NamesContainerEntry
      findEntry (Ptr<const NNNAddress> name);

      Ptr<const NNNAddress>
      findNewestName ();

      void
      updateLeaseTime (Ptr<const NNNAddress> name, Time lease_expire);

      uint32_t
      size ();

      bool
      isEmpty ();

      bool
      isFixed (Ptr<const NNNAddress> name);

      bool
      hasFixedName ();

      Time
      findNameExpireTime (Ptr<const NNNAddress> name);

      void
      cleanExpired ();

      void
      clear ();

      void
      willAttemptRenew ();

      void
      Print (std::ostream &os) const;

      void
      printByAddress ();

      void
      printByLease ();

    private:
      names_set container;         ///< \brief Internal structure holding the 3N names
      Time defaultRenewal;         ///< \brief Default negative default time to fire renewal callback

      Callback<void> renewName;    ///< \brief Renewal callback
      Callback<void> hasNoName;    ///< \brief Enroll callback - done when container is empty
    };

    std::ostream& operator<< (std::ostream& os, const NamesContainer &names);

  } /* namespace nnn */
} /* namespace ns3 */

#endif /* NNN_NAMES_CONTAINER_H_ */
