/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-app.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-app.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-app.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-app.h"

#include "ns3/boolean.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/string.h"

#include "ns3/nnn-header-helper.h"
#include "ns3/nnn-pdus.h"
#include "ns3/nnn-app-face.h"
#include "ns3/nnn-l3-protocol.h"
#include "ns3/nnn-pdu-buffer-queue.h"
#include "ns3/nnn-forwarding-strategy.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.App");

  namespace nnn
  {
    NS_OBJECT_ENSURE_REGISTERED (App);

    TypeId
    App::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::nnn::App")
	.SetGroupName ("Nnn")
	.SetParent<Application> ()
	.AddConstructor<App> ()
	.AddAttribute ("3NLifetime", "LifeTime for 3N PDUs",
		       StringValue ("3s"),
		       MakeTimeAccessor (&App::m_3n_lifetime),
		       MakeTimeChecker ())
	.AddAttribute ("IsMobile", "Flags that the App is mobile",
			 BooleanValue (false),
			 MakeBooleanAccessor(&App::m_isMobile),
			 MakeBooleanChecker ())

	.AddTraceSource ("ReceivedNULLps", "ReceivedNULLps",
	                 MakeTraceSourceAccessor (&App::m_receivedNULLps),
			 "ns3::nnn::App::ReceivedNULLpTracedCallback")

	.AddTraceSource ("ReceivedSOs", "ReceivedSOs",
	                 MakeTraceSourceAccessor (&App::m_receivedSOs),
			 "ns3::nnn::App::ReceivedSOTracedCallback")

	.AddTraceSource ("ReceivedDOs", "ReceivedDOs",
	                 MakeTraceSourceAccessor (&App::m_receivedDOs),
			 "ns3::nnn::App::ReceivedDOTracedCallback")

	.AddTraceSource ("ReceivedDUs", "ReceivedDUs",
	                 MakeTraceSourceAccessor (&App::m_receivedDUs),
			 "ns3::nnn::App::ReceivedDUTracedCallback")

	.AddTraceSource ("TransmittedNULLps", "TransmittedNULLps",
	                 MakeTraceSourceAccessor (&App::m_transmittedNULLps),
			 "ns3::nnn::App::TransmittedNULLpTracedCallback")

	.AddTraceSource ("TransmittedSOs", "TransmittedSOs",
	                 MakeTraceSourceAccessor (&App::m_transmittedSOs),
			 "ns3::nnn::App::TransmittedSOTracedCallback")

	.AddTraceSource ("TransmittedDOs", "TransmittedDOs",
	                 MakeTraceSourceAccessor (&App::m_transmittedDOs),
			 "ns3::nnn::App::TransmittedDOTracedCallback")

	.AddTraceSource ("TransmittedDUs", "TransmittedDUs",
	                 MakeTraceSourceAccessor (&App::m_transmittedDUs),
			 "ns3::nnn::App::TransmittedDUTracedCallback")
	;
      return tid;
    }

    App::App ()
    : m_active              (false)
    , m_face                (0)
    , m_has3Nname           (false)
    , m_current3Nname       (Create<NNNAddress> ())
    , m_isMobile            (false)
    , m_possibleDestination (Create<NNNAddress> ())
    {
    }

    App::~App ()
    {
    }

    void
    App::DoDispose (void)
    {
      NS_LOG_FUNCTION_NOARGS ();

      // Unfortunately, this causes SEGFAULT
      // The best reason I see is that apps are freed after nnn stack is removed
      // StopApplication ();
      Application::DoDispose ();
    }

    uint32_t
    App::GetId () const
    {
      if (m_face == 0)
	return (uint32_t)-1;
      else
	return m_face->GetId ();
    }

    void
    App::OnSO (Ptr<const SO> soObject)
    {
      NS_LOG_FUNCTION (this << soObject);
      m_receivedSOs (soObject, this, m_face);
    }

    void
    App::OnDO (Ptr<const DO> doObject)
    {
      NS_LOG_FUNCTION (this << doObject);
      m_receivedDOs (doObject, this, m_face);
    }

    void
    App::OnDU (Ptr<const DU> duObject)
    {
      NS_LOG_FUNCTION (this << duObject);
      m_receivedDUs (duObject, this, m_face);
    }

    void
    App::OnNULLp (Ptr<const NULLp> nullpObject)
    {
      NS_LOG_FUNCTION (this << nullpObject);
      m_receivedNULLps (nullpObject, this, m_face);
    }

    void
    App::GotName ()
    {
      NS_LOG_FUNCTION (this);
      // We know that the underlying ForwardingStrategy has a name

      // Flag the change
      m_has3Nname = true;

      // Update the 3N name used by the application to create PDUs
      m_current3Nname = GetNode ()->GetObject<ForwardingStrategy> ()->GetNode3NNamePtr();

      NS_LOG_INFO ("App will now use 3N name (" << *m_current3Nname << ")");
    }

    void
    App::NoName ()
    {
      NS_LOG_FUNCTION (this);

      m_has3Nname = false;
    }

    // Application Methods
    void
    App::StartApplication () // Called at time specified by Start
    {
      NS_LOG_FUNCTION_NOARGS ();

      NS_ASSERT (m_active != true);
      m_active = true;

      NS_ASSERT_MSG (GetNode ()->GetObject<L3Protocol> () != 0,
		     "3N stack should be installed on the node " << GetNode ());

      // step 1. Create a face
      m_face = CreateObject<AppFace> (/*Ptr<App> (this)*/this);

      // step 2. Add face to the 3N stack
      GetNode ()->GetObject<L3Protocol> ()->AddFace (m_face);

      // step 3. Enable face
      m_face->SetUp (true);

      // Step 4. Obtain information about the underlying forwarding strategy
      Ptr<ForwardingStrategy> fw = GetNode ()->GetObject<ForwardingStrategy> ();

      fw->TraceConnectWithoutContext("Got3NName", MakeCallback (&App::GotName, this));
      fw->TraceConnectWithoutContext("No3NName", MakeCallback (&App::NoName, this));

      // Step 5. Check if we happen to already have a name!
      if (fw->Has3NName())
	GotName ();
    }

    void
    App::StopApplication () // Called at time specified by Stop
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
