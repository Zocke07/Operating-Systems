# Problem 6.33  

Assumethat a finite number of resources of a single resource type must be managed. Processes may ask for a number of these resources and will return them once finished. As an example, many commercial software packages provide a given number of ***licenses***, indicating the number of applications that may run concurrently. When the application is started, the license count is decremented. When the application is terminated, the license count is incremented. If all licenses are in use, requests to start the application are denied. Such a request will be granted only whenanexisting license holder terminates the application and a license is returned.  

The following program segment is used to manage a finite number of instances of an available resource. The maximum number of resources and the number of available resources are declared as follows:  

```
#define MAX_RESOURCES 5
int available_resources = MAX RESOURCES;
```

When a process wishes to obtain a number of resources, it invokes the `decrease_count()` function:  

```
/* decrease available_resources by count resources */
/* return 0 if sufficient resources available, */
/* otherwise return -1 */
int decrease_count(int count) {
  if (available_resources < count)
    return -1;
  else {
    available_resources -= count;
    return 0;
  }
}
```

When a process wants to return a number of resources, it calls the `increase_count()` function:  

```
 /* increase available_resources by count */
 int increase_count(int count) {
   available_resources += count;
   return 0;
 }
```

The preceding program segment produces a race condition. Do the following:  

1. Identify the data involved in the race condition.
2. Identify the location (or locations) in the code where the race con dition occurs.
3. Using a semaphore or mutex lock, fix the race condition. It is permissible to modify the `decrease_count()` function so that the calling process is blocked until sufficient resources are available.  


# Documentation and Snapshot 6.33  

Using the following code as a base
```
#define MAX_RESOURCES 5
int available_resources = MAX RESOURCES;
int decrease_count(int count) {
  if (available_resources < count)
    return -1;
  else {
    available_resources -= count;
    return 0;
  }
}
 int increase_count(int count) {
   available_resources += count;
   return 0;
 }
```
1. The data involved in the race condition is the `available_resources`
2. The locations in the code where the race condition occurs are at `available_resources -= count` and `available_resources += count`
3. The modified code using the mutex lock is provided in the [source code folder](https://github.com/Zocke07/Operating-Systems/tree/main/HW2/Exercise/6.33/Source).
