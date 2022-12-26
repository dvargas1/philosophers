/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:36:29 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/22 12:34:26 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	printf("Thanks for your time");
	printf("Good luck Aristoteles !");
	exit(1);
}

int	main(int argc, char **argv)
{
	t_table	*round;

	if (argc < 5 || argc > 6)
		help();
	if (ft_checkargs(argc, argv) != 0)
		exit(1);
	round = malloc(sizeof(t_table));
	if (!round)
		return (-1) ;
	if (ft_ignite(round, argc, argv) != 0)
		return (1);
	if (lets_start(round) != 0)
		return (1);
	if (lets_join(round) != 0)
		return (1);
	lets_end_this(round);
	return (0);
}
