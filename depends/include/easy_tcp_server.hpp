/**
* @file easy_tcp_server.hpp
*
* @brief This message displayed in Doxygen Files index
*
* @ingroup PackageName
* (note: this needs exactly one @defgroup somewhere)
*
* @date	2021-06-20-18-43
* @author Nemausa
* @contact: tappanmorris@outlook.com
*
*/
#ifndef EASY_TCP_SERVER
#define EASY_TCP_SERVER

#include <vector>

#include "cell_server.hpp"
#include "timestamp.hpp"
#include "cell_thread.hpp"


class easy_tcp_server : public subject {
private:
    cell_thread thread_;
    std::vector<cell_server*> cell_servers_;
    observer* observer_;
    SOCKET sockfd_;
    timestamp time_;
public:
    easy_tcp_server();
    ~easy_tcp_server();
    SOCKET init_socket();
    int bind(const char* ip, unsigned short port);
    int listen(int n);
    SOCKET accept();
    void add_client_to_server(cell_client *client);
    void start(int cellserver_count);
    void close();
    bool is_run();
    void on_run(cell_thread *pthread);
    void time4msg();

};

#endif // EASY_TCP_SERVER