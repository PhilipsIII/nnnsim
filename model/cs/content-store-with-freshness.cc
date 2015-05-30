/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  content-store-with-freshness.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  content-store-with-freshness.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with content-store-with-freshness.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *  Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "content-store-with-freshness.h"

#include "../../utils/trie/random-policy.h"
#include "../../utils/trie/lru-policy.h"
#include "../../utils/trie/fifo-policy.h"
#include "../../utils/trie/lfu-policy.h"

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
    using namespace nnnSIM;

    namespace cs
    {
      // explicit instantiation and registering
      /**
       * @brief ContentStore with freshness and LRU cache replacement policy
       **/
      template class ContentStoreWithFreshness<lru_policy_traits>;

      /**
       * @brief ContentStore with freshness and random cache replacement policy
       **/
      template class ContentStoreWithFreshness<random_policy_traits>;

      /**
       * @brief ContentStore with freshness and FIFO cache replacement policy
       **/
      template class ContentStoreWithFreshness<fifo_policy_traits>;

      /**
       * @brief ContentStore with freshness and Least Frequently Used (LFU) cache replacement policy
       **/
      template class ContentStoreWithFreshness<lfu_policy_traits>;

      NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithFreshness, lru_policy_traits);
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithFreshness, random_policy_traits);
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithFreshness, fifo_policy_traits);

      NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithFreshness, lfu_policy_traits);

#ifdef DOXYGEN
      // /**
      //  * \brief Content Store with freshness implementing LRU cache replacement policy
      //  */
      class Freshness::Lru : public ContentStoreWithFreshness<lru_policy_traits> { };

      /**
       * \brief Content Store with freshness implementing FIFO cache replacement policy
       */
      class Freshness::Fifo : public ContentStoreWithFreshness<fifo_policy_traits> { };

      /**
       * \brief Content Store with freshness implementing Random cache replacement policy
       */
      class Freshness::Random : public ContentStoreWithFreshness<random_policy_traits> { };

      /**
       * \brief Content Store with freshness implementing Least Frequently Used cache replacement policy
       */
      class Freshness::Lfu : public ContentStoreWithFreshness<lfu_policy_traits> { };

#endif

    } // namespace cs
  } // namespace nnn
} // namespace ns3
