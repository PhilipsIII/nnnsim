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

#ifndef NNN_ICN_APP_FACE_H
#define NNN_ICN_APP_FACE_H

#include "ns3/traced-callback.h"

#include "ns3/nnn-app-face.h"

namespace ns3
{
  class Packet;

  namespace nnn
  {
    class Data;
    class Interest;

    class ICNApp;

    /**
     * \ingroup nnn-face
     * \brief Implementation of 3N ICN capable application Face
     *
     * This class defines basic functionality of Face. Face is core
     * component responsible for actual delivery of data packet to and
     * from 3N stack
     *
     * \see AppFace, NetDeviceFace
     */
    class ICNAppFace  : public AppFace
    {
    public:
      static TypeId
      GetTypeId ();


      /**
       * \brief Default constructor
       */
      ICNAppFace (Ptr<ICNApp> app);
      virtual ~ICNAppFace();

      ////////////////////////////////////////////////////////////////////
      // methods overloaded from Face
      virtual bool
      SendInterest (Ptr<const Interest> interest);

      virtual bool
      SendData (Ptr<const Data> data);

      virtual bool
      SendNULLp (Ptr<const NULLp> nullpObject);

      virtual bool
      SendSO (Ptr<const SO> soObject);

      virtual bool
      SendDO (Ptr<const DO> doObject);

      virtual bool
      SendDU (Ptr<const DU> duObject);

    public:
      virtual std::ostream&
      Print (std::ostream &os) const;
      ////////////////////////////////////////////////////////////////////

    private:
      ICNAppFace ();
      ICNAppFace (const ICNAppFace &); ///< \brief Disabled copy constructor
      ICNAppFace& operator= (const ICNAppFace &); ///< \brief Disabled copy operator

    private:
      Ptr<ICNApp> m_app;
    };
  } // namespace nnn
} // namespace ns3

#endif // NNN_ICN_APP_FACE_H
