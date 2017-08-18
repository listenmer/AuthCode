//
// Created by scifly-01 on 2017/8/16.
//

#ifndef TESTNATIVELIBS_UTILITY_H
#define TESTNATIVELIBS_UTILITY_H

//#include <jni.h>
#include <string>
#include <chrono>

namespace Utility {
    using std::string;

    using seconds_t                             = std::chrono::seconds;
    using microseconds_t                        = std::chrono::microseconds;
    typedef decltype(seconds_t().count())         seconds_size_t;
    typedef decltype(microseconds_t().count())    microseconds_size_t;


//    std::string         jstring2str(JNIEnv *env, jstring jstr);

    seconds_size_t      time();
    std::string         time_str();
    microseconds_size_t microtime();
    std::string         microtime_str();

    extern std::string default_key;
}

#endif //TESTNATIVELIBS_UTILITY_H
