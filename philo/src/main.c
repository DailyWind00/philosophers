/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:29:34 by mgallais          #+#    #+#             */
/*   Updated: 2024/04/28 14:18:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->dying);
	pthread_mutex_destroy(&data->time_eaten);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

// This function initializes the threads and waits for them to finish.
// It also make them start the routine functions.
static void	init_threads(t_data *data)
{
	size_t	i;

	i = -1;
	printf("Starting simulation\n\n");
	if (data->number_of_philosophers == 1)
	{
		printf("\033[1;37m0 1  has taken a fork\n");
		ft_usleep(data->time_to_die);
		printf("\033[1;31m%li 1 died\n\033[0m", data->time_to_die);
		return ;
	}
	pthread_create(&data->mortuary_keeper, NULL, mortuary, data);
	while (++i < data->number_of_philosophers)
		pthread_create(&data->philos[i].thread, NULL,
			routine, &data->philos[i]);
	if (data->nb_meals != -1)
	{
		pthread_create(&data->cook, NULL, kitchen, data);
		pthread_join(data->cook, NULL);
	}
	i = 0;
	pthread_join(data->mortuary_keeper, NULL);
	while (i < data->number_of_philosophers)
		pthread_join(data->philos[i++].thread, NULL);
	printf("\nSimulation ended\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init(&data, argc, argv))
		return (EXIT_FAILURE);
	init_threads(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
