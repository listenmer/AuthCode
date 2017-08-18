//
// Created by scifly-01 on 2017/8/16.
//

#include "Utility.h"
#include <cstdlib>
#include <memory>
#include <sstream>

namespace Utility {
//    std::string jstring2str(JNIEnv *env, jstring jstr) {
//        const char *cstr = env->GetStringUTFChars(jstr, NULL);
//        std::string str = std::string(cstr);
//        env->ReleaseStringUTFChars(jstr, cstr);
//        return str;
//    }

    seconds_size_t time() {
        const auto epoch = std::chrono::system_clock::now().time_since_epoch();
        const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);

        return seconds.count();
    }

    string time_str() {
        std::ostringstream os;
        os << time();

        return os.str();
    }

    microseconds_size_t microtime() {
        const auto epoch = std::chrono::system_clock::now().time_since_epoch();
        const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(epoch);

        return microseconds.count();
    }

    string microtime_str() {
        std::ostringstream os;
        os << microtime();

        return os.str();
    }

    const char ___[] = {
            'h', 'e', 'l', 'l', '0', 'w', '0', 'r', 'l', 'd', '\0'
    };

    string default_key = ___;
}
