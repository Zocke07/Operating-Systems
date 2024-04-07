# Problem 2.24
In Section 2.3, we described a program that copies the contents of one file to a destination file. This program works by first prompting the user for the name of the source and destination files. Write this program using either the POSIX or Windows API. Be sure to include all necessary error checking, including ensuring that the source file exists.  

Once you have correctly designed and tested the program, if you used a system that supports it, run the program using a utility that traces system calls. Linux systems provide the `strace` utility, and macOS systems use the `dtruss` command. (The `dtruss` command, which actually is a front end to `dtrace`, requires `admin` privileges, so it must be run using `sudo`.) These tools can be used as follows (assume that the name of the executable file is `FileCopy`:  

**Linux:**
<pre><code>strace ./FileCopy</code></pre>
**MacOS:**
<pre><code>sudo dtruss ./FileCopy</code></pre>

Since Windows systems do not provide such a tool, you will have to trace through the Windows version of this program using a debugger.

---

> Linux Ubuntu 22.04.4 with gcc 11.4.0  

In the source code folder, run the following command to compile the c program  
<pre><code>gcc fileCopy.c -o fileCopy</code></pre>  
Execute the program by inputing the following command  
<pre><code>./fileCopy [source file] [destination file]</code></pre> 
In this case, we will use ***hello.txt*** as the source file and ***output.txt*** as the destination file

![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/08c8f267-1dcd-467f-b53a-5191ed88576d)

As seen from the snapshot above, after executing the program, a file called ***output.txt*** was made with the content being copied from the ***hello.txt*** file.

Running the strace command:

![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/63bed835-12d1-48af-b300-777a80e85f6d)
