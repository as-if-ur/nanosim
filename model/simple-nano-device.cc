/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013,2014 TELEMATICS LAB, DEI - Politecnico di Bari
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Giuseppe Piro <peppe@giuseppepiro.com>, <g.piro@poliba.it>
 */



#include "ns3/log.h"
#include "ns3/queue.h"
#include "ns3/simulator.h"
#include "ns3/enum.h"
#include "ns3/boolean.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/channel.h"
#include "simple-nano-device.h"
#include "nano-spectrum-phy.h"
#include "nano-mac-entity.h"
#include "nano-mac-header.h"
#include "ns3/seq-ts-header.h"
#include "ns3/simulator.h"
#include "nano-routing-entity.h"
#include "message-process-unit.h"


NS_LOG_COMPONENT_DEFINE ("SimpleNanoDevice");

namespace ns3 {


NS_OBJECT_ENSURE_REGISTERED (SimpleNanoDevice);

TypeId
SimpleNanoDevice::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SimpleNanoDevice")
    .SetParent<NetDevice> ()
    .AddConstructor<SimpleNanoDevice> ()
  ;
  return tid;
}

SimpleNanoDevice::SimpleNanoDevice ()
{
  NS_LOG_FUNCTION (this);
  m_node = 0;
  m_mac = 0;
  m_phy = 0;
  m_l3 = 0;
  m_mpu = 0;
}

SimpleNanoDevice::~SimpleNanoDevice ()
{
  NS_LOG_FUNCTION (this);
}

void
SimpleNanoDevice::DoDispose ()
{
  NS_LOG_FUNCTION (this);
  m_node = 0;
  m_mac = 0;
  m_phy = 0;
  m_l3 = 0;
  m_mpu = 0;
  NetDevice::DoDispose ();
}


void
SimpleNanoDevice::SetIfIndex (const uint32_t index)
{
  NS_LOG_FUNCTION (index);
  m_ifIndex = index;
}

uint32_t
SimpleNanoDevice::GetIfIndex (void) const
{
  NS_LOG_FUNCTION (this);
  return m_ifIndex;
}

bool
SimpleNanoDevice::SetMtu (uint16_t mtu)
{
  NS_LOG_FUNCTION (mtu);
  return (mtu == 0);
}

uint16_t
SimpleNanoDevice::GetMtu (void) const
{
  NS_LOG_FUNCTION (this);
  return 0;
}

Ptr<Channel>
SimpleNanoDevice::GetChannel (void) const
{
  NS_LOG_FUNCTION (this);
  return 0;
}

void
SimpleNanoDevice::SetAddress (Address address)
{
  NS_LOG_FUNCTION (this);
}

Address
SimpleNanoDevice::GetAddress (void) const
{
  NS_LOG_FUNCTION (this);
  return Address ();
}

bool
SimpleNanoDevice::IsBroadcast (void) const
{
  NS_LOG_FUNCTION (this);
  return false;
}

Address
SimpleNanoDevice::GetBroadcast (void) const
{
  NS_LOG_FUNCTION (this);
  return Address ();
}

bool
SimpleNanoDevice::IsMulticast (void) const
{
  NS_LOG_FUNCTION (this);
  return false;
}

Address
SimpleNanoDevice::GetMulticast (Ipv4Address addr) const
{
  NS_LOG_FUNCTION (addr);
  return Address ();
}

Address
SimpleNanoDevice::GetMulticast (Ipv6Address addr) const
{
  NS_LOG_FUNCTION (addr);
  return Address ();
}

bool
SimpleNanoDevice::IsPointToPoint (void) const
{
  NS_LOG_FUNCTION (this);
  return false;
}

bool
SimpleNanoDevice::IsBridge (void) const
{
  NS_LOG_FUNCTION (this);
  return false;
}


Ptr<Node>
SimpleNanoDevice::GetNode (void) const
{
  NS_LOG_FUNCTION (this);
  return m_node;
}

void
SimpleNanoDevice::SetNode (Ptr<Node> node)
{
  NS_LOG_FUNCTION (node);
  m_node = node;
}

bool
SimpleNanoDevice::NeedsArp (void) const
{
  NS_LOG_FUNCTION (this);
  return false;
}

bool
SimpleNanoDevice::IsLinkUp (void) const
{
  NS_LOG_FUNCTION (this);
  return false;
}

void
SimpleNanoDevice::AddLinkChangeCallback (Callback<void> callback)
{
  NS_LOG_FUNCTION (&callback);
}

void
SimpleNanoDevice::SetReceiveCallback (NetDevice::ReceiveCallback cb)
{
  NS_LOG_FUNCTION (&cb);
}

void
SimpleNanoDevice::SetPromiscReceiveCallback (NetDevice::PromiscReceiveCallback cb)
{
  NS_LOG_FUNCTION (&cb);
}

bool
SimpleNanoDevice::SupportsSendFrom () const
{
  NS_LOG_FUNCTION (this);
  return false;
}

bool
SimpleNanoDevice::Send (Ptr<Packet> packet,const Address& dest, uint16_t protocolNumber)
{
  NS_LOG_FUNCTION (packet << dest << protocolNumber);
  return false;
}

bool
SimpleNanoDevice::SendFrom (Ptr<Packet> packet, const Address& src, const Address& dest, uint16_t protocolNumber)
{
  NS_LOG_FUNCTION (packet << src << dest << protocolNumber);
  return false;
}

void
SimpleNanoDevice::SetPhy (Ptr<NanoSpectrumPhy> phy)
{
  NS_LOG_FUNCTION (this << phy);
  m_phy = phy;
}

Ptr<NanoSpectrumPhy>
SimpleNanoDevice::GetPhy () const
{
  NS_LOG_FUNCTION (this);
  return m_phy;
}


void
SimpleNanoDevice::SendPacket (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p << "node" << GetNode ()->GetId ());
  GetL3 ()->SendPacket (p);
}

void
SimpleNanoDevice::ReceivePacket (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  GetL3 ()->ReceivePacket (p);
}

void
SimpleNanoDevice::SetMac (Ptr<NanoMacEntity> mac)
{
  NS_LOG_FUNCTION (this);
  m_mac = mac;
}

Ptr<NanoMacEntity>
SimpleNanoDevice::GetMac () const
{
  NS_LOG_FUNCTION (this);
  return m_mac;
}

void
SimpleNanoDevice::SetL3 (Ptr<NanoRoutingEntity> l3)
{
  NS_LOG_FUNCTION (this);
  m_l3 = l3;
}

Ptr<NanoRoutingEntity>
SimpleNanoDevice::GetL3 () const
{
  NS_LOG_FUNCTION (this);
  return m_l3;
}

void
SimpleNanoDevice::SetMessageProcessUnit (Ptr<MessageProcessUnit> mpu)
{
  NS_LOG_FUNCTION (this);
  m_mpu = mpu;
}

Ptr<MessageProcessUnit>
SimpleNanoDevice::GetMessageProcessUnit (void)
{
  NS_LOG_FUNCTION (this);
  return m_mpu;
}

} // namespace ns3
