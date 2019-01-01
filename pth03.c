// pth03.c
//使用信号了编程实现线程的同步
/*
要求：
1、在程序中创建两个线程，一个用于数据的输入，一个用于数据的计算，主线程用于控制
2、在线程创建之前，使用线程属性操作函数将线程设为分离的
3、实现线程间的同步控制，先输入再计算
****************** ERROR：出现了段错误 ********************
****************** ERROR：出现了段错误 ********************
****************** ERROR：出现了段错误 ********************
****************** ERROR：出现了段错误 ********************
****************** ERROR：出现了段错误 ********************
****************** ERROR：出现了段错误 ********************
****************** ERROR：出现了段错误 ********************
****************** ERROR：出现了段错误 ********************

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
void *pth_input(void *);
void *pth_calc(void *);
sem_t sem1, sem2;
int main(int argc, char *argv[]) {
	char mesg[100];
	pthread_t tid;
	pthread_attr_t attr;
//1 属性操作
	pthread_attr_init(&attr);						//属性初始化
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);		//设为分离
//2 信号操作
	if (sem_init(&sem1, 0, 0) != 0) {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(&sem2, 0, 0) != 0) {
		perror("sem_init");
		exit(1);
	}
	printf("\tpthread semaphore demonstraion.\n");
//3 创建计算线程
	if (pthread_create(&tid, &attr, pth_calc, (void *)mesg) != 0) {
		perror("pthread_create 1");
		exit(2);
	}
//4 创建输入线程
	if (pthread_create(&tid, &attr, pth_input, (void *)mesg) != 0) {
		perror("pthread_create 2");
		exit(2);
	}
//5 主线程
	sem_wait(&sem2);								//等待资源
	printf("\nmain thread tid=%d,mseg=%s\n", pthread_self(), mesg);
//显示立方
	sem_destroy(&sem1);								//销毁sem1
	sem_destroy(&sem2);								//销毁sem2	
	pthread_attr_destroy(&attr);							//销毁属性
	return 0;
}
//6 计算函数
void *pth_calc(void *arg) {
	int i;
	sem_wait(&sem1);								//等待输入
	printf("\ncalc thread, tid=%d\n",pthread_self());				//显示自己的信息
	i = atoi((char *)arg);								//将参数转换为整数
	printf("mseg=%s\n",i*i);							//显示输入的平方
	sprintf((char *)arg,"%d",i*i*i);						//返回参数的立方
	sem_post(&sem1);
	sem_post(&sem2);								//释放资源
}
//7 输入函数
void * pth_input(void *arg) {
	char tmp[11];
	printf("\ninput thread, tid=%d\n",pthread_self());
	printf("Input a interger:");
	fgets(tmp, 10, stdin);
	tmp[strlen(tmp) - 1] = '\0';							//读取整数字符串并去除尾部'\0'
	strcpy((char)arg, tmp);								//通过参数arg返回给主线程
	sem_post(&sem1);
}
