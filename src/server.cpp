#include "server.h"
#include "client.h"

Server::Server()
{
    // constructor Server class
}

std::shared_ptr<Client> Server::add_client(std::string id)
{
    // if this id already exists,
    // the server should add a random 4 digit number at the end of it

    if (this->get_client(id) != nullptr) {
        // give seed { rd } to mersenne_twister_engine
        std::random_device rd;
        // the engine generate random numbers unlimitedly
        std::mt19937 mt(rd());
        // bring numbers in continuous random distribution on range[min, max)
        // random number is 4 digit so (min,max] =(999,9999]
        double min { 999 };
        double max { 9999 };
        std::uniform_real_distribution<double> dist(min, max);
        // make  new client to clients (passing id by refrence)
        std::shared_ptr<Client> client {
            std::make_shared<Client>(
                id.append(std::to_string(static_cast<int>(dist(mt)))), *this)
        };
        // add 4 digit to end of id
        id.append(std::to_string(static_cast<int>(dist(mt))));
        // add new client to clients
        clients.insert({ client, 5 });
        return client;
    } else {
        // make and add new client to clients
        std::shared_ptr<Client> client { std::make_shared<Client>(id, *this) };
        clients.insert({ client, 5 });
        return client;
    }
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    // make a new client in object refrence with the same id (client1)
    // then compare clients id s  in server with client1 through loop
    // if same id found between ....
    //  return the client saved in server clients(previous client)
    for (auto iter = clients.begin(); iter != clients.end(); ++iter) {

        if ((iter->first)->get_id() == id) {
            return iter->first;
        }
    }
    // else there is no client with this id
    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    for (auto iter = clients.begin(); iter != clients.end(); ++iter) {

        if ((iter->first)->get_id() == id) {
            return iter->second;
        }
    }
    // else there is no client with this id
    return 0;
}

bool Server::parse_trx(std::string trx, std::string& sender,
    std::string& receiver, double& value)
{
    std::string seperator { "-" };
    size_t count {};
    std::string value_str {};
    if (std::count(trx.begin(), trx.end(), '-') != 2) {
        throw std::runtime_error("not standard form ");
    } else {
        for (auto c : trx) {
            if (c == '-') {
                count++;
                continue;
            }
            switch (count) {
            case 0:
                sender += c;
                break;
            case 1:
                receiver += c;
                break;
            case 2:
                value_str += c;
                break;
            }
        }
        value = std::stod(value_str);
    }
    return 1;
}
void show_wallets(const Server& server)
{
    // using virtual function method to access refrence of private clients
    // notice :its not so good method  unfortunately
    std::map<std::shared_ptr<Client>, double>* serverx
        = (std::map<std::shared_ptr<Client>, double>*)&server;
    std::cout << std::string(20, '*') << std::endl;

    for (auto x = serverx->begin(); x != serverx->end(); x++) {
        std::cout << ((x)->first)->get_id() << " : " << (x)->second
                  << std::endl;
    }
    std::cout << std::string(20, '*') << std::endl;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{

    std::string receiver, sender;
    double value;
    if (parse_trx(trx, sender, receiver, value) != 1) {
        return 0;
    } else if (this->get_client(sender) == nullptr) {
        return 0;
    } else if (this->get_client(receiver) == nullptr) {
        return 0;
    } else if (this->get_wallet(sender) < value) {
        return 0;
    } else {
        auto public_key = (this->get_client(sender))->get_publickey();
        bool authentic = crypto::verifySignature(public_key, trx, signature);
        if (authentic) {
            pending_trxs.push_back(trx);
            return 1;
        }
        return 0;
    }
    return 0;
}

size_t Server::mine()
{
    std::string mempool {};
    for (const auto& trx : pending_trxs)
        mempool += trx;

    for (auto iter = clients.begin();; iter++) {

        auto nonce = (iter->first)->generate_nonce();
        std::string hash { crypto::sha256(mempool + std::to_string(nonce)) };
        if (hash.substr(0, 10).find("000") != std::string::npos) {
            iter->second += 6.25;
            std::cout <<"lucky miner is :"<<(iter->first)->get_id()<<std::endl;
            for (const auto& trx : pending_trxs) {
                std::string sender, receiver;
                double value;
                parse_trx(trx, sender, receiver, value);
                clients[this->get_client(sender)] -= value;
                clients[this->get_client(receiver)] += value;
            }
            pending_trxs.clear();
            return nonce;
        }
        if (iter == clients.end()) {
            iter = clients.begin();
        }
    }
}