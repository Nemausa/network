#ifdef _WIN32

#include "cell_iocp_server.hpp"

cell_iocp_server::cell_iocp_server() {
    iocp_.create();
}

cell_iocp_server::~cell_iocp_server() noexcept {
    close();
}

bool cell_iocp_server::do_net_events() {
    cell_client *pclient = nullptr;
    for (auto iter = clients_.begin(); iter != clients_.end();) {
        pclient = iter->second;
        if (pclient->need_write()) {
            auto p_io_data = pclient->make_send_iodata();
            if (p_io_data) {
                if (iocp_.post_send(p_io_data)) {
                    iter = clients_.erase(iter);
                    continue;
                }
            }
            p_io_data = pclient->make_recv_iodata();
            if (p_io_data) {
                if (!iocp_.post_recv(p_io_data)) {
                    iter = clients_.erase(iter);
                    continue;
                }
            }
        } else {
            auto p_io_data = pclient->make_recv_iodata();
            if (p_io_data) {
                if (!iocp_.post_recv(p_io_data)) {
                    iter = clients_.erase(iter);
                    continue;
                }
            }
        }
        iter++;
    }
    while (true) {
        int ret = do_iocp_net_events();
        if (ret <0) {
            return false;
        } else if (ret == 0) {
            return true;
        }
    }
    return true;
}

// 每次只处理一件网络事件
// ret = -1 iocp error
// ret = 0  nothing
// ret = 1  iocp events

int cell_iocp_server::do_iocp_net_events() {
    int ret = iocp_.wait(io_event_, 1);
    if (ret < 0) {
        cell_log::info("cell_iocp_server%d.wait", id_);
        return ret;
    } else if (ret == 0) {
        return ret;
    }

    if (io_type_e::RECV == io_event_.p_io_data->io_type) {
        if (io_event_.bytes_trans <= 0) {
            cell_log::info("rm_client sockfd=%d, RECV byte_trans = %d", io_event_.p_io_data->sockfd, io_event_.bytes_trans);
            rm_client(io_event_);
            return ret;
        }
        cell_client *pclient = (cell_client*)io_event_.data.ptr;
        if (pclient) {
            pclient->recv_for_iocp(io_event_.bytes_trans);
        }
    } else if (io_type_e::SEND == io_event_.p_io_data->io_type) {
        if (io_event_.bytes_trans <= 0) {
            cell_log::info("rm_client sockfd=%d, RECV byte_trans = %d", io_event_.p_io_data->sockfd, io_event_.bytes_trans);
            rm_client(io_event_);
            return ret;
        }
        cell_client *pclient = (cell_client*)io_event_.data.ptr;
        if (pclient) {
            pclient->send_to_iocp(io_event_.bytes_trans);
        } 
    } else {
        cell_log::info("undefine io type");
    }
    return ret;
}

void cell_iocp_server::rm_client(cell_client *pclient) {
    auto iter = clients_.find(pclient->sockfd());
    if (iter != clients_.end()) {
        clients_.erase(iter);
    }
}

void cell_iocp_server::rm_client(io_event &_ioevent) {
    cell_client *pclient = (cell_client*)io_event_.data.ptr;
    if (pclient) {
        rm_client(pclient);
    }
}
#endif
