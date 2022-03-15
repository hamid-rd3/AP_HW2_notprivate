#include "server.h"
#include "client.h"
Server::Server()
{
    //constructor Server class
}

std::shared_ptr<Client> Server::add_client(std::string id)
{
    std::shared_ptr<Client> client { std::make_shared<Client>(id, *this) };
    // if this id already exists,
    // the server should add a random 4 digit number at the end of it
    if (clients.count(client)) {
        // give seed { rd } to mersenne_twister_engine
        std::random_device rd;
        // the engine generate random numbers unlimitedly
        std::mt19937 mt(rd());
        // bring numbers in continuous random distribution on range[min, max)
        // random number is 4 digit so (min,max] =(999,9999]
        double min { 999 };
        double max { 9999 };
        std::uniform_real_distribution<double> dist(min, max);
        id.append(std::to_string(dist(mt)));
    } else {
        clients.insert({ client, 5 });  
    }
    return client;
    
}

std::shared_ptr<Client> Server::get_client(std::string id)
{
    //make a new client in object refrence with the same id (client1)
    //then compare clients id s  in server with client1 through loop 
    //if same id found between ....
    // return the client saved in server clients(previous client) 
    std::shared_ptr<Client> client1 {std::make_shared<Client>(id,*this)};

    for(auto iter=clients.begin();iter != clients.end();++ iter ){

        if ((iter->first)->get_id()==client1->get_id()){
            return iter->first;
            break;
        }
    }
    //if 
    throw(std::logic_error("there is not such id in server bro!"));
}