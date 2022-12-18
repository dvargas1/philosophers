/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:36:29 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/18 20:38:39 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <time.h>

void help()
{
    printf("DEU RUIM CHEFE");
    exit(1);
}

void help2()
{
    printf("DEU RUIM CHEFEeeeeeeeeeeeee");
    exit(1);
}

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
  printf("%05ld %d %s \n", cur_time, philo->name, s);
}

t_fork **ft_fork_ignite(t_table *round)
{
  t_fork **forks;
  unsigned int i = 0;
  
  forks = malloc(sizeof(t_fork) * round->nb_of_philos);
  if(!forks)
    return(0); //PRECISA RETORNAR ERRO DE MALLOC AQUI
  while(i < round->nb_of_philos)
    {
      forks[i] = malloc(sizeof(t_fork) * 1);
      forks[i]->id = i;
      pthread_mutex_init(&forks[i]->lock, 0);
      i++;
    }
  return(forks);
}

t_philo **ft_philo_ignite(t_table *round)
{
  t_philo **philo;
  t_fork **forks;
  unsigned int i = 0;

  forks = ft_fork_ignite(round);
  philo = malloc(sizeof(t_philo) * round->nb_of_philos);
  if(!philo)
    return(0); //PRECISA RETORNAR ERRO DE MALLOC AQUI

  while(i < round->nb_of_philos)
    {
      philo[i] = malloc(sizeof(t_philo) * 1);
      philo[i]->name = i;
      philo[i]->table = round;
      philo[i]->times_eat = 0;
      philo[i]->r_fork = forks[i];
      if(i == round->nb_of_philos - 1)
        philo[i]->l_fork = forks[0];
      else
        philo[i]->l_fork = forks[i+1];
      pthread_mutex_init(&philo[i]->print, 0);
      pthread_mutex_init(&philo[i]->meal_time, 0);
      i++;
    }
  return(philo);
}

int ft_ignite(t_table *round, int argc, char **argv)
{
    round->nb_of_philos = ft_littleatoi(argv[1]);
    round->time_to_die = ft_littleatoi(argv[2]);
    round->time_to_eat = ft_littleatoi(argv[3]);
    round->time_to_sleep = ft_littleatoi(argv[4]);
    round->many_eats = 0;
    if(argc == 6)  
      round-> many_eats = ft_littleatoi(argv[5]);
    round->philos = ft_philo_ignite(round);
  return (0);
}

void smart_sleep(long int time_in_ms)
{
  long int start_time;
  start_time = get_time_stamp();
  while((get_time_stamp() - start_time) < time_in_ms)
      usleep(50);

}
void eat_routine(t_philo *philo)
{
      pthread_mutex_lock(&philo->l_fork->lock);
      print_status(philo, "GOT LEFT FORK");
      pthread_mutex_lock(&philo->r_fork->lock);
      print_status(philo, "GOT RIGHT FORK");
      print_status(philo, "EATING MCDONLADS");
      smart_sleep(philo->table->time_to_eat);
      pthread_mutex_unlock(&philo->l_fork->lock);
      pthread_mutex_unlock(&philo->r_fork->lock);
      print_status(philo, "IS SLEEPING");
      smart_sleep(philo->table->time_to_sleep);
}

void *test_routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *)arg;

  while(1)
    {
      if(philo->name % 2 != 0)
      {
        print_status(philo, "IS THINKING");
        smart_sleep(philo->table->time_to_eat);
      }
      eat_routine(philo);
    }
  return(NULL);

}
void lets_start(t_table *round)
{
  unsigned int i = 0;

  round->time_start = get_time_stamp();
  
  while(i < round->nb_of_philos)
    {
      pthread_create(&round->philos[i]->thread, NULL, &test_routine, round->philos[i]);
      i++;
    }
}

void lets_end(t_table *round)
{
  unsigned int i = 0;

  while(i<round->nb_of_philos)
    {
      pthread_join(round->philos[i]->thread, NULL);
      i++;
    }
}


int main(int argc, char **argv)
{
    t_table *round;

    round = malloc(sizeof(t_table) * 1);
    if(!round)
      return(-1); // precisa retornar erro de malloc
    if(argc < 5)
        help();
    if(ft_checkargs(argc, argv) != 0)
      help();
    if(ft_ignite(round, argc, argv) == 0)
    {
      lets_start(round);
      lets_end(round);
    }
    return 0;

}



/*
    lidar com argumentos e possiveis erros
    criar structs, vou utilizar index ou listas ?
    iniciar mesa
        converter parametros
        iniciar philosofos ( lembrar de iniciar garfos x = x  x = x+1)
        iniciar garfos (mutex)
    Iniciar o banquete
       mandela (get time of day) cirar timestamps que serao impressos
        (pthread_create) criar threads dos filosofos chamando a funcao que coordena eles
            criar rotina pensar
            criar rotina comer
            criar rotina dormir
            criar rotina morrer ? ou criar entidade que mata eles
        escolher qual filosofo vai começar comendo na mesa (ideia la do iniciar garfos )
    Terminar banquete
*
*/
