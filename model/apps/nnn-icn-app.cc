/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-app.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-app.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-app.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-icn-app.h"

#include "ns3/boolean.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/string.h"

#include "../../helper/nnn-header-helper.h"
#include "../nnn-icn-app-face.h"
#include "../nnn-l3-protocol.h"
#include "../buffers/nnn-pdu-buffer-queue.h"
#include "../fw/nnn-forwarding-strategy.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.ICNApp");

  namespace nnn
  {
    NS_OBJECT_ENSURE_REGISTERED (ICNApp);

    TypeId
    ICNApp::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::nnn::ICNApp")
	.SetGroupName ("Nnn")
	.SetParent<App> ()
	.AddConstructor<ICNApp> ()

	.AddTraceSource ("ReceivedInterests", "ReceivedInterests",
	                 MakeTraceSourceAccessor (&ICNApp::m_receivedInterests),
			 "ns3::nnn:ICNApp::ReceivedInterestTracedCallback")

	.AddTraceSource ("ReceivedNacks", "ReceivedNacks",
	                 MakeTraceSourceAccessor (&ICNApp::m_receivedNacks),
			 "ns3::nnn:ICNApp::ReceivedNackTracedCallback")

	.AddTraceSource ("ReceivedDatas", "ReceivedDatas",
	                 MakeTraceSourceAccessor (&ICNApp::m_receivedDatas),
			 "ns3::nnn:ICNApp::ReceivedDataTracedCallback")

	.AddTraceSource ("TransmittedInterests", "TransmittedInterests",
			 MakeTraceSourceAccessor (&ICNApp::m_transmittedInterests),
			 "ns3::nnn:ICNApp::TransmittedInterestTracedCallback")

	.AddTraceSource ("TransmittedDatas", "TransmittedDatas",
	                 MakeTraceSourceAccessor (&ICNApp::m_transmittedDatas),
			 "ns3::nnn:ICNApp::TransmittedDataTracedCallback")
	;
      return tid;
    }

    ICNApp::ICNApp ()
    : App ()
    {
    }

    ICNApp::~ICNApp ()
    {
    }

    void
    ICNApp::DoDispose (void)
    {
      NS_LOG_FUNCTION_NOARGS ();

      // Unfortunately, this causes SEGFAULT
      // The best reason I see is that apps are freed after nnn stack is removed
      // StopApplication ();
      Application::DoDispose ();
    }

    void
    ICNApp::OnInterest (Ptr<const Interest> interest)
    {
      NS_LOG_FUNCTION (this << interest);
      m_receivedInterests (interest, this, m_face);
    }

    void
    ICNApp::OnNack (Ptr<const Interest> interest)
    {
      NS_LOG_FUNCTION (this << interest);
      m_receivedNacks (interest, this, m_face);
    }

    void
    ICNApp::OnData (Ptr<const Data> contentObject)
    {
      NS_LOG_FUNCTION (this << contentObject);
      m_receivedDatas (contentObject, this, m_face);
    }

    // Application Methods
    void
    ICNApp::StartApplication () // Called at time specified by Start
    {
      NS_LOG_FUNCTION_NOARGS ();

      NS_ASSERT (m_active != true);
      m_active = true;

      NS_ASSERT_MSG (GetNode ()->GetObject<L3Protocol> () != 0,
		     "3N stack should be installed on the node " << GetNode ());

      // step 1. Create a face
      m_face = CreateObject<ICNAppFace> (/*Ptr<App> (this)*/this);

      // step 2. Add face to the 3N stack
      GetNode ()->GetObject<L3Protocol> ()->AddFace (m_face);

      // step 3. Enable face
      m_face->SetUp (true);

      // Step 4. Obtain information about the underlying forwarding strategy
      Ptr<ForwardingStrategy> fw = GetNode ()->GetObject<ForwardingStrategy> ();

      fw->TraceConnectWithoutContext("Got3NName", MakeCallback (&ICNApp::GotName, this));
      fw->TraceConnectWithoutContext("No3NName", MakeCallback (&ICNApp::NoName, this));

      // Step 5. Check if we happen to already have a name!
      if (fw->Has3NName())
	GotName ();
    }

    void
    ICNApp::StopApplication () // Called at time specified by Stop
    {
      NS_LOG_FUNCTION_NOARGS ();

      if (!m_active) return; //don't assert here, just return

      NS_ASSERT (GetNode ()->GetObject<L3Protocol> () != 0);

      m_active = false;

      // step 1. Disable face
      m_face->SetUp (false);

      // step 2. Remove face from Nnn stack
      GetNode ()->GetObject<L3Protocol> ()->RemoveFace (m_face);

      // step 3. Destroy face
      if (m_face->GetReferenceCount () != 1)
	{
	  NS_LOG_ERROR ("At this point, nobody else should have referenced this face, but we have "
	      << m_face->GetReferenceCount () << " references");

	}
      m_face = 0;
    }
  } // namespace nnn
} // namespace ns3
