/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-en-pdus.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-en-pdus.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-en-pdus.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "nnn-en-pdus.h"

namespace ns3
{
  namespace nnn
  {

    ENPDU::ENPDU ()
    : NNNPDU ()
    , m_poas (std::vector<Address> ())
    {
    }

    ENPDU::~ENPDU ()
    {
    }

    void
    ENPDU::AddPoa (Address signature)
    {
      m_poas.push_back(signature);
    }

    void
    ENPDU::AddPoa (std::vector<Address> signatures)
    {
      m_poas.insert(m_poas.end (), signatures.begin (), signatures.end ());
    }

    uint32_t
    ENPDU::GetNumPoa () const
    {
      return m_poas.size();
    }

    std::vector<Address>
    ENPDU::GetPoas () const
    {
      return m_poas;
    }

    Address
    ENPDU::GetOnePoa (uint32_t index) const
    {
      if (index < GetNumPoa ())
	return m_poas[index];
      else
	return Address();
    }

    void
    ENPDU::Print(std::ostream &os) const
    {
      uint32_t num = GetNumPoa ();

      os << "  <POA Num>" << num << "</POA Num>"<< std::endl;
      for (uint32_t i = 0; i < num; i++)
	{
	  os << "  <POA" << i << ">" << GetOnePoa(i) << "</POA" << i << ">"<< std::endl;
	}
    }
  } /* namespace nnn */
} /* namespace ns3 */
