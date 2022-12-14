/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:53:00 by dvargas           #+#    #+#             */
/*   Updated: 2023/01/03 10:02:59 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_death(t_philo *philo)
{
	long	cur_time;

	cur_time = get_time_stamp();
	if (philo->last_meal != 0 && (cur_time - philo->last_meal)
		>= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->mutex_kill);
		philo->table->is_dead = 1;
		pthread_mutex_unlock(&philo->table->mutex_kill);
		usleep(200);
		pthread_mutex_lock(&philo->table->print);
		cur_time = get_time_stamp() - philo->table->time_start;
		printf("%ld %d %s \n", cur_time, philo->name, "died");
		pthread_mutex_unlock(&philo->table->print);
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

void	*reaper_routine(void *args)
{
	t_table	*round;
	int		i;

	i = 0;
	round = (t_table *)args;
	while (1)
	{
		pthread_mutex_lock(&round->philos[i]->meal_time);
		if (check_if_death(round->philos[i]) == 1)
		{
			pthread_mutex_unlock(&round->philos[i]->meal_time);
			break ;
		}
		if (check_if_full(round->philos[i]) == 1)
		{
			pthread_mutex_unlock(&round->philos[i]->meal_time);
			break ;
		}
		pthread_mutex_unlock(&round->philos[i]->meal_time);
		i++;
		if (i == round->nb_of_philos)
				i = 0;
	}
	return (NULL);
}
