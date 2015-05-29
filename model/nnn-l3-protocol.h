/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-l3-protocol.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-l3-protocol.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-l3-protocol.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Zhu Li <phillipszhuli1990@gmail.com>
 *          Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef NNN_L3_PROTOCOL_H
#define NNN_L3_PROTOCOL_H

#include <vector>

#include "ns3/ptr.h"

namespace ns3 {

  class Packet;
  class NetDevice;
  class Node;
  class Header;

  namespace nnn {

    class Face;
    class ForwardingStrategy;

    /**
     * \defgroup nnn nnnSIM: 3N simulation module
     *
     * This is a modular implementation of 3N protocol for NS-3
     */
    /**
     * \ingroup nnn
     * \brief Implementation network-layer of 3N stack
     *
     * This class defines the API to manipulate the following aspects of
     * the 3N stack implementation:
     * -# register a face (Face-derived object) for use by the 3N
     *    layer
     *
     * Each Face-derived object has conceptually a single 3N
     * interface associated with it.
     *
     * In addition, this class defines 3N PDU coding constants
     *
     * \see Face, ForwardingStrategy
     */
    class L3Protocol :
	public Object
    {
    public:
      typedef std::vector<Ptr<Face> > FaceList;

      /**
       * \brief Interface ID
       *
       * \return interface ID
       */
      static TypeId GetTypeId ();

      static const uint16_t ETHERNET_FRAME_TYPE; ///< @brief Ethernet Frame Type of 3N
      //static const uint16_t IP_STACK_PORT;       ///< @brief TCP/UDP port for 3N stack
      // static const uint16_t IP_PROTOCOL_TYPE;    ///< \brief IP protocol type of 3N

      /**
       * \brief Default constructor. Creates an empty stack without forwarding strategy set
       */
      L3Protocol ();
      virtual ~L3Protocol  ();

      /**
       * \brief Add face to 3N stack
       *
       * \param face smart pointer to Face-derived object
       * (LocalFace, NetDeviceFace, UdpFace) \returns the
       * index of the interface added.
       *
       * \see LocalFace, NetDeviceFace, UdpFace
       */
      virtual uint32_t
      AddFace (const Ptr<Face> &face);

      /**
       * \brief Get current number of faces added to 3N stack
       *
       * \returns the number of faces
       */
      virtual uint32_t
      GetNFaces () const;

      /**
       * \brief Get face by face index
       * \param face The face number (number in face list)
       * \returns The Face associated with the 3N face number.
       */
      virtual Ptr<Face>
      GetFace (uint32_t face) const;

      /**
       * \brief Get face by face ID
       * \param face The face ID number
       * \returns The Face associated with the 3N face number.
       */
      virtual Ptr<Face>
      GetFaceById (uint32_t face) const;

      /**
       * \brief Remove face from 3N stack (remove callbacks)
       */
      virtual void
      RemoveFace (Ptr<Face> face);

      /**
       * \brief Get face for NetDevice
       */
      virtual Ptr<Face>
      GetFaceByNetDevice (Ptr<NetDevice> netDevice) const;

    protected:
      virtual void DoDispose (void); ///< @brief Do cleanup

      /**
       * This function will notify other components connected to the node that a new stack member is now connected
       * This will be used to notify Layer 3 protocol of layer 4 protocol stack to connect them together.
       */
      virtual void NotifyNewAggregate ();

    private:
      L3Protocol (const L3Protocol  &); ///< copy constructor is disabled
      L3Protocol  &operator = (const L3Protocol  &); ///< copy operator is disabled

    private:
      uint32_t m_faceCounter; ///< \brief counter of faces. Increased every time a new face is added to the stack
      FaceList m_faces; ///< \brief list of faces that belongs to 3N stack on this node

      // These objects are aggregated, but for optimization, get them here
      Ptr<Node> m_node; ///< \brief node on which 3N stack is installed
      Ptr<ForwardingStrategy> m_forwardingStrategy; ///< \brief smart pointer to the selected forwarding strategy
    };
  } // namespace nnn
} // namespace ns3

#endif /* NNN_L3_PROTOCOL_H */
