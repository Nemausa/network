
#include "depends/tcp_select_server.hpp"

#include "depends/select_server.hpp"

void tcp_select_server::start(int n) {
    tcp_server::start<select_server>(n);
}

void tcp_select_server::on_run(cell_thread *pthread) {
    cell_fdset fd_read;
    while (pthread->is_run()) {
        time4msg();
        fd_read.zero();
        fd_read.add(sockfd());
        timeval t = {0, 1};
        int ret = select(sockfd() + 1, fd_read.fdset(), 0, 0, &t);
        if (ret < 0) {
            if (errno == EINTR) {
                SPDLOG_LOGGER_INFO(spdlog::get(LOG_NAME), "tcp_select_server select EINTR");
                continue;
            }
            SPDLOG_LOGGER_ERROR(spdlog::get(LOG_NAME), "tcp_select_server.on_run select");
            pthread->exit();
            break;
        }
        if (fd_read.has(sockfd())) {
            accept();
        }
    }
}