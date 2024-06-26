# Problem 3.19  

Write a C program called `time.c` that determines the amount of time necessary to run a command from the command line. This program will be run as `./time <command>` and will report the amount of elapsed time to run the specified command. This will involve using `fork()` and `exec()` functions, as well as the `gettimeofday()` function to determine the elapsed time. It will also require the use of two different IPC mechanisms.  

The general strategy is to fork a child process that will execute the specified command. However, before the child executes the command, it will record a timestamp of the current time (which we term “starting time”). The parent process will wait for the child process to terminate. Once the child terminates, the parent will record the current timestamp for the ending time. The difference between the starting and ending times represents the elapsed time to execute the command. The example output below reports the amount of time to run the command ls:  

```
./time ls
time.c
time

Elapsed time: 0.25422
```

As the parent and child are separate processes, they will need to arrange how the starting time will be shared between them. You will write two versions of this program, each representing a different method of IPC.  

The first version will have the child process write the starting time to a region of shared memory before it calls `exec()`. After the child process terminates, the parent will read the starting time from shared memory. Refer to Section 3.7.1 for details using POSIX shared memory. In that section, there are separate programs for the producer and consumer. As the solution to this problem requires only a single program, the region of shared memory can be established before the child process is forked, allowing both the parent and child processes access to the region of shared memory.  

The second version will use a pipe. The child will write the starting time to the pipe, and the parent will read from it following the termination of the child process.  

You will use the `gettimeofday()` function to record the current timestamp. This function is passed a pointer to a struct timeval object, which contains two members: `tv_sec` and `t_usec`. These represent the number of elapsed seconds and microseconds since January 1, 1970 (known as the UNIX EPOCH). The following code sample illustrates how this function can be used:

```
struct timeval current;

gettimeofday(&current,NULL);

// current.tv sec represents seconds
// current.tv usec represents microseconds
```

For IPC between the child and parent processes, the contents of the shared memory pointer can be assigned the `struct timeval` representing the starting time. When pipes are used, a pointer to a `struct timeval` can be written to—and read from— the pipe.


# Documentation and Snapshot 3.19

> Linux Ubuntu 22.04.4 with gcc 11.4.0  

There will be 2 codes, which are for the shared memory version `timeshm.c` and for the pipe version `timepipe.c`.  

In the source code folder, run the following command to compile the `timeshm.c` program  
<pre><code>gcc timeshm.c -o timeshm</code></pre>  
Execute the program by inputting the following command  
<pre><code>./timeshm [command]</code></pre>  
In this case, we will use ***ls*** as the command  
![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/62fff170-8540-45d1-b5c5-e814070e7767)  

In the source code folder, run the following command to compile the `timepipe.c` program  
<pre><code>gcc timepipe.c -o timepipe</code></pre>  
Execute the program by inputting the following command  
<pre><code>./timepipe [command]</code></pre>  
In this case, we will use ***ls*** as the command  
![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/e12c6237-3edf-4070-863b-c03ef4e1af7c)
