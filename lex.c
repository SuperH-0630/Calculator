#include<stdio.h>
#include<string.h>
#include"token.h"
#include <ctype.h>
#define debug 0

#define is_NUM 1
#define no_NUM 0
#define is_STOP 2

FILE *fp = NULL;

typedef enum NUM_TYPE{
    START=0,
    INT=1,
    DOT=2,
    DOUBLE=3,
} NUM_TYPE;

Token token;
char str=' ';

int get_char_back = 0;

void get_char(){
    if (get_char_back){  // 回退
        get_char_back = 0;
    }
    else{
        str = fgetc(fp);
    }
}

void unget_char(){
    get_char_back = 1;
}

void exit(int);
// int isdigit(char);
double atof(char *);

void get_token(Token *token){
    static int is_number = no_NUM;
    token->type = NULL_TOKEN;
    memset(token->str,0,sizeof(MAX_TOKEN_WIDTH));
    token->NUMBER = 0;
    NUM_TYPE num_type = START;  // 数字输入默认情况

    for (int num=0;;num += 1)
    {
        get_char();  // 取得一个输入的字符
        token->str[num] = str;
        if ((num_type == INT)&&(str == '.')){  // 小数点
            if (num_type == INT){
                num_type++;
                continue;
            }
        }
        else if ((num_type == DOT)&&(isdigit(str))){  // 小数点到小数
            num_type++;
            continue;
            }
        if (num_type != START){
            if (isdigit(str)){  // 整数或者小数
                continue;
            }
            else{
                token->str[num] = '\0';
                is_number = is_NUM;
                unget_char();
                token->NUMBER = atof(token->str);
                return ;
            }
        }

        if (str == ' '){
            token->str[num] = '\0';
            num -= 1;  //num要减少一位，否则就会空出来 
            continue;
        }
        else if ((num_type == START)&&(isdigit(str))){  // 开始写入数字
            token->type=NUM;  // 数字模式
            num_type++;
            continue;
        }
        else if (str == '+'){
            token->type=ADD;
            is_number = no_NUM;
            return;
        }
        else if (str == '-'){
            if (is_number != is_NUM){  // 上一个不是数字，这个是负数
                token->type=NUM;  // 数字模式
                num_type++;
                continue;
            }
            else{
                token->type=SUB;
                is_number = no_NUM;
                return;
            }
        }
        else if (str == '*'){
            token->type=MUL;
            is_number = no_NUM;
            return;
        }
        else if (str == '/'){
            token->type=DIV;
            is_number = no_NUM;
            return;
        }
        else if (str == '('){
            token->type=LB;
            is_number = no_NUM;
            return;
        }
        else if (str == ')'){
            token->type=RB;
            is_number = no_NUM;
            return;
        }
        else if ((str == '\n')|| (str == ';')){  // 停止
            if (is_number == is_STOP){
                token->type=NULL_TOKEN;
                return;
            }
            token->type=STOP;
            token->str[0] = ' ';
            is_number = is_STOP;
            return;
        }
        else if (str = '\\'){  // 多行
            token->type=NULL_TOKEN;
            token->str[0] = ' ';
            is_number = is_STOP;
            return;
        }
        else{  // 停止
            token->type=EXIT;
            token->str[0] = ' ';
            is_number = no_NUM;
            return;
        }
    }
    
}

// #ifdef 0
// void debug_get_token(){
//     get_token(&token);
//     printf("type = %d, str = %s, NUMBER = %f\n", token.type, token.str, token.NUMBER);
// }

// int main(){
//     fp = stdin;
//     while(1){
//     debug_get_token();
//     }
//     return 0;
// }
// #endif