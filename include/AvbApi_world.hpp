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

#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <iomanip>
#include <atomic>
#include <cstdint>
#include <utility>
#include <tuple>
#include <sys/socket.h>

namespace AvbApi2014
{
using std::pair;
using std::make_pair;
using std::tuple;
using std::make_tuple;
using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;
using std::make_shared;
using std::function;
using std::vector;
using std::array;

typedef std::uint64_t EntityId;
typedef std::uint64_t EntityModelId;
typedef std::uint64_t StreamId;
typedef std::uint64_t MACAddress;
typedef std::uint16_t CommandCode;
typedef std::uint16_t ConfigurationIndexType;
typedef std::uint16_t DescriptorType;
typedef std::uint16_t DescriptorIndexType;
typedef std::vector<uint8_t> DescriptorStorage;
typedef std::tuple<ConfigurationIndexType, DescriptorType, DescriptorIndexType> DescriptorIdentifier;

struct NetworkAddress
{
    bool m_isMac;
    MACAddress m_macAddress;
    sockaddr_storage m_sockaddr;
};
}

namespace AvbApi = AvbApi2014;
