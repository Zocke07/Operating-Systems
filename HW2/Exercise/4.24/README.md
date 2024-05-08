# Problem 4.24  

An interesting way of calculating π is to use a technique known as ***Monte Carlo***, which involves randomization. This technique works as follows:  

Suppose you have a circle inscribed within a square. (Assume that the radius of this circle is 1)  

![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/651c2efd-f1d2-406c-87d4-781e8c4d979f)  

- First, generate a series of random points as simple (x,y) coordinates. These points must fall within the Cartesian coordinates that bound the square. Of the total number of random points that are generated, some will occur within the circle.
- Next, estimate π by performing the following calculation:  
  π = 4 × (*number of points in circle*) / (*total number of points*)

Write a multithreaded version of this algorithm that creates a separate thread to generate a number of random points. The thread will count the number of points that occur within the circle and store that result in a global variable. When this thread has exited, the parent thread will calculate and output the estimated value of π. It is worth experimenting with the number of random points generated. As a general rule, the greater the number of points, the closer the approximation to π.  


# Documentation and Snapshot 4.24  

> Linux Ubuntu 22.04.4 with gcc 11.4.0

In the source code folder, run the following command to compile the c program  

<pre><code>gcc montecarlo.c -o montecarlo</code></pre>  

Execute the program by inputting the following command  

<pre><code>./montecarlo</code></pre>  

The user will be prompted to input a number, which indicates the number of the random points that will be created. The user can also input -1 to let the number be random.  

After that, the estimated value of pi will also be outputted, calculated according to the mentioned calculation from the problem.  

Example:  

![image](https://github.com/Zocke07/Operating-Systems/assets/91361456/8c8707c5-48a1-4817-a3b4-fe9cb0ffe678)
