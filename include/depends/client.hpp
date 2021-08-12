/**
* @file client.hpp
*
* @brief This message displayed in Doxygen Files index
*
* @ingroup PackageName
* (note: this needs exactly one @defgroup somewhere)
*
* @date	2021-06-30-00-21
* @author Nemausa
* @contact: tappanmorris@outlook.com
*
*/
#ifndef CLIENT
#define CLIENT

#include "cell.hpp"
#include "buffer.hpp"
#include "network.hpp"

#ifndef RECV_BUFF_SIZE
#define RECV_BUFF_SIZE 10240
#define SEND_BUFF_SIZE RECV_BUFF_SIZE
#endif

#define CLIENT_HEART_DEAD_TIME  20000
#define CLIENT_SEND_BUFF_TIME   200

class client {
public:
    client(SOCKET sockfd = INVALID_SOCKET, int send_size = SEND_BUFF_SIZE, int recv_size = RECV_BUFF_SIZE);
    ~client();
    void destory();
    SOCKET sockfd();
    int recv_data();
    bool has_msg();
    data_header *front_msg();
    void pop_msg();
    bool need_write();
    int send_data_real();
    int send_data(data_header *header);
    int send_data(const char *data, int length);
    void reset_heart_time();
    void reset_send_time();
    bool check_heart_time(time_t dt);
    bool check_send_time(time_t dt);
#ifdef _WIN32
    io_data_base *make_recv_iodata();
    void recv_for_iocp(int nrecv);
    io_data_base *make_send_iodata();
    void send_to_iocp(int nsend);
    bool is_post_action();
#endif
public:
    int id_ = -1;
    int service_id_ = -1;
    int recv_id = 1;
    int send_id = 1;
private:
    buffer recv_buffer_;
    buffer send_buffer_;
    time_t heart_time_;
    time_t send_time_;
    SOCKET sockfd_;
    int last_pos_;
    int last_send_pos_;
    bool is_post_recv_ = false;
    bool is_post_send_ = false;
};

#endif // CLIENT