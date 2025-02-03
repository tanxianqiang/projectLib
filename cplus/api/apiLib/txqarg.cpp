#include "txqarg.h"
#include "txqcom.h"
#include <getopt.h>
#include <cstdio>
#include <iostream>
#include <cstring>

struct SET_ARG_T {
    bool verbose;
    char* outFile;
};
TXQ_STATUS txq_setArg(int argc, char *argv[], void* setArg) {
    const struct option longOptions[] = {
        {"verbose", no_argument,       0, 'v'},
        {"output",  required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };
    const char* shortOptions = "vo:";
    SET_ARG_T& sarg = *((SET_ARG_T*)setArg);
    int opt {};
    int optionIndex {};

    while ((opt = getopt_long(argc, argv, shortOptions, longOptions, &optionIndex))!= -1) {
        switch (opt) {
            case 'v':
                sarg.verbose = true;
                break;
            case 'o':
                sarg.outFile = optarg;
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                return TXQ_FAILURE;
            case ':':
                printf("Missing argument for option: %c\n", optopt);
                return TXQ_FAILURE;
            default:
                break;
        }
    }

    if (sarg.verbose) {
        printf("Verbose mode enabled.\n");
    }

    if (sarg.outFile) {
        printf("Output file: %s\n", sarg.outFile);
    }

    // 处理剩余的非选项参数
    for (; optind < argc; optind++) {
        printf("Non-option argument: %s\n", argv[optind]);
    }

    return TXQ_SUCESS;
}

#if 1
int main(int argc, char* argv[]) {
    START_APP(argv[0]);
    SET_ARG_T setArg {};
    txq_setArg(argc, argv, &setArg);
    if (setArg.verbose) {
        printf("Verbose mode enabled.\n");
    }

    if (setArg.outFile) {
        printf("Output file: %s\n", setArg.outFile);
    }
    END_APP(argv[0]);
}
#endif