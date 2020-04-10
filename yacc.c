#include <stdio.h>
#include"lex.c"
#include<setjmp.h>

// Token old_token;
int need_TOOKEN = 1;
int jup_number = 0;

void safe_get_token(Token *token){
    if (need_TOOKEN){
        while (1)
        {
            get_token(token);
            if (token->type != NULL_TOKEN){  // 忽略空语句
                break;
            }
        }
    }
    else{
        need_TOOKEN = 1;
    }
}

void unget_token(){
    need_TOOKEN = 0;
}

double base(int jmp, jmp_buf *self_env){
    double polynomial();  // 声明

    safe_get_token(&token);
    if (token.type == NUM){
        return token.NUMBER;
    }
    else if (token.type == LB){  // 遇到括号
        double value = polynomial();
        safe_get_token(&token);
        if (token.type = RB){  // 右括号
            return value;
        }
        longjmp(*self_env, jmp);
    }
    else{
        longjmp(*self_env, jmp);
    }
}

double term(int jmp, jmp_buf *self_env){
    jmp_buf env;
    jup_number = setjmp(env);
    if (jup_number == 1){
        unget_token();
        goto returnZero;
    }
    else if (jup_number == 2){
        unget_token();
        goto returnV1;
    }

    double v1 = base(1, &env);
    while (1){
        safe_get_token(&token);
        if (token.type == MUL){
            double v2 = base(2, &env);
            v1 *= v2;
        }
        else if (token.type == DIV){
            double v2 = base(2, &env);
            v1 /= v2;
        }
        else{
            unget_token();
            break;
        }
    }
    returnV1:return v1;

    returnZero:longjmp(*self_env, jmp);
}

double polynomial(int jmp, jmp_buf *self_env){
    jmp_buf env;
    jup_number = setjmp(env);
    if (jup_number == 1){
        unget_token();
        goto returnZero;
    }
    else if (jup_number == 2){
        unget_token();
        goto returnV1;
    }

    double v1 = term(1, &env);
    while (1){
        safe_get_token(&token);
        if (token.type == ADD){
            double v2 = term(2, &env);
            v1 += v2;
        }
        else if (token.type == SUB){
            double v2 = term(2, &env);
            v1 -= v2;
        }
        else{
            unget_token();
            break;
        }
    }
    returnV1:return v1;

    returnZero:longjmp(*self_env, jmp);
}

double expression(){  // 收集STOP的
    jmp_buf env;
    jup_number = setjmp(env);
    if (jup_number == 1){
        safe_get_token(&token);
        if (token.type == EXIT){
            puts("Bye bye!");
            exit(1);
        }
        return 0;
    }

    double v1 = polynomial(1, &env);

    safe_get_token(&token);
    if ((token.type != STOP) && (token.type != EXIT)){
        unget_token();
        }
    return v1;
}

void show_answer(){
    while (token.type != EXIT){
        printf("answer = %f\n", expression());
    }
}

void close(){
    fclose(fp);
}

int main(int argc,char *argv[]){
    int atexit (void (*function) (void));

    if (argc == 2){
        printf("from %s >>>\n", argv[1]);
        fp = fopen(argv[1], "r");
        atexit(&close);
    }
    else{
        fp = stdin;
        fflush(fp);
    }
    show_answer();
    return 0;
}