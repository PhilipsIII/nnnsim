/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnnsim-icn-data.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnnsim-icn-data.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnnsim-icn-data.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *
 */

#include "ns3/nnnsim-icn-data.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.wire.icnSIM.Data");

  namespace icn
  {
    namespace wire
    {
      namespace icnSIM
      {
	Data::Data ()
	  : m_data (Create<nnn::Data> ())
	{
	}

	Data::Data (Ptr<nnn::Data> data)
	  : m_data (data)
	{
	}

	TypeId
	Data::GetTypeId (void)
	{
	  static TypeId tid = TypeId ("ns3::nnn::Data::nnnSIM")
	    .SetGroupName ("Nnn")
	    .SetParent<Header> ()
	    .AddConstructor<Data> ()
	    ;
	  return tid;
	}

	TypeId
	Data::GetInstanceTypeId (void) const
	{
	  return GetTypeId ();
	}

	Ptr<nnn::Data>
	Data::GetData ()
	{
	  return m_data;
	}

	Ptr<Packet>
	Data::ToWire (Ptr<const nnn::Data> data)
	{
	  Ptr<const Packet> p = data->GetWire ();
	  if (!p)
	    {
	      Ptr<Packet> packet = Create<Packet> (*data->GetPayload ());
	      Data wireEncoding (ConstCast<nnn::Data> (data));
	      packet->AddHeader (wireEncoding);
	      data->SetWire (packet);

	      p = packet;
	    }

	  return p->Copy ();
	}

	Ptr<nnn::Data>
	Data::FromWire (Ptr<Packet> packet)
	{
	  Ptr<nnn::Data> data = Create<nnn::Data> ();
	  Ptr<Packet> wire = packet->Copy ();

	  Data wireEncoding (data);
	  packet->RemoveHeader (wireEncoding);

	  data->SetPayload (packet);
	  data->SetWire (wire);

	  return data;
	}

	uint32_t
	Data::GetSerializedSize () const
	{
	  uint32_t size = 1 + 1 + 2 +
	    ((2 + 2) +
	     icn::wire::IcnSim::SerializedSizeName (m_data->GetName ()) +
	     (2 + 2 + 4 + 2 + 2 + (2 + 0)));
	  if (m_data->GetSignature () != 0)
	    size += 4;

	  NS_LOG_INFO ("Serialize size = " << size);
	  return size;
	}

	void
	Data::Serialize (Buffer::Iterator start) const
	{
	  start.WriteU8 (0x80); // version
	  start.WriteU8 (0x01); // packet type
	  start.WriteU16 (GetSerializedSize () - 4); // length

	  if (m_data->GetSignature () != 0)
	    {
	      start.WriteU16 (6); // signature length
	      start.WriteU16 (0xFF00); // "fake" simulator signature
	      start.WriteU32 (m_data->GetSignature ());
	    }
	  else
	    {
	      start.WriteU16 (2); // signature length
	      start.WriteU16 (0); // empty signature
	    }

	  // name
	  icn::wire::IcnSim::SerializeName (start, m_data->GetName ());

	  // content
	  // for now assume that contentdata length is zero
	  start.WriteU16 (2 + 4 + 2 + 2 + (2 + 0));
	  start.WriteU16 (4 + 2 + 2 + (2 + 0));
	  start.WriteU32 (static_cast<uint32_t> (m_data->GetTimestamp ().ToInteger (Time::S)));
	  start.WriteU16 (static_cast<uint16_t> (m_data->GetFreshness ().ToInteger (Time::S)));
	  start.WriteU16 (0); // reserved
	  start.WriteU16 (0); // Length (ContentInfoOptions)

	  // that's it folks
	}

	uint32_t
	Data::Deserialize (Buffer::Iterator start)
	{
	  Buffer::Iterator i = start;

	  if (i.ReadU8 () != 0x80)
	    throw new nnn::DataException ();

	  if (i.ReadU8 () != 0x01)
	    throw new nnn::DataException ();

	  i.ReadU16 (); // length

	  uint32_t signatureLength = i.ReadU16 ();
	  if (signatureLength == 6)
	    {
	      if (i.ReadU16 () != 0xFF00) // signature type
	        throw new nnn::DataException ();
	      m_data->SetSignature (i.ReadU32 ());
	    }
	  else if (signatureLength == 2)
	    {
	      if (i.ReadU16 () != 0) // signature type
	        throw new nnn::DataException ();
	      m_data->SetSignature (0);
	    }
	  else
	    throw new nnn::DataException ();

	  m_data->SetName (icn::wire::IcnSim::DeserializeName (i));

	  if (i.ReadU16 () != (2 + 4 + 2 + 2 + (2 + 0))) // content length
	    throw new nnn::DataException ();

	  if (i.ReadU16 () != (4 + 2 + 2 + (2 + 0))) // Length (content Info)
	    throw new nnn::DataException ();

	  m_data->SetTimestamp (Seconds (i.ReadU32 ()));
	  m_data->SetFreshness (Seconds (i.ReadU16 ()));

	  if (i.ReadU16 () != 0) // Reserved
	    throw new nnn::DataException ();
	  if (i.ReadU16 () != 0) // Length (ContentInfoOptions)
	    throw new nnn::DataException ();

	  NS_ASSERT_MSG (i.GetDistanceFrom (start) == GetSerializedSize (),
	                 "Something wrong with Data::Deserialize");

	  return i.GetDistanceFrom (start);
	}

	void
	Data::Print (std::ostream &os) const
	{
	  m_data->Print (os);
	}

      } /* namespace icnSIM */
    } /* namespace wire */
  } /* namespace icn */
} /* namespace ns3 */
