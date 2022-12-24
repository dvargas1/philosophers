/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:53:00 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/21 19:19:35 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo)
{
	long	cur_time;

	cur_time = get_time_stamp();
	if ((cur_time - philo->last_meal) >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->mutex_kill);
		philo->table->is_dead = 1;
		usleep(200);
		pthread_mutex_lock(&philo->table->print);
		cur_time = get_time_stamp() - philo->table->time_start;
		printf("%ld %d %s \n", cur_time, philo->name, "died");
		pthread_mutex_unlock(&philo->table->print);
		pthread_mutex_unlock(&philo->table->mutex_kill);
		return (1);
	}
	return (0);
}

int	check_if_full(t_philo *philo)
{
	if (philo->table->is_full == philo->table->nb_of_philos)
	{
		pthread_mutex_lock(&philo->table->mutex_kill);
		philo->table->is_dead = 1;
		pthread_mutex_unlock(&philo->table->mutex_kill);
		return (1);
	}
	return (0);
}

int	check_if_dead(t_table *round)
{
	int	i;

	i = 0;
	while (i < round->nb_of_philos)
	{
		pthread_mutex_lock(&round->philos[i]->meal_time);
		if (check_death(round->philos[i]) == 1)
		{
			pthread_mutex_unlock(&round->philos[i]->meal_time);
			return (1);
		}
		pthread_mutex_unlock(&round->philos[i]->meal_time);
		if (check_if_full(round->philos[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	*reaper_routine(void *args)
{
	t_table	*round;

	round = (t_table *)args;
	sim_start_delay(round->time_start);
	while (1)
	{
		if (check_if_dead(round) == 1)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
