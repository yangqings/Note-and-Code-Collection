#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pipe1_p2c[2],pipe2_c2p[2];//two pipe, pipe[0]:read, pipe[1]:wirte
    char buffer[] = {'Y'};
    long length = sizeof(buffer);
    pipe(pipe1_p2c);   
    pipe(pipe2_c2p);



    if(fork() == 0){ //child
        close(pipe1_p2c[1]);
        close(pipe2_c2p[0]);

        if(read(pipe1_p2c[0],buffer,length) != length){
            printf("parent--pipe-->child error\n");
            exit(1);
        }

        printf("%d: received ping\n",getpid());

        if(write(pipe2_c2p[1],buffer,length) != length){
            printf("child--piepe-->parent error\n");
            exit(1);
        }
        exit(0);
    }
    
    //parent
    close(pipe1_p2c[0]);
    close(pipe2_c2p[1]);

    if(write(pipe1_p2c[1],buffer,length) != length){
        printf("parent--pipe-->child error\n");
        exit(1);
    }

    if(read(pipe2_c2p[0], buffer, length) != length){
        printf("child--pipe-->parent error\n");
        exit(1);
    }

    printf("%d: received pong\n",getpid());

    exit(0);
}


