/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:40:12 by mgallais          #+#    #+#             */
/*   Updated: 2024/05/01 12:19:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// This function is used to handle the mutex of the forks. It locks them if
// to_lock is true, and unlock them if to_lock is false.
static void	fork_mutex_handle(t_philo *philo,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, bool to_lock)
{
	if (to_lock)
	{
		pthread_mutex_lock(left_fork);
		pthread_mutex_lock(right_fork);
		philos_printf(philo, "has taken a fork", B_WHITE, false);
		philos_printf(philo, "has taken a fork", B_WHITE, false);
		return ;
	}
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}

// This function is the routine of the philosophers. It makes them eat, sleep
// and think. It also checks if someone is dead or if they eat enough meals.
void	*routine(void *philosoph)
{
	t_philo	*philo;

	philo = (t_philo *)philosoph;
	while (42)
	{
		if (check_death(philo->data))
			return (NULL);
		fork_mutex_handle(philo, philo->l_fork, philo->r_fork, LOCK);
		philos_printf(philo, "is eating", B_YELLOW, false);
		ft_usleep(philo->data, philo->data->time_to_eat);
		pthread_mutex_lock(&philo->eating);
		philo->last_meal = get_time();
		philo->time_eaten++;
		pthread_mutex_unlock(&philo->eating);
		fork_mutex_handle(philo, philo->l_fork, philo->r_fork, UNLOCK);
		philos_printf(philo, "is sleeping", B_CYAN, false);
		ft_usleep(philo->data, philo->data->time_to_sleep);
		philos_printf(philo, "is thinking", B_GREEN, false);
	}
}
