/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-en.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-en.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-en.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *          Zhu Li <philipszhuli1990@ruri.waseda.jp>
 */

#include "ns3/log.h"

#include "nnn-en.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("nnn.EN");

  namespace nnn
  {
    EN::EN ()
    : NNNPDU (EN_NNN, Seconds(0))
    , ENPDU ()
    {
    }

    EN::EN (std::vector<Address> signatures)
    : NNNPDU (EN_NNN, Seconds(0))
    , ENPDU ()
    {
    }

    EN::EN (const EN &en_p)
    {
      NS_LOG_FUNCTION("EN correct copy constructor");
      EN ();
      SetVersion (en_p.GetVersion ());
      SetLifetime (en_p.GetLifetime ());
      AddPoa (en_p.GetPoas ());
      SetWire (en_p.GetWire ());
    }

    void
    EN::Print (std::ostream &os) const
    {
      os << "<EN>"<< std::endl;
      NNNPDU::Print(os);
      ENPDU::Print(os);
      os << "</EN>" << std::endl;
    }
  } // namespace nnn
} // namespace ns3
