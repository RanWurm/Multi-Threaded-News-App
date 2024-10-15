# Process Management and Multithreading Simulation

This project implements a robust system simulation, designed to showcase key operating system concepts such as process scheduling, multithreading, synchronization, and inter-process communication (IPC). The system is built in C and leverages advanced concurrency mechanisms to manage resources efficiently while executing multiple tasks in parallel.

## Table of Contents
- [Overview](#overview)
- [Project Features](#project-features)
- [Technologies Used](#technologies-used)
- [System Architecture](#system-architecture)
- [Directory Structure](#directory-structure)
- [Setup and Usage](#setup-and-usage)
- [How It Works](#how-it-works)
- [Future Improvements](#future-improvements)
- [License](#license)

## Overview

This project simulates a multi-threaded operating system environment where several threads and processes interact to complete tasks while sharing resources. The main focus is on efficient thread management, synchronization of shared resources, and the implementation of inter-process communication to create a cohesive and performant system.

The project demonstrates how an operating system allocates resources between competing threads and processes, ensuring fairness, preventing deadlocks, and minimizing race conditions.

## Project Features

- **Process Management**: Multiple processes are simulated with clear lifecycle management (creation, execution, termination).
- **Multithreading**: Efficient use of threads to run concurrent tasks, enhancing system performance.
- **Synchronization**: Mutexes and semaphores are employed to prevent race conditions and deadlocks, ensuring threads can access shared resources safely.
- **Inter-Process Communication (IPC)**: Demonstrates how processes communicate with each other using standard IPC techniques.
- **Resource Management**: Proper handling of CPU time and memory allocation across multiple threads and processes.

## Technologies Used

- **C Programming Language**: Core language for process and thread management.
- **POSIX Threads (pthreads)**: Utilized for creating and managing multiple threads.
- **Semaphores & Mutexes**: For synchronization across threads.
- **Makefile**: For automated compilation of the project.

## System Architecture

Below is a diagram that illustrates the structure and flow of the system:

![image](https://github.com/user-attachments/assets/57005ea7-7b4a-4ede-b6eb-200a865e3583)


The key components of the architecture include:

- **Thread Pool**: A pool of worker threads that execute tasks in parallel.
- **Task Scheduler**: Manages the scheduling of tasks and ensures that all threads are efficiently utilized.
- **IPC Mechanism**: Implements communication channels between processes, allowing for coordination and data sharing.
- **Synchronization**: Mutex locks and semaphores are used to avoid race conditions and ensure smooth operation when accessing shared resources.

## Directory Structure

```
Exercise3/
│
├── src/                    # Source files for the project
│   ├── main.c              # Main entry point for the simulation
│   ├── thread_pool.c       # Thread pool implementation
│   ├── scheduler.c         # Task scheduler implementation
│   └── ipc.c               # Inter-process communication logic
│
├── include/                # Header files for function declarations
│   ├── thread_pool.h       
│   ├── scheduler.h
│   └── ipc.h
│
├── Makefile                # Build script for compiling the project
│
└── README.md               # Project documentation
```

## Setup and Usage

### Prerequisites

Ensure you have the following installed:
- GCC (for compiling C programs)
- POSIX-compliant operating system (e.g., Linux)

### Compilation

To compile the project, run the following command from the root directory:

```bash
make
```

This will generate an executable file named `main.out` in the root folder.

### Running the Simulation

Once compiled, you can run the simulation with:

```bash
make run
```

The system will start the multithreaded simulation, where each thread will execute its assigned tasks. Resource management and synchronization mechanisms will be in place to ensure proper execution.

## How It Works

### Multithreading & Synchronization

The project implements a thread pool, where a fixed number of worker threads are created. The thread pool continuously processes incoming tasks, which are submitted by the main process or other threads. Each task may require access to shared resources, for which mutexes and semaphores are used to manage concurrent access.

### Inter-Process Communication

The project also demonstrates basic IPC mechanisms to allow the simulated processes to exchange data or synchronize actions. This is done using pipes, shared memory, or message queues, depending on the specific requirements of the task.

### Scheduling

The scheduler is responsible for allocating tasks to threads in the pool, ensuring that all threads are utilized and no task is left unprocessed. The scheduler follows a fair scheduling algorithm to balance the workload.

## Future Improvements

Some potential improvements that could be made to this project include:

- Dynamic thread pool resizing: Automatically adjust the number of threads based on the system load.
- Advanced IPC methods: Implement more sophisticated IPC techniques such as sockets or remote procedure calls (RPC).
- Improved scheduling algorithms: Incorporate real-time scheduling algorithms for better performance under different workloads.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
