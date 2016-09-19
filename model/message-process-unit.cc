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


#include "message-process-unit.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "ns3/packet.h"
#include "simple-nano-device.h"
#include "nano-mac-queue.h"
#include "nano-spectrum-phy.h"
#include "nano-mac-header.h"
#include "ns3/seq-ts-header.h"
#include "ns3/simulator.h"
#include "ns3/nano-l3-header.h"

NS_LOG_COMPONENT_DEFINE ("MessageProcessUnit");

namespace ns3 {


NS_OBJECT_ENSURE_REGISTERED (MessageProcessUnit);

TypeId MessageProcessUnit::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MessageProcessUnit")
    .SetParent<Object> ()
    .AddTraceSource ("outTX",  "outTX",  MakeTraceSourceAccessor (&MessageProcessUnit::m_outTX))
    .AddTraceSource ("outRX",  "outRX",  MakeTraceSourceAccessor (&MessageProcessUnit::m_outRX));
;
  return tid;
}


MessageProcessUnit::MessageProcessUnit ()
{
  NS_LOG_FUNCTION (this);
  m_device = 0;
  m_packetSize = 0;
  m_interarrivalTime = 99999999999;
}


MessageProcessUnit::~MessageProcessUnit ()
{
  NS_LOG_FUNCTION (this);
}

void 
MessageProcessUnit::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_device = 0;
}

void
MessageProcessUnit::SetDevice (Ptr<SimpleNanoDevice> d)
{
  NS_LOG_FUNCTION (this);
  m_device = d;
}

Ptr<SimpleNanoDevice>
MessageProcessUnit::GetDevice (void)
{
  return m_device;
}

void
MessageProcessUnit::CreteMessage ()
{
  NS_LOG_FUNCTION (this);
  uint8_t *buffer  = new uint8_t[m_packetSize=102];
  for (int i = 0; i < m_packetSize; i++)
    {
	  buffer[i] = 129;
    }
  Ptr<Packet> p = Create<Packet>(buffer, m_packetSize);
  SeqTsHeader seqTs;
  seqTs.SetSeq (p->GetUid ());
  p->AddHeader (seqTs);

  m_outTX ((int)p->GetUid (), (int)GetDevice ()->GetNode ()->GetId ());

  m_device->SendPacket (p);
  Simulator::Schedule (Seconds (m_interarrivalTime), &MessageProcessUnit::CreteMessage, this);
}

void
MessageProcessUnit::ProcessMessage (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this);

  NanoL3Header l3Header;
  p->RemoveHeader (l3Header);

  SeqTsHeader seqTs;
  p->RemoveHeader (seqTs);

  NS_LOG_FUNCTION (this << l3Header);
  NS_LOG_FUNCTION (this << seqTs);

  double delay = Simulator::Now ().GetPicoSeconds () - seqTs.GetTs ().GetPicoSeconds ();

  m_outRX (seqTs.GetSeq (), p->GetSize (), (int)l3Header.GetSource (), (int)GetDevice ()->GetNode ()->GetId (), delay);
}


void
MessageProcessUnit::SetPacketSize (int s)
{
  NS_LOG_FUNCTION (this);
  m_packetSize = s;
}

void
MessageProcessUnit::SetInterarrivalTime (double t)
{
  NS_LOG_FUNCTION (this);
  m_interarrivalTime = t;
}

} // namespace ns3
