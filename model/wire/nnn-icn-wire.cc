/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright (c) 2015 Waseda University, Sato Laboratory
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-wire.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-wire.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-wire.cc. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#include "ns3/global-value.h"
#include "ns3/integer.h"

#include "nnn-icn-wire.h"
#include "ns3/wire-nnnsim-icn.h"
#include "ns3/nnn-icn-header-helper.h"

#include "ns3/nnnsim-icn-data.h"
#include "ns3/nnnsim-icn-interest.h"

ICN_NAMESPACE_BEGIN

static
GlobalValue g_wireFormat ("icn::WireFormat",
                          "Default wire format for ICN.  ICN will be accepting packets "
                          "in any supported packet formats, but if encoding requested, it will "
                          "use default wire format to encode (0 for NDNSIM style (default))",
                          IntegerValue (Wire::WIRE_FORMAT_NDNSIM),
                          MakeIntegerChecker<int32_t> ());

static inline uint32_t
GetWireFormat ()
{
  static int32_t format = -1;
  if (format >= 0)
    return format;

  IntegerValue value;
  g_wireFormat.GetValue (value);
  format = value.Get ();

  return format;
}

Ptr<Packet>
Wire::FromInterest (Ptr<const nnn::Interest> interest, int8_t wireFormat/* = WIRE_FORMAT_DEFAULT*/)
{
  if (wireFormat == WIRE_FORMAT_DEFAULT)
    wireFormat = GetWireFormat ();

  if (wireFormat == WIRE_FORMAT_NDNSIM)
    return wire::icnSIM::Interest::ToWire (interest);
  else
    {
      NS_FATAL_ERROR ("Unsupported format requested");
      return 0;
    }
}

Ptr<nnn::Interest>
Wire::ToInterest (Ptr<Packet> packet, int8_t wireFormat/* = WIRE_FORMAT_AUTODETECT*/)
{
  if (wireFormat == WIRE_FORMAT_AUTODETECT)
    {
      try
        {
          HeaderHelper::Type type = HeaderHelper::GetICNHeaderType (packet);
          switch (type)
            {
            case HeaderHelper::INTEREST_ICN:
              {
                return wire::icnSIM::Interest::FromWire (packet);
              }
            case HeaderHelper::CONTENT_OBJECT_ICN:
            default:
              NS_FATAL_ERROR ("Unsupported format");
              return 0;
            }

          // exception will be thrown if packet is not recognized
        }
      catch (UnknownHeaderException)
        {
          NS_FATAL_ERROR ("Unknown NDN header");
          return 0;
        }
    }
  else
    {
      if (wireFormat == WIRE_FORMAT_NDNSIM)
        return wire::icnSIM::Interest::FromWire (packet);
      else
        {
          NS_FATAL_ERROR ("Unsupported format requested");
          return 0;
        }
    }
}

Ptr<Packet>
Wire::FromData (Ptr<const nnn::Data> data, int8_t wireFormat/* = WIRE_FORMAT_DEFAULT*/)
{
  if (wireFormat == WIRE_FORMAT_DEFAULT)
    wireFormat = GetWireFormat ();

  if (wireFormat == WIRE_FORMAT_NDNSIM)
    return wire::icnSIM::Data::ToWire (data);
  else
    {
      NS_FATAL_ERROR ("Unsupported format requested");
      return 0;
    }
}

Ptr<nnn::Data>
Wire::ToData (Ptr<Packet> packet, int8_t wireFormat/* = WIRE_FORMAT_AUTODETECT*/)
{
  if (wireFormat == WIRE_FORMAT_AUTODETECT)
    {
      try
        {
          HeaderHelper::Type type = HeaderHelper::GetICNHeaderType (packet);
          switch (type)
            {
            case HeaderHelper::CONTENT_OBJECT_ICN:
              {
                return wire::icnSIM::Data::FromWire (packet);
              }
            case HeaderHelper::INTEREST_ICN:
            default:
              NS_FATAL_ERROR ("Unsupported format");
              return 0;
            }

          // exception will be thrown if packet is not recognized
        }
      catch (UnknownHeaderException)
        {
          NS_FATAL_ERROR ("Unknown ICN header");
          return 0;
        }
    }
  else
    {
      if (wireFormat == WIRE_FORMAT_NDNSIM)
        return wire::icnSIM::Data::FromWire (packet);
      else
        {
          NS_FATAL_ERROR ("Unsupported format requested");
          return 0;
        }
    }
}


std::string
Wire::FromInterestStr (Ptr<const nnn::Interest> interest, int8_t wireFormat/* = WIRE_FORMAT_DEFAULT*/)
{
  Ptr<Packet> pkt = FromInterest (interest, wireFormat);
  std::string wire;
  wire.resize (pkt->GetSize ());
  pkt->CopyData (reinterpret_cast<uint8_t*> (&wire[0]), wire.size ());

  return wire;
}

Ptr<nnn::Interest>
Wire::ToInterestStr (const std::string &wire, int8_t type/* = WIRE_FORMAT_AUTODETECT*/)
{
  Ptr<Packet> pkt = Create<Packet> (reinterpret_cast<const uint8_t*> (&wire[0]), wire.size ());
  return ToInterest (pkt, type);
}

std::string
Wire::FromDataStr (Ptr<const nnn::Data> data, int8_t wireFormat/* = WIRE_FORMAT_DEFAULT*/)
{
  Ptr<Packet> pkt = FromData (data, wireFormat);
  std::string wire;
  wire.resize (pkt->GetSize ());
  pkt->CopyData (reinterpret_cast<uint8_t*> (&wire[0]), wire.size ());

  return wire;
}

Ptr<nnn::Data>
Wire::ToDataStr (const std::string &wire, int8_t type/* = WIRE_FORMAT_AUTODETECT*/)
{
  Ptr<Packet> pkt = Create<Packet> (reinterpret_cast<const uint8_t*> (&wire[0]), wire.size ());
  return ToData (pkt, type);
}

std::string
Wire::FromName (Ptr<const Name> name, int8_t wireFormat/* = WIRE_FORMAT_DEFAULT*/)
{

  if (wireFormat == WIRE_FORMAT_DEFAULT)
    wireFormat = GetWireFormat ();

  if (wireFormat == WIRE_FORMAT_NDNSIM)
    {
      Buffer buf;
      buf.AddAtStart (wire::IcnSim::SerializedSizeName (*name));
      Buffer::Iterator i = buf.Begin ();

      wire::IcnSim::SerializeName (i, *name);

      std::string wire;
      wire.resize (buf.GetSize ());
      buf.CopyData (reinterpret_cast<uint8_t *>(&wire[0]), wire.size ());

      return wire;
    }
  else
    {
      NS_FATAL_ERROR ("Unsupported format requested");
    }
}

Ptr<Name>
Wire::ToName (const std::string &name, int8_t wireFormat/* = WIRE_FORMAT_DEFAULT*/)
{
  Buffer buf;
  buf.AddAtStart (name.size ());
  Buffer::Iterator i = buf.Begin ();
  i.Write (reinterpret_cast<const uint8_t *> (&name[0]), name.size ());

  i = buf.Begin ();

  if (wireFormat == WIRE_FORMAT_DEFAULT)
    wireFormat = GetWireFormat ();

  if (wireFormat == WIRE_FORMAT_NDNSIM)
    {
      return wire::IcnSim::DeserializeName (i);
    }
  else
    {
      NS_FATAL_ERROR ("Unsupported format requested");
    }
}

ICN_NAMESPACE_END
