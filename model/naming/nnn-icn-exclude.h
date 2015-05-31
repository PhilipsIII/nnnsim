/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-exclude.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-exclude.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-exclude.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *  Initial implementation made by Alexander Afanasyev for the Regents of the
 *  University of California
 */

#ifndef NNN_ICN_EXCLUDE_H
#define NNN_ICN_EXCLUDE_H

#include "ns3/simple-ref-count.h"
#include <map>

#include "ns3/nnn-name-component.h"
#include "ns3/nnn-icn-common.h"

ICN_NAMESPACE_BEGIN

/**
 * @ingroup icn
 * @brief Class to represent Exclude component in ICN interests
 */
class Exclude : public SimpleRefCount<Exclude>
{
public:
  typedef std::map<nnn::name::Component, bool /*any*/, std::greater<nnn::name::Component> > exclude_type;

  typedef exclude_type::iterator iterator;
  typedef exclude_type::const_iterator const_iterator;
  typedef exclude_type::reverse_iterator reverse_iterator;
  typedef exclude_type::const_reverse_iterator const_reverse_iterator;

  /**
   * @brief Default constructor an empty exclude
   */
  Exclude ();

  // no need for explicit copy constructor

  /**
   * @brief Check if name component is excluded
   * @param comp Name component to check against exclude filter
   */
  bool
  isExcluded (const nnn::name::Component &comp) const;

  /**
   * @brief Exclude specific name component
   * @param comp component to exclude
   * @returns *this to allow chaining
   */
  Exclude &
  excludeOne (const nnn::name::Component &comp);

  /**
   * @brief Exclude components from range [from, to]
   * @param from first element of the range
   * @param to last element of the range
   * @returns *this to allow chaining
   */
  Exclude &
  excludeRange (const nnn::name::Component &from, const nnn::name::Component &to);

  /**
   * @brief Exclude all components from range [/, to]
   * @param to last element of the range
   * @returns *this to allow chaining
   */
  inline Exclude &
  excludeBefore (const nnn::name::Component &to);

  /**
   * @brief Exclude all components from range [from, +Inf]
   * @param to last element of the range
   * @returns *this to allow chaining
   */
  Exclude &
  excludeAfter (const nnn::name::Component &from);

  /**
   * @brief Method to directly append exclude element
   * @param name excluded name component
   * @param any  flag indicating if there is a postfix ANY component after the name
   *
   * This method is used during conversion from wire format of exclude filter
   *
   * If there is an error with ranges (e.g., order of components is wrong) an exception is thrown
   */
  void
  appendExclude (const nnn::name::Component &name, bool any);

  /**
   * @brief Get number of exclude terms
   */
  inline size_t
  size () const;

  /**
   * @brief Get begin iterator of the exclude terms
   */
  inline const_iterator
  begin () const;

  /**
   * @brief Get end iterator of the exclude terms
   */
  inline const_iterator
  end () const;

  /**
   * @brief Get begin iterator of the exclude terms
   */
  inline const_reverse_iterator
  rbegin () const;

  /**
   * @brief Get end iterator of the exclude terms
   */
  inline const_reverse_iterator
  rend () const;

private:
  Exclude &
  excludeRange (iterator fromLowerBound, iterator toLowerBound);

private:
  exclude_type m_exclude;
};

std::ostream&
operator << (std::ostream &os, const Exclude &name);

inline Exclude &
Exclude::excludeBefore (const nnn::name::Component &to)
{
  return excludeRange (nnn::name::Component (), to);
}

inline size_t
Exclude::size () const
{
  return m_exclude.size ();
}

inline Exclude::const_iterator
Exclude::begin () const
{
  return m_exclude.begin ();
}

inline Exclude::const_iterator
Exclude::end () const
{
  return m_exclude.end ();
}

inline Exclude::const_reverse_iterator
Exclude::rbegin () const
{
  return m_exclude.rbegin ();
}

inline Exclude::const_reverse_iterator
Exclude::rend () const
{
  return m_exclude.rend ();
}

ICN_NAMESPACE_END

#endif // NNN_ICN_EXCLUDE_H
