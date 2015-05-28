/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-app-face.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-app-face.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-app-face.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "../apps/nnn-icn-app.h"

#include "ns3/log.h"

#include "nnn-icn-app-face.h"
#include "nnn-pdus.h"
#include "nnn-icn-pdus.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.ICNAppFace");

  namespace nnn
  {
    NS_OBJECT_ENSURE_REGISTERED (ICNAppFace);

    TypeId
    ICNAppFace::GetTypeId ()
    {
      static TypeId tid = TypeId ("ns3::nnn::ICNAppFace")
		.SetParent<AppFace> ()
		.SetGroupName ("Nnn")
		;
      return tid;
    }

    ICNAppFace::ICNAppFace (Ptr<ICNApp> app)
    : m_app (app)
    {
      NS_LOG_FUNCTION (this << app);

      NS_ASSERT (m_app != 0);
      SetFlags (Face::APPLICATION);

      m_node = app->GetNode ();
      m_ifup = false;
      m_id = (uint32_t)-1;
      m_metric = 0;

      m_upstreamNULLpHandler = MakeNullCallback <void, Ptr<Face>, Ptr<NULLp> > ();
      m_upstreamSOHandler = MakeNullCallback< void, Ptr<Face>, Ptr<SO> > ();
      m_upstreamDOHandler = MakeNullCallback< void, Ptr<Face>, Ptr<DO> > ();
      m_upstreamENHandler = MakeNullCallback< void, Ptr<Face>, Ptr<EN> > ();
      m_upstreamAENHandler =MakeNullCallback< void, Ptr<Face>, Ptr<AEN> > ();
      m_upstreamRENHandler = MakeNullCallback< void, Ptr<Face>, Ptr<REN> > ();
      m_upstreamDENHandler = MakeNullCallback< void, Ptr<Face>, Ptr<DEN> > ();
      m_upstreamINFHandler = MakeNullCallback< void, Ptr<Face>, Ptr<INF> > ();
      m_upstreamDUHandler = MakeNullCallback< void, Ptr<Face>, Ptr<DU> > ();
      m_upstreamOENHandler = MakeNullCallback< void, Ptr<Face>, Ptr<OEN> > ();
    }

    ICNAppFace::~ICNAppFace ()
    {
      NS_LOG_FUNCTION_NOARGS ();
    }

    ICNAppFace::ICNAppFace ()
    {
    }

    ICNAppFace::ICNAppFace (const ICNAppFace &)
    {
    }

    ICNAppFace&
    ICNAppFace::operator= (const ICNAppFace &)
    {
      return *((ICNAppFace*)0);
    }

    bool
    ICNAppFace::SendInterest (Ptr<const Interest> interest)
    {
      NS_LOG_FUNCTION (this << interest);

      if (!IsUp ())
	{
	  return false;
	}

      if (interest->GetNack () > 0)
	m_app->OnNack (interest);
      else
	m_app->OnInterest (interest);

      return true;
    }

    bool
    ICNAppFace::SendData (Ptr<const Data> data)
    {
      NS_LOG_FUNCTION (this << data);

      if (!IsUp ())
	{
	  return false;
	}

      m_app->OnData (data);
      return true;
    }

    bool
    ICNAppFace::SendSO (Ptr<const SO> soObject)
    {
      NS_LOG_FUNCTION (this << soObject);

      if (!IsUp ())
	{
	  return false;
	}
      m_app->OnSO (soObject);
      return true;
    }

    bool
    ICNAppFace::SendNULLp (Ptr<const NULLp> nullpObject)
    {
      NS_LOG_FUNCTION (this << nullpObject);

      if (!IsUp ())
	{
	  return false;
	}

      m_app->OnNULLp (nullpObject);
      return true;
    }

    bool
    ICNAppFace::SendDO (Ptr<const DO> doObject)
    {
      NS_LOG_FUNCTION (this << doObject);

      if (!IsUp ())
	{
	  return false;
	}

      m_app->OnDO (doObject);
      return true;
    }

    bool
    ICNAppFace::SendDU (Ptr<const DU> duObject)
    {
      NS_LOG_FUNCTION (this << duObject);

      if (!IsUp ())
	{
	  return false;
	}

      m_app->OnDU (duObject);
      return true;
    }

    std::ostream&
    ICNAppFace::Print (std::ostream& os) const
    {
      os << "dev=local(" << GetId() << ")";
      return os;
    }
  } // namespace nnn
} // namespace ns3
