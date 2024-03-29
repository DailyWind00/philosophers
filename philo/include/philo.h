/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:30:22 by mgallais          #+#    #+#             */
/*   Updated: 2024/03/08 13:57:11 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <thread_db.h>
# include <stdbool.h>
# include <sys/time.h>

# define RESET "\033[0m"
# define B_RED "\033[1;31m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"
# define B_CYAN "\033[1;36m"
# define B_WHITE "\033[1;37m"

# define CORRECT_SYNTAX "Correct syntax :\n\t./philo <number_of_philosophers>\
 <time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n\
If confusion, check subject -> Global Rules\n"

typedef struct s_philo
{
	struct s_data		*data;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	size_t				last_meal;
	ssize_t				time_eaten;
	int					id;
}	t_philo;

typedef struct s_data
{
	t_philo				*philos;
	pthread_t			cook;
	size_t				number_of_philosophers;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	ssize_t				nb_meals;
	bool				someone_ded;
	size_t				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		writing;
	pthread_mutex_t		dying;
	pthread_mutex_t		time_eaten;
}	t_data;

void			error_exit(t_data *data, char *strerror);
void			init(t_data *data, int argc, char **argv);
void			*kitchen(void *data);
void			*routine(void *philo);
size_t			get_time(void);
void			ft_usleep(size_t time);
bool			starving(t_philo *philo);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
void			philos_printf(t_philo *philo, char *str, char *color,
					bool death_message);
void			free_data(t_data *data);

#endif