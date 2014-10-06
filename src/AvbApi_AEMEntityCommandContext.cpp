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

#include "AvbApi_AEMEntityCommandContext.hpp"

namespace AvbApi2014
{

void AEMEntityCommandContext::readDescriptor(
    AEMConfigurationIndexType configuration,
    AEMDescriptorType descriptorType,
    AEMDescriptorIndex descriptorIndex,
    std::function<void(const shared_ptr<AECPAEMResponse> &, shared_ptr<AEMDescriptorStorage> &)> successCallback,
    std::function<void(const string &)> failureCallback )
{
    AEMCommandPayload commandPayload;

    append( commandPayload, configuration );
    append( commandPayload, uint16_t( 0 ) );
    append( commandPayload, descriptorType );
    append( commandPayload, descriptorIndex );

    shared_ptr<AECPAEMRequest> request = m_factory->createAECPAEMRequest( m_targetNetworkAddress,
                                                                          0,
                                                                          m_targetEntityId,
                                                                          m_controllerEntityId,
                                                                          m_sequenceId,
                                                                          AEMCommandType::READ_DESCRIPTOR,
                                                                          commandPayload );

    m_network->doAECPAEMRequest( request,
                                 [&]( shared_ptr<AECPAEMResponse> const &response )
                                 {
                                     // TODO: extract AEMDescriptorStorage payload
                                     shared_ptr<AEMDescriptorStorage> payload = make_shared<AEMDescriptorStorage>();
                                     successCallback( response, payload );
                                 },
                                 failureCallback );
}
}
