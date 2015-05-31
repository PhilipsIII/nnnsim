/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-lifetime-stats-policy.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-lifetime-stats-policy.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-lifetime-stats-policy.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef PROBABILITY_POLICY_H_
#define PROBABILITY_POLICY_H_

#include <boost/intrusive/options.hpp>
#include <boost/intrusive/list.hpp>

#include "ns3/random-variable-stream.h"

namespace ns3
{
  namespace nnn
  {
    namespace nnnSIM
    {
      /**
       * @brief Traits for freshness policy
       */
      struct probability_policy_traits
      {
	static std::string GetName () { return "ProbabilityImpl"; }

	struct policy_hook_type : public boost::intrusive::list_member_hook<> {};

	template<class Container>
	struct container_hook
	{
	  typedef boost::intrusive::member_hook< Container,
	      policy_hook_type,
	      &Container::policy_hook_ > type;
	};

	template<class Base,
	class Container,
	class Hook>
	struct policy
	{
	  typedef typename boost::intrusive::list< Container, Hook > policy_container;

	  class type : public policy_container
	  {
	  public:
	    typedef policy policy_base; // to get access to get_freshness methods from outside
	    typedef Container parent_trie;

	    type (Base &base)
	    : base_ (base)
	    , max_size_ (100)
	    , probability_ (1.0)
	    {
	    }

	    inline void
	    update (typename parent_trie::iterator item)
	    {
	    }

	    inline bool
	    insert (typename parent_trie::iterator item)
	    {
	      if (ns3_rand_->GetValue (0.0, 1.0) < probability_)
		{
		  policy_container::push_back (*item);

		  // allow caching
		  return true;
		}
	      else
		{
		  // don't allow caching
		  return false;
		}
	    }

	    inline void
	    lookup (typename parent_trie::iterator item)
	    {
	      // do nothing. it's random policy
	    }

	    inline void
	    erase (typename parent_trie::iterator item)
	    {
	      policy_container::erase (policy_container::s_iterator_to (*item));
	    }

	    inline void
	    clear ()
	    {
	      policy_container::clear ();
	    }

	    inline void
	    set_max_size (size_t max_size)
	    {
	      max_size_ = max_size;
	    }

	    inline size_t
	    get_max_size () const
	    {
	      return max_size_;
	    }

	    inline void
	    set_probability (double probability)
	    {
	      probability_ = probability;
	    }

	    inline double
	    get_probability () const
	    {
	      return probability_;
	    }

	  private:
	    type () : base_(*((Base*)0)) { };

	  private:
	    Base &base_;
	    size_t max_size_;
	    double probability_;
	    Ptr<UniformRandomVariable> ns3_rand_;
	  };
	};
      };

    } // nnnSIM
  } // nnn
} // ns3

#endif // PROBABILITY_POLICY_H
