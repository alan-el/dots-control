//
// Created by alan on 5/10/22.
//

#ifndef DOTS_CONTROL_PACKET_H
#define DOTS_CONTROL_PACKET_H

#include <stdint.h>

#define DOTS_CONTROL_HEADER_LEN     sizeof(dcp_head_t)
#define DOTS_CONTROL_PAYLOAD_MAX_LEN    17
#define DOTS_CONTROL_PACK_MAX_LEN       DOTS_CONTROL_HEADER_LEN + DOTS_CONTROL_PAYLOAD_MAX_LEN
#define START_CODE                      0x55AA

typedef struct
{
    uint16_t start_code;
    uint8_t cmd_type;
    uint8_t payload_len;
    uint8_t seq_num;
    uint8_t dummy;
    uint16_t check_code;
}dcp_head_t;

typedef dcp_head_t * dcp_head_handle_t;
#endif //DOTS_CONTROL_PACKET_H
