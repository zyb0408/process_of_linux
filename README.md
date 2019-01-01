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
> > 使用信号了编程实现线程的同步.[出现了段错误，。。。。] 
> > 要求：1、在程序中创建两个线程，一个用于数据的输入，一个用于数据的计算，主线程用于控制 2、在线程创建之前，使用线程属性操作函数将线程设为分离的.3、实现线程间的同步控制，先输入再计算

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

```
