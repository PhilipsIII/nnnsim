/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnnsim-icn-interest.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnnsim-icn-interest.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnnsim-icn-interest.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "../../nnnsim-common.h"

#ifndef NNNSIM_ICN_INTEREST_H_
#define NNNSIM_ICN_INTEREST_H_

namespace ns3
{
  namespace icn
  {
    namespace wire
    {
      namespace icnSIM
      {

	class Interest : public Header
	{
	public:
	  Interest ();
	  Interest (Ptr<nnn::Interest> interest);

	  Ptr<nnn::Interest>
	  GetInterest ();

	  static Ptr<Packet>
	  ToWire (Ptr<const nnn::Interest> interest);

	  static Ptr<nnn::Interest>
	  FromWire (Ptr<Packet> packet);

	  // from Header
	  static TypeId GetTypeId (void);
	  virtual TypeId GetInstanceTypeId (void) const;
	  virtual void Print (std::ostream &os) const;
	  virtual uint32_t GetSerializedSize (void) const;
	  virtual void Serialize (Buffer::Iterator start) const;
	  virtual uint32_t Deserialize (Buffer::Iterator start);

	private:
	  Ptr<nnn::Interest> m_interest;
	};

      } /* namespace icnSIM */
    } /* namespace wire */
  } /* namespace nnn */
} /* namespace ns3 */

#endif /* NNNSIM_ICN_INTEREST_H_ */
