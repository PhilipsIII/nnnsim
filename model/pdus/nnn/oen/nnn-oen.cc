/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-oen.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-oen.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-oen.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/log.h"

#include "nnn-oen.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.OEN");

  namespace nnn
  {
    OEN::OEN ()
    : NNNPDU (OEN_NNN, Seconds(0))
    , ENPDU ()
    {
    }

    OEN::OEN (Ptr<NNNAddress> name)
    : NNNPDU (OEN_NNN, Seconds(0))
    , ENPDU ()
    {
      SetName (name);
    }

    OEN::OEN (const NNNAddress &name)
    : NNNPDU (OEN_NNN, Seconds (0))
    , ENPDU ()
    {
      SetName (name);
    }

    OEN::~OEN ()
    {
    }

    OEN::OEN (const OEN &oen_p)
    {
      NS_LOG_FUNCTION("OEN correct copy constructor");
      OEN ();
      SetVersion (oen_p.GetVersion ());
      SetLifetime (oen_p.GetLifetime ());
      SetLeasetime (oen_p.GetLeasetime ());
      AddPoa (oen_p.GetPoas ());
      SetName (oen_p.GetName ());
      AddPersonalPoa (oen_p.GetPersonalPoas ());
      SetSrcName (oen_p.GetSrcName ());
      SetWire (oen_p.GetWire ());
    }

    const NNNAddress&
    OEN::GetName () const
    {
      if (m_name == 0) throw OENException ();
      return *m_name;
    }

    Ptr<const NNNAddress>
    OEN::GetNamePtr () const
    {
      return m_name;
    }

    void
    OEN::SetName(Ptr<NNNAddress> name)
    {
      m_name = name;
      SetWire (0);
    }

    void
    OEN::SetName (const NNNAddress &name)
    {
      m_name = Create<NNNAddress> (name);
      SetWire (0);
    }

    const NNNAddress&
    OEN::GetSrcName () const
    {
      if (m_src_name == 0) throw OENException ();
      return *m_src_name;
    }

    Ptr<const NNNAddress>
    OEN::GetSrcNamePtr () const
    {
      return m_src_name;
    }

    void
    OEN::SetSrcName(Ptr<NNNAddress> name)
    {
      m_src_name = name;
      SetWire (0);
    }

    void
    OEN::SetSrcName (const NNNAddress &name)
    {
      m_src_name = Create<NNNAddress> (name);
      SetWire (0);
    }

    Time
    OEN::GetLeasetime() const
    {
      return m_lease;
    }

    void
    OEN::SetLeasetime (Time lease)
    {
      m_lease = lease;
    }

    void
    OEN::Print (std::ostream &os) const
    {
      uint32_t num = GetPersonalNumPoa ();

      os << "<OEN>" << std::endl;
      NNNPDU::Print(os);
      os << "  <Name>" << GetName () << "</Name>" << std::endl;
      os << "  <Lease>" << GetLeasetime () << "</Lease>" << std::endl;
      ENPDU::Print(os);

      os << "  <Giving Name>" << GetSrcName () << "</Giving Name>" << std::endl;
      os << "  <Personal POA Num>" << num << "</Personal POA Num>"<< std::endl;
      for (int i = 0; i < num; i++)
	{
	  os << "  <Personal POA" << i << ">" << GetPersonalOnePoa (i) << "</Personal POA" << i << ">"<< std::endl;
	}
      os << "</OEN>" << std::endl;
    }

    void
    OEN::AddPersonalPoa (Address signature)
    {
      m_personal_poas.push_back(signature);
    }

    void
    OEN::AddPersonalPoa (std::vector<Address> signatures)
    {
      m_personal_poas.insert(m_personal_poas.end (), signatures.begin (), signatures.end ());
    }

    uint32_t
    OEN::GetPersonalNumPoa () const
    {
      return m_personal_poas.size();
    }

    std::vector<Address>
    OEN::GetPersonalPoas () const
    {
      return m_personal_poas;
    }

    Address
    OEN::GetPersonalOnePoa (uint32_t index) const
    {
      if (index < GetPersonalNumPoa ())
	return m_personal_poas[index];
      else
	return Address();
    }
  } /* namespace nnn */
} /* namespace ns3 */
