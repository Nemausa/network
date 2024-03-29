/**
* @file tcp_select_client.hpp
*
* @brief This message displayed in Doxygen Files index
*
* @ingroup PackageName
* (note: this needs exactly one @defgroup somewhere)
*
* @date	2021-08-01-19-53
* @author Nemausa
* @contact: tappanmorris@outlook.com
*
*/
#ifndef EASY_SELECT_CLIENT
#define EASY_SELECT_CLIENT

#include "fdset.hpp"
#include "tcp_client.hpp"

namespace nemausa {
namespace io {

class tcp_select_client : public tcp_client {
public:
    tcp_select_client();
    virtual bool on_run(int microseconds = 1);
protected:
    cell_fdset fd_read_;
    cell_fdset fd_write_;
};

} // namespace io 
} // namespace nemausa

#endif // EASY_SELECT_CLIENT