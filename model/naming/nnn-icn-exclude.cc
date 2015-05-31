/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-exclude.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-exclude.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-exclude.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *   Initial implementation made by Alexander Afanasyev for the Regents of the
 *   University of California
 */

#include "nnn-icn-exclude.h"

#include "ns3/nnn-error.h"

ICN_NAMESPACE_BEGIN

Exclude::Exclude ()
{
}

// example: ANY /b /d ANY /f
//
// ordered in map as:
//
// /f (false); /d (true); /b (false); / (true)
//
// lower_bound (/)  -> / (true) <-- excluded (equal)
// lower_bound (/a) -> / (true) <-- excluded (any)
// lower_bound (/b) -> /b (false) <--- excluded (equal)
// lower_bound (/c) -> /b (false) <--- not excluded (not equal and no ANY)
// lower_bound (/d) -> /d (true) <- excluded
// lower_bound (/e) -> /d (true) <- excluded
bool
Exclude::isExcluded (const nnn::name::Component &comp) const
{
  const_iterator lowerBound = m_exclude.lower_bound (comp);
  if (lowerBound == end ())
    return false;

  if (lowerBound->second)
    return true;
  else
    return lowerBound->first == comp;

  return false;
}

Exclude &
Exclude::excludeOne (const nnn::name::Component &comp)
{
  if (!isExcluded (comp))
    {
      m_exclude.insert (std::make_pair (comp, false));
    }
  return *this;
}


// example: ANY /b0 /d0 ANY /f0
//
// ordered in map as:
//
// /f0 (false); /d0 (true); /b0 (false); / (true)
//
// lower_bound (/)  -> / (true) <-- excluded (equal)
// lower_bound (/a0) -> / (true) <-- excluded (any)
// lower_bound (/b0) -> /b0 (false) <--- excluded (equal)
// lower_bound (/c0) -> /b0 (false) <--- not excluded (not equal and no ANY)
// lower_bound (/d0) -> /d0 (true) <- excluded
// lower_bound (/e0) -> /d0 (true) <- excluded


// examples with desired outcomes
// excludeRange (/, /f0) ->  ANY /f0
//                          /f0 (false); / (true)
// excludeRange (/, /f1) ->  ANY /f1
//                          /f1 (false); / (true)
// excludeRange (/a0, /e0) ->  ANY /f0
//                          /f0 (false); / (true)
// excludeRange (/a0, /e0) ->  ANY /f0
//                          /f0 (false); / (true)

// excludeRange (/b1, /c0) ->  ANY /b0 /b1 ANY /c0 /d0 ANY /f0
//                          /f0 (false); /d0 (true); /c0 (false); /b1 (true); /b0 (false); / (true)

Exclude &
Exclude::excludeRange (const nnn::name::Component &from, const nnn::name::Component &to)
{
  if (from >= to)
    {
      BOOST_THROW_EXCEPTION (nnn::error::Exclude ()
      << nnn::error::msg ("Invalid exclude range (for single name exclude use Exclude::excludeOne)")
      << nnn::error::msg (from.toUri ())
      << nnn::error::msg (to.toUri ()));
    }

  iterator newFrom = m_exclude.lower_bound (from);
  if (newFrom == end () || !newFrom->second /*without ANY*/)
    {
      std::pair<iterator, bool> fromResult = m_exclude.insert (std::make_pair (from, true));
      newFrom = fromResult.first;
      if (!fromResult.second)
	{
	  // this means that the lower bound is equal to the item itself. So, just update ANY flag
	  newFrom->second = true;
	}
    }
  // else
  // nothing special if start of the range already exists with ANY flag set

  iterator newTo = m_exclude.lower_bound (to); // !newTo cannot be end ()
  if (newTo == newFrom || !newTo->second)
    {
      std::pair<iterator, bool> toResult = m_exclude.insert (std::make_pair (to, false));
      newTo = toResult.first;
      ++ newTo;
    }
  else
    {
      // nothing to do really
    }

  m_exclude.erase (newTo, newFrom); // remove any intermediate node, since all of the are excluded

  return *this;
}

Exclude &
Exclude::excludeAfter (const nnn::name::Component &from)
{
  iterator newFrom = m_exclude.lower_bound (from);
  if (newFrom == end () || !newFrom->second /*without ANY*/)
    {
      std::pair<iterator, bool> fromResult = m_exclude.insert (std::make_pair (from, true));
      newFrom = fromResult.first;
      if (!fromResult.second)
	{
	  // this means that the lower bound is equal to the item itself. So, just update ANY flag
	  newFrom->second = true;
	}
    }
  // else
  // nothing special if start of the range already exists with ANY flag set

  if (newFrom != m_exclude.begin ())
    {
      m_exclude.erase (m_exclude.begin (), newFrom); // remove any intermediate node, since all of the are excluded
    }

  return *this;
}

void
Exclude::appendExclude (const nnn::name::Component &name, bool any)
{
  m_exclude.insert (std::make_pair (name, any));
}

std::ostream&
operator << (std::ostream &os, const Exclude &exclude)
{
  for (Exclude::const_reverse_iterator i = exclude.rbegin (); i != exclude.rend (); i++)
    {
      os << i->first.toUri () << " ";
      if (i->second)
	os << "----> ";
    }
  return os;
}

ICN_NAMESPACE_END
