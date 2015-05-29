/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-fib.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-fib.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-fib.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/names.h"
#include "ns3/node.h"

#include "nnn-fib.h"

namespace ns3
{
  namespace nnn
  {
    TypeId
    Fib::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::nnn::Fib") // cheating ns3 object system
	.SetParent<Object> ()
	.SetGroupName ("Nnn")
	;
      return tid;
    }

    std::ostream&
    operator<< (std::ostream& os, const Fib &fib)
    {
      os << "Node " << Names::FindName (fib.GetObject<Node>()) << "\n";
      os << "  Dest prefix      Interfaces(Costs)                  \n";
      os << "+-------------+--------------------------------------+\n";

      fib.Print (os);
      return os;
    }

  } // namespace nnn
} // namespace ns3
