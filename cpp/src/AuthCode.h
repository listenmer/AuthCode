//
// Created by scifly-01 on 2017/8/16.
//

#ifndef TESTNATIVELIBS_AUTHCODE_H
#define TESTNATIVELIBS_AUTHCODE_H

#include <string>

namespace AuthCode {
    std::string encryt(const std::string &src);
    std::string decryt(const std::string &src);
}


#endif //TESTNATIVELIBS_AUTHCODE_H
