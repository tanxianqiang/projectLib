#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// 定义长选项
static struct option long_options[] = {
    {"verbose", no_argument,       0, 'v'},
    {"output",  required_argument, 0, 'o'},
    {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
    int opt;
    int option_index = 0;
    char *output_file = NULL;
    int verbose = 0;

    while ((opt = getopt_long(argc, argv, "vo:", long_options, &option_index))!= -1) {
        switch (opt) {
            case 'v':
                verbose = 1;
                break;
            case 'o':
                output_file = optarg;
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                return 1;
            case ':':
                printf("Missing argument for option: %c\n", optopt);
                return 1;
            default:
                break;
        }
    }

    if (verbose) {
        printf("Verbose mode enabled.\n");
    }

    if (output_file) {
        printf("Output file: %s\n", output_file);
    }

    // 处理剩余的非选项参数
    for (; optind < argc; optind++) {
        printf("Non-option argument: %s\n", argv[optind]);
    }

    return 0;
}