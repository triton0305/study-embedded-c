#include "cli.h"        // project header
#include <stdarg.h>     // standard arguments(인자들)
#include <windows.h>    // platform header

// cli.h에서 정의한 최대 길이만큼 CLI 한 줄 입력 버퍼 배열 정의
static char cli_line_buf[CLI_LINE_BUF_MAX];


// 현재 입력된 전체 길이
// cli.c 안에서만 사용하는 16비트 양의 정수 변수를 cli_line_idx를 만들고
// 처음 값을 0으로 둔다. (16bit = (decimal)0~65535 = (hexa)0xFFFF)
static uint16_t cli_line_idx = 0;

// CLI의 cursor 위치
// 그 문자열 안에서 내가 현재 서있는 위치
static uint16_t cli_cursor = 0;

typedef enum
{
    CLI_STATE_NORMAL = 0,
    CLI_STATE_ESC_RCVD,
    CLI_STATE_BRACKET_RCVD
} cli_input_state_t;

// 표준 출력 콘솔을 가리킬 핸들
static HANDLE hStdout = NULL;

static cli_input_state_t input_state = CLI_STATE_NORMAL;


//from cli.h >> typedef void 로 선언됨
static cli_callback_t ctrl_c_handler = NULL;

static void cliRedrawTail(void)
{
    for ( int i = cli_cursor; i< cli_line_idx; i++)
    {
        cliPrintf("%c", cli_line_buf[i]);
    }

    cliPrintf(" ");

    for (int i  = cli_cursor ; i < cli_line_idx; i++)
    {
        cliPrintf("\b");
    }
}
//handle Character Insert 
static void handleChrInsert(uint8_t c)
{
    if (cli_line_idx >= CLI_LINE_BUF_MAX)
    {
        return;
    }
}

static void handleBackspace(void)
{
    if (cli_cursor ==0 ) return ;
    // cursor 가 처음을 가리키면 함수 종료
    for (int i = cli_cursor; i < cli_line_idx; i++)
    {
        cli_line_buf[i-1] = cli_line_buf[i];
    }

    cli_line_idx--;
    cli_cursor--;       // 프로그램 내부 변수에서 조정

    cliPrintf("\b");    // 우리가 보는 화면에서 조정
    cliRedrawTail();
}

void cliInit(void)
{   // (hStout => line 26) (GSH, SOH => windows.h 's function)
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    cli_line_idx = 0;
    cli_cursor = 0;

    ctrl_c_handler = NULL;

    cliPrintf("\r\n==========================================\r\n");
    cliPrintf("\tMSVC Windows Console CLI Terminal V0.1\r\n");
    cliPrintf("CLI> ");
}


void cliMain(void)
{

}


void cliPrintf(char *fmt, ...)
{
    char buf[256];

    // 가변인자리스트 type선언
    va_list args;       // va : variable argument
                        // ... 으로 들어온 값을 찾는 도구
    int len;

    va_start(args, fmt);

    len = vsnprintf(buf, sizeof(buf), fmt, args);

    va_end(args);

    if (len > 0)
    {
        DWORD written = 0;

        WriteConsoleA(
            hStdout,
            (uint8_t *)buf,
            (DWORD)len,
            &written,
            NULL
        );
    }
}


void cliAdd(char *cmd_str,
            void (*cmd_func)(uint8_t argc, char *argv[]))
{

}


void cliSetCtrlHandler(cli_callback_t handler)
{

}