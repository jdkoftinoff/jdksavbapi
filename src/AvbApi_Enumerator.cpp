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

#include "AvbApi_Enumerator.hpp"
#include "AvbApi_AEMCommandTypes.hpp"
#include "AvbApi_AEMDescriptorTypes.hpp"
#include "AvbApi_EntityModel.hpp"

namespace AvbApi2014
{

void Enumerator::startEnumeration()
{
    m_entityContext->readDescriptor(
        0,
        AEMDescriptorType::ENTITY,
        0,
        [&]( shared_ptr<AECPAEMResponse> const &response, shared_ptr<AEMDescriptorStorage> &descriptorData )
        {
            (void)response;
            // TODO: parseEntityDescriptor( response );
            // TODO: fill in entity info into m_entityModel
            // TODO: iterate through all configurations and read all descriptors in each
            m_entityModel->m_descriptors[DescriptorIdentifier( 0, AEMDescriptorType::ENTITY, 0 )] = descriptorData;
            AEMConfigurationIndexType numConfigurations = 1; // TODO: m_entityModel->getNumConfigurations();
            for ( AEMConfigurationIndexType config = 0; config < numConfigurations; ++config )
            {
                enumerateConfiguration( config );
            }
            m_enumerationCompletedCallback( m_entityContext->m_targetEntityId, m_entityModel );
        },
        [&]( string const &info )
        {
            m_enumerationFailedCallback( m_entityContext->m_targetEntityId, m_entityModel, info );
        } );
}

void Enumerator::enumerateConfiguration( AEMConfigurationIndexType configuration )
{
    m_entityContext->readDescriptor(
        configuration,
        AEMDescriptorType::CONFIGURATION,
        0,
        [&]( shared_ptr<AECPAEMResponse> const &response, shared_ptr<AEMDescriptorStorage> &descriptorData )
        {

            // TODO: parse Configuration descriptor
            m_entityModel->m_descriptors[DescriptorIdentifier( 0, AEMDescriptorType::CONFIGURATION, 0 )] = descriptorData;

            // read all descriptors in this configuration for all descriptor types
            for ( uint16_t type = 0; type < AEMDescriptorType::NUM_DESCRIPTOR_TYPES; ++type )
            {
                enumerateAllDescriptorsOfType( configuration, AEMDescriptorType( type ) );
            }
        },
        [&]( string const &info )
        {
            m_enumerationFailedCallback( m_entityContext->m_targetEntityId, m_entityModel, info );
        } );
}

void Enumerator::enumerateAllDescriptorsOfType( AEMConfigurationIndexType configuration, AEMDescriptorType type )
{
    bool finished = false;
    for ( AEMDescriptorIndex i = 0; i < 0xffff; ++i )
    {
        m_entityContext->readDescriptor(
            configuration,
            type,
            0,
            [&]( shared_ptr<AECPAEMResponse> const &response, shared_ptr<AEMDescriptorStorage> &descriptorData )
            {
                // TODO: if(response->status != SUCCESS) { finished=true; } else {...}
                m_entityModel->m_descriptors[DescriptorIdentifier( configuration, type, i )] = descriptorData;

            },
            [&]( string const &info )
            {
                m_enumerationFailedCallback( m_entityContext->m_targetEntityId, m_entityModel, info );
            } );
        if ( finished )
        {
            break;
        }
    }
}
}
