#pragma once

/*
Copyright (c) 2014, Jeff Koftinoff
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "AvbApi_world.hpp"

namespace AvbApi2014
{
class Factory;
class Network;
class Entity;
class EntityModel;
class Enumerator;
class ACMPRequest;
class ACMPResponse;
class ACMPUnsolicitedResponse;
class ADPRequest;
class ADPResponse;
class AECPAARequest;
class AECPAAResponse;
class AECPAEMRequest;
class AECPAEMResponse;
class AECPAEMUnsolicitedResponse;

class Factory : public std::enable_shared_from_this<Factory>
{
  public:
    virtual ~Factory() {}

    virtual shared_ptr<Network> createNetwork() = 0;

    virtual shared_ptr<EntityModel> createEntityModel( EntityModelId entityModelId ) = 0;

    virtual shared_ptr<Entity> createEntity( EntityId entityId, EntityModelId entityModelId, shared_ptr<EntityModel> & ) = 0;

    virtual shared_ptr<Enumerator> createEnumerator( EntityId targetEntityId,
                                                     function<void(EntityId, shared_ptr<EntityModel> &)> callback ) = 0;

    virtual shared_ptr<ACMPRequest> createACMPRequest( NetworkAddress network_address,
                                                       uint16_t message_type,
                                                       uint16_t status,
                                                       EntityId controller_entity_id,
                                                       EntityId talker_entity_id,
                                                       EntityId listener_entity_id,
                                                       DescriptorIndexType talker_unique_id,
                                                       DescriptorIndexType listener_unique_id,
                                                       MACAddress stream_dest_mac,
                                                       uint16_t connection_count,
                                                       uint16_t sequence_id,
                                                       uint16_t flags,
                                                       uint16_t stream_vlan_id ) = 0;

    virtual shared_ptr<ACMPResponse> createACMPResponse( NetworkAddress network_address,
                                                         uint16_t message_type,
                                                         uint16_t status,
                                                         EntityId controller_entity_id,
                                                         EntityId talker_entity_id,
                                                         EntityId listener_entity_id,
                                                         DescriptorIndexType talker_unique_id,
                                                         DescriptorIndexType listener_unique_id,
                                                         MACAddress stream_dest_mac,
                                                         uint16_t connection_count,
                                                         uint16_t sequence_id,
                                                         uint16_t flags,
                                                         uint16_t stream_vlan_id ) = 0;

    virtual shared_ptr<ACMPUnsolicitedResponse> createACMPUnsolicitedResponse( NetworkAddress network_address,
                                                                               uint16_t message_type,
                                                                               uint16_t status,
                                                                               EntityId controller_entity_id,
                                                                               EntityId talker_entity_id,
                                                                               EntityId listener_entity_id,
                                                                               DescriptorIndexType talker_unique_id,
                                                                               DescriptorIndexType listener_unique_id,
                                                                               MACAddress stream_dest_mac,
                                                                               uint16_t connection_count,
                                                                               uint16_t sequence_id,
                                                                               uint16_t flags,
                                                                               uint16_t stream_vlan_id ) = 0;

    virtual shared_ptr<ADPRequest> createADPRequest( NetworkAddress network_address, uint16_t message_type, EntityId entity_id )
        = 0;

    virtual shared_ptr<ADPResponse> createADPResponse( NetworkAddress network_address,
                                                       uint16_t message_type,
                                                       uint16_t status,
                                                       EntityId entity_id,
                                                       EntityModelId entity_model_id,
                                                       uint32_t entity_capabilities,
                                                       uint16_t talker_stream_sources,
                                                       uint16_t talker_capabilities,
                                                       uint16_t listener_stream_sinks,
                                                       uint16_t listener_capabilities,
                                                       uint32_t controller_capabilities,
                                                       uint32_t available_index,
                                                       uint64_t gptp_grandmaster_id,
                                                       uint8_t gptp_domain_number,
                                                       DescriptorIndexType identify_control_index,
                                                       DescriptorIndexType interface_index,
                                                       uint64_t association_id ) = 0;

    virtual shared_ptr<AECPAARequest> createAECPAARequest( NetworkAddress network_address,
                                                           uint16_t status,
                                                           EntityId target_entity_id,
                                                           EntityId controller_entity_id,
                                                           uint16_t sequence_id,
                                                           uint16_t tlv_count,
                                                           vector<uint8_t> const &tlv_payload ) = 0;

    virtual shared_ptr<AECPAAResponse> createAECPAAResponse( NetworkAddress network_address,
                                                             uint16_t status,
                                                             EntityId target_entity_id,
                                                             EntityId controller_entity_id,
                                                             uint16_t sequence_id,
                                                             uint16_t tlv_count,
                                                             vector<uint8_t> const &tlv_payload ) = 0;

    virtual shared_ptr<AECPAEMRequest> createAECPAEMRequest( NetworkAddress network_address,
                                                             uint16_t status,
                                                             EntityId target_entity_id,
                                                             EntityId controller_entity_id,
                                                             uint16_t sequence_id,
                                                             uint16_t command_type,
                                                             vector<uint8_t> const &command_payload ) = 0;

    virtual shared_ptr<AECPAEMResponse> createAECPAEMResponse( NetworkAddress network_address,
                                                               uint16_t status,
                                                               EntityId target_entity_id,
                                                               EntityId controller_entity_id,
                                                               uint16_t sequence_id,
                                                               uint16_t command_type,
                                                               vector<uint8_t> const &response_payload ) = 0;

    virtual shared_ptr<AECPAEMUnsolicitedResponse> createAECPAEMUnsolicitedResponse( NetworkAddress network_address,
                                                                                     uint16_t status,
                                                                                     EntityId target_entity_id,
                                                                                     EntityId controller_entity_id,
                                                                                     uint16_t sequence_id,
                                                                                     uint16_t command_type,
                                                                                     vector<uint8_t> const &response_payload )
        = 0;
};
}
