#include "depends/tcp_select_server.hpp"
#include "depends/select_server.hpp"

namespace nemausa {
namespace io {

void tcp_select_server::start(int n) {
    tcp_server::start<select_server>(n);
}

void tcp_select_server::on_run(cell_thread *pthread) {
    cell_fdset fd_read;
    fd_read.create(max_client_);
    while (pthread->is_run()) {
        time4msg();
        fd_read.zero();
        fd_read.add(sockfd());
        timeval t = {0, 1};
        int ret = select(sockfd() + 1, fd_read.fdset(), 0, 0, &t);
        if (ret < 0) {
            if (errno == EINTR) {
                //SPDLOG_LOGGER_INFO(spdlog::get(MULTI_SINKS), 
                        // "tcp_select_server select EINTR");
                continue;
            }
            // SPDLOG_LOGGER_ERROR(spdlog::get(FILE_SINK), 
            //         "tcp_select_server.on_run select");
            pthread->exit();
            break;
        }
        if (fd_read.has(sockfd())) {
            accept();
        }
    }
}

} // namespace io 
} // namespace nemausa