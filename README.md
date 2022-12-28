# Implementation of Merge Sort using Multithreading in C++
The code attached is for implementing multithreading in merge sort. The code of merge sort is taken from Programiz. This code first checks the number of elements user entered. After that, it checks if no. of elements in array are greater than 4 then maximum threads that can be created are 4 and after that it creates 4 threads (maximum no. of threads) and divides the array into maximum of 4 parts (maximum threads that can be created) to sort it in different threads side by side to improve performance. Then main function waits for all threads to complete execution of program and then all the 4 parts of programs are merged into one sorted array and printed on the screen.

To implement multithreading, I used **“pthread.h”** header file with **“pthread_create()”** function to create different threads, after that **“pthread_join()”** is used to join all the threads and continue the execution of main function after **“pthread_join()”**.

As the processing of different parts of array is done through different threads which run side by side, improving the performance of merge sort.

## Working
![Flow Chart](https://github.com/aa22dev/merge-sort-multithreading/img/blob/master/flowChart-OS.png?raw=true)

## Usage
1. Run the program
2. Enter the total no. of elements that you will enter.
3. Start inputting elements
4. Result will be printed.

## Explanation
### Variables
| Variables     | Data Type           | Scope  | Description  	                                                                                                                   |
|---------------|---------------------|--------|----------------------------------------------------------------------------------------------------------------------------------|
| arrSize  	    | int 	               | global | Defines the size of input array                                                                                                  |
| maxThreads    | int 	               | global | Defines the size of maximum no. of Threads                                                                                       |
| currentThread | int 	               | global | Used for keeping record of current thread no.                                                                                    |
| arr[]         | int (pointer)	      | global | Used for storing input numbers                                                                                                   |
| threads[]     | pthread_t (pointer) | local  | Used for making different threads                                                                                                |
| curThread     | int 	               | local  | Used in function called by thread to store current thread no.                                                                    |
| start         | int 	               | local  | Used in multiple functions for dividing array and keeping record of starting index                                               |
| mid           | int 	               | local  | Used in multiple functions for dividing array and keeping record of ending index (of left arr) and starting index (of right arr) |
| end           | int                 | local  | Used in multiple functions for dividing array and keeping record of ending index (of right arr)                                  |
| leftArrSize   | int 	               | local  | Defines the size of left array in merge function                                                                                 |
| rightArrSize  | int 	               | local  | Defines the size of right array in merge function                                                                                |
| left[]        | int (pointer)	      | local  | Store left elements of current divided array                                                                                     |
| right[]       | int (pointer)       | local  | Store right elements of current divided array                                                                                    |
| i             | int 	               | local  | Used for iteration through different arrays                                                                                      |
| j             | int 	               | local  | Used for iteration through different arrays                                                                                      |
| k             | int 	               | local  | Used for merging arrays into one as pointing index                                                                               |

### Functions
| Functions    | Return Type    | Parameters                   | Description  	                                                                                                                                                                                                                                                                   |
|--------------|----------------|------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| main()       | int            | None                         | Main function which is executed when program starts                                                                                                                                                                                                                              |
| *mergeSort() | void (pointer) | void *args                   | Called by threads to define divide array based on the current thread no. (using curThread variable) and implement merge sort                                                                                                                                                     |
| mergeSort()  | void           | int start, int end           | Used to implement merge sort. It divides array into left and right array by defining starting point, ending point and mid point. Mid point defines the ending of left array and starting of right array.                                                                         |
| merge()      | void           | int start, int mid, int end  | This function is called for merging two arrays. Start defines the starting of left array and mid defines the ending of left array and starting of right array. End defines the end of right array. After that, i, j, and k pointers are used for merging left and right arrays.  |

### Libraries Used
| Libraries | Description  	                                                   |
|-----------|------------------------------------------------------------------|
| iostream  | For using console input and output operations                    |
| pthread.h | For creating different threads for array to improve performance  |

### Calculations
```C++
int start = curThread * (arrSize / maxThreads) + (curThread != 0 && arrSize % maxThreads != 0) + (curThread >= 2 && arrSize % maxThreads != 0) + (curThread == 3 && (arrSize % maxThreads == 1 || arrSize % maxThreads == 3));
```
In this part, starting index is being calculated for the array in different threads. 

It multiplies the current thread index (if thread is 1 then 0 is multiplied) with answer of total elements of array divided by maximum no. of threads. 

After that it checks if current thread index is not 0 and mod of size of array with maximum threads is not 0 (to check whether the array is completely divisible into different parts or not) then add 1 else add 0. 

After that it checks if the index of current thread is greater than or equal to 2 (meaning whether the current thread is 3 or 4) and mod of size of array with maximum threads is not 0 (to check whether the array is completely divisible into different parts or not) then add 1 else add 0. 

After that it checks if the index of current thread is equal to 3 (meaning whether the current thread is 4) and mod of size of array with maximum threads is equal to 1 or 3 (to check whether the array is completely divisible into different parts or not) then add 1 else add 0. 

Extra calculation in this part is done to make sure that array that is not completely divisible by maximum number of threads is properly divided.

```C++
int end = (curThread + 1) * (arrSize / maxThreads) - 1 + (curThread < arrSize% maxThreads) + (curThread != 0 && arrSize % maxThreads != 0) + (curThread >= 2 && arrSize % maxThreads != 0) + (curThread == 3 && (arrSize % maxThreads == 1 || arrSize % maxThreads == 3));
```
In this part, ending index is being calculated for the array in different threads.

It multiplies the current thread no. (if thread is 1 then 1 is multiplied) with answer of total
elements of array divided by maximum no. of threads and subtracts 1 from it.

After that it checks if current thread index is less than the mod of size of array with
maximum threads (to check whether the array is completely divisible into different parts or not)
then add 1 else add 0.

After that it checks if current thread index is not 0 and mod of size of array with maximum
threads is not 0 (to check whether the array is completely divisible into different parts or not) then
add 1 else add 0.

After that it checks if the index of current thread is greater than or equal to 2 (meaning
whether the current thread is 3 or 4) and mod of size of array with maximum threads is not 0 (to
check whether the array is completely divisible into different parts or not) then add 1 else add 0.

After that it checks if the index of current thread is equal to 3 (meaning whether the current
thread is 4) and mod of size of array with maximum threads is equal to 1 or 3 (to check whether
the array is completely divisible into different parts or not) then add 1 else add 0.

Extra calculation in this part is done to make sure that array that is not completely divisible
by maximum number of threads is properly divided.


```C++
int mid = (start + end) / 2;
```
Here, the midpoint is calculated to divide the array in two parts (left and right) during
merge sort.

```C++
merge(0, ((arrSize / 2) - 1) / 2, (arrSize / 2));
```
This part comes after the threads have finished their job and joined with main program.

Here 0 is passed as starting index in first parameter. Midpoint of array is calculated and 1 is
subtracted from it and then that answer is divided with 2 to calculate the end point of 1
st thread which is passed as mid in second parameter, after that the midpoint of array is calculated to pass
as end point (of thread 2) in merge function as third array.

This is done to combine arrays generated by thread 1 and thread 2. Thread 1 array is passed
as left and thread 2 array is passed as right array by mentioning starting point, midpoint and end
point of arrays.

```C++
merge(arrSize / 2 + 1, (arrSize / 2) + (arrSize - 1 - (arrSize / 2)) / 2 + (2 < (arrSize % 
maxThreads)), arrSize - 1);
```
This part is to join arrays of thread 3 and 4. Adding 1 to the midpoint of an array gives us
the starting index of array in thread 3.

Subtracting 1 from array size gives us the last index of array from which midpoint is
subtracted and divided by 2, and then midpoint is added. Check is applied to see if the 3rd thread
is less than mod of array size and maximum no. of threads to add 1 or 0 in it. This calculated value
give us the end point of array in thread 3.

Subtracting 1 from array size gives us the last index which is the end point of array in
thread 4.

Somehow, same type of calculations is done when the no. of elements of array are
completely divisible by total no. of maximum threads (4).

```C++
merge(0, (arrSize - 1) / 2 + (arrSize % maxThreads != 0 && arrSize % 2 == 0), arrSize - 1);
```
This part is to join the two arrays returned by previous two merge functions (merge thread 1 & 2 arrays and thread 3 & 4 arrays as one).

Starting index passed is 0 (for left array).

Ending index for left array passed is calculated by calculating the midpoint of array and then adding 1 to it if array size is not completely divisible by maximum no. of threads and it is even.

Ending index for right array passed is calculated by subtracting 1 from array size.
