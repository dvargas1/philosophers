/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:26:13 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/21 19:32:37 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_fork(t_philo *philo, char a)
{
	if (a == 'l')
	{
		pthread_mutex_lock(&philo->l_fork->lock);
		print_status(philo, "has taken a fork");
	}
	if (a == 'r')
	{
		pthread_mutex_lock(&philo->r_fork->lock);
		print_status(philo, "has taken a fork");
	}
}

void	drop_fork(t_philo *philo, char a)
{
	if (a == 'l')
		pthread_mutex_unlock(&philo->l_fork->lock);
	if (a == 'r')
		pthread_mutex_unlock(&philo->r_fork->lock);
}

void	eat_routine(t_philo *philo)
{
	get_fork(philo, 'l');
	get_fork(philo, 'r');
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_time);
	philo->times_eat++;
	if (philo->times_eat == philo->table->many_eats)
		philo->table->is_full++;
	philo->last_meal = get_time_stamp();
	pthread_mutex_unlock(&philo->meal_time);
	smart_sleep(philo, philo->table->time_to_eat);
	drop_fork(philo, 'l');
	drop_fork(philo, 'r');
}

void	sleep_routine(t_philo *philo)
{
	print_status(philo, "is sleeping");
	smart_sleep(philo, philo->table->time_to_sleep);
}

void	think_routine(t_philo *philo)
{
	print_status(philo, "is thinking");
}
