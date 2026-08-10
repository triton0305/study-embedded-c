#include "app.h"
#include "cli.h"

#include <stdlib.h>


static void cmdHelp(uint8_t argc, char * argv[])
{
    cliPrintf("Help command\r\n");
}

static void appCtrlCHandler(void)
{
    exit(0);
}
void appInit(void)
{
    cliInit();
    cliAdd("help", cmdHelp);
    cliSetCtrlHandler(appCtrlCHandler);
}
void appMain(void)
{
    while(1)
    {
        cliMain();
    }
}



