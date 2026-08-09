#include "cli.h"        // project header
#include <stdarg.h>     // standard arguments(인자들)
#include <windows.h>    // platform header
#include <conio.h>
#include <string.h>        // memmove()

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

// Windows 표준 출력 콘솔을 식별하기 위한 핸들
// 아직 핸들을 얻지 않았으므로 NULL로 초기화
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
{  // Windows 표준 출력 콘솔의 HANDLE 획득
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
    int key;

    if (!_kbhit())
    {
        return;
    }

    key = _getch();
    
    if (key == 0 || key == 0xE0)
    {
        key = _getch();
        switch(key)
        {   
            // left arrow
            case 75:
                if (cli_cursor>0)
                {
                    cliPrintf("\b");
                    cli_cursor--;
                }
                break;

            // right arrow
            case 77:
                if (cli_cursor < cli_line_idx)
                {
                    cliPrintf("%c", cli_line_buf[cli_cursor]);
                    cli_cursor++;
                }
                break;
        }
        return ;
    }

    // enter 
    if (key == '\r')
    {
        cli_line_buf[cli_line_idx] = '\0';

        cliPrintf("\r\n");

        // 나중에 여기서 명령어 실행
        // cliRunCommand();
        
        cli_line_idx = 0;
        cli_cursor = 0;

        cliPrintf("CLI> ");

        return ;
    }

    // ctrl + c
    if (key == 3)
    {
        if (ctrl_c_handler != NULL)
        {
            ctrl_c_handler();
        }

        cli_line_idx = 0;
        cli_cursor = 0;

        cliPrintf("^C\r\n");
        cliPrintf("CLI> ");
        
        return ;
    }

    // backspace
    if (key == '\b')
    {
        if (cli_cursor > 0 )
        {
            // memmove(목적지, 원본, 몇바이트)
            memmove(
                &cli_line_buf[cli_cursor - 1],
                &cli_line_buf[cli_cursor],
                cli_line_idx - cli_cursor
            );
            cli_cursor--;
            cli_line_idx--;
            
            cli_line_buf[cli_line_idx] = '\0';

            cliPrintf("\b");

            for (uint16_t i = cli_cursor; i< cli_line_idx; i++)
            {
                cliPrintf("%c", cli_line_buf[i]);
            }

            cliPrintf(" ");

            for (uint16_t i = cli_cursor; i<=cli_line_idx; i++)
            {
                cliPrintf("\b");
            }
        }
        return ;
    }
    // general
    if (key >= 32 && key <= 126 )
    {
        if (cli_line_idx < (CLI_LINE_BUF_MAX - 1))
        {
            memmove(
                &cli_line_buf[cli_cursor +1],
                &cli_line_buf[cli_cursor],
                cli_line_idx - cli_cursor
            );
            cli_line_buf[cli_cursor] = (char)key;

            cli_line_idx++;
            cli_cursor++;

            cli_line_buf[cli_line_idx] = '\0';
            for (uint16_t i = cli_cursor -1; i< cli_line_idx; i++)
            {
                cliPrintf("%c", cli_line_buf[i]);
            }
            
            for(uint16_t i = cli_cursor; i < cli_line_idx; i++)
            {
                cliPrintf("\b");
            }
        }
        return;
    }
}


void cliPrintf(char *fmt, ...)
{
    char buf[256];

    // 가변인자리스트 type선언
    va_list args;       // va : variable argument
                        // ... 으로 들어온 값을 찾는 도구
    int len;

    va_start(args, fmt);

    // vsnprintf(결과를 어디에 저장? ,
    //             최대 몇 byte 까지? , 
    //              어떤 형식으로?  ,
    //             어떤 값을 넣어서?)
    len = vsnprintf(buf, sizeof(buf), fmt, args);
    

    va_end(args);

    if (len > 0)
    {
        DWORD written = 0;  // 32-bit unsigned integer 계열

        WriteConsoleA(
            hStdout,            // 어느 콘솔에 출력할건데?
            buf,                // 무엇을 출력할건데?
            (DWORD)len,         // 몇글자 출력할건데 ?
            &written,           //"내가 실제로 몇 글자를 출력했는지"
            NULL                // 예약인자
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