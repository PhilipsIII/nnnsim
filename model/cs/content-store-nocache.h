/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 *   This file is part of nnnsim.
 *
 *  content-store-nocache.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  content-store-nocache.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with content-store-nocache.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *  Modified for nnnsim by Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef ICN_CONTENT_STORE_NOCACHE_H
#define	ICN_CONTENT_STORE_NOCACHE_H

#include "nnn-icn-content-store.h"

namespace ns3
{
  namespace nnn
  {
    namespace cs
    {
      /**
       * @ingroup nnn-cs
       * @brief Implementation of ContentStore that completely disables caching
       */
      class Nocache : public ContentStore
      {
      public:
	/**
	 * \brief Interface ID
	 *
	 * \return interface ID
	 */
	static
	TypeId GetTypeId ();

	/**
	 * @brief Default constructor
	 */
	Nocache ();

	/**
	 * @brief Virtual destructor
	 */
	virtual
	~Nocache ();

	virtual Ptr<Data>
	Lookup (Ptr<const Interest> interest);

	virtual bool
	Add (Ptr<const Data> data);

	virtual void
	Print (std::ostream &os) const;

	virtual uint32_t
	GetSize () const;

	virtual Ptr<cs::Entry>
	Begin ();

	virtual Ptr<cs::Entry>
	End ();

	virtual Ptr<cs::Entry>
	Next (Ptr<cs::Entry>);

      };
    } // namespace cs
  } // namespace nnn
} // namespace ns3

#endif // ICN_CONTENT_STORE_NOCACHE_H
