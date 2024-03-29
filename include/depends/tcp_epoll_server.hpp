/**
* @file esay_epoll_server.hpp
*
* @brief This message displayed in Doxygen Files index
*
* @ingroup PackageName
* (note: this needs exactly one @defgroup somewhere)
*
* @date	2021-07-24-22-42
* @author Nemausa
* @contact: tappanmorris@outlook.com
*
*/
#ifndef ESAY_EPOLL_SERVER
#define ESAY_EPOLL_SERVER

#if __linux__

#include "tcp_server.hpp"
#include "epoll_server.hpp"
#include "epoll.hpp"

namespace nemausa {
namespace io {

class tcp_epoll_server : public tcp_server {
public:
    void start(int n);
protected:
    void on_run(cell_thread *pthread);
};

} // namespace io 
} // namespace nemausa

#endif // __linux__
#endif // ESAY_EPOLL_SERVER