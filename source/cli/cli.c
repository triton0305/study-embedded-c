#include "cli.h"        // project header
#include "uart_win.h"

#include <stdarg.h>     // standard arguments(인자들)
//#include <windows.h>    // platform header
//#include <conio.h>
#include <string.h>
//=================typedef=================
typedef enum
{
    CLI_STATE_NORMAL = 0,
    CLI_STATE_ESC_RCVD,
    CLI_STATE_BRACKET_RCVD
} cli_input_state_t;

typedef struct
{
    char *cmd_str;
    void (*cmd_func)(uint8_t argc, char *argv[]);
} cli_cmd_t;

//=================static variable=================
// CLI 한 줄 입력 버퍼
static char cli_line_buf[CLI_LINE_BUF_MAX];

// 현재 입력된 문자열 길이
static uint16_t cli_line_idx = 0;

// 현재 cursor 위치
static uint16_t cli_cursor = 0;

// 등록된 CLI 명령어 목록
static cli_cmd_t cli_cmd_list[CLI_CMD_LIST_MAX];

// 현재 등록된 명령어 개수
static uint8_t cli_cmd_count = 0;

// Windows 표준 출력 HANDLE
//static HANDLE hStdout = NULL;
//static HANDLE hStdin = NULL;

// CLI 입력 상태
static cli_input_state_t input_state = CLI_STATE_NORMAL;

// Ctrl+C callback
static cli_callback_t ctrl_c_handler = NULL;

//=================function=================
static void cliRedrawTail(bool erase_last)
{

    for ( int i = cli_cursor; i< cli_line_idx; i++)
    {
        cliPrintf("%c", cli_line_buf[i]);
    }
    if (erase_last)
    {
        cliPrintf(" ");
        cliPrintf("\b");
    }
    for (int i  = cli_cursor ; i < cli_line_idx; i++)
    {
        cliPrintf("\b");
    }
}
//handle Character Insert 
static void handleChrInsert(uint8_t c)
{   
    if (cli_line_idx >= (CLI_LINE_BUF_MAX-1))
    {
        return;
    }
    for (int i = cli_line_idx; i> cli_cursor; i--)
    {
        cli_line_buf[i] = cli_line_buf[i-1];
    }
    cli_line_buf[cli_cursor] = (char)c;
    cli_line_idx++;

    cli_line_buf[cli_line_idx] = '\0';

    cliPrintf("%c", cli_line_buf[cli_cursor]);
    cli_cursor++;

    cliRedrawTail(false);
    return;
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
    cliPrintf("\b");
    cli_line_buf[cli_line_idx] = '\0';
    
    cliRedrawTail(true);
    return ;
}

static void cliRunCommand(void)
{
    char * argv[CLI_CMD_ARG_MAX];
    uint8_t argc = 0;

    char *p = cli_line_buf;

    while (*p == ' ')
    {
        p++;
    }
    if (*p == '\0')
    {
        return;
    }

    while(*p != '\0' && argc < CLI_CMD_ARG_MAX)
    {
        argv[argc] = p;
        argc ++;

        while(*p != '\0' && *p != ' ')
        {
            p++;
        }
        if(*p == ' ')
        {
            *p = '\0';
            p++;
        }
        while(*p == ' ')
        {
            p++;
        }
    }

    bool found = false;

    for (int i = 0 ; i < cli_cmd_count ; i++ )
    {
        if(strcmp(argv[0], cli_cmd_list[i].cmd_str)==0)
        {
            cli_cmd_list[i].cmd_func(argc, argv);
            found = true;
            break;
        }
    }
    if (found == false)
    {
        cliPrintf("Unknown command: %s\r\n", argv[0]);
    }
}


void cliInit(void)
{   /*Windows 표준 출력 콘솔의 HANDLE 획득
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;
    
    GetConsoleMode(hStdin, &mode);

    mode &= ~ENABLE_PROCESSED_INPUT;
    SetConsoleMode(hStdin, mode);
    */
    uartInit();

    cli_line_idx = 0;
    cli_cursor = 0;
    input_state = CLI_STATE_NORMAL;

    ctrl_c_handler = NULL;

    cliPrintf("\r\n===============================================================\r\n");
    cliPrintf("\tMSVC Windows Console CLI Terminal V0.1\r\n");
    cliPrintf("CLI> ");
}


void cliMain(void)
{
    /*
    int key;

    if (!_kbhit())
    {
        return;
    }

    key = _getch();
    */
    uint8_t key;
    
    if (uartReadBlock(0, &key, 0) == false)
    {
        return;
    }

    /*
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
    */
    if (input_state == CLI_STATE_BRACKET_RCVD)
    {
        if(key == 'D')  // Left
        {
            if(cli_cursor > 0)
            {
                cliPrintf("\b");
                cli_cursor--;
            }
        }
        else if(key=='C')   // right
        {
            if (cli_cursor < cli_line_idx)
            {
                cliPrintf("%c", cli_line_buf[cli_cursor]);
                cli_cursor++;
            }
        }
        input_state = CLI_STATE_NORMAL;
        return ;
    }



    if(input_state == CLI_STATE_ESC_RCVD)
    {
        if(key=='[')
        {
            input_state = CLI_STATE_BRACKET_RCVD;
        }
        else
        {
            input_state = CLI_STATE_NORMAL;
        }
        return ;
    }

    if (key == 0x1B)
    {
        input_state = CLI_STATE_ESC_RCVD;
        return;
    }

    // enter 
    if (key == '\r')
    {
        cli_line_buf[cli_line_idx] = '\0';

        cliPrintf("\r\n");

        cliRunCommand();
        
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
    if (key == '\b' || key == 0x7F)
    {
        handleBackspace();
        return ;
    }
    // general
    if (key >= 32 && key <= 126 )
    {
        handleChrInsert((uint8_t)key);
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
        /*
        DWORD written = 0;  // 32-bit unsigned integer 계열

        WriteConsoleA(
            hStdout,            // 어느 콘솔에 출력할건데?
            buf,                // 무엇을 출력할건데?
            (DWORD)len,         // 몇글자 출력할건데 ?
            &written,           //"내가 실제로 몇 글자를 출력했는지"
            NULL                // 예약인자
        );
        */
        uartWrite(0, (uint8_t *)buf, (uint32_t)len);
    }
}


void cliAdd(char *cmd_str,
            void (*cmd_func)(uint8_t argc, char *argv[]))
{
    if(cli_cmd_count >= CLI_CMD_LIST_MAX)
    {
        return;
    }
    cli_cmd_list[cli_cmd_count].cmd_str = cmd_str;
    cli_cmd_list[cli_cmd_count].cmd_func = cmd_func;
    cli_cmd_count++;
}

void cliSetCtrlHandler(cli_callback_t handler)
{
    ctrl_c_handler = handler;
}