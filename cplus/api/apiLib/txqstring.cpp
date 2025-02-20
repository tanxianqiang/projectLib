#include "txqstring.h"

#include "txqcom.h"


#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cstdint>
#include "arpa/inet.h"

// 函数声明

struct uint24_t {
    uint8_t byte[3];
};

uint8_t converBuff[1024] {};
void txq_removeSpaceNewLineTab(std::string& str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](char c){
    if ((c == ' ') || (c == '\t') || (c == '\n')) {return true;}
    return false;}), str.end());
}

template <typename T>
T txq_fillMem(std::stringstream& ss, uint8_t* msg, uint16_t& msgLen) {
    uint16_t tmp;
    T tmpInt;
    auto& mem = *(reinterpret_cast<T*>(msg + msgLen));
    msgLen += sizeof (mem);
    std::string item;
    getline(ss, item, ',');
    if (typeid(T) == typeid(uint8_t))  {
         std::stringstream (item) >> tmp;
         tmpInt = tmp;
    }
    else
    {
        std::stringstream (item) >> tmpInt;
    }
    mem = tmpInt;
    return tmpInt;
}

#define TXQ_FILLMEM8()   txq_fillMem<uint8_t>(ss, msg, msgLen)
#define TXQ_FILLMEM16()  txq_fillMem<uint16_t>(ss, msg, msgLen)
#define TXQ_FILLMEM32()  txq_fillMem<uint32_t>(ss, msg, msgLen)

#define TXQ_FILLMEM8_RE(r)   do{txq_fillMem<uint8_t>(ss, msg, msgLen);}while(--r)
#define TXQ_FILLMEM16_RE(r)  do{txq_fillMem<uint16_t>(ss, msg, msgLen);}while(--r)
#define TXQ_FILLMEM32_RE(r)  do{txq_fillMem<uint32_t>(ss, msg, msgLen);}while(--r)

void txq_strToBuff(std::string& str, uint8_t* msg) {
    uint16_t tmpInt {};
    uint16_t msgLen = 0;
    std::stringstream ss(str);
    // uint8_t times = 3;
    // TXQ_FILLMEM8r(times);
    std::cout << (int16_t)TXQ_FILLMEM8() << std::endl;
    // times = 3;
    // TXQ_FILLMEM8r(times);
    std::cout << (uint16_t)TXQ_FILLMEM8() << std::endl;
    std::cout << TXQ_FILLMEM16()  << std::endl;
}



void testDeep(char* p, std::stringstream& ss) {
     ss << "<>" << '\n';

     if (!(*p)){ return;}
     testDeep(p+1, ss);
    ss << *p;
    ss << "</>" << '\n';

}

int main(int argc, char* argv[]) {
    START_APP(argv[0]);

    #if 0
    std::string str = R"(4,     0101, 1,    2, 3, 4,    5, 6,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5, )";
    txq_removeSpaceNewLineTab (str);
    std::cout << str << std::endl;
    std::cout << "call after:   \n";
    txq_strToBuff(str, converBuff);
    #endif

    std::stringstream ss;
    testDeep("123", ss);
    std::cout << ss.str();


    END_APP(argv[0]);
    return 0;
}