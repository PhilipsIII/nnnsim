/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-pit-impl.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-pit-impl.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-pit-impl.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-pit-impl.h"

#include "../../utils/trie/nnn-empty-policy.h"
#include "../../utils/trie/nnn-persistent-policy.h"
#include "../../utils/trie/nnn-random-policy.h"
#include "../../utils/trie/nnn-lru-policy.h"
#include "../../utils/trie/nnn-multi-policy.h"
#include "../../utils/trie/nnn-aggregate-stats-policy.h"

#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE ("nnn.pit.PitImpl");

#include "custom-policies/nnn-serialized-size-policy.h"

#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "ns3/string.h"
#include "ns3/uinteger.h"
#include "ns3/simulator.h"

using namespace boost::tuples;
using namespace boost;
namespace ll = boost::lambda;

#define NS_OBJECT_ENSURE_REGISTERED_TEMPL(type, templ)  \
    static struct X ## type ## templ ## RegistrationClass \
    {                                                     \
  X ## type ## templ ## RegistrationClass () {        \
      ns3::TypeId tid = type<templ>::GetTypeId ();      \
      tid.GetParent ();                                 \
    }                                                   \
    } x_ ## type ## templ ## RegistrationVariable

namespace ns3
{
  namespace nnn
  {
    namespace pit
    {
      template<>
      uint32_t
      PitImpl<serialized_size_policy_traits>::GetCurrentSize () const
      {
	return super::getPolicy ().get_current_space_used ();
      }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

      // explicit instantiation and registering
      template class PitImpl<nnn::nnnSIM::persistent_policy_traits>;
      template class PitImpl<nnn::nnnSIM::random_policy_traits>;
      template class PitImpl<nnn::nnnSIM::lru_policy_traits>;
      template class PitImpl<nnn::nnnSIM::serialized_size_policy_traits>;

      typedef nnn::nnnSIM::persistent_policy_traits ppt;
      typedef nnn::nnnSIM::random_policy_traits rpt;
      typedef nnn::nnnSIM::lru_policy_traits lpt;
      typedef nnn::nnnSIM::serialized_size_policy_traits sspt;

      NS_OBJECT_ENSURE_REGISTERED_TEMPL(PitImpl, ppt);
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(PitImpl, rpt);
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(PitImpl, lpt);
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(PitImpl, sspt);

      typedef nnn::nnnSIM::multi_policy_traits< boost::mpl::vector2< nnn::nnnSIM::persistent_policy_traits,
	  nnn::nnnSIM::aggregate_stats_policy_traits > > PersistentWithCountsTraits;
      typedef nnn::nnnSIM::multi_policy_traits< boost::mpl::vector2< nnn::nnnSIM::random_policy_traits,
	  nnn::nnnSIM::aggregate_stats_policy_traits > > RandomWithCountsTraits;
      typedef nnn::nnnSIM::multi_policy_traits< boost::mpl::vector2< nnn::nnnSIM::lru_policy_traits,
	  nnn::nnnSIM::aggregate_stats_policy_traits > > LruWithCountsTraits;
      typedef nnn::nnnSIM::multi_policy_traits< boost::mpl::vector2< nnn::nnnSIM::serialized_size_policy_traits,
	  nnn::nnnSIM::aggregate_stats_policy_traits > > SerializedSizeWithCountsTraits;

      template class PitImpl<PersistentWithCountsTraits>;
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(PitImpl, PersistentWithCountsTraits);

      template class PitImpl<RandomWithCountsTraits>;
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(PitImpl, RandomWithCountsTraits);

      template class PitImpl<LruWithCountsTraits>;
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(PitImpl, LruWithCountsTraits);

      template class PitImpl<SerializedSizeWithCountsTraits>;
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(PitImpl, SerializedSizeWithCountsTraits);

#ifdef DOXYGEN
// /**
//  * \brief PIT in which new entries will be rejected if PIT size reached its limit
      //  */
      class Persistent : public PitImpl<persistent_policy_traits> { };

      /**
       * \brief PIT in which PIT reaches its limit, random entry (could be the newly created one) will be removed from PIT
       */
      class Random : public PitImpl<random_policy_traits> { };

      /**
       * \brief PIT in which  the least recently used entry (the oldest entry with minimum number of incoming faces)
       * will be removed when PIT size reached its limit
       */
      class Lru : public PitImpl<lru_policy_traits> { };

      /**
       * @brief A variant of persistent PIT implementation where size of PIT is based on size of interests in bytes (MaxSize parameter)
       */
      class SerializedSize : public PitImpl<serialized_size_policy_traits> { };

#endif

    } // namespace pit
  } // namespace nnn
} // namespace ns3
