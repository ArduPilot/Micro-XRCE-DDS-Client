// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! 
 * @file HelloWorldWriter.c
 * This source file contains the write function of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#include "HelloWorldWriter.h"

#include <micrortps/client/core/serialization/xrce_protocol.h>
#include <micrortps/client/core/session/submessage.h>

bool mr_write_HelloWorld_topic(mrSession* session, mrStreamId stream_id, mrObjectId datawriter_id, const
        HelloWorld* topic)
{
    bool written = false;

    uint32_t topic_length = HelloWorld_size_of_topic(topic, 0);
    uint32_t payload_length = 0;
    payload_length += 4; //request_id + object_id
    payload_length += 4; //topic_length (remove in future version to be compliant)

    MicroBuffer mb;
    if(prepare_stream_to_write(&session->streams, stream_id, payload_length + topic_length + SUBHEADER_SIZE, &mb))
    {
        (void) write_submessage_header(&mb, SUBMESSAGE_ID_WRITE_DATA, payload_length + topic_length, FORMAT_DATA);

        WRITE_DATA_Payload_Data payload;
        init_base_object_request(session, datawriter_id, &payload.base);
        (void) serialize_WRITE_DATA_Payload_Data(&mb, &payload);
        (void) serialize_uint32_t(&mb, topic_length); //REMOVE: when topics have not a previous size in the agent.

        MicroBuffer mb_topic;
        init_micro_buffer(&mb_topic, mb.iterator, topic_length);
        (void) HelloWorld_serialize_topic(&mb_topic, topic);

        written = true;
    }

    return written;
}
