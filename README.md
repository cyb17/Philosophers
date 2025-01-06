# Philosophers

A project to learn the basics of threading a process: **threads** and **mutexes**
(see the subject for details).

### How to use it

  * Clone the repository in your terminal.
  * Navigate to the philo repository.
  * Run make.

You will then get an executable program named philo. This program takes the following arguments:

```
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
```

number_of_philosophers: Number of philosophers (max 200).

time_to_die (in ms): Maximum time a philosopher can survive without eating.

time_to_eat (in ms): Time required for a philosopher to eat.

time_to_sleep (in ms): Time a philosopher spends sleeping.

number_of_times_each_philosopher_must_eat (optional): If specified, the simulation stops when each philosopher has eaten at least this number of times.

Example:

```
./philo 5 800 200 200
./philo 5 800 200 200 7
```
Output:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
200 1 is sleeping
200 5 has taken a fork
200 5 has taken a fork
200 5 is eating
200 2 has taken a fork
200 3 is sleeping
200 2 has taken a fork
200 2 is eating
200 4 has taken a fork
400 2 is sleeping
400 3 is thinking
400 1 is thinking
400 5 is sleeping
400 4 has taken a fork
400 4 is eating
400 all philosophers have eaten enough
```
