/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  wire-nnnsim-icn.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  wire-nnnsim-icn.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with wire-nnnsim-icn.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "wire-nnnsim-icn.h"

#include <boost/foreach.hpp>

ICN_NAMESPACE_BEGIN

namespace wire
{
  size_t
  IcnSim::SerializeName (Buffer::Iterator &i, const Name &name)
  {
    Buffer::Iterator start = i;

    i.WriteU16 (static_cast<uint16_t> (SerializedSizeName (name)-2));

    for (Name::const_iterator item = name.begin ();
	item != name.end ();
	item++)
      {
	i.WriteU16 (static_cast<uint16_t> (item->size ()));
	i.Write (reinterpret_cast<const uint8_t*> (item->buf ()), item->size ());
      }

    return i.GetDistanceFrom (start);
  }

  size_t
  IcnSim::SerializedSizeName (const Name &name)
  {
    size_t nameSerializedSize = 2;

    for (Name::const_iterator i = name.begin ();
	i != name.end ();
	i++)
      {
	nameSerializedSize += 2 + i->size ();
      }
    NS_ASSERT_MSG (nameSerializedSize < 30000, "Name is too long (> 30kbytes)");

    return nameSerializedSize;
  }

  Ptr<Name>
  IcnSim::DeserializeName (Buffer::Iterator &i)
  {
    Ptr<Name> name = Create<Name> ();

    uint16_t nameLength = i.ReadU16 ();
    while (nameLength > 0)
      {
	uint16_t length = i.ReadU16 ();
	nameLength = nameLength - 2 - length;

	uint8_t tmp[length];
	i.Read (tmp, length);

	name->append (tmp, length);
      }

    return name;
  }


  size_t
  IcnSim::SerializeExclude (Buffer::Iterator &i, const Exclude &exclude)
  {
    Buffer::Iterator start = i;

    i.WriteU16 (static_cast<uint16_t> (SerializedSizeExclude (exclude)-2));

    for (Exclude::const_reverse_iterator item = exclude.rbegin ();
	item != exclude.rend ();
	item++)
      {
	if (!item->first.empty ())
	  {
	    i.WriteU8 (ExcludeNameType);
	    i.WriteU16 (static_cast<uint16_t> (item->first.size ()));
	    i.Write (reinterpret_cast<const uint8_t*> (item->first.buf ()), item->first.size ());
	  }
	if (item->second)
	  {
	    i.WriteU8 (ExcludeAnyType);
	  }
      }
    return i.GetDistanceFrom (start);
  }

  size_t
  IcnSim::SerializedSizeExclude (const Exclude &exclude)
  {
    size_t excludeSerializedSize = 2;

    for (Exclude::const_reverse_iterator item = exclude.rbegin ();
	item != exclude.rend ();
	item++)
      {
	if (!item->first.empty ())
	  {
	    excludeSerializedSize += 1 + 2 + item->first.size ();
	  }
	if (item->second)
	  {
	    excludeSerializedSize += 1;
	  }
      }

    return excludeSerializedSize;
  }

  Ptr<Exclude>
  IcnSim::DeserializeExclude (Buffer::Iterator &i)
  {
    Ptr<Exclude> exclude = Create<Exclude> ();

    uint16_t excludeLength = i.ReadU16 ();
    while (excludeLength > 0)
      {
	uint8_t type = i.ReadU8 ();
	excludeLength --;

	if (type == ExcludeAnyType)
	  {
	    exclude->appendExclude (nnn::name::Component (), true);
	  }
	else if (type == ExcludeNameType)
	  {
	    uint16_t length = i.ReadU16 ();
	    excludeLength = excludeLength - 2 - length;

	    uint8_t tmp[length];
	    i.Read (tmp, length);

	    bool any = false;
	    if (excludeLength > 0)
	      {
		uint8_t type = i.ReadU8 ();
		if (type != ExcludeAnyType)
		  {
		    i.Prev ();
		  }
		else
		  {
		    any = true;
		    excludeLength --;
		  }
	      }

	    exclude->appendExclude (nnn::name::Component (tmp, length), any);
	  }
	else
	  {
	    NS_FATAL_ERROR ("Incorrect format of Exclude filter");
	  }
      }
    return exclude;
  }
} // wire

ICN_NAMESPACE_END
