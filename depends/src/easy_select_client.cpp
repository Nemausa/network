#include "easy_select_client.hpp"

bool easy_select_client::on_run(int microseconds) {
    if (is_run()) {
        SOCKET _sock = pclient_->sockfd();
        fd_read_.zero();
        fd_read_.add(_sock);
        fd_write_.zero();
        
        timeval t = {0, microseconds};
        int ret = 0;
        if (pclient_->need_write()) {
            fd_write_.add(_sock);
            ret = select(_sock + 1, fd_read_.fdset(), fd_write_.fdset(), nullptr, &t);
        } else {
            ret = select(_sock + 1, fd_read_.fdset(), nullptr, nullptr, &t);
        }
        if (ret < 0) {
            LOG_INFO("socke=%d select exit", (int)_sock);
            close();
            return false;
        }

        if (fd_read_.has(_sock)) {
            if (SOCKET_ERROR == recv_data()) {
                LOG_INFO("socket=%d onrun select recv_data exit", (int)_sock);
                close();
                return false;
            }
        }

        if (fd_write_.has(_sock)) {
            if (SOCKET_ERROR == pclient_->send_data_real()) {
                LOG_INFO("socket=%d onrun select send_data_real exit", (int)_sock);
                close();
                return false;
            }
        }

        return true;
    }
    return false;
}