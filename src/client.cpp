#include "client.h"
#include "server.h"
Client::Client( std::string& _id, const Server & _server):id{_id},server{&_server}
{
    std::cout << "Client constructor " << std::endl;
}
std::string Client::get_id()const{return id;};