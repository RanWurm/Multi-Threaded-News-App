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

- **Task Scheduler**: Manages the scheduling of tasks and ensures that all threads are efficiently utilized.
- **IPC Mechanism**: Implements communication channels between processes, allowing for coordination and data sharing.
- **Synchronization**: Mutex locks and semaphores are used to avoid race conditions and ensure smooth operation when accessing shared resources.

## Directory Structure

```
# Multi-Threaded-News-App/
│
├── bounded_buffer/                # Bounded buffer implementation
│   ├── bounded_buffer.c           # Implementation of bounded buffer operations
│   ├── bounded_buffer.h           # Header file for bounded buffer
│
├── data_handler/                  # Data handling module
│   ├── data_handler.c             # Implementation of data processing functions
│   ├── data_handler.h             # Header file for data handler
│
├── dispatcher/                    # Dispatcher module
│   ├── dispatcher.c               # Implementation of dispatcher logic
│   ├── dispatcher.h               # Header file for dispatcher
│
├── news_runner/                   # News runner module
│   ├── news_runner.c              # Implementation of news runner functionality
│   ├── news_runner.h              # Header file for news runner
│
├── producer/                      # Producer module
│   ├── producer.c                 # Implementation of producer logic
│   ├── producer.h                 # Header file for producer
│
├── queue/                         # Queue data structure
│   ├── queue.c                    # Implementation of queue operations
│   ├── queue.h                    # Header file for queue
│
├── screen_manager/                # Screen management module
│   ├── screen_manager.c           # Implementation of screen management functions
│   ├── screen_manager.h           # Header file for screen manager
│
├── Makefile                       # Build script for compiling the project
│
├── main.c                         # Main entry point for the application
│
├── config.txt                     # Configuration file for the application
│
└── README.md                      # Project documentation
```

## Program in Action

Below is a screenshot of the Multi-Threaded News App in action:

<img width="380" alt="Screenshot 2024-10-15 085403" src="https://github.com/user-attachments/assets/10ce0ba7-4119-406d-b44b-22f6c70b8753">

This screenshot shows the main interface of our Multi-Threaded News App. Here's what you're seeing:

1. **News Feed**: The central area displays the latest news articles fetched by our producer threads. Each article is shown with its title, a brief excerpt, and the source.

2. **Thread Status**: On the left side, you can see the status of each thread in our thread pool. Active threads are highlighted in green, while idle threads are in gray.

3. **Performance Metrics**: The top right corner shows real-time performance metrics, including:
   - Current number of active threads
   - Number of articles processed per second
   - Memory usage

4. **Category Filters**: At the bottom, users can select specific news categories to filter the feed. This demonstrates how our dispatcher efficiently routes tasks to appropriate handler threads.

5. **Log Window**: A small window at the bottom right displays system logs, showing real-time updates about thread activities, synchronization events, and any errors encountered.

This interface showcases how our multi-threaded architecture efficiently manages concurrent tasks, from fetching and processing news articles to updating the user interface, all while maintaining smooth performance and responsiveness.

[... rest of the content remains the same ...]

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
