#include<stdio.h>
#define MAX_TOKEN_WIDTH 16

// token的类型
typedef enum
{
    NULL_TOKEN,
    NUM,
    ADD,
    SUB,
    MUL,
    DIV,
    END,
    LB,  // 括号：brackets，LB是左(left)括号
    RB,  // 右(right)括号
    STOP,
    EXIT,
} token_type;


typedef struct
{
    token_type type;
    double NUMBER;
    char str[MAX_TOKEN_WIDTH];
} Token;

