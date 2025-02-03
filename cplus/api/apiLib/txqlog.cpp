#include "txqlog.h"
#include "txqcom.h"
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"   // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/syslog_sink.h"
#include <cstdarg>
#include <syslog.h>
#include <iostream>

void spdLog(int l, const char *f, ...) {
    const uint16_t len = 512u;
    char buf[len];
    va_list args;
    va_start(args, f);
    vsnprintf(buf, len, f, args);
    va_end(args);
    switch (l) {
        case TXQ_LEVEL_INFO:
            spdlog::info(buf);
            break;
        case TXQ_LEVEL_DEBUG:
            spdlog::debug(buf);
            break;
        case TXQ_LEVEL_WARN:
            spdlog::warn(buf);
            break;
        case TXQ_LEVEL_ERROR:
            spdlog::error(buf);
            break;
        default:
            break;
    }
}

void defaultPrint(int level, const char* f, ...) {
    const uint16_t len = 512u;
    char buf[len];
    snprintf(buf, len, "%s \n", f);
    va_list args;
    va_start(args, f);
    vprintf(buf, args);
    va_end(args);
}

typedef void (*FUNC_LOG)(int l, const char * f, ...);
FUNC_LOG txqLogFuc =  defaultPrint;

#define TXQ_LOG(l, f, ...) do {\
const uint16_t len = 512u;\
char buf[len];\
snprintf (buf, len, "%s %d %s() %s", basename(__FILE__), __LINE__, __FUNCTION__, f);\
txqLogFuc(l, buf, ##__VA_ARGS__);\
} while(0)

#define TXQ_LOG_INFO(f, ...)  TXQ_LOG(TXQ_LEVEL_INFO, f, ##__VA_ARGS__)
#define TXQ_LOG_DEBUG(f, ...)  TXQ_LOG(TXQ_LEVEL_DEBUG, f, ##__VA_ARGS__)
#define TXQ_LOG_WARN(f, ...)  TXQ_LOG(TXQ_LEVEL_WARN, f, ##__VA_ARGS__)
#define TXQ_LOG_ERROR(f, ...)  TXQ_LOG(TXQ_LEVEL_ERROR, f, ##__VA_ARGS__)


void txq_setSpdLogLevel(int l) {
    spdlog::level::level_enum log_level {};
    switch (l) {
        case TXQ_LEVEL_INFO:
            log_level = spdlog::level::info;
            break;
        case TXQ_LEVEL_DEBUG:
            log_level = spdlog::level::debug;
            break;
        case TXQ_LEVEL_WARN:
            log_level = spdlog::level::warn;
            break;
        case TXQ_LEVEL_ERROR:
            log_level = spdlog::level::err;
            break;
        default:
            log_level = spdlog::level::off;
            break;
    }
   spdlog::set_level(log_level);
}

void txq_setSpdLogPath(const char* logPath, const char* logName, bool f) {
    auto old_logger = spdlog::default_logger();
    auto new_logger = old_logger;
    if (f) {
        new_logger = spdlog::basic_logger_mt(logName, logPath, true);
    }
    else {
        new_logger = spdlog::stdout_color_mt("console");
    }
    spdlog::set_default_logger(new_logger);
}


// void setSpdLogFunc() {
//     logInfo = spdlog::info;
//     logDebug = spdlog::debug;
//     logWarn = spdlog::warn;
//     logError = spdlog::error;
// }

void txq_setSpdLog (const char* logPath, const char* logName, bool isInfile, int level) {
    txq_setSpdLogPath(logPath, logName, isInfile);
    txq_setSpdLogLevel(level);
}





void my_logger(int priority, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsyslog(priority, format, args);
    va_end(args);
}

int sysLog() {   // var/log/syslog
    // 配置日志设施
    openlog("MyAppName", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    // 发送不同级别的日志消息
    my_logger(LOG_ERR, "这是一个错误级别的日志信息: %d", 123);
    my_logger(LOG_INFO, "这是一个信息级别的日志信息: %s", "hello world");

    // 关闭日志设施
    closelog();

    return 0;
}


int tanxxxx (char * p ) {

    *p = '\n';
    return 0;
}


int qiangXXXX (char * N ) {

    *N = '\n';
    return 0;
}








// int main(int argc, char* argv[]) {

//     char *p = nullptr;


//     char a = 10;
//     p = &a;
//     if (qiangXXXX(p) == 1) {
//         std::cout << "good, you change it " << std::endl;
//     }

//     p = nullptr;
//     tanxxxx(p);
//     std::cout << "nihoa " << std::endl;
//     p = "nullptr";



// }




#if 1
int main(int argc, char* argv[]) {
    START_APP(argv[0]);
 //   pfunc((const char *)"nihoa %d \n", 1111);
  //  defaultPrint ((const char *)"nihoa %d \n", 123);
   // setSpdLogFunc();
    txq_setSpdLog ((const char*)"txq.log", (const char*)"txq", false, TXQ_LEVEL_ERROR);

    TXQ_LOG_INFO("This an info message with custom info");
    TXQ_LOG_DEBUG("This an info message with custom TXQ_LOG_DEBUG");
    TXQ_LOG_WARN("This an info message with custom TXQ_LOG_WARN");

    TXQ_LOG_ERROR("This an info message with custom TXQ_LOG_ERROR %d %s", 1, "ddfgdffsd");
    TXQ_LOG_ERROR("This an info message with custom TXQ_LOG_ERROR %s","ddfgdffsd");
    END_APP(argv[0]);
}
#endif



