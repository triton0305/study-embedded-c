#include "app.h"
#include "cli.h"

void appInit(void)
{
    cliInit();
}
void appMain(void)
{
    while(1)
    {
        cliMain();
    }
}



