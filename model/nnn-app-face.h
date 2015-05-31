/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-app-face.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-app-face.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-app-face.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *   Original template made for ndnSIM for University of California,
 *   Los Angeles by Ilya Moiseenko
 */
#ifndef NNN_APP_FACE_H
#define NNN_APP_FACE_H

#include "ns3/nnn-face.h"
#include "ns3/traced-callback.h"

namespace ns3
{
  class Packet;

  namespace nnn
  {
    class NULLp;
    class SO;
    class DO;
    class DU;

    class App;

    /**
     * \ingroup nnn-face
     * \brief Implementation of 3N application Face
     *
     * This class defines basic functionality of 3N Face. Face is core
     * component responsible for actual delivery of data packet to and
     * from 3N stack
     *
     * \see App ns3::nnn:NetDeviceFace
     */
    class AppFace  : public Face
    {
    public:
      static TypeId
      GetTypeId ();

      /**
       * \brief Default constructor
       */
      AppFace ();

      AppFace (Ptr<App> app);
      virtual ~AppFace();

      ////////////////////////////////////////////////////////////////////
      // methods overloaded from Face
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
      AppFace (const AppFace &); ///< \brief Disabled copy constructor
      AppFace& operator= (const AppFace &); ///< \brief Disabled copy operator

    private:
      Ptr<App> m_app;
    };

  } // namespace nnn
} // namespace ns3

#endif // NNN_APP_FACE_H
