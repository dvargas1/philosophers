/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:32:35 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/22 12:37:08 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_destoy(t_table *round)
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
	pthread_mutex_destroy(&round->mutex_kill);
	pthread_mutex_destroy(&round->print);
}

void	clean_philos(t_table *round)
{
	int	i;

	i = 0;
	while (i < round->nb_of_philos)
	{
		free(round->philos[i]->r_fork);
		free(round->philos[i]);
		i++;
	}
	free(round->philos);
	free(round);

}

void lets_end_this(t_table *round)
{
	mutex_destoy(round);
	clean_philos(round);
}
