*This project has been created as part of the 42 curriculum by zoeschne.*

# philosophers

A solution to the dining philosophers problem using threads and mutexes, avoiding deadlocks and data races.
The bonus folder is the same project but using process and semaphores instead.

## Usage

```sh
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Times are in milliseconds. Example: `./philo 5 800 200 200`
