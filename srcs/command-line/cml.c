
#include "cml.h"

void help(void)
{
    printf("Usage:cnet-tools [OPTIONS] [TAGS] ...\n\
            \tOPTIONS:\n\
            \t    -b               broadcast\n\
            \t    --arp,           arp attack\n\
            \t    \n\
            \tEXIT:\n\
            \t    0 - ok\n\
            \t    -1 - error\n");
}

int nettools_cml(int argc, char **argv)
{
    if (argc == 1)
    {
        help();
        return 0;
    }

    return 0;
}