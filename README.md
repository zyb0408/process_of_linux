# Linux下进程的一些实例代码

> 进程创建系统调用

> > proc01.c:创建一个子进程，并观察父子进程表示和fork()返回后的执行情况
> > 要求：分别在父子进程中各自显示自己和父进程PID

> > proc02.c:使用fork() exec()设计一个恒旭，实现shell对命令执行的简单功能
> > 要求：程序执行是从键盘接收命令字符串，当命令串非空时，创建子进程，并在子进程中执行输入的命令，父进程等待子进程退出，然后再接收下一条命令。如果用户输入的命令是exit，则父进程结束执行。

> > pth01.c：创建线程，实现主线程向新线程传递变量，子线程在执行时使用参数变量，并在结束时返回一个给定值。
> > 要求：1，主线程创建一个线程，向线程传递一个字符串变量，并显示新线程创建前后的信息；2，线程显示得到的变量，并在结束时返回“th_func returned"；3，同时观察全局变量在线程中的实验情况

> > pth02.c: 在主函数中创建多个线程，并等待每个线程的结束。
> > 要求在线程的创建前后和线程工作期间给出过程信息

> > pth03.c: 使用信号量编程实现线程的同步.[出现了段错误，。。。。] 
> > 要求：1、在程序中创建两个线程，一个用于数据的输入，一个用于数据的计算，主线程用于控制 2、在线程创建之前，使用线程属性操作函数将线程设为分离的.3、实现线程间的同步控制，先输入再计算

> > pth04.c: 使用互斥量实现线程间同步。使用互斥锁保护临界区
> > 要求：两个线程函数，一个用于全局变量的逐1正价；另一个用于对全局变量逐1减少，在主线程的控制下，增减相同的次数后，使其值保持不变。

> > pth05.c：使用互斥量解决生产者和消费者问题
> > 1.为了便于观察使用随机函数产生生产者与消费者间的时间间隔，2.设计出具有N个有界缓冲区的生产者和消费者线程函数，3.主线程用于控制，4.尝试多个生产者与消费者的情况
```
gcc -o pth01 pth01.c -lpthread

tf@z:~/zyb/gitrepo/process_of_linux$ ./pth01 "1 2 3 4 5"
		This is my 1'st pthread program!
Now,create a thread.
Waiting thread -2084256000 to finish...
thread got argument 1 2 3 4 5,mesg=1 2 3 4 5
thread sleeping 3 seconds ...
thread -2084256000 finished
main() report: tid=-2084256000 threads th_func returned!
The mesg is 'finished'

tf@z:~/zyb/gitrepo/process_of_linux$ ./pth02 4
./pth02 will create 3 threads
thread 1203795712 sleeping 4 seconds ...
thread 1195403008 sleeping 4 seconds ...
thread 1187010304 sleeping 4 seconds ...
thread 1203795712 terminated
thread 1195403008 terminated
thread 1187010304 terminated
main: all 3 threads have been terminated

tf@z:~/zyb/gitrepo/process_of_linux$ ./pth05 20 2 3
Consumer 1024923392: delay_time=1
 buffer[0] ITERM[0],0,
Producer 1041708800: delay=3
Producer 1050101504: delay=3
Consumer 1016530688: delay_time=3
 buffer[1] ITERM[2],1,00001
Consumer 1033316096: delay_time=3
 buffer[2] ITERM[2],0,
Consumer 1024923392: delay_time=3
 buffer[3] ITERM[2],0,
...
```
