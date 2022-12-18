/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:42:07 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/18 08:11:25 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_table t_table;

typedef struct s_fork
{
    int id;
    pthread_mutex_t lock;
} t_fork;

typedef struct s_philo
{
  pthread_t thread;
  unsigned int name;
  unsigned int times_eat;
  unsigned int last_meal;
  t_fork *l_fork;
  t_fork *r_fork;
  t_table *table;
  pthread_mutex_t print;
  pthread_mutex_t meal_time;
} t_philo;


typedef struct s_table
{
    time_t time_start;
    unsigned int nb_of_philos;
    time_t time_to_die;
    time_t time_to_eat;
    time_t time_to_sleep;
    int many_eats;
    t_philo **philos;
} t_table;



//Parse Functions
int ft_isdigit(char c);
int ft_littleatoi(char *s);
int ft_isallnum(char *s);
int ft_checkargs(int argc, char **argv);


void help2();
void help();

#endif
