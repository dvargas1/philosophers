/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:42:07 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/14 16:56:23 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_philo
{
    int philo_id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int many_eats;
}   t_philo;

#endif
