# Problem 3.21  

The Collatz conjecture concerns what happens when we take any positive integer *n* and apply the following algorithm:  

![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/efb8ca5e-f8b6-4b41-8ca1-9516c8ca07a3)  

The conjecture states that when this algorithm is continually applied, all positive integers will eventually reach 1. For example, if *n* = 35, the sequence is  

35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8, 4, 2, 1  

Write a C program using the `fork()` system call that generates this sequence in the child process. The starting number will be provided from the command line. For example, if 8 is passed as a parameter on the command line, the child process will output 8, 4, 2, 1. Because the parent and child processes have their own copies of the data, it will be necessary for the child to output the sequence. Have the parent invoke the `wait()` call to wait for the child process to complete before exiting the program. Perform necessary error checking to ensure that a positive integer is passed on the command line.


# Documentation and Snapshot 3.21

> Linux Ubuntu 22.04.4 with gcc 11.4.0

In the source code folder, run the following command to compile the c program  

<pre><code>gcc collatz.c -o collatz</code></pre>

Execute the program by inputting the following command  

<pre><code>./collatz [positive integer]</code></pre>  

In this case, we will use ***35*** as the positive integer  

![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/f44bb3ec-a765-4054-a123-d55a605e8557)
