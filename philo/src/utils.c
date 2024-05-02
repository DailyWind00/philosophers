/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:56:09 by mgallais          #+#    #+#             */
/*   Updated: 2024/05/02 10:18:01 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_death(t_data *data)
{
	pthread_mutex_lock(&data->dying);
	if (data->someone_ded)
	{
		pthread_mutex_unlock(&data->dying);
		return (true);
	}
	pthread_mutex_unlock(&data->dying);
	return (false);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_data *data, size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (data && check_death(data))
			return ;
		usleep(1);
	}
}

void	philos_printf(t_philo *philo, char *str, char *color,
											bool death_message)
{
	pthread_mutex_lock(&philo->data->writing);
	if (death_message || !check_death(philo->data))
		printf("%s%zu %d %s\n%s", color, get_time() - philo->data->start_time,
			philo->id, str, RESET);
	pthread_mutex_unlock(&philo->data->writing);
}
