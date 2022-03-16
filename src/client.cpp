#include "client.h"
#include "crypto.h"
#include "server.h"
Client::Client(std::string& _id, const Server& _server)
    : id { _id }
    , server { &_server }
{
    crypto::generate_key(public_key, private_key);
    std::cout << "Client constructor " << std::endl;
}

std::string Client::get_id() const { return id; };

double Client::get_wallet() const
{
    // becuase server type is "Server const* const" -> const_cast
    // useing Server::get_wallet for Client::get_wallet
    return const_cast<Server&>(*server).get_wallet(id);
}
std::string Client::get_publickey() const
{
    {
        return public_key;
    }
}

std::string Client::sign(std::string txt)const{
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value){
    //first make test trx (using entities) 
    //then sign it and initialize signature with
    //finally pass test trx and signature to server 
   std::string trx_test {};
    trx_test.append(id);
    trx_test.append('-'+receiver+'-');
    trx_test.append(std::to_string(value));
    std::string signature {sign(trx_test)};
    return const_cast<Server&>(*server).add_pending_trx(trx_test,signature);

}

size_t Client::generate_nonce(){
    // give seed { rd } to mersenne_twister_engine
        std::random_device rd;
        // the engine generate random numbers unlimitedly
        std::mt19937 mt(rd());
        // bring numbers in continuous random distribution on range[min, max)
        // random number is 6 digit so (min,max] =(-1,999999]
        double min { -1 };
        double max { 999999 };
        std::uniform_real_distribution<double> dist(min, max);
        return dist(mt);
}