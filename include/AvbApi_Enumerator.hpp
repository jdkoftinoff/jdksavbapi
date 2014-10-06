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
#include "AvbApi_Factory.hpp"
#include "AvbApi_Network.hpp"
#include "AvbApi_Request.hpp"
#include "AvbApi_Response.hpp"
#include "AvbApi_AEMEntityCommandContext.hpp"

namespace AvbApi2014
{

class Enumerator : public std::enable_shared_from_this<Enumerator>
{
  public:
    Enumerator( shared_ptr<AEMEntityCommandContext> &entityContext,
                shared_ptr<EntityModel> &entityModel,
                function<void(EntityId, shared_ptr<EntityModel> &)> enumerationCompletedCallback,
                function<void(EntityId, shared_ptr<EntityModel> &, string const &)> enumerationFailedCallback )
        : m_entityContext( entityContext )
        , m_entityModel( entityModel )
        , m_enumerationCompletedCallback( enumerationCompletedCallback )
        , m_enumerationFailedCallback( enumerationFailedCallback )
    {
    }

    virtual void startEnumeration();

    virtual void enumerateConfiguration( AEMConfigurationIndexType configuration );

    virtual void enumerateAllDescriptorsOfType( AEMConfigurationIndexType configuration, AEMDescriptorType type );

  protected:
    shared_ptr<AEMEntityCommandContext> m_entityContext;
    shared_ptr<EntityModel> m_entityModel;
    function<void(EntityId, shared_ptr<EntityModel> &)> m_enumerationCompletedCallback;
    function<void(EntityId, shared_ptr<EntityModel> &, string const &)> m_enumerationFailedCallback;
};
}
