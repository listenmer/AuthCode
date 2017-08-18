//
// Created by scifly-01 on 2017/8/16.
//

#include <sstream>
#include <iomanip>

#include "AuthCode.h"
#include "md5.h"
#include "modp_base64/modp_b64.h"
#include "Utility.h"

using std::string;

static string ssbstr(const string &str, int start, int len = -1, int line = 0) {
    return start >= 0 ? str.substr(start, len == -1 ? string::npos : len) : str.substr(str.length() + start, len == -1 ? string::npos : len);
}

template <typename T>
static string pad(T val, int width = 0, char padchar = ' ') {
    std::ostringstream os;

    os << std::setw(width) << std::setfill(padchar) << val;

    return os.str().substr(0, width);
}

#define md5(str)    MD5(str).toStr()
#define strlen(str) str.size()

#define substr(...) ssbstr(__VA_ARGS__, __LINE__)

typedef int uint;

static string _authcode(string $string, bool $encode, string $key = "", int $expiry = 0) {
    // 动态密匙长度，相同的明文会生成不同密文就是依靠动态密匙
    auto $ckey_length = 8;   // 随机密钥长度 取值 0-32;
    // 加入随机密钥，可以令密文无任何规律，即便是原文和密钥完全相同，加密结果也会每次不同，增大破解难度。
    // 取值越大，密文变动规律越大，密文变化 = 16 的 $ckey_length 次方
    // 当此值为 0 时，则不产生随机密钥
    // 密匙
    $key = md5($key.empty() ? $key : Utility::default_key);

    // 密匙a会参与加解密
    auto $keya = md5(substr($key, 0, 16));

    // 密匙b会用来做数据完整性验证
    auto $keyb = md5(substr($key, 16, 16));

    // 密匙c用于变化生成的密文
    auto $keyc = $ckey_length ?
                (!$encode ? substr($string, 0, $ckey_length)
                          : substr(md5(Utility::microtime_str()), -$ckey_length))
              : "";

    // 参与运算的密匙
    auto $cryptkey = $keya + md5($keya + $keyc);
    auto $key_length = strlen($cryptkey);

    // 明文，前10位用来保存时间戳，解密时验证数据有效性，10到26位用来保存$keyb(密匙b)，解密时会通过这个密匙验证数据完整性
    // 如果是解码的话，会从第$ckey_length位开始，因为密文前$ckey_length位保存 动态密匙，以保证解密正确
    auto $sstring = !$encode ? Base64::decode(substr($string, $ckey_length, -1)) : (pad(0, 10, '0')  + substr(md5($string + $keyb), 0, 16) + $string);
    auto $string_length = strlen($sstring);

    string $result = "";
    uint $box[256];
    for(uint $i = 0; $i <= 255; $i++) {
        $box[$i] = $i;
    }

    uint $rndkey[256];

    // 产生密匙簿
    for(uint $i = 0; $i <= 255; $i++) {
        $rndkey[$i] = $cryptkey[$i % $key_length];
    }

    // 用固定的算法，打乱密匙簿，增加随机性，好像很复杂，实际上对并不会增加密文的强度
    uint $tmp;
    for(uint $j = 0, $i = 0; $i < 256; $i++) {
        $j = ($j + $box[$i] + $rndkey[$i]) % 256;

        $tmp = $box[$i];
        $box[$i] = $box[$j];
        $box[$j] = $tmp;
    }

    // 核心加解密部分
    for(int $a = 0, $j = 0, $i = 0; $i < $string_length; $i++) {

//        std::cout << $i << "\t" << $string_length;
        $a = ($a + 1) % 256;
        $j = ($j + $box[$a]) % 256;
        $tmp = $box[$a];
        $box[$a] = $box[$j];
        $box[$j] = $tmp;
        // 从密匙簿得出密匙进行异或，再转成字符
        $result += (char)($sstring[$i] ^ $box[(int)((int)$box[$a] + (int)$box[$j]) % 256]);
    }

//    std::cout << "#styring:" << $sstring << "\t" << "result.size: " << $result.size() << std::endl;;
    if(!$encode) {
        // 验证数据有效性，请看未加密明文的格式
        if(substr($result, 10, 16) == substr(md5(substr($result, 26, -1) + $keyb), 0, 16)) {
            return substr($result, 26);
        } else {
            return "";
        }
    } else {
        // 把动态密匙保存在密文里，这也是为什么同样的明文，生产不同密文后能解密的原因
        // 因为加密后的密文可能是一些特殊字符，复制过程可能会丢失，所以用base64编码
        return $keyc + Base64::encode($result);
    }
}


void StringReplaceAll(string &strBase, string::value_type src, string::value_type des)
{
    string::size_type pos = 0;

    pos = strBase.find(src, pos);
    while ((pos != string::npos)) {
        strBase.replace(pos, 1, 1, des);
        pos = strBase.find(src, (pos + 1));
    }
}

std::string AuthCode::encryt(const std::string &src)
{
    std::string _src(_authcode(src, true, Utility::default_key, 300));

    StringReplaceAll(_src, '+', '-');
    StringReplaceAll(_src, '/', '_');

    return _src;
}

std::string AuthCode::decryt(const std::string &src)
{
    std::string _src(src);

    StringReplaceAll(_src, '-', '+');
    StringReplaceAll(_src, '_', '/');

    return _authcode(_src, false, Utility::default_key, 300);
}
