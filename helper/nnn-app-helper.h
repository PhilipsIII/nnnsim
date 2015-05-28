/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2014 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-app-helper.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-app-helper.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-app-helper.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *   Original template made for ndnSIM for University of California,
 *   Los Angeles by Ilya Moiseenko
 */

#ifndef NNN_APP_HELPER_H
#define NNN_APP_HELPER_H

#include "ns3/application-container.h"
#include "ns3/attribute.h"
#include "ns3/node-container.h"
#include "ns3/object-factory.h"
#include "ns3/ptr.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn-helpers
     * \brief A helper to make it easier to instantiate 3N applications
     * on a set of nodes.
     */
    class AppHelper
    {
    public:

      /**
       * \brief Create an AppHelper to make it easier to work with 3N Apps
       *
       * \param app Class of the application
       */
      AppHelper (const std::string &prefix);

      /**
       * @brief Set the prefix consumer will be requesting
       */
      void
      SetPrefix (const std::string &prefix);

      /**
       * \brief Helper function used to set the underlying application attributes.
       *
       * \param name the name of the application attribute to set
       * \param value the value of the application attribute to set
       */
      void SetAttribute (std::string name, const AttributeValue &value);

      /**
       * Install an ns3::nnn::App on each node of the input container
       * configured with all the attributes set with SetAttribute.
       *
       * \param c NodeContainer of the set of nodes on which an App
       * will be installed.
       * \returns Container of Ptr to the applications installed.
       */
      ApplicationContainer Install (NodeContainer c);

      /**
       * Install an ns3::nnn::App on the node configured with all the
       * attributes set with SetAttribute.
       *
       * \param node The node on which an App will be installed.
       * \returns Container of Ptr to the applications installed.
       */
      ApplicationContainer Install (Ptr<Node> node);

      /**
       * Install an ns3::nnn::App on the node configured with all the
       * attributes set with SetAttribute.
       *
       * \param nodeName The node on which an NnnConsumer will be installed.
       * \returns Container of Ptr to the applications installed.
       */
      ApplicationContainer Install (std::string nodeName);

    private:
      /**
       * \internal
       * Install an ns3::nnn::App on the node configured with all the
       * attributes set with SetAttribute.
       *
       * \param node The node on which an NdnConsumer will be installed.
       * \returns Ptr to the application installed.
       */
      Ptr<Application> InstallPriv (Ptr<Node> node);
      ObjectFactory m_factory;
    };

  } // namespace nnn
} // namespace ns3

#endif // NNN_APP_HELPER_H
