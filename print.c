/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:50:13 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/19 07:53:33 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t get_time_stamp(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_status(t_philo *philo, char *s)
{
    long cur_time;

    cur_time = get_time_stamp() - philo->table->time_start;
    if(philo->table->is_dead == 0)
    {
    pthread_mutex_lock(&philo->table->print);
    printf("%ldms %d %s \n", cur_time, philo->name, s);
    pthread_mutex_unlock(&philo->table->print);
    }
}
