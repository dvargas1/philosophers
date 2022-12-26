/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:23:33 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/21 19:25:31 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal = philo->table->time_start;
	pthread_mutex_unlock(&philo->meal_time);
	sim_start_delay(philo->table->time_start);
	if (philo->name % 2 != 0)
		smart_sleep(philo, 100);
	if (philo->table->nb_of_philos == 1)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex_kill);
		if (philo->table->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->table->mutex_kill);
			break ;
		}
		pthread_mutex_unlock(&philo->table->mutex_kill);
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}

int	lets_start(t_table *round)
{
	int	i;

	i = 0;
	round->time_start = get_time_stamp() + (round->nb_of_philos * 2 * 10);
	while (i < round->nb_of_philos)
	{
		if (pthread_create(&round->philos[i]->thread, NULL, \
				&philo_routine, round->philos[i]) != 0)
			return (1);
		i++;
	}
	if (round->nb_of_philos > 1)
	{
		if (pthread_create(&round->reaper, NULL, &reaper_routine, round) != 0)
			return (1);
	}
	return (0);
}

int	lets_join(t_table *round)
{
	int	i;

	i = 0;
	while (i < round->nb_of_philos)
	{
		if (pthread_join(round->philos[i]->thread, NULL) != 0)
			return (1);
		i++;
	}
	if (round->nb_of_philos > 1)
		pthread_join(round->reaper, NULL);
	return (0);
}
