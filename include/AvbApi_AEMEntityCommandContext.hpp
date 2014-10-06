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
#include "AvbApi_AEMDescriptorTypes.hpp"
#include "AvbApi_AEMCommandTypes.hpp"
#include "AvbApi_Factory.hpp"
#include "AvbApi_Network.hpp"

namespace AvbApi2014
{
class AEMEntityCommandContext : public std::enable_shared_from_this<AEMEntityCommandContext>
{
  public:
    AEMEntityCommandContext( shared_ptr<Factory> &factory,
                             shared_ptr<Network> &network,
                             EntityId controllerEntityId,
                             NetworkAddress targetNetworkAddress,
                             EntityId targetEntityId )
        : m_factory( factory )
        , m_network( network )
        , m_controllerEntityId( controllerEntityId )
        , m_targetNetworkAddress( targetNetworkAddress )
        , m_targetEntityId( targetEntityId )
        , m_sequenceId( 0 )
    {
    }

    virtual ~AEMEntityCommandContext() {}

    virtual void acquireEntity( uint32_t flags,
                                EntityId owner_id,
                                AEMDescriptorType descriptorType,
                                AEMDescriptorIndex descriptorIndex,
                                std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                std::function<void(string const &)> failureCallback );

    virtual void lockEntity( uint32_t flags,
                             EntityId locked_id,
                             AEMDescriptorType descriptorType,
                             AEMDescriptorIndex descriptorIndex,
                             std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                             std::function<void(string const &)> failureCallback );

    virtual void entityAvailable( std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                  std::function<void(string const &)> failureCallback );

    virtual void controllerAvailable( std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                      std::function<void(string const &)> failureCallback );

    virtual void readDescriptor(
        AEMConfigurationIndexType configuration,
        AEMDescriptorType descriptorType,
        AEMDescriptorIndex descriptorIndex,
        std::function<void(shared_ptr<AECPAEMResponse> const &, shared_ptr<AEMDescriptorStorage> &)> successCallback,
        std::function<void(string const &)> failureCallback );

    virtual void writeDescriptor( AEMConfigurationIndexType configuration,
                                  AEMDescriptorType descriptorType,
                                  AEMDescriptorIndex descriptorIndex,
                                  std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                  std::function<void(string const &)> failureCallback );

    virtual void setConfiguration( AEMDescriptorIndex configuration,
                                   std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                   std::function<void(string const &)> failureCallback );

    virtual void getConfiguration( std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                   std::function<void(string const &)> failureCallback );

    virtual void setStreamFormat( AEMDescriptorType descriptorType,
                                  AEMDescriptorIndex descriptorIndex,
                                  StreamFormat streamFormat,
                                  std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                  std::function<void(string const &)> failureCallback );

    virtual void getStreamFormat( AEMDescriptorType descriptorType,
                                  AEMDescriptorIndex descriptorIndex,
                                  std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                  std::function<void(string const &)> failureCallback );

    shared_ptr<Factory> m_factory;
    shared_ptr<Network> m_network;
    EntityId m_controllerEntityId;
    NetworkAddress m_targetNetworkAddress;
    EntityId m_targetEntityId;
    uint16_t m_sequenceId;
};
}
