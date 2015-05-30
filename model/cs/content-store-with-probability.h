/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  content-store-with-probability.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  content-store-with-probability.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with content-store-with-probability.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *  Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef ICN_CONTENT_STORE_WITH_PROBABILITY_H_
#define ICN_CONTENT_STORE_WITH_PROBABILITY_H_

#include "content-store-impl.h"

#include "../../utils/trie/multi-policy.h"
#include "custom-policies/probability-policy.h"
#include <ns3-dev/ns3/double.h>
#include <ns3-dev/ns3/type-id.h>

namespace ns3 {
  namespace nnn {
    namespace cs {

      /**
       * @ingroup icn-cs
       * @brief Special content store realization that honors Freshness parameter in Data packets
       */
      template<class Policy>
      class ContentStoreWithProbability :
	  public ContentStoreImpl< nnnSIM::multi_policy_traits< boost::mpl::vector2< nnnSIM::probability_policy_traits, Policy > > >
      {
      public:
	typedef ContentStoreImpl< nnnSIM::multi_policy_traits< boost::mpl::vector2< nnnSIM::probability_policy_traits, Policy > > > super;

	typedef typename super::policy_container::template index<0>::type probability_policy_container;

	ContentStoreWithProbability () {};

	static TypeId
	GetTypeId ();
      private:

	void SetCacheProbability (double probability)
	{
	  this->getPolicy ()
	  .template get<probability_policy_container> ()
	  .set_probability (probability);
	}

	double
	GetCacheProbability () const
	{
	  return
	      this->getPolicy ()
	      .template get<probability_policy_container> ()
	      .get_probability ();
	}
      };

      //////////////////////////////////////////
      ////////// Implementation ////////////////
      //////////////////////////////////////////

      template<class Policy>
      TypeId
      ContentStoreWithProbability< Policy >::GetTypeId ()
      {
	static TypeId tid = TypeId (("ns3::nnn::cs::Probability::"+Policy::GetName ()).c_str ())
	.SetGroupName ("Nnn")
	.SetParent<super> ()
	.template AddConstructor< ContentStoreWithProbability< Policy > > ()

	.AddAttribute ("CacheProbability",
		       "Set probability of caching in ContentStore. "
		       "If 1, every content is cached. If 0, no content is cached.",
		       DoubleValue (1.0),//(+)
		       MakeDoubleAccessor (&ContentStoreWithProbability< Policy >::GetCacheProbability,
					   &ContentStoreWithProbability< Policy >::SetCacheProbability),
					   MakeDoubleChecker<double> ())
	;

	return tid;
      }
    } // namespace cs
  } // namespace nnn
} // namespace ns3

#endif // ICN_CONTENT_STORE_WITH_PROBABILITY_H_
