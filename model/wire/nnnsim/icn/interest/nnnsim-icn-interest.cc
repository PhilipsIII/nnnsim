/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnnsim-icn-interest.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnnsim-icn-interest.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnnsim-icn-interest.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/nnnsim-icn-interest.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.wire.icnSIM.Interest");

  namespace icn
  {
    namespace wire
    {
      namespace icnSIM
      {
	Interest::Interest ()
	: m_interest (Create<nnn::Interest> ())
	{
	}

	Interest::Interest (Ptr<nnn::Interest> interest)
	: m_interest (interest)
	{
	}

	Ptr<nnn::Interest>
	Interest::GetInterest ()
	{
	  return m_interest;
	}


	TypeId
	Interest::GetTypeId (void)
	{
	  static TypeId tid = TypeId ("ns3::nnn::Interest::nnnSIM")
		.SetGroupName ("Nnn")
		.SetParent<Header> ()
		.AddConstructor<Interest> ()
		;
	  return tid;
	}

	TypeId
	Interest::GetInstanceTypeId (void) const
	{
	  return GetTypeId ();
	}

	Ptr<Packet>
	Interest::ToWire (Ptr<const nnn::Interest> interest)
	{
	  Ptr<const Packet> p = interest->GetWire ();
	  if (!p)
	    {
	      Ptr<Packet> packet = Create<Packet> (*interest->GetPayload ());
	      Interest wireEncoding (ConstCast<nnn::Interest> (interest));
	      packet->AddHeader (wireEncoding);
	      interest->SetWire (packet);

	      p = packet;
	    }

	  return p->Copy ();
	}

	Ptr<nnn::Interest>
	Interest::FromWire (Ptr<Packet> packet)
	{
	  Ptr<nnn::Interest> interest = Create<nnn::Interest> ();
	  Ptr<Packet> wire = packet->Copy ();

	  Interest wireEncoding (interest);
	  packet->RemoveHeader (wireEncoding);

	  interest->SetPayload (packet);
	  interest->SetWire (wire);

	  return interest;
	}

	uint32_t
	Interest::GetSerializedSize (void) const
	{
	  size_t size =
	      1/*version*/ + 1 /*type*/ + 2/*length*/ +
	      (4/*nonce*/ + 1/*scope*/ + 1/*nack type*/ + 2/*timestamp*/ +
		  icn::wire::IcnSim::SerializedSizeName (m_interest->GetName ()) +

		  (2 +
		      (m_interest->GetExclude () == 0 ? 0 : (1 + icn::wire::IcnSim::SerializedSizeExclude (*m_interest->GetExclude ())))
		  )/* selectors */ +

		  (2 + 0)/* options */);

	  NS_LOG_INFO ("Serialize size = " << size);
	  return size;
	}

	void
	Interest::Serialize (Buffer::Iterator start) const
	{
	  start.WriteU8 (0x80); // version
	  start.WriteU8 (0x00); // packet type

	  start.WriteU16 (GetSerializedSize () - 4);

	  start.WriteU32 (m_interest->GetNonce ());
	  start.WriteU8 (m_interest->GetScope ());
	  start.WriteU8 (m_interest->GetNack ());

	  NS_ASSERT_MSG (0 <= m_interest->GetInterestLifetime ().ToInteger (Time::S) && m_interest->GetInterestLifetime ().ToInteger (Time::S) < 65535,
			 "Incorrect InterestLifetime (should not be smaller than 0 and larger than 65535");

	  // rounding timestamp value to seconds
	  start.WriteU16 (static_cast<uint16_t> (m_interest->GetInterestLifetime ().ToInteger (Time::S)));

	  icn::wire::IcnSim::SerializeName (start, m_interest->GetName ());

	  if (m_interest->GetExclude () == 0)
	    {
	      start.WriteU16 (0); // no selectors
	    }
	  else
	    {
	      start.WriteU16 (1 + icn::wire::IcnSim::SerializedSizeExclude (*m_interest->GetExclude ()));
	      start.WriteU8 (0x01);
	      icn::wire::IcnSim::SerializeExclude (start, *m_interest->GetExclude ());
	    }

	  start.WriteU16 (0); // no options
	}

	uint32_t
	Interest::Deserialize (Buffer::Iterator start)
	{
	  Buffer::Iterator i = start;

	  if (i.ReadU8 () != 0x80)
	    throw new nnn::InterestException ();

	  if (i.ReadU8 () != 0x00)
	    throw new nnn::InterestException ();

	  i.ReadU16 (); // length, don't need it right now

	  m_interest->SetNonce (i.ReadU32 ());
	  m_interest->SetScope (i.ReadU8 ());
	  m_interest->SetNack (i.ReadU8 ());

	  m_interest->SetInterestLifetime (Seconds (i.ReadU16 ()));

	  m_interest->SetName (icn::wire::IcnSim::DeserializeName (i));

	  uint32_t selectorsLen = i.ReadU16 ();
	  if (selectorsLen > 0)
	    {
	      if (i.ReadU8 () != 0x01) // exclude filter only
		throw nnn::InterestException ();

	      m_interest->SetExclude (icn::wire::IcnSim::DeserializeExclude (i));
	    }
	  i.ReadU16 ();

	  NS_ASSERT (GetSerializedSize () == (i.GetDistanceFrom (start)));

	  return i.GetDistanceFrom (start);
	}

	void
	Interest::Print (std::ostream &os) const
	{
	  m_interest->Print (os);
	}

      } /* namespace icnSIM */
    } /* namespace wire */
  } /* namespace nnn */
} /* namespace ns3 */
