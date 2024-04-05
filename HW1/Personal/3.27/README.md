# Problem 3.27  

Design a file-copying program named `filecopy.c` using ordinary pipes. This program will be passed two parameters: the name of the file to be copied and the name of the destination file. The program will then create an ordinary pipe and write the contents of the file to be copied to the pipe. The child process will read this file from the pipe and write it to the destination file. For example, if we invoke the program as follows:  

<pre><code>./filecopy input.txt copy.txt</code></pre>  

the file `input.txt` will be written to the pipe. The child process will read the contents of this file and write it to the destination file `copy.txt`. You may write this program using either UNIX or Windows pipes.

---

> Linux Ubuntu 22.04.4 with gcc 11.4.0

In the source code folder, run the following command to compile the c program  

<pre><code>gcc fileCopyPipe.c -o fileCopyPipe</code></pre>  

Execute the program by inputing the following command  

<pre><code>./fileCopyPipe [source file] [destination file]</code></pre>  

In this case, we will use ***hello.txt*** as the source file and ***output.txt*** as the destination file  

![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/e3afcb72-e9bb-4a9f-9e03-b2a7d3a5e449)  

As seen from the snapshot above, after executing the program, a file called `output.txt` was made with the content being copied from the `hello.txt` file.
