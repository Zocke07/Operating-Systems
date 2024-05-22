# Problem 7.15  

In [Exercise 4.27](https://github.com/Zocke07/Operating-Systems/tree/main/HW2/Exercise/4.27), you wrote a program to generate the Fibonacci sequence. The program required the parent thread to wait for the child thread to finish its execution before printing out the computed values. If we let the parent thread access the Fibonacci numbers as soon as they were computed by the child thread—rather than waiting for the child thread to terminate—what changes would be necessary to the solution for this exercise? Implement your modified solution.
