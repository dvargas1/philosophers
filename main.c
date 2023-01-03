/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:36:29 by dvargas           #+#    #+#             */
/*   Updated: 2023/01/03 10:03:13 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	*round;

	if (argc < 5 || argc > 6)
		help();
	if (ft_checkargs(argc, argv) != 0)
		return (1);
	round = malloc(sizeof(t_table));
	if (!round)
		return (1);
	if (ft_ignite(round, argc, argv) != 0)
		return (1);
	usleep(200);
	if (lets_start(round) != 0)
		return (1);
	if (lets_join(round) != 0)
		return (1);
	lets_end_this(round);
	return (0);
}
