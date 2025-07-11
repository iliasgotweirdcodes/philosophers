# Philosophers (42 Project)

This repository contains my implementation of the **Philosophers** project from the 42 curriculum. The project focuses on solving the classic Dining Philosophers problem using threads in C, specifically with POSIX threads (pthreads). Only the mandatory parts are implemented.

## Project Overview

The Dining Philosophers problem is a classic synchronization problem illustrating challenges in concurrent programming. The goal is to prevent deadlocks and race conditions while philosophers (threads) alternate between thinking, eating, and sleeping.

### Features

- **POSIX Threads:** All concurrency is handled using pthreads.
- **Mandatory Parts Only:** This implementation covers the mandatory requirements of the project.
- **Thread-safe Synchronization:** Mutexes are used to manage access to shared resources (forks).
- **Accurate Timing:** The simulation follows strict timing rules for philosophers' actions.

## How to Use

### Build

Clone the repository and build the project using `make`:

```sh
git clone https://github.com/iliasgotweirdcodes/philosophers.git
cd philosophers/philo
make
```

### Run

Usage:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo 5 800 200 200
```

## Project Structure

- **philo/** - Contains all source code for the mandatory part of the project.

## Key Concepts

- **Threads:** Each philosopher is a thread.
- **Mutexes:** Used to protect shared resources (forks).
- **No Deadlocks:** The solution prevents deadlocks and starvation.

## 42 Project Mandatory Requirements

- Only POSIX threads used (no semaphores for mandatory part).
- Proper handling of input arguments.
- Philosophers never die unexpectedly or eat simultaneously.
- All error cases are handled gracefully.

## Resources

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [42 Project Specifications](https://github.com/42Paris/subjects/blob/master/philosophers.pdf)

---

Feel free to explore the code and try out different scenarios!
