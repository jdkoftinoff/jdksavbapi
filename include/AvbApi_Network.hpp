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
#include "AvbApi_FunctionList.hpp"

namespace AvbApi2014
{

class Network : public std::enable_shared_from_this<Network>
{
  public:
    virtual void doADPRequest( shared_ptr<ADPRequest> & ) = 0;

    virtual void doAECPAARequest( shared_ptr<AECPAARequest> &request,
                                  std::function<void(shared_ptr<AECPAAResponse> const &)> successCallback,
                                  std::function<void(string const &)> failureCallback ) = 0;

    virtual void doACMPRequest( shared_ptr<ACMPRequest> &request,
                                std::function<void(shared_ptr<ACMPResponse> const &)> successCallback,
                                std::function<void(string const &)> failureCallback ) = 0;

    virtual void doAECPAEMRequest( shared_ptr<AECPAEMRequest> &request,
                                   std::function<void(shared_ptr<AECPAEMResponse> const &)> successCallback,
                                   std::function<void(string const &)> failureCallback ) = 0;

    FunctionList<void(NetworkAddress const &, bool)> m_LinkStatusChangedEvent;

    FunctionList<void(shared_ptr<ADPResponse> const &)> m_ADPResponseEvent;

    FunctionList<void(shared_ptr<ACMPUnsolicitedResponse> const &)> m_ACMPUnsolicitedResponseEvent;

    FunctionList<void(shared_ptr<AECPAEMUnsolicitedResponse> const &)> m_AECPAEMUnsolicitedResponseEvent;
};
}
