/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-ren.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-ren.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-ren.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"
#include "ns3/unused.h"

#include "nnn-ren.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.REN");

  namespace nnn
  {
    REN::REN ()
    : NNNPDU (REN_NNN, Seconds (0))
    , ENPDU ()
    , m_re_lease (Seconds (0))
    {
    }

    REN::REN (Ptr<NNNAddress> name)
    : NNNPDU (REN_NNN, Seconds (0))
    , ENPDU ()
    , m_name     (name)
    , m_re_lease (Seconds (0))
    {
    }

    REN::REN (const NNNAddress &name)
    : NNNPDU (REN_NNN, Seconds (0))
    , ENPDU ()
    , m_re_lease (Seconds (0))
    {
      SetName (name);
    }

    REN::REN (const REN &ren_p)
    {
      NS_LOG_FUNCTION("REN correct copy constructor");
      REN ();
      SetVersion (ren_p.GetVersion ());
      SetLifetime (ren_p.GetLifetime ());
      AddPoa (ren_p.GetPoas ());
      SetRemainLease (ren_p.GetRemainLease ());
      SetName (ren_p.GetName ());
      SetWire (ren_p.GetWire ());
    }

    const NNNAddress&
    REN::GetName () const
    {
      if (m_name == 0) throw RENException ();
      return *m_name;
    }

    Ptr<const NNNAddress>
    REN::GetNamePtr () const
    {
      return m_name;
    }

    void
    REN::SetName (Ptr<NNNAddress> name)
    {
      m_name = name;
      m_wire = 0;
    }

    void
    REN::SetName (const NNNAddress &name)
    {
      m_name = Create<NNNAddress> (name);
      m_wire = 0;
    }

    Time
    REN::GetRemainLease () const
    {
      return m_re_lease;
    }

    void
    REN::SetRemainLease (Time ex_lease)
    {
      m_re_lease = ex_lease;
    }

    void
    REN::Print (std::ostream &os) const
    {
      os << "<REN>" << std::endl;
      NNNPDU::Print(os);
      os << "  <Name>" << GetName () << "</Name>" << std::endl;
      os << "  <RLease>" << GetRemainLease () << "</RLease>" << std::endl;
      ENPDU::Print(os);
      os << "</REN>" << std::endl;
    }
  } // namespace nnn
} // namespace ns3
