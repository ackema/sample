#include "common.h"

int main(int argc, char **argv)
{
    init_debug(0, "/var/log/sample.log", 3, 1024*1024*128, LOG_INFO, "sample");

    log_info("hello, world 1!");



    return 0;
}
