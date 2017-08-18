#include <iostream>

using namespace std;

#include "cpp/src/AuthCode.h"


int main()
{
    auto a = AuthCode::encryt("1234");

    std::cout  << a << std::endl
               << AuthCode::decryt(a)<< std::endl;
    return 0;
}
