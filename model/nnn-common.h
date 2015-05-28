/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-common.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-common.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-common.h.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Zhu Li <phillipszhuli1990@gmail.com>
 *          Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *   Original template made for ndnSIM for University of California,
 *   Los Angeles by Ilya Moiseenko
 */
#ifndef NNN_COMMON_H
#define NNN_COMMON_H

#include "ns3/nstime.h"
#include "ns3/simulator.h"

#define NNNSIM_MODE 1

#define NNN_NAMESPACE_BEGIN  namespace ns3 { namespace nnn {
#define NNN_NAMESPACE_END    } /*nnn*/ } /*ns3*/

/**
 * @brief NS-3 namespace
 */
namespace ns3
{

  /**
   * @brief 3N namespace
   */
  namespace nnn
  {
  }

}

NNN_NAMESPACE_BEGIN

typedef Time TimeInterval;

namespace time
{

  inline Time
  NowUnixTimestamp ()
  {
    return Simulator::Now ();
  }

}

NNN_NAMESPACE_END

#endif // NNN_COMMON_H
