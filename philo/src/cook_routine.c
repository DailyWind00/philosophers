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

// This function is the routine of the cook. It makes the cook wait for all the
// philosophers to eat enough meals, then it retires and dies.
// (So someone_ded is set to true and the program ends)
void	*kitchen(void *data_struct)
{
	t_data	*data;
	int		i;
	size_t	philos_fulls;

	data = (t_data *)data_struct;
	i = 0;
	philos_fulls = 0;
	while (philos_fulls < data->number_of_philosophers && !check_death(data))
	{
		ft_usleep(NULL, 1);
		pthread_mutex_lock(&data->philos[i].eating);
		if (data->philos[i].time_eaten >= data->nb_meals)
		{
			pthread_mutex_unlock(&data->philos[i].eating);
			philos_fulls++;
			i++;
			continue ;
		}
		pthread_mutex_unlock(&data->philos[i].eating);
	}
	pthread_mutex_lock(&data->dying);
	data->someone_ded = true;
	pthread_mutex_unlock(&data->dying);
	return (NULL);
}
