#include<stdio.h>
#include<setjmp.h>
#define try if(setjmp(env) == 0)  
#define except else  
#define raise() longjmp(env,1)
jmp_buf env;

void fuck(){
    raise();
}

int main(int argc,char *argv[]){
    FILE *fe;
    // /home/songzihuan/test
    if (argc == 2){
        printf(argv[1]);
        FILE *fp = fopen(argv[1], "r");
        atexit(&close);
    }
    else{
        fp = stdin;
    }
    fe= fopen(argv[1], "r");
    char a;
    a = fgetc(fe);
    putchar(a);
    fclose(fe);

    return 0;
}