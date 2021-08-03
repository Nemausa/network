/**
* @file easy_server_mgr.hpp
*
* @brief This message displayed in Doxygen Files index
*
* @ingroup PackageName
* (note: this needs exactly one @defgroup somewhere)
*
* @date	2021-08-03-23-23
* @author Nemausa
* @contact: tappanmorris@outlook.com
*
*/
#ifndef EASY_SERVER_MGR
#define EASY_SERVER_MGR

#include "easy_epoll_server.hpp"
#include "easy_iocp_server.hpp"
#include "easy_select_server.hpp"

#ifdef _WIN32
    typedef easy_iocp_server easy_server_mgr;
#elif __linux__
    typedef easy_epoll_server easy_server_mgr; 
#else
    typedef easy_select_serve reasy_server_mgr;
#endif


#endif // EASY_SERVER_MGR