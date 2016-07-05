#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    size_t size;
    char str[11]={'/0'};
    int fd[2];
    if (pipe(fd)<0){
        printf("pipe create error\n");
        exit(-1);
    }
    pid=fork();
    if (pid<0){
        printf("fork child error\n");
    }
    if (pid==0){
        close(fd[0]);
        scanf("%s",str);
        size=write(fd[1],str,10);
        if (size<0){
            printf("write error\n");
            exit(-1);
        }
    }
    else{
        close(fd[1]);
        size=read(fd[0],str,10);
        if (size<0){
            printf("read error\n");
            exit(-1);
        }
        printf("%s\n",str);
    }
    return 0;
}
