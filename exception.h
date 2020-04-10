#include<setjmp.h>
#define try if(setjmp(env) == 0)  
#define except else  
#define raise longjmp(env,1)
jmp_buf env;