/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnnsim-oen.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnnsim-oen.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnnsim-oen.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef _NNNSIM_OEN_H_
#define _NNNSIM_OEN_H_

#include "../../nnnsim-common-hdr.h"
#include "../../nnnsim-common.h"

namespace ns3
{
  namespace nnn
  {
    namespace wire
    {
      namespace nnnSIM
      {
	class OEN : public CommonHeader<nnn::OEN>
	{
	public:
	  OEN ();

	  OEN (Ptr<nnn::OEN> oen_p);

	  static Ptr<Packet>
	  ToWire (Ptr<const nnn::OEN> den_p);

	  static Ptr<nnn::OEN>
	  FromWire (Ptr<Packet> packet);

	  // from Header
	  static TypeId GetTypeId (void);
	  TypeId GetInstanceTypeId (void) const;
	  uint32_t GetSerializedSize (void) const;
	  void Serialize (Buffer::Iterator start) const;
	  uint32_t Deserialize (Buffer::Iterator start);
	};
      } /* namespace nnnSIM */
    } /* namespace wire */
  } /* namespace nnn */
} /* namespace ns3 */

#endif /* _NNNSIM_OEN_H_ */
