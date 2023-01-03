/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:32:35 by dvargas           #+#    #+#             */
/*   Updated: 2023/01/03 10:25:04 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_destoy(t_table *round)
{
	int	i;

	i = 0;
	while (i < round->nb_of_philos)
	{
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

void	lets_end_this(t_table *round)
{
	mutex_destoy(round);
	clean_philos(round);
}

void	help(void)
{
	printf("\n=======================================\n");
	printf("Welcome to the Philosophers Dinner\n");
	printf("=======================================\n");
	printf("You can run the program with the args:\n");
	printf("./philo [nb_of_philos] [time_to_die] [time_to_eat]");
	printf("[time_to_sleep] [times_each_philo_must_eat]\n");
	printf("all the args should be positive numbers and integer safe\n");
	printf("The last arg is optional, depending on args this dinner");
	printf("can take longer\n");
	printf("This Algorithm will stop at the first death of a Philosopher");
	printf("or when they are full\n");
	printf("\n========================================\n");
	printf("Args exemples:\n");
	printf("./philo 6 410 200 200 ---> No philosopher will die\n");
	printf("./philo 6 310 200 200 ---> One philosopher will die\n");
	printf("Thanks for your time\n");
	printf("Good luck next time Aristoteles !\n");
	exit(1);
}

int	error_function(char *s, int code)
{
	printf("%s\n", s);
	return (code);
}
