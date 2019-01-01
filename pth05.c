#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>
#define BUFFER_NUM 10
typedef struct {
	int no;
	char content[10];
} buffer_t;
buffer_t *buffer;
int buffi = 0, buffo = 0, cnt = 0;
int run_time = 20, prd_num = 1, cst_num = 1;
sem_t full, avail;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *producer(void *arg) {
	int delay_time = 0, err;
	buffer_t iterm;
	while (1) {
		delay_time = (int)(rand()*10.0 / RAND_MAX / 3.0) + 1;
		sleep(delay_time);
		if (sem_wait(&avail) != 0) { perror("sem_wait(avail)"); break; }
		err = pthread_mutex_lock(&mutex);
		if (err != 0) { printf("mutex lock:%s\n", strerror(err)); break; }
		printf("Producer %d: delay=%d\n",pthread_self(),delay_time);
		iterm.no = cnt;
		sprintf(iterm.content,"%5.5d",cnt);
		buffer[buffi] = iterm;
		buffi = (buffi + 1) % BUFFER_NUM;
		cnt++;
		pthread_mutex_unlock(&mutex);
		if (sem_post(&full) != 0) { perror("sem_post"); break; }
	}
	pthread_exit(NULL);
}
void *consumer(void *arg) {
	int delay_time, err;
	buffer_t iterm;
	while (1) {
		delay_time = (int)(rand()*10.0 / RAND_MAX / 3.0) + 1;
		sleep(delay_time);
		if (sem_wait(&avail) != 0) { perror("sem_wait(avail)"); break; }
		err = pthread_mutex_lock(&mutex);
		if (err != 0) { printf("mutex lock:%s\n", strerror(err)); break; }
		iterm = buffer[buffo];
		printf("Consumer %d: delay_time=%d\n buffer[%d] ITERM[%d],%d,%s\n",
			pthread_self(),delay_time,buffo,cnt,iterm.no,iterm.content);
		buffo = (buffo + 1) % BUFFER_NUM;
		pthread_mutex_unlock(&mutex);
		if (sem_post(&avail) != 0) { perror("sem_post"); break; }
	}
	pthread_exit(NULL);
}


main(int argc, char **argv) {
	pthread_t *prd_tid, *cst_tid;
	int i, ret, buff_num;
	if (argc == 1) buff_num = BUFFER_NUM;
	if (argc == 2) buff_num = atoi(argv[1]);
	if (argc == 3) { buff_num = atoi(argv[1]); prd_num = atoi(argv[2]); }
	if (argc == 4) {
		buff_num = atoi(argv[1]); prd_num = atoi(argv[2]); cst_num = atoi(argv[3]);
	}
	if (buff_num == 0) buff_num = BUFFER_NUM; srand(time(NULL));
	if ((buffer = (buffer_t *)calloc(buff_num, sizeof(buffer_t))) == NULL) {
		perror("calloc buffer"); exit(errno);
	}
	if ((prd_tid = (pthread_t *)calloc(prd_num, sizeof(pthread_t))) == NULL) {
		perror("calloc prd_tid"); exit(errno);
	}
	if ((cst_tid = (pthread_t *)calloc(cst_num, sizeof(pthread_t))) == NULL) {
		perror("calloc cst_tid"); exit(errno);
	}
	if(sem_init(&avail,0,BUFFER_NUM)!=0 || sem_init(&full,0,0)!=0) {
		printf("semaphore init error\n"); exit(3);
	}
	for (i = 0; i < prd_num; i++) {
		if ((ret = pthread_create(prd_tid + 1, NULL, producer, NULL)) != 0) {
			printf("pthread create prd: %s\n",strerror(ret)); exit(ret);
		}
	}
	for (i = 0; i < cst_num; i++) {
		if ((ret = pthread_create(cst_tid + 1, NULL, consumer, NULL)) != 0) {
			printf("pthread create cst: %s\n",strerror(ret)); exit(ret);
		}
	}
	for (i = 0; i < prd_num; i++) pthread_join(prd_tid[i], NULL);
	for (i = 0; i < cst_num; i++) pthread_join(cst_tid[i], NULL);
	free(prd_tid);
	free(cst_tid);
	sem_destroy(&avail);
	sem_destroy(&full);
	return 0;
}