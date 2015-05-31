/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  nnn-content-store-with-probability.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-content-store-with-probability.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-content-store-with-probability.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *  Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-content-store-with-probability.h"

#include "ns3/nnn-random-policy.h"
#include "ns3/nnn-lru-policy.h"
#include "ns3/nnn-fifo-policy.h"
#include "ns3/nnn-lfu-policy.h"

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
      template class ContentStoreWithProbability<lru_policy_traits>;

      /**
       * @brief ContentStore with freshness and random cache replacement policy
       **/
      template class ContentStoreWithProbability<random_policy_traits>;

      /**
       * @brief ContentStore with freshness and FIFO cache replacement policy
       **/
      template class ContentStoreWithProbability<fifo_policy_traits>;

      /**
       * @brief ContentStore with freshness and Least Frequently Used (LFU) cache replacement policy
       **/
      template class ContentStoreWithProbability<lfu_policy_traits>;


      NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithProbability, lru_policy_traits);
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithProbability, random_policy_traits);
      NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithProbability, fifo_policy_traits);

      NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithProbability, lfu_policy_traits);

#ifdef DOXYGEN
      // /**
      //  * \brief Content Store with freshness implementing LRU cache replacement policy
      //  */
      class Probability::Lru : public ContentStoreWithProbability<lru_policy_traits> { };

      /**
       * \brief Content Store with freshness implementing FIFO cache replacement policy
       */
      class Probability::Fifo : public ContentStoreWithProbability<fifo_policy_traits> { };

      /**
       * \brief Content Store with freshness implementing Random cache replacement policy
       */
      class Probability::Random : public ContentStoreWithProbability<random_policy_traits> { };

      /**
       * \brief Content Store with freshness implementing Least Frequently Used cache replacement policy
       */
      class Probability::Lfu : public ContentStoreWithProbability<lfu_policy_traits> { };

#endif


    } // namespace cs
  } // namespace nnn
} // namespace ns3
