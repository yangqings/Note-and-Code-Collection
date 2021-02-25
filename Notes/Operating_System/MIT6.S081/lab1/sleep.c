/**
 * @file sleep.c
 * @author YangQingsheng
 * @brief Implement the UNIX program sleep for xv6
 * @version 0.1
 * @date 2021-02-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int seconds;
    if(argc != 2){
        fprintf(2, "usage: sleep [seconds]\n");
        exit(1);
    }

    seconds = atoi(argv[1]);

    if(seconds < 0){
        fprintf(2, "sleep: parameter error\n");
        exit(1);
    }
    printf("Nothing happens for a little while.\n");
    sleep(seconds);
    exit(0);
}