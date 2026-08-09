#ifndef CLI_H
#define CLI_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define CLI_LINE_BUF_MAX 128    //  한줄 입력 최대 128자
#define CLI_CMD_LIST_MAX 32     // 명령어 목록 최대 32개
#define CLI_CMD_ARG_MAX 16      // 인자 최대 16개
#define CLI_HIST_MAX 10         // 히스토리 최대 10개
typedef void (*cli_callback_t)(void);
// 인자 없고 반환값 없는 함수를 가리키는 함수 포인터 타입


// CLI가 외부에 공개하는 함수
void cliInit(void);
void cliMain(void);
void cliPrintf(char *fmt, ...);
void cliAdd(char * cmd_str, void (*cmd_func)(uint8_t argc, char * argv[]));
void cliSetCtrlHandler(cli_callback_t handler);

// command line interface

#endif