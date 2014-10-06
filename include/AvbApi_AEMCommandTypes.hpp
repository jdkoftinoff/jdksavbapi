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

namespace AvbApi2014
{
typedef std::vector<uint8_t> AEMCommandPayload;

inline void append( std::vector<uint8_t> &buf, uint8_t v ) { buf.push_back( v ); }

inline void append( std::vector<uint8_t> &buf, uint16_t v )
{
    buf.push_back( static_cast<uint8_t>( ( v >> 8 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 0 ) & 0xff ) );
}

inline void append( std::vector<uint8_t> &buf, uint32_t v )
{
    buf.push_back( static_cast<uint8_t>( ( v >> 24 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 16 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 8 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 0 ) & 0xff ) );
}

inline void append( std::vector<uint8_t> &buf, uint64_t v )
{
    buf.push_back( static_cast<uint8_t>( ( v >> 56 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 48 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 40 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 32 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 24 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 16 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 8 ) & 0xff ) );
    buf.push_back( static_cast<uint8_t>( ( v >> 0 ) & 0xff ) );
}

enum AEMCommandType : uint16_t
{
    ACQUIRE_ENTITY = ( 0x0000 ),
    LOCK_ENTITY = ( 0x0001 ),
    ENTITY_AVAILABLE = ( 0x0002 ),
    CONTROLLER_AVAILABLE = ( 0x0003 ),
    READ_DESCRIPTOR = ( 0x0004 ),
    WRITE_DESCRIPTOR = ( 0x0005 ),
    SET_CONFIGURATION = ( 0x0006 ),
    GET_CONFIGURATION = ( 0x0007 ),
    SET_STREAM_FORMAT = ( 0x0008 ),
    GET_STREAM_FORMAT = ( 0x0009 ),
    SET_VIDEO_FORMAT = ( 0x000a ),
    GET_VIDEO_FORMAT = ( 0x000b ),
    SET_SENSOR_FORMAT = ( 0x000c ),
    GET_SENSOR_FORMAT = ( 0x000d ),
    SET_STREAM_INFO = ( 0x000e ),
    GET_STREAM_INFO = ( 0x000f ),
    SET_NAME = ( 0x0010 ),
    GET_NAME = ( 0x0011 ),
    SET_ASSOCIATION_ID = ( 0x0012 ),
    GET_ASSOCIATION_ID = ( 0x0013 ),
    SET_SAMPLING_RATE = ( 0x0014 ),
    GET_SAMPLING_RATE = ( 0x0015 ),
    SET_CLOCK_SOURCE = ( 0x0016 ),
    GET_CLOCK_SOURCE = ( 0x0017 ),
    SET_CONTROL = ( 0x0018 ),
    GET_CONTROL = ( 0x0019 ),
    INCREMENT_CONTROL = ( 0x001a ),
    DECREMENT_CONTROL = ( 0x001b ),
    SET_SIGNAL_SELECTOR = ( 0x001c ),
    GET_SIGNAL_SELECTOR = ( 0x001d ),
    SET_MIXER = ( 0x001e ),
    GET_MIXER = ( 0x001f ),
    SET_MATRIX = ( 0x0020 ),
    GET_MATRIX = ( 0x0021 ),
    START_STREAMING = ( 0x0022 ),
    STOP_STREAMING = ( 0x0023 ),
    REGISTER_UNSOLICITED_NOTIFICATION = ( 0x0024 ),
    DEREGISTER_UNSOLICITED_NOTIFICATION = ( 0x0025 ),
    IDENTIFY_NOTIFICATION = ( 0x0026 ),
    GET_AVB_INFO = ( 0x0027 ),
    GET_AS_PATH = ( 0x0028 ),
    GET_COUNTERS = ( 0x0029 ),
    REBOOT = ( 0x002a ),
    GET_AUDIO_MAP = ( 0x002b ),
    ADD_AUDIO_MAPPINGS = ( 0x002c ),
    REMOVE_AUDIO_MAPPINGS = ( 0x002d ),
    GET_VIDEO_MAP = ( 0x002e ),
    ADD_VIDEO_MAPPINGS = ( 0x002f ),
    REMOVE_VIDEO_MAPPINGS = ( 0x0030 ),
    GET_SENSOR_MAP = ( 0x0031 ),
    ADD_SENSOR_MAPPINGS = ( 0x0032 ),
    REMOVE_SENSOR_MAPPINGS = ( 0x0033 ),
    START_OPERATION = ( 0x0034 ),
    ABORT_OPERATION = ( 0x0035 ),
    OPERATION_STATUS = ( 0x0036 ),
    AUTH_ADD_KEY = ( 0x0037 ),
    AUTH_DELETE_KEY = ( 0x0038 ),
    AUTH_GET_KEY_LIST = ( 0x0039 ),
    AUTH_GET_KEY = ( 0x003a ),
    AUTH_ADD_KEY_TO_CHAIN = ( 0x003b ),
    AUTH_DELETE_KEY_FROM_CHAIN = ( 0x003c ),
    AUTH_GET_KEYCHAIN_LIST = ( 0x003d ),
    AUTH_GET_IDENTITY = ( 0x003e ),
    AUTH_ADD_TOKEN = ( 0x003f ),
    AUTH_DELETE_TOKEN = ( 0x0040 ),
    AUTHENTICATE = ( 0x0041 ),
    DEAUTHENTICATE = ( 0x0042 ),
    ENABLE_TRANSPORT_SECURITY = ( 0x0043 ),
    DISABLE_TRANSPORT_SECURITY = ( 0x0044 ),
    ENABLE_STREAM_ENCRYPTION = ( 0x0045 ),
    DISABLE_STREAM_ENCRYPTION = ( 0x0046 ),
    SET_MEMORY_OBJECT_LENGTH = ( 0x0047 ),
    GET_MEMORY_OBJECT_LENGTH = ( 0x0048 ),
    SET_STREAM_BACKUP = ( 0x0049 ),
    GET_STREAM_BACKUP = ( 0x004a ),
    NUM_COMMANDS = ( 0x004b ),
    EXPANSION = ( 0x7fff )
};
}
