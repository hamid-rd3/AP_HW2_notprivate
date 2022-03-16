#include "client.h"
#include "server.h"
#include <gtest/gtest.h>
#include <iostream>
 void  show_pending_transactions()
 {
 	std::cout  <<  std::string(20, '*') <<  std::endl;
 	for(const  auto& trx : pending_trxs)
 		std::cout << trx <<  std::endl;
 	std::cout  <<  std::string(20, '*') <<  std::endl;
 }
int main(int argc, char** argv)
{
    if (false) // make false to run unit-tests
    {
        // Server server {};
        // auto bryan1 { server.add_client("bryan") };
        // auto bryan2 { server.add_client("bryan") };
        // auto bryan3 { server.add_client("bryan") };
        // auto bryan { server.add_client("bryan") };
        // Client const* p { bryan.get() };
        // std::string signature { p->sign("mydata") };
        // // std::cout << bryan1->get_publickey() << std::endl;
        // // std::cout << bryan2->get_publickey() << std::endl;
        // // std::cout << bryan3->get_publickey() << std::endl;
        // Server const * p{&server};
        //  std::map<std::shared_ptr<Client>,double>* serverx=(std::map<std::shared_ptr<Client>,double>*)&server;

        //  for(auto x=serverx->begin();x !=serverx->end() ;x++)
        //         std::cout <<((x)->first)->get_id()<<std::endl;
        // using virtual function method to access refrence of private clients
        //     // notice :its not so good method  unfortunately
        //     std::map<std::shared_ptr<Client>, double>* serverx
        //         = (std::map<std::shared_ptr<Client>, double>*)&server;
        //     std::cout << std::string(20, '*') << std::endl;
 
        //     for (auto x = serverx->begin(); x != serverx->end(); x++) {
        //         std::cout << ((x)->first)->get_id() << " : " << (x)->second << std::endl;
        //     }
        // std::cout << bryan1.get() << std::endl;
        Server server{};
    auto bryan{server.add_client("bryan")};
    auto clint{server.add_client("clint")};
    bool valid{bryan->transfer_money("clint", 0.5)};
    std::cout <<valid <<std::endl;
    show_pending_transactions();

    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret { RUN_ALL_TESTS() };
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}