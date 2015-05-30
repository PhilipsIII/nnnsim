/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-aen.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-aen.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-aen.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include <ns3-dev/ns3/log.h>

#include "nnn-aen.h"

NS_LOG_COMPONENT_DEFINE ("nnn.AEN");

namespace ns3
{
  namespace nnn
  {
    AEN::AEN ()
    : NNNPDU (AEN_NNN, Seconds(0))
    , ENPDU ()
    {
    }

    AEN::AEN (Ptr<NNNAddress> name)
    : NNNPDU (AEN_NNN, Seconds (0))
    , ENPDU ()
    , m_name     (name)
    {
    }

    AEN::AEN (const NNNAddress &name)
    : NNNPDU (AEN_NNN, Seconds (0))
    , ENPDU ()
    , m_name     (Create<NNNAddress> (name))
    {
    }

    AEN::AEN (const AEN &aen_p)

    {
      NS_LOG_FUNCTION("AEN correct copy constructor");
      AEN ();
      SetVersion (aen_p.GetVersion ());
      SetLifetime (aen_p.GetLifetime ());
      AddPoa (aen_p.GetPoas ());
      SetName (aen_p.GetName ());
      SetLeasetime (aen_p.GetLeasetime ());
      SetWire (aen_p.GetWire ());
    }

    const NNNAddress&
    AEN::GetName () const
    {
      if (m_name == 0) throw AENException ();
      return *m_name;
    }

    Ptr<const NNNAddress>
    AEN::GetNamePtr () const
    {
      return m_name;
    }

    void
    AEN::SetName (Ptr<NNNAddress> name)
    {
      m_name = name;
      SetWire (0);
    }

    void
    AEN::SetName (const NNNAddress &name)
    {
      m_name = Create<NNNAddress> (name);
      SetWire (0);
    }

    Time
    AEN::GetLeasetime () const
    {
      return m_lease;
    }

    void
    AEN::SetLeasetime (Time lease)
    {
      m_lease = lease;
    }

    void
    AEN::Print (std::ostream &os) const
    {
      os << "<AEN>" << std::endl;
      NNNPDU::Print (os);
      os << "  <Name>" << GetName () << "</Name>" << std::endl;
      os << "  <Lease>" << GetLeasetime () << "</Lease>" << std::endl;
      ENPDU::Print(os);
      os << "</AEN>"  << std::endl;
    }
  } // namespace nnn
} // namespace ns3
