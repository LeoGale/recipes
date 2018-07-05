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
