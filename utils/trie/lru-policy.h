/* -*-  Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2012 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 * Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef LRU_POLICY_H_
#define LRU_POLICY_H_

#include <boost/intrusive/options.hpp>
#include <boost/intrusive/list.hpp>

namespace ns3
{
  namespace nnn
  {
    namespace nnnSIM
    {
      /**
       * @brief Traits for Least Recently Used replacement policy
       */
      struct lru_policy_traits
      {
	/// @brief Name that can be used to identify the policy (for NS-3 object model and logging)
	static std::string GetName () { return "Lru"; }

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

	  // could be just typedef
	      class type : public policy_container
	      {
	      public:
	    typedef Container parent_trie;

	    type (Base &base)
	    : base_ (base)
	    , max_size_ (100)
	    {
	    }

	    inline void
	    update (typename parent_trie::iterator item)
	    {
	      // do relocation
	      policy_container::splice (policy_container::end (),
					*this,
					policy_container::s_iterator_to (*item));
	    }

	    inline bool
	    insert (typename parent_trie::iterator item)
	    {
	      if (max_size_ != 0 && policy_container::size () >= max_size_)
		{
		  base_.erase (&(*policy_container::begin ()));
		}

	      policy_container::push_back (*item);
	      return true;
	    }

	    inline void
	    lookup (typename parent_trie::iterator item)
	    {
	      // do relocation
	      policy_container::splice (policy_container::end (),
					*this,
					policy_container::s_iterator_to (*item));
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

	      private:
	    type () : base_(*((Base*)0)) { };

	      private:
	    Base &base_;
	    size_t max_size_;
	      };
	};
      };
    } // nnnSIM
  } // nnn
} // ns3

#endif
