# The Dining-Philosophers Problem  

This project involves implementing a solution to this problem using either POSIX mutex locks and condition variables or Java condition variables. Solutions will be based on the algorithm illustrated in Figure 7.7.  

```
monitor DiningPhilosophers
{
  enum {THINKING, HUNGRY, EATING} state[5];
  condition self[5];

  void pickup(int i) {
    state[i] = HUNGRY;
    test(i);
    if (state[i] != EATING) {
      self[i].wait();
  }

  void putdown(int i) {
    state[i] = THINKING;
    test((i + 4) % 5);
    test((i + 1) % 5);
  }

  void test(int i) {
    if ((state[(i + 4) % 5] != EATING) &&
    (state[i] == HUNGRY) &&
    (state[(i + 1) % 5] != EATING)) {
      state[i] = EATING;
      self[i].signal();
    }
  }

  initialization code() {
    for (int i = 0; i < 5; i++)
      state[i] = THINKING;
  }
}
```
> Figure 7.7 A monitor solution to the dining-philosophers problem.

Both implementations will require creating five philosophers, each identified by a number 0 . . 4. Each philosopher will run as a separate thread. Philosophers alternate between thinking and eating. To simulate both activities, have each thread sleep for a random period between one and three seconds.


## I. POSIX  
Thread creation using Pthreads is covered in Section 4.4.1. When a philosopher wishes to eat, she invokes the function  

<pre><code>pickup forks(int philosopher_number)</code></pre>  

where `philosopher_number` identifies the number of the philosopher wishing to eat. When a philosopher finishes eating, she invokes  

<pre><code>return forks(int philosopher_number)</code></pre>  

Your implementation will require the use of POSIX condition variables, which are covered in Section 7.3.  


## II. Java  
en a philosopher wishes to eat, she invokes the method `takeForks(philosopherNumber)`, where `philosopherNumbe`r identifies the number of the philosopher wishing to eat. When a philosopher finishes eating, she invokes `returnForks(philosopherNumber)`. Your solution will implement the following interface:  

```
public interface DiningServer
{
  /* Called by a philosopher when it wishes to eat */
  public void takeForks(int philosopherNumber);

  /* Called by a philosopher when it is finished eating */
  public void returnForks(int philosopherNumber);
}
```

It will require the use of Java condition variables, which are covered in Section 7.4.4.  
