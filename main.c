/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:36:29 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/22 07:32:02 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	help(void)
{
	printf("ERRO DE HELP");
	exit(1);
}

void	lets_end_this(t_table *round)
{
	int	i;

	i = 0;
	while (i < round->nb_of_philos)
	{
		pthread_mutex_destroy(&round->philos[i]->l_fork->lock);
		pthread_mutex_destroy(&round->philos[i]->r_fork->lock);
		pthread_mutex_destroy(&round->philos[i]->meal_time);
		i++;
	}
	i = 0;
	while (i < round->nb_of_philos)
	{
		free(round->philos[i]->r_fork);
		free(round->philos[i]);
		i++;
	}
	free(round->philos);
	pthread_mutex_destroy(&round->mutex_kill);
	pthread_mutex_destroy(&round->print);
	free(round);
}

int	main(int argc, char **argv)
{
	t_table	*round;

	round = malloc(sizeof(t_table) * 1);
	if (!round)
		return (-1); // precisa retornar erro
	if (argc < 5 || argc > 6)
		help();
	if (ft_checkargs(argc, argv) != 0)
		help();
	if (ft_ignite(round, argc, argv) != 0)
		return (1);
	if (lets_start(round) != 0)
		return (1);
	if (pthread_create(&round->reaper, NULL, &reaper_routine, round) != 0)
		return (1);
	if (lets_join(round) != 0)
		return (1);
	if (pthread_join(round->reaper, NULL) != 0)
		return (1);
	lets_end_this(round);
	return (0);
}
