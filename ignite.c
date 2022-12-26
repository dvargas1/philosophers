/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:47:40 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/22 08:34:29 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	**ft_fork_ignite(t_table *round)
{
	t_fork	**forks;
	int		i;

	i = 0;
	forks = malloc(sizeof(t_fork) * round->nb_of_philos);
	if (!forks)
		return (0); //PRECISA RETORNAR ERRO DE MALLOC AQUI
	while (i < round->nb_of_philos)
	{
		forks[i] = malloc(sizeof(t_fork) * 1);
		forks[i]->id = i;
		pthread_mutex_init(&forks[i]->lock, 0);
		i++;
	}
	return (forks);
}

t_philo	**ft_philo_ignite(t_table *round)
{
	t_philo	**philo;
	t_fork	**forks;
	int		i;

	i = 0;
	forks = ft_fork_ignite(round);
	philo = malloc(sizeof(t_philo) * round->nb_of_philos);
	if (!philo)
		return (0); //PRECISA RETORNAR ERRO DE MALLOC AQUI
	while (i < round->nb_of_philos)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		philo[i]->name = i;
		philo[i]->table = round;
		philo[i]->times_eat = 0;
		philo[i]->r_fork = forks[i];
		if (i == round->nb_of_philos - 1)
			philo[i]->l_fork = forks[0];
		else
			philo[i]->l_fork = forks[i + 1];
		pthread_mutex_init(&philo[i]->meal_time, 0);
	
		i++;
	}
	free(forks);
	return (philo);
}

int	ft_ignite(t_table *round, int argc, char **argv)
{
	round->nb_of_philos = ft_littleatoi(argv[1]);
	round->time_to_die = ft_littleatoi(argv[2]);
	round->time_to_eat = ft_littleatoi(argv[3]);
	round->time_to_sleep = ft_littleatoi(argv[4]);
	round->many_eats = 0;
	if (argc == 6)
		round->many_eats = ft_littleatoi(argv[5]);
	round->is_dead = 0;
	round->is_full = 0;
	round->philos = ft_philo_ignite(round);
	pthread_mutex_init(&round->mutex_kill, 0);
	pthread_mutex_init(&round->print, 0);
	pthread_mutex_init(&round->check, 0);
	return (0);
}
