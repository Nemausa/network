/**
* @file websocket.hpp
*
* @brief This message displayed in Doxygen Files index
*
* @ingroup PackageName
* (note: this needs exactly one @defgroup somewhere)
*
* @date	2021-10-27-09-16
* @author Nemausa
* @contact: tappanmorris@outlook.com
*
*/
#ifndef NEMAUSA_IO_WEBSOCKET_HPP_
#define NEMAUSA_IO_WEBSOCKET_HPP_

#include <cstdint>

namespace nemausa {
namespace io {

enum websocket_code_e
{
    opcode_continuation = 0x00,
    opcode_text = 0x1,
    opcode_binary = 0x2,
    opcode_close = 0x8,
    opcode_ping = 0x9,
    opcode_pong = 0xA
};

struct websocket_header
{
    uint16_t len;
    //操作代码，Opcode 的值决定了应该如何解析后续的 数据载荷（data payload）
    //如果操作代码是不认识的，那么接收端应该 断开连接（fail the connection）   
    websocket_code_e opcode;
    //所有从客户端传送到服务端的数据帧，数据载荷都进行了掩码操作，
    //Mask 为 1，且携带了 4 字节的 Masking-key。
    //如果 Mask 为 0，则没有 Masking-key
    //备注：载荷数据的长度len，不包括 mask key 的长度。
    uint8_t masking_key[4];
    //如果值为true，表示这是 消息（message）的最后一个分片（fragment）
    //如果是 0，表示不是 消息（message）的最后一个 分片（fragment）
    bool fin;
    //表示是否要对数据（消息体）进行掩码操作
    //从客户端向服务端发送数据时，需要对数据进行掩码操作；
    //从服务端向客户端发送数据时，不需要对数据进行掩码操作。
    //如果服务端接收到的数据没有进行过掩码操作，服务端需要断开连接。
    bool mask;
    //数据载荷的长度,如果值为x
    //x 为 0~126：数据的长度为 x 字节。
    //x 为 126：后续 2 个字节代表一个 16 位的无符号整数，该无符号整数的值为数据的长度。
    //x 为 127：后续 8 个字节代表一个 64 位的无符号整数（最高位为 0），该无符号整数的值为数据的长度。
    //此外，如果 payload length 占用了多个字节的话，payload length 的二进制表达采用 网络序（big endian，重要的位在前）。
    uint8_t len0;
    //websocket数据帧头部字节长度
    uint8_t header_size;
};

} // namespace nemausa
} // namespace io

#endif // NEMAUSA_IO_WEBSOCKET_HPP_