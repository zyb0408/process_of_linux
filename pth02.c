#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define MAX_THRD 3							//最大线程数
void *sleeping(void *);							//线程函数声明
int main(int argc, char *argv[]) {		
  void *th_ret;								//线程返回结果
  int i;								//临时变量
  pthread_t tid[MAX_THRD];						//线程id数组
//1 处理命令行参数
  if(argc==1) { fprintf(stderr, "Usage：%s string\n",argv[0]); exit(0); }
  printf("%s will create %d threads\n",argv[0],MAX_THRD);		//显示线程数
//2 创建MAX_THRD个线程
  for(i=0;i<MAX_THRD;i++)
    pthread_create(&tid[i],NULL,sleeping,(void *)argv[1]);
//3 等待每个线程结束，并显示其返回值
  for(i=0;i<MAX_THRD;i++) {
    pthread_join(tid[i],&th_ret);
	printf("thread %d terminated\n",(int *)th_ret);
  }
//4 显示全部线程结束
  printf("main: all %d threads have been terminated\n",i);
  return 0;
}
//5 线程函数实现
void *sleeping(void *arg) {
  int scnds=atoi(arg);							//临时变量，将参数转化为整数
  printf("thread %d sleeping %d seconds ...\n",pthread_self(),scnds);
  return (void *)pthread_self();					//返回线程的tid
}
