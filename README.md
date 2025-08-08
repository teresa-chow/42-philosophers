# Philosophers - Thread Synchronization with Mutexes
[![42 School: Rank 3](https://img.shields.io/badge/42%20School-Rank%203-%2315bbbb)](https://www.42network.org/)

_This project is based on the dining philosophers problem, a classic concurrency problem in computer science. It presents an opportunity to learn about synchronization issues and how to resolve them._

___


### Table of contents
[Features](#features) · [Usage](#usage) · [License](#license) · [Study notes](#study-notes)

</br>

![demo](./philosophers.gif)

</br>

___

## Features

- Thread creation and management for parallel task execution

- Structured sequencing of operations with precise timing control

- Mutex-based synchronization for controlled access to shared resources

- Configurable runtime parameters through command-line input

- Real-time monitoring of thread states and timing constraints

- Graceful termination of all threads upon meeting stop conditions

- Error handling and memory management


</br>

## Usage
### Setup and compilation

1. Clone repository
    ```bash
    git clone git@github.com:teresa-chow/42-philosophers.git philosophers
    ```

2. Go inside project directory and run `make`
    ```bash
    cd philosophers/philo
    make
    ```

3. Execute `philo` program
    ```bash
    ./philo <number_of_philosophers> <time_to_die_ms> <time_to_eat_ms> <time_to_sleep_ms> [number_of_times_each_philosopher_must_eat]
    ```

</br>

___

### License
This work is published under the terms of [MIT License](./LICENSE).

</br>

#### Study notes

Further reading on the topic: [Wiki](https://github.com/teresa-chow/42-philosophers/wiki)

</br></br>

[⬆ back to top](#philosophers---thread-synchronization-with-mutexes)
