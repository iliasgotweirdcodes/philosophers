# Philosophers (42 Project)

This repository contains my implementation of the **Dining Philosophers** problem using C and POSIX threads (pthreads).

## Project Overview

The Dining Philosophers problem is a classic example in concurrent programming, focusing on resource sharing and synchronization. Philosophers sit at a table with forks between them and alternate between thinking, eating, and sleeping. The challenge is to coordinate their actions to avoid deadlocks (where everyone waits forever) and starvation (where someone never gets to eat).

## Key Features

- **POSIX Threads (pthreads):** Each philosopher is represented as a thread, enabling concurrent execution.
- **Mutex-Based Synchronization:** Forks are shared resources protected by mutexes to ensure that only one philosopher can hold a fork at a time.
- **Deadlock Avoidance:** The program is designed to prevent situations where philosophers are stuck waiting for each other, ensuring continuous progress.
- **Precise Timing:** Philosophers' actions (eat, sleep, think) are controlled to follow specified timing constraints.
- **Graceful Error Handling:** Robust management of input parameters and system errors.

## Problems Solved

- **Resource Contention:** Ensures that no two philosophers pick up the same fork at the same time.
- **Deadlock Prevention:** Implements strategies to avoid cyclic waiting, a common cause of deadlocks.
- **Starvation Prevention:** Guarantees that every philosopher gets a chance to eat, preventing indefinite waiting.
- **Concurrency Management:** Demonstrates safe parallel execution and synchronization in C.

## Threads vs Processes

### Key Differences

| Feature            | Thread                        | Process                        |
|--------------------|------------------------------|--------------------------------|
| Memory Space       | Shares memory with parent     | Separate memory space          |
| Communication      | Fast, via shared memory       | Slower, via IPC mechanisms     |
| Creation Overhead  | Lower                        | Higher                         |
| Scheduling         | Lightweight, faster switch    | Heavier, slower switch         |
| Resource Sharing   | Shares resources easily       | Isolated resources             |

### Why Use Threads Instead of Processes?

- **Efficiency:** Threads are lightweight and faster to create/switch compared to processes.
- **Resource Sharing:** Threads share memory, making it easier and faster to share state (like forks).
- **Simpler Synchronization:** Mutexes work efficiently with threads in the same process.
- **Performance:** Using threads avoids the overhead of inter-process communication and separate memory management.

Threads are ideal for problems like Dining Philosophers, where multiple entities (philosophers) need to perform similar concurrent tasks while sharing resources.

## Build & Run

Clone the repository and build the project:

```sh
git clone https://github.com/iliasgotweirdcodes/philosophers.git
cd philosophers/philo
make
```

Run the simulation:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo 5 800 200 200
```

## References

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)

---

Explore the code and experiment with different scenarios to learn more about concurrent programming!
