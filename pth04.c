#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *pth_inc(void *);							//增加1函数
void *pth_dec(void *);							//减少1函数
int num = 500, loop = 5;						//num为指定数，loop为循环次数，即+1，-1的次数
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int main(int argc, char *argv[]) {
	pthread_t tid1, tid2;						//线程id
	printf("pthread mutex_lock demonstration\n");
	printf("A number=%d\n",num);
//1 创建逐个+1的线程
	if (pthread_create(&tid1, NULL, pth_inc, NULL) != 0) {
		perror("pthread_create 1"); exit(2);
	}
//2 创建逐个-1的线程
	if (pthread_create(&tid2, NULL, pth_dec, NULL) != 0) {
		perror("pthread_create 2"); exit(3);
	}
//3 主线程
	pthread_join(tid2, NULL);
	pthread_join(tid1, NULL);
//4 显示增减后值
	printf("\nmain thread tid=%d,the number=%d\n",pthread_self(),num);
	return 0;
}

//5 逐+1函数
void * pth_inc(void *arg){
	int i, j;
	printf("inc thread, tid=%d, the number=%d\n", pthread_self(), num);
	pthread_mutex_lock(&mtx);									//获取互斥锁
	for (i = 0; i < loop; i++){
		j = num; sleep(1); num++;
	}
	pthread_mutex_unlock(&mtx);								//释放互斥锁
}
//6 逐-1函数
void * pth_dec(void *arg) {
	int i, j;
	printf("dec thread, tid=%d, the number=%d\n", pthread_self(), num);
	pthread_mutex_lock(&mtx);									//获取互斥锁
	for (i = 0; i < loop; i++) {
		j = num; sleep(1); num=j-1;
	}
	pthread_mutex_unlock(&mtx);								//释放互斥锁
}
