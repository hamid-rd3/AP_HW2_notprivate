#include <iostream>
#include <gtest/gtest.h>
#include "client.h"
#include "server.h"


int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
         std::map<std::string,double> a1;
        std::string a2="asd";
         a1[a2]=5;
        // debug section
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}