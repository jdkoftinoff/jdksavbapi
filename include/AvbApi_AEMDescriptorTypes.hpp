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
typedef std::uint16_t AEMConfigurationIndexType;
typedef std::uint16_t AEMDescriptorIndex;
typedef std::vector<uint8_t> AEMDescriptorStorage;

enum AEMDescriptorType : uint16_t
{
    ENTITY = ( 0x0000 ),
    CONFIGURATION = ( 0x0001 ),
    AUDIO_UNIT = ( 0x0002 ),
    VIDEO_UNIT = ( 0x0003 ),
    SENSOR_UNIT = ( 0x0004 ),
    STREAM_INPUT = ( 0x0005 ),
    STREAM_OUTPUT = ( 0x0006 ),
    JACK_INPUT = ( 0x0007 ),
    JACK_OUTPUT = ( 0x0008 ),
    AVB_INTERFACE = ( 0x0009 ),
    CLOCK_SOURCE = ( 0x000a ),
    MEMORY_OBJECT = ( 0x000b ),
    LOCALE = ( 0x000c ),
    STRINGS = ( 0x000d ),
    STREAM_PORT_INPUT = ( 0x000e ),
    STREAM_PORT_OUTPUT = ( 0x000f ),
    EXTERNAL_PORT_INPUT = ( 0x0010 ),
    EXTERNAL_PORT_OUTPUT = ( 0x0011 ),
    INTERNAL_PORT_INPUT = ( 0x0012 ),
    INTERNAL_PORT_OUTPUT = ( 0x0013 ),
    AUDIO_CLUSTER = ( 0x0014 ),
    VIDEO_CLUSTER = ( 0x0015 ),
    SENSOR_CLUSTER = ( 0x0016 ),
    AUDIO_MAP = ( 0x0017 ),
    VIDEO_MAP = ( 0x0018 ),
    SENSOR_MAP = ( 0x0019 ),
    CONTROL = ( 0x001a ),
    SIGNAL_SELECTOR = ( 0x001b ),
    MIXER = ( 0x001c ),
    MATRIX = ( 0x001d ),
    MATRIX_SIGNAL = ( 0x001e ),
    SIGNAL_SPLITTER = ( 0x001f ),
    SIGNAL_COMBINER = ( 0x0020 ),
    SIGNAL_DEMULTIPLEXER = ( 0x0021 ),
    SIGNAL_MULTIPLEXER = ( 0x0022 ),
    SIGNAL_TRANSCODER = ( 0x0023 ),
    CLOCK_DOMAIN = ( 0x0024 ),
    CONTROL_BLOCK = ( 0x0025 ),
    NUM_DESCRIPTOR_TYPES = ( 0x0026 ),
    INVALID = ( 0xffff )
};

typedef std::tuple<AEMConfigurationIndexType, AEMDescriptorType, AEMDescriptorIndex> DescriptorIdentifier;
}
