/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  content-store-with-stats.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  content-store-with-stats.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with content-store-with-stats.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *  Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef ICN_CONTENT_STORE_WITH_STATS_H_
#define ICN_CONTENT_STORE_WITH_STATS_H_

#include "content-store-impl.h"

#include "../../utils/trie/multi-policy.h"
#include "custom-policies/lifetime-stats-policy.h"

namespace ns3
{
  namespace nnn
  {
    namespace cs
    {

      /**
       * @ingroup nnn-cs
       * @brief Special content store realization that provides ability to track stats of CS operations
       */
      template<class Policy>
      class ContentStoreWithStats :
	  public ContentStoreImpl< nnnSIM::multi_policy_traits< boost::mpl::vector2< Policy, nnnSIM::lifetime_stats_policy_traits > > >
      {
      public:
	typedef ContentStoreImpl< nnnSIM::multi_policy_traits< boost::mpl::vector2< Policy, nnnSIM::lifetime_stats_policy_traits > > > super;

	typedef typename super::policy_container::template index<1>::type lifetime_stats_container;

	ContentStoreWithStats ()
	{
	  // connect traceback to the policy
	  super::getPolicy ().template get<1> ().set_traced_callback (&m_willRemoveEntry);
	}

	static TypeId
	GetTypeId ();

	virtual inline void
	Print (std::ostream &os) const;

	typedef void (* WillRemoveEntryTracedCallback)
	    (const Ptr<const Entry>, const Time);

      private:
	static LogComponent g_log; ///< @brief Logging variable

	/// @brief trace of for entry removal: first parameter is pointer to the CS entry, second is how long entry was in the cache
	TracedCallback< Ptr<const Entry>, Time > m_willRemoveEntry;
      };

      //////////////////////////////////////////
      ////////// Implementation ////////////////
      //////////////////////////////////////////


      template<class Policy>
      LogComponent ContentStoreWithStats< Policy >::g_log = LogComponent (("nnn.cs.Stats." + Policy::GetName ()).c_str (), __FILE__);

      template<class Policy>
      TypeId
      ContentStoreWithStats< Policy >::GetTypeId ()
      {
	static TypeId tid = TypeId (("ns3::nnn::cs::Stats::"+Policy::GetName ()).c_str ())
	.SetGroupName ("Ndn")
	.SetParent<super> ()
	.template AddConstructor< ContentStoreWithStats< Policy > > ()

	.AddTraceSource ("WillRemoveEntry", "Trace called just before content store entry will be removed",
			 MakeTraceSourceAccessor (&ContentStoreWithStats< Policy >::m_willRemoveEntry),
			 ("ns3::nnn::cs::Stats::"+Policy::GetName ()+"::WillRemoveEntryTracedCallback").c_str ())

			 // trace stuff here
			 ;

	return tid;
      }

      template<class Policy>
      void
      ContentStoreWithStats< Policy >::Print (std::ostream &os) const
      {
	// const freshness_policy_container &freshness = this->getPolicy ().template get<freshness_policy_container> ();

	for (typename super::policy_container::const_iterator item = this->getPolicy ().begin ();
	    item != this->getPolicy ().end ();
	    item++)
	  {
	    Time alive = lifetime_stats_container::policy_base::get_time (&(*item)) - Simulator::Now ();
	    os << item->payload ()->GetName () << "(alive: " << alive.ToDouble (Time::S) << "s)" << std::endl;
	  }
      }
    } // namespace cs
  } // namespace nnn
} // namespace ns3

#endif // ICN_CONTENT_STORE_IMPL_H_
