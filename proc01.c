#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
main(){
// 0 定义变量
  pid_t pid;
  printf("Demo Program for Process Create!\n");
// 1 创建子进程
  while((pid=fork() == -1)) {  //若创建失败，则返回 1
    perror("forck()");
    exit(1);
  }
  printf("PID=%d\n",pid);	//打印进程标识符（两个程序的公共部分）
// 2 判断在哪个进程中
  if(pid>0) {			//pid>0，在父进程中
    printf("Parent:ppid=%d\tpid=%d!\n",getppid(),getpid());
  }
  else {			//pid=0，在子进程中
    printf("Child:ppid=%d\tpid=%d!\n",getppid(),getpid());
  }
// 3 两个程序的公共部分
  printf("-------- END --------\n");	//显示结束提示
  exit(0);
}
