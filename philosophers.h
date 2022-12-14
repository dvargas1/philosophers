/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:42:07 by dvargas           #+#    #+#             */
/*   Updated: 2023/01/03 10:23:00 by dvargas          ###   ########.fr       */
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

# define ARGS_ERROR "Args must be a positive interger different from zero"
# define PHILOS_ERROR "Error During Philosophers creation"

typedef struct s_table	t_table;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	name;
	t_table			*table;
	unsigned int	times_eat;
	long int		last_meal;
	long int		time_out;
	t_fork			*l_fork;
	t_fork			*r_fork;
	pthread_mutex_t	meal_time;
}	t_philo;

typedef struct s_table
{
	time_t			time_start;
	int				nb_of_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	unsigned int	many_eats;
	pthread_t		reaper;
	int				is_dead;
	int				is_full;
	pthread_mutex_t	mutex_kill;
	pthread_mutex_t	print;
	pthread_mutex_t	check;
	t_philo			**philos;
}	t_table;

// Routine functions
void	eat_routine(t_philo *philo);
void	sleep_routine(t_philo *philo);
void	think_routine(t_philo *philo);
int		lets_start(t_table *round);
int		lets_join(t_table *round);
void	lets_end_this(t_table *round);

//Parse Functions
int		ft_isdigit(char c);
int		ft_positive_atoi(char *s);
int		ft_isallnum(char *s);
int		ft_checkargs(int argc, char **argv);

//reaper
void	*reaper_routine(void *args);
int		ft_ignite(t_table *round, int argc, char **argv);
void	print_status(t_philo *philo, char *s);
time_t	get_time_stamp(void);
void	smart_sleep(t_philo *philo, long int time_in_ms);

//Error functions
int		error_function(char *s, int code);
void	help(void);
void	sim_start_delay(time_t time_start);

#endif
