#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void)
{
    void *handler;
    int (*demo_add)(int a,int b);
    char *error;

    handler = dlopen("lib/libliuj.so",RTLD_LAZY);
    if(!handler){
        fprintf(stderr,"open libliuj.so filed %s\n",dlerror());
        exit(1);
    }
    dlerror();

    //*(void **)(&demo_add)= dlsym(handler,"liuj_add");
    demo_add = dlsym(handler,"liuj_del");
          if ((error = dlerror()) != NULL)  {
               fprintf(stderr, "%s\n", error);
               exit(EXIT_FAILURE);
           }

           printf("%d\n", demo_add(2,5));
           dlclose(handler);
           exit(EXIT_SUCCESS);
    
}

