#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LINE_MAX 1024			//定义命令缓冲区最大长度

main() {
  char cmd_l[LINE_MAX];			//预留命令缓冲区，最长不得超过LINE_MAX
  char *p="<$ Ctrl_D to exit! $>";	//定义提示符串
// 1 读取键盘的命令字符串，并做相应处理
  while(printf("%s",p),fgets(cmd_l, sizeof(cmd_l)-1, stdin) != NULL) { //读命令串
    cmd_l[strlen(cmd_l)-1]='\0';	//去除尾部回车键
    if(strlen(cmd_l==0))
      continue;				//空串继续
    if(strcasecmp(cmd_l, "exit")==0)
      break;				//exit
// 2 创建子进程
    if(fork()==0) {			//在子进程中
// 3 调用execlp，使用PATH环境变量
      if(execlp(cmd_l, cmd_l, (char*)0)==-1) {	//exec调用错误，返回-1
        fprintf(stderr,"'%s' is not a shell CMD!\n", cmd_l);
        exit(-1);
      }
    }
// 4 在父进程中
    else wait(0);			//等待子进程结束
  }
  exit(0);
}
