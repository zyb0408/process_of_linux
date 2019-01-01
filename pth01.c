/*
* 首先进行参数检查，如果没有参数就退出并返回-1.
* 若有参数，就显示工作信息，然后创建线程，并将命令行参数1作为线程函数th_func()的参数。
* 在创建线程是，将线程的属性值设置为NULL让系统为其使用默认属性。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void *th_func(void *);
char mesg[100];						//全局变量
int main(int argc, char *argv[]) {
//0 定义变量
  pthread_t tid;					//线程id
  void *th_ret;						//线程返回结果
//1 命令行出来参数
  if(argc==1){ fprintf(stderr, "Usage: %s string\n", argv[0]); exit(1); }
//2 创建前的显示
  printf("\t\tThis is my 1'st pthread program!\nNow,create a thread.\n");
  strcpy(mesg,argv[1]);					//为全局变量赋值
//3 创建线程
  if(pthread_create(&tid, NULL, th_func,(void *)argv[1])!=0) {	//创建失败
    perror("pthread_create");
    exit(2);
  }
//4 线程等待
  printf("Waiting thread %d to finish...\n",tid);
  if(pthread_join(tid, &th_ret)!=0) {			//failed
    perror("pthread_join");
    exit(3);
  }
//5 线程返回后
  printf("main() report: tid=%d threads %s\n",tid, (char *)th_ret);	//显示结果
  printf("The mesg is '%s'\n",mesg);
  return 0;
}
//6 线程函数
void * th_func(void *arg) {
//6.1 显示线程参数和全局就是mesg
  printf("thread got argument %s,mesg=%s\n",(char *)arg,mesg);
  printf("thread sleeping %d seconds ...\n",3);
  sleep(3);
  strcpy(mesg,"finished");				//修改全部变量
  printf("thread %d finished\n",pthread_self());	//显示自己的tid
//6.2线程返回
  pthread_exit("th_func returned!");
}
