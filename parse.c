/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:12:18 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/21 12:01:22 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int error_handler(void)
{
	printf("sorry, all args must be a integer range number different from 0");
	return(1);
}
int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_littleatoi(char *s)
{
	int			i;
	long int	nb;

	nb = 0;
	i = 0;
	while (s[i] && ft_isdigit(s[i]))
	{
		nb *= 10;
		nb += s[i] - '0';
		i++;
	}
	if (nb > 2147483647)
		return(-1);
	if (nb == 0)
		return(-1);
	return ((int)nb);
}

int	ft_isallnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_checkargs(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if(ft_littleatoi(argv[i]) == -1)
			return(error_handler());
		if (ft_isallnum(argv[i]) != 0)
			return(error_handler());
		i++;
	}
	return (0);
}
