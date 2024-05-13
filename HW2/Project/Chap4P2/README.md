# Multithreaded Sorting Application  

Write a multithreaded sorting program that works as follows: A list of integers is divided into two smaller lists of equal size. Two separate threads (which we will term ***sorting threads***) sort each sublist using a sorting algorithm of your choice. The two sublists are then merged by a third thread—a ***merging thread*** —which merges the two sublists into a single sorted list.  

Because global data are shared across all threads, perhaps the easiest way to set up the data is to create a global array. Each sorting thread will work on one half of this array. A second global array of the same size as the unsorted integer array will also be established. The merging thread will then merge the two sublists into this second array. Graphically, this program is structured as in Figure 4.27.  

![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/8f97c06a-fab3-47b7-bb49-d8ad1b74479e)  

This programming project will require passing parameters to each of the sorting threads. In particular, it will be necessary to identify the starting index from which each thread is to begin sorting.  

The parent thread will output the sorted array once all sorting threads have exited.


# Documentation and Snapshot Chap4P2  

> Linux Ubuntu 22.04.4 with gcc 11.4.0 and kernel 6.5.0-26-generic.

In the source code folder, run  
<pre><code>gcc sort.c -o sort</code></pre>  
to compile the `sort.c` file and create an executable file called `sort`.  

Run the sort file with the command  
<pre><code>./sort</code></pre>  

Snapshot:  
![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/69314d97-3035-42b3-aeb0-70e37c95f39c)
