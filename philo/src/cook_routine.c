/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cook_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:43:21 by marvin            #+#    #+#             */
/*   Updated: 2024/04/28 09:43:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	cooking(t_data *data, int philo_number)
{
	int		i;
	int		satisfied_philos;

	i = 0;
	satisfied_philos = 0;
	while (42)
	{
		if (satisfied_philos == philo_number || check_death(data))
			break ;
		pthread_mutex_lock(&data->time_eaten);
		if (data->philos[i].time_eaten == data->nb_meals)
		{
			satisfied_philos++;
			i = (i + 1) % philo_number;
		}
		pthread_mutex_unlock(&data->time_eaten);
	}
}

// This function is the routine of the cook. It makes the cook wait for all the
// philosophers to eat enough meals, then it retires and dies.
// (So someone_ded is set to true and the program ends)
void	*kitchen(void *data_struct)
{
	t_data	*data;
	int		philo_number;

	data = (t_data *)data_struct;
	philo_number = data->number_of_philosophers;
	cooking(data, philo_number);
	pthread_mutex_lock(&data->dying);
	data->someone_ded = true;
	pthread_mutex_unlock(&data->dying);
	return (NULL);
}
