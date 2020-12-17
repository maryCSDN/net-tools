#include <stdio.h>
#include <string.h>

#include "netops.h"
#include "cml.h"

void help(void)
{
    printf("Usage:cnet-tools [OPTIONS] [TAGS] ...\n\
            \rOPTIONS:\n\
            \r    -b               broadcast\n\
            \r    --arp,           arp attack\n\
            \r    \n\
            \rEXIT:\n\
            \r    0 - ok\n\
            \r   -1 - error\n");
}

int nettools_cml(int argc, char **argv)
{
    if (argc == 1)
    {
        help();
        return 0;
    }

    char *option = argv[1];
    if (strcmp(option, "-b") == 0)
    {
        cheat();
    }
    return 0;
}