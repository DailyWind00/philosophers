# philosophers ✅100/100
Simulation of the dining philosophers problem

This project makes you understand multi-threading by using threads and mutexes :
- ![philosophers subject](en.philosophers.subject.pdf)

To check if the program have leaks / data races / threads or mutexes errors you have these followind commands / methods :
```shell
valgrind --tool=helgrind ./philo ...
valgrind --tool=drd ./philo ...

# Or go in the Makefile and change the -pthread compiler flag with -fsanitize=thread & recompile the program
```
(note : These commands / methods may cause some lag in the program so it won't work properly, they have to be used only to check errors)
(note : In this project you cannot handle lock-order-inversion errors, these errors have been ignored during my defense)

  To use the program, you must do these commands :
```shell
cd philo
make

# Program :
./philo <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

You also have these commands for cleaning the philo directory :
```shell
# Clean all object files (*.o)
make clean

# Clean executable & object files
make fclean

# Clean everything and recompile the executable
make re
```
