/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:30:22 by mgallais          #+#    #+#             */
/*   Updated: 2024/04/28 14:20:27 by marvin           ###   ########.fr       */
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

# define LOCK true
# define UNLOCK false

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
	pthread_t			mortuary_keeper;
	size_t				number_of_philosophers;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	ssize_t				nb_meals;
	bool				someone_ded;
	size_t				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing;
	pthread_mutex_t		dying;
	pthread_mutex_t		time_eaten;
}	t_data;

int				init(t_data *data, int argc, char **argv);
bool			check_death(t_data *data);
void			*kitchen(void *data);
void			*mortuary(void *data);
void			*routine(void *philo);
size_t			get_time(void);
void			ft_usleep(size_t time);
void			philos_printf(t_philo *philo, char *str, char *color,
					bool death_message);

#endif