/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-producer.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-producer.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-producer.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/uinteger.h"

#include <boost/ref.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
namespace ll = boost::lambda;

#include "nnn-icn-producer.h"
#include "../../helper/icn-header-helper.h"
#include "../nnn-app-face.h"
#include "../fib/nnn-fib.h"
#include "../fw/nnn-forwarding-strategy.h"
#include "../../utils/nnn-fw-hop-count-tag.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.ICNProducer");

  namespace nnn
  {
    NS_OBJECT_ENSURE_REGISTERED (Producer);

    TypeId
    Producer::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::nnn::ICNProducer")
	.SetGroupName ("Nnn")
	.SetParent<ICNApp> ()
	.AddConstructor<Producer> ()
	.AddAttribute ("Prefix","Prefix, for which producer has the data",
		       StringValue ("/"),
		       MakeNameAccessor (&Producer::m_prefix),
		       icn::MakeNameChecker ())
	.AddAttribute ("Postfix", "Postfix that is added to the output data (e.g., for adding producer-uniqueness)",
		       StringValue ("/"),
		       MakeNameAccessor (&Producer::m_postfix),
		       icn::MakeNameChecker ())
	.AddAttribute ("PayloadSize", "Virtual payload size for Content packets",
		       UintegerValue (1024),
		       MakeUintegerAccessor (&Producer::m_virtualPayloadSize),
		       MakeUintegerChecker<uint32_t> ())
	.AddAttribute ("Freshness", "Freshness of data packets, if 0, then unlimited freshness",
		       TimeValue (Seconds (0)),
		       MakeTimeAccessor (&Producer::m_freshness),
		       MakeTimeChecker ())
	.AddAttribute ("Signature", "Fake signature, 0 valid signature (default), other values application-specific",
		       UintegerValue (0),
		       MakeUintegerAccessor (&Producer::m_signature),
		       MakeUintegerChecker<uint32_t> ())
	.AddAttribute ("KeyLocator", "Name to be used for key locator.  If root, then key locator is not used",
		       icn::NameValue (),
		       MakeNameAccessor (&Producer::m_keyLocator),
		       icn::MakeNameChecker ())
	;
      return tid;
    }

    Producer::Producer ()
    {
      // NS_LOG_FUNCTION_NOARGS ();
    }

    // inherited from Application base class.
    void
    Producer::StartApplication ()
    {
      NS_LOG_FUNCTION_NOARGS ();
      NS_ASSERT (GetNode ()->GetObject<Fib> () != 0);

      ICNApp::StartApplication ();

      NS_LOG_DEBUG ("NodeID: " << GetNode ()->GetId ());

      Ptr<Fib> fib = GetNode ()->GetObject<Fib> ();

      Ptr<fib::Entry> fibEntry = fib->Add (m_prefix, m_face, 0);

      fibEntry->UpdateStatus (m_face, fib::FaceMetric::NDN_FIB_GREEN);

      // // make face green, so it will be used primarily
      // StaticCast<fib::FibImpl> (fib)->modify (fibEntry,
      //                                        ll::bind (&fib::Entry::UpdateStatus,
      //                                                  ll::_1, m_face, fib::FaceMetric::NDN_FIB_GREEN));

      NS_LOG_INFO ("Finished setting up Producer application");
    }

    void
    Producer::StopApplication ()
    {
      NS_LOG_FUNCTION_NOARGS ();
      NS_ASSERT (GetNode ()->GetObject<Fib> () != 0);

      ICNApp::StopApplication ();
    }

    void
    Producer::OnInterest (Ptr<const Interest> interest)
    {
      ICNApp::OnInterest (interest); // tracing inside

      NS_LOG_FUNCTION (this << interest);

      if (!m_active) return;

      Ptr<Data> data = Create<Data> (Create<Packet> (m_virtualPayloadSize));
      Ptr<icn::Name> dataName = Create<icn::Name> (interest->GetName ());
      dataName->append (m_postfix);
      data->SetName (dataName);
      data->SetFreshness (m_freshness);
      data->SetTimestamp (Simulator::Now());

      data->SetSignature (m_signature);
      if (m_keyLocator.size () > 0)
	{
	  data->SetKeyLocator (Create<icn::Name> (m_keyLocator));
	}

      NS_LOG_INFO ("node("<< GetNode()->GetId() <<") responding with Data: " << data->GetName ());

      // Echo back FwHopCountTag if exists
      FwHopCountTag hopCountTag;
      if (interest->GetPayload ()->PeekPacketTag (hopCountTag))
	{
	  data->GetPayload ()->AddPacketTag (hopCountTag);
	}
      // Will have to be adapted to 3N
      //m_face->ReceiveData (data);
      m_transmittedDatas (data, this, m_face);
    }

    Ptr<Packet>
    Producer::CreateReturnData (Ptr<Interest> interest)
    {
      NS_LOG_FUNCTION (this << interest);

      Ptr<Data> data = Create<Data> (Create<Packet> (m_virtualPayloadSize));
      Ptr<icn::Name> dataName = Create<icn::Name> (interest->GetName ());
      dataName->append (m_postfix);
      data->SetName (dataName);
      data->SetFreshness (m_freshness);
      data->SetTimestamp (Simulator::Now());

      data->SetSignature (m_signature);
      if (m_keyLocator.size () > 0)
	{
	  data->SetKeyLocator (Create<icn::Name> (m_keyLocator));
	}

      NS_LOG_INFO ("Responding with Data: " << data->GetName () << " seq: " << std::dec << data->GetName ().get (-1).toSeqNum ());

      // Echo back FwHopCountTag if exists
      FwHopCountTag hopCountTag;
      if (interest->GetPayload ()->PeekPacketTag (hopCountTag))
	{
	  data->GetPayload ()->AddPacketTag (hopCountTag);
	}

      m_transmittedDatas (data, this, m_face);
      return icn::Wire::FromData (data);
    }

    void
    Producer::OnNULLp (Ptr<const NULLp> nullpObject)
    {
      if (!m_active) return;

      ICNApp::OnNULLp(nullpObject);

      NS_LOG_FUNCTION (this << nullpObject);

      Ptr<Packet> packet = nullpObject->GetPayload ()->Copy ();
      uint16_t pdutype = nullpObject->GetPDUPayloadType ();

      NS_LOG_INFO (this << " obtained pdu type " << pdutype);

      if (pdutype == ICN_NNN)
	{
	  try
	  {
	      icn::HeaderHelper::Type type = icn::HeaderHelper::GetICNHeaderType (packet);
	      Ptr<Interest> interest = 0;
	      switch (type)
	      {
		case icn::HeaderHelper::INTEREST_NDNSIM:
		  interest = icn::Wire::ToInterest (packet, icn::Wire::WIRE_FORMAT_NDNSIM);
		  break;
	      }

	      if (interest != 0)
		{
		  ICNApp::OnInterest (interest);

		  Ptr<Packet> retPkt = CreateReturnData(interest);

		  if (m_isMobile && m_has3Nname)
		    {
		      NS_LOG_INFO ("Responding NULLp with SO from (" << *m_current3Nname << ")");
		      // We don't have all the information for a DU, so send a SO
		      Ptr<SO> so_o = Create<SO> ();
		      so_o->SetPDUPayloadType (pdutype);
		      so_o->SetLifetime (m_3n_lifetime);
		      so_o->SetName (*m_current3Nname);
		      so_o->SetPayload (retPkt);

		      m_face->ReceiveSO (so_o);
		      m_transmittedSOs (so_o, this, m_face);
		    }
		  else
		    {
		      NS_LOG_INFO ("Responding NULLp with NULLp");
		      Ptr<NULLp> nullp_o = Create<NULLp> ();
		      nullp_o->SetPDUPayloadType (pdutype);
		      nullp_o->SetLifetime (m_3n_lifetime);
		      nullp_o->SetPayload (retPkt);

		      m_face->ReceiveNULLp (nullp_o);
		      m_transmittedNULLps (nullp_o, this, m_face);
		    }
		}

	      // exception will be thrown if packet is not recognized
	  }
	  catch (icn::UnknownHeaderException)
	  {
	      NS_FATAL_ERROR ("Unknown NDN header. Should not happen");
	  }
	}
    }

    void
    Producer::OnSO (Ptr<const SO> soObject)
    {
      if (!m_active) return;

      App::OnSO(soObject);

      NS_LOG_FUNCTION (this << soObject);

      Ptr<Packet> packet = soObject->GetPayload ()->Copy ();
      uint16_t pdutype = soObject->GetPDUPayloadType ();

      NS_LOG_INFO (this << " obtained pdu type " << pdutype);

      if (pdutype == ICN_NNN)
	{
	  try
	  {
	      icn::HeaderHelper::Type type = icn::HeaderHelper::GetICNHeaderType (packet);
	      Ptr<Interest> interest = 0;
	      switch (type)
	      {
		case icn::HeaderHelper::INTEREST_NDNSIM:
		  interest = icn::Wire::ToInterest (packet, icn::Wire::WIRE_FORMAT_NDNSIM);
		  break;
	      }

	      if (interest != 0)
		{
		  ICNApp::OnInterest (interest);

		  Ptr<Packet> retPkt = CreateReturnData(interest);

		  if (m_isMobile && m_has3Nname)
		    {
		      NS_LOG_INFO ("Responding SO with DU from (" << *m_current3Nname << ") to (" << soObject->GetName () << ")");
		      // We can use DU packets now
		      Ptr<DU> du_o = Create<DU> ();
		      du_o->SetPDUPayloadType(pdutype);
		      du_o->SetSrcName(*m_current3Nname);
		      du_o->SetDstName(soObject->GetName ());
		      du_o->SetLifetime(m_3n_lifetime);
		      du_o->SetPayload(retPkt);

		      m_face->ReceiveDU(du_o);
		      m_transmittedDUs (du_o, this, m_face);
		    }
		  else
		    {
		      NS_LOG_INFO ("Responding SO with DO to (" << soObject->GetName () << ")");
		      Ptr<DO> do_o = Create<DO> ();

		      do_o->SetName (soObject->GetName ());
		      do_o->SetPDUPayloadType (pdutype);
		      do_o->SetLifetime(m_3n_lifetime);
		      do_o->SetPayload (retPkt);

		      m_face->ReceiveDO(do_o);
		      m_transmittedDOs (do_o, this, m_face);
		    }
		}

	      // exception will be thrown if packet is not recognized
	  }
	  catch (icn::UnknownHeaderException)
	  {
	      NS_FATAL_ERROR ("Unknown NDN header. Should not happen");
	  }
	}
    }

    void
    Producer::OnDO (Ptr<const DO> doObject)
    {
      if (!m_active) return;
      ICNApp::OnDO (doObject);
      NS_LOG_FUNCTION (this << doObject);
      Ptr<Packet> packet = doObject->GetPayload ()->Copy ();
      uint16_t pdutype = doObject->GetPDUPayloadType ();
      NS_LOG_INFO (this << " obtained pdu type " << pdutype);
      if (pdutype == ICN_NNN)
	{
	  try
	  {
	      icn::HeaderHelper::Type type = icn::HeaderHelper::GetICNHeaderType (packet);
	      Ptr<Interest> interest = 0;
	      switch (type)
	      {
		case icn::HeaderHelper::INTEREST_NDNSIM:
		  interest = icn::Wire::ToInterest (packet, icn::Wire::WIRE_FORMAT_NDNSIM);
		  break;
	      }
	      if (interest != 0)
		{
		  ICNApp::OnInterest (interest);
		  Ptr<Packet> retPkt = CreateReturnData(interest);
		  if (m_isMobile && m_has3Nname)
		    {
		      NS_LOG_INFO ("Responding DO with SO from (" << *m_current3Nname << ")");
		      Ptr<SO> so_o = Create<SO> ();
		      so_o->SetLifetime (m_3n_lifetime);
		      so_o->SetPDUPayloadType (pdutype);
		      so_o->SetName (*m_current3Nname);
		      so_o->SetPayload (retPkt);
		      m_face->ReceiveSO (so_o);
		      m_transmittedSOs (so_o, this, m_face);
		    }
		  else
		    {
		      NS_LOG_INFO ("Responding DO with NULLp");
		      Ptr<NULLp> nullp_o = Create<NULLp> ();
		      nullp_o->SetLifetime (m_3n_lifetime);
		      nullp_o->SetPDUPayloadType (pdutype);
		      nullp_o->SetPayload (retPkt);
		      m_face->ReceiveNULLp (nullp_o);
		      m_transmittedNULLps (nullp_o, this, m_face);
		    }
		}
	      // exception will be thrown if packet is not recognized
	  }
	  catch (icn::UnknownHeaderException)
	  {
	      NS_FATAL_ERROR ("Unknown NDN header. Should not happen");
	  }
	}
    }

    void
    Producer::OnDU (Ptr<const DU> duObject)
    {
      if (!m_active) return;

      ICNApp::OnDU(duObject);

      NS_LOG_FUNCTION (this << duObject);

      Ptr<Packet> packet = duObject->GetPayload ()->Copy ();
      uint16_t pdutype = duObject->GetPDUPayloadType ();

      NS_LOG_INFO (this << " obtained pdu type " << pdutype);

      if (pdutype == ICN_NNN)
	{
	  try
	  {
	      icn::HeaderHelper::Type type = icn::HeaderHelper::GetICNHeaderType (packet);
	      Ptr<Interest> interest = 0;
	      switch (type)
	      {
		case icn::HeaderHelper::INTEREST_NDNSIM:
		  interest = icn::Wire::ToInterest (packet, icn::Wire::WIRE_FORMAT_NDNSIM);
		  break;
	      }

	      if (interest != 0)
		{
		  ICNApp::OnInterest (interest);

		  Ptr<Packet> retPkt = CreateReturnData(interest);

		  NS_LOG_INFO ("Responding DU with DU");
		  Ptr<DU> du_o = Create<DU> ();
		  du_o->SetLifetime (m_3n_lifetime);
		  if (m_has3Nname)
		    du_o->SetSrcName(*m_current3Nname);
		  else
		    du_o->SetSrcName (duObject->GetDstName ());

		  du_o->SetDstName (duObject->GetSrcName ());
		  du_o->SetPDUPayloadType (pdutype);
		  du_o->SetPayload (retPkt);


		  m_face->ReceiveDU(du_o);
		  m_transmittedDUs (du_o, this, m_face);
		}

	      // exception will be thrown if packet is not recognized
	  }
	  catch (icn::UnknownHeaderException)
	  {
	      NS_FATAL_ERROR ("Unknown NDN header. Should not happen");
	  }
	}
    }
  } // namespace nnn
} // namespace ns3
