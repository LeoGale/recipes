[ TOC ]
# Yet another implementation of lock-free circle array queue 
## Instruduction
Improving applications with high-performance constraints has an obvious choice nowadays
  **<font color=red>Multithreading</font>**, threads are mainly used as a way of dividing the total work 
  into **smaller excution units**, allow them to do actual work(that's processing) while other smaller execution units 
  were waiting for resources.
  i.g., The network application which listens to a TCP port and do processing data once a message arrives through that port.
  You might think one reason using current program, task-separation??
## Under monoprocessor machines, how is processing-eager multithread applications going?
* The program might not have an intended purpose. the overall performance might be the same or worser then before
  * threads might end up "fighting" to get the resource to do real work. 
  * the overhead of data commucation and sharing between threads.
## Under symmetrical multi-processor(SMP) machines. how is the former multithreading applications going?
* The applications would really do several tasks at the same time. (run parallel to each other)
  * each thread will have a real phsical processor, instead of sharing the only one available resource 
    i.g., In a N-processor SMP system, a N-threaded application could reduce the amount of time needed by N times.(it always be less,
    because of there is still overhead 
## Multicore processor is reasonably cheap. but write a muliti-threaded program a not a easy task.
## Problems in multithreading
* deadlock 
* uncontrolled access to shared data
* dynamic memory allocation/deleteing 
* cache trashing 
* Contention on your synchonization mechanism. Queues
## aims to minimize the former three performance related problems
* using array based lock-free queue
## thread 
* the smallest unit of processing that can be scheduled by an operating system, each OS have its implementation of the thread.
* In Linux, (this queue I'm writing about was firstly intended to work in this OS) a thread is just another "context of execution",
in this OS there "is no concept of a thread. Linux implements threads as standard processes. 
The Linux kernel does not provide any special scheduling semantics or data structures to represent threads. 
Instead, a thread is merely a process that shares certain resources with other processes.
## ABA Problems
In multithreaded computing, the ABA problem occurs during synchronization, when a location is read twice, has the same value for both reads, and "value is the same" is used to indicate "nothing has changed". However, another thread can execute between the two reads and change the value, do other work, then change the value back, thus fooling the first thread into thinking "nothing has changed" even though the second thread did work that violates that assumption.

The ABA problem occurs when multiple threads (or processes) accessing shared data interleave. Below is the sequence of events that will result in the ABA problem:

Process 
P
1
P_{1} reads value A from shared memory,
P
1
P_{1} is preempted, allowing process 
P
2
P_{2} to run,
P
2
P_{2} modifies the shared memory value A to value B and back to A before preemption,
P
1
P_{1} begins execution again, sees that the shared memory value has not changed and continues.
Although 
P
1
P_{1} can continue executing, it is possible that the behavior will not be correct due to the "hidden" modification in shared memory.

A common case of the ABA problem is encountered when implementing a lock-free data structure. If an item is removed from the list, deleted, and then a new item is allocated and added to the list, it is common for the allocated object to be at the same location as the deleted object due to optimization. A pointer to the new item is thus sometimes equal to a pointer to the old item which is an ABA problem.
