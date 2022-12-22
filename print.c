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

time_t	get_time_stamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_sleep(t_philo *philo, long int time_in_ms)
{
	long int	start_time;

	start_time = get_time_stamp();
	while ((get_time_stamp() - start_time) < time_in_ms)
	{
		if (philo->table->is_dead == 1)
			break ;
		usleep(50);
	}
}

void	print_status(t_philo *philo, char *s)
{
	long	cur_time;

	cur_time = get_time_stamp() - philo->table->time_start;
	if (philo->table->is_dead == 0)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%05ld %d %s \n", cur_time, philo->name, s);
		pthread_mutex_unlock(&philo->table->print);
	}
}
