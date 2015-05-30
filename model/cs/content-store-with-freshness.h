/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  content-store-with-freshness.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  content-store-with-freshness.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with content-store-with-freshness.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *  Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef ICN_CONTENT_STORE_WITH_FRESHNESS_H_
#define ICN_CONTENT_STORE_WITH_FRESHNESS_H_

#include "content-store-impl.h"

#include "../../utils/trie/multi-policy.h"
#include "custom-policies/freshness-policy.h"

namespace ns3
{
  namespace nnn
  {
    namespace cs
    {
      /**
       * @ingroup icn-cs
       * @brief Special content store realization that honors Freshness parameter in Data packets
       */
      template<class Policy>
      class ContentStoreWithFreshness :
	  public ContentStoreImpl< nnnSIM::multi_policy_traits< boost::mpl::vector2< Policy, nnnSIM::freshness_policy_traits > > >
      {
      public:
	typedef ContentStoreImpl< nnnSIM::multi_policy_traits< boost::mpl::vector2< Policy, nnnSIM::freshness_policy_traits > > > super;

	typedef typename super::policy_container::template index<1>::type freshness_policy_container;

	static TypeId
	GetTypeId ();

	virtual inline void
	Print (std::ostream &os) const;

	virtual inline bool
	Add (Ptr<const Data> data);

      private:
	inline void
	CleanExpired ();

	inline void
	RescheduleCleaning ();

      private:
	static LogComponent g_log; ///< @brief Logging variable

	EventId m_cleanEvent;
	Time m_scheduledCleaningTime;
      };

      //////////////////////////////////////////
      ////////// Implementation ////////////////
      //////////////////////////////////////////


      template<class Policy>
      LogComponent
      ContentStoreWithFreshness< Policy >::g_log = LogComponent (("nnn.cs.Freshness." + Policy::GetName ()).c_str (), __FILE__);


      template<class Policy>
      TypeId
      ContentStoreWithFreshness< Policy >::GetTypeId ()
      {
	static TypeId tid = TypeId (("ns3::nnn::cs::Freshness::"+Policy::GetName ()).c_str ())
	.SetGroupName ("Nnn")
	.SetParent<super> ()
	.template AddConstructor< ContentStoreWithFreshness< Policy > > ()

	// trace stuff here
	;

	return tid;
      }


      template<class Policy>
      inline bool
      ContentStoreWithFreshness< Policy >::Add (Ptr<const Data> data)
      {
	bool ok = super::Add (data);
	if (!ok) return false;

	NS_LOG_DEBUG (data->GetName () << " added to cache");
	RescheduleCleaning ();
	return true;
      }

      template<class Policy>
      inline void
      ContentStoreWithFreshness< Policy >::RescheduleCleaning ()
      {
	const freshness_policy_container &freshness = this->getPolicy ().template get<freshness_policy_container> ();

	if (freshness.size () > 0)
	  {
	    Time nextStateTime = freshness_policy_container::policy_base::get_freshness (&(*freshness.begin ()));

	    if (m_scheduledCleaningTime.IsZero () || // if not yet scheduled
		m_scheduledCleaningTime > nextStateTime) // if new item expire sooner than already scheduled
	      {
		if (m_cleanEvent.IsRunning ())
		  {
		    Simulator::Remove (m_cleanEvent); // just canceling would not clean up list of events
		  }

		// NS_LOG_DEBUG ("Next event in: " << (nextStateTime - Now ()).ToDouble (Time::S) << "s");
		m_cleanEvent = Simulator::Schedule (nextStateTime - Now (), &ContentStoreWithFreshness< Policy >::CleanExpired, this);
		m_scheduledCleaningTime = nextStateTime;
	      }
	  }
	else
	  {
	    if (m_cleanEvent.IsRunning ())
	      {
		Simulator::Remove (m_cleanEvent); // just canceling would not clean up list of events
	      }
	  }
      }


      template<class Policy>
      inline void
      ContentStoreWithFreshness< Policy >::CleanExpired ()
      {
	freshness_policy_container &freshness = this->getPolicy ().template get<freshness_policy_container> ();

	// NS_LOG_LOGIC (">> Cleaning: Total number of items:" << this->getPolicy ().size () << ", items with freshness: " << freshness.size ());
	Time now = Simulator::Now ();

	while (!freshness.empty ())
	  {
	    typename freshness_policy_container::iterator entry = freshness.begin ();

	    if (freshness_policy_container::policy_base::get_freshness (&(*entry)) <= now) // is the record stale?
	      {
		super::erase (&(*entry));
	      }
	    else
	      break; // nothing else to do. All later records will not be stale
	  }
	// NS_LOG_LOGIC ("<< Cleaning: Total number of items:" << this->getPolicy ().size () << ", items with freshness: " << freshness.size ());

	m_scheduledCleaningTime = Time ();
	RescheduleCleaning ();
      }

      template<class Policy>
      void
      ContentStoreWithFreshness< Policy >::Print (std::ostream &os) const
      {
	// const freshness_policy_container &freshness = this->getPolicy ().template get<freshness_policy_container> ();

	for (typename super::policy_container::const_iterator item = this->getPolicy ().begin ();
	    item != this->getPolicy ().end ();
	    item++)
	  {
	    Time ttl = freshness_policy_container::policy_base::get_freshness (&(*item)) - Simulator::Now ();
	    os << item->payload ()->GetName () << "(left: " << ttl.ToDouble (Time::S) << "s)" << std::endl;
	  }
      }
    } // namespace cs
  } // namespace nnn
} // namespace ns3

#endif // ICN_CONTENT_STORE_WITH_FRESHNESS_H_
