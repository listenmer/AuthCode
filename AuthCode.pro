TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cpp/src/modp_base64/modp_b64.cc \
    cpp/src/AuthCode.cpp \
    cpp/src/md5.cpp \
    cpp/src/Utility.cpp \
    cpp/native-lib.cpp \
    main.cpp

HEADERS += \
    cpp/src/modp_base64/modp_b64.h \
    cpp/src/modp_base64/modp_b64_data.h \
    cpp/src/AuthCode.h \
    cpp/src/md5.h \
    cpp/src/Utility.h
