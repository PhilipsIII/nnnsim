/** -*- Mode:C++; c-file-style:"gnu"; -*- */
/* 
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-common.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-common.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-common.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */
#ifndef ICN_COMMON_H
#define ICN_COMMON_H

#include "ns3/nstime.h"
#include "ns3/simulator.h"

#define ICNSIM_MODE 1

#define ICN_NAMESPACE_BEGIN  namespace ns3 { namespace icn {
#define ICN_NAMESPACE_END    } /*icn*/ } /*ns3*/

ICN_NAMESPACE_BEGIN

typedef Time TimeInterval;

namespace time
{

  inline Time
  NowUnixTimestamp ()
  {
    return Simulator::Now ();
  }

}

ICN_NAMESPACE_END

#endif // ICN_COMMON_H
