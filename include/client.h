#ifndef CLIENT_H
#define CLIENT_H
#include <memory>
#include <string>
#include <iostream>
#include <map>
class Server;//forward declaration
class Client
{
public:
	Client(std::string& id, const Server& server);
	std::string get_id()const;
	// std::string get_publickey();
	// double get_wallet();
	// std::string sign(std::string txt);
	// bool transfer_money(std::string receiver, double value);
	// size_t generate_nonce();
private:
	Server const* const server;
	const std::string id;
	// std::string public_key;
	// std::string private_key;
};

#endif //CLIENT_H