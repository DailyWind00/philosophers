/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mortuary_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:43:18 by marvin            #+#    #+#             */
/*   Updated: 2024/04/28 09:43:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// This function is the routine of the mortuary keeper. It checks if
// a philosopher is dead and if so, it makes the program end.
void	*mortuary(void *data_struct)
{
	t_data		*data;
	size_t		i;

	data = (t_data *)data_struct;
	while (42)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->time_eaten);
			if (get_time() - data->philos[i].last_meal > data->time_to_die)
			{
				pthread_mutex_unlock(&data->time_eaten);
				pthread_mutex_lock(&data->dying);
				philos_printf(&data->philos[i], "died", B_RED, true);
				data->someone_ded = true;
				pthread_mutex_unlock(&data->dying);
			}
			if (check_death(data))
				return (NULL);
			pthread_mutex_unlock(&data->time_eaten);
			i++;
		}
	}
}
