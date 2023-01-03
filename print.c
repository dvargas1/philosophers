/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:33:49 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/22 08:33:50 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

time_t	get_time_stamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_sleep(t_philo *philo, long int time_in_ms)
{
	long int	wake_up;

	wake_up = get_time_stamp() + time_in_ms;
	while (get_time_stamp() < wake_up)
	{
		pthread_mutex_lock(&philo->table->mutex_kill);
		if (philo->table->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->table->mutex_kill);
			break ;
		}
		pthread_mutex_unlock(&philo->table->mutex_kill);
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *s)
{
	long	cur_time;

	if (philo->table->is_dead == 0)
	{
		pthread_mutex_lock(&philo->table->print);
		cur_time = get_time_stamp() - philo->table->time_start;
		printf("%ld %d %s \n", cur_time, philo->name + 1, s);
		pthread_mutex_unlock(&philo->table->print);
	}
}
