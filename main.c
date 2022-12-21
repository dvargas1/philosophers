/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:36:29 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/20 17:07:16 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <time.h>

void help()
{
    printf("ERRO DE HELP");
    exit(1);
}

void help2()
{
    printf("ERRO DE HELP2");
    exit(1);
}

int    check_death(t_philo *philo)
{
    long    meal_check;
    long    cur_time;


    meal_check = (get_time_stamp() - philo->table->time_start) - philo->last_meal;
    if (meal_check > philo->table->time_to_die)
    {
        pthread_mutex_lock(&philo->table->mutex_kill);
        philo->table->is_dead = 1;
        pthread_mutex_lock(&philo->table->print);
        cur_time = get_time_stamp() - philo->table->time_start;
        printf("%ldms %d %s \n", cur_time, philo->name, "is dead");
        pthread_mutex_unlock(&philo->table->print);
        pthread_mutex_unlock(&philo->table->mutex_kill);

        return(1);
    }
    else
    {
        return(0);
    }

}

void smart_sleep(long int time_in_ms)
{
    long int start_time;

    start_time = get_time_stamp();
    while((get_time_stamp() - start_time) < time_in_ms)
        usleep(10);

}

void eat_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_fork->lock);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->r_fork->lock);
    print_status(philo, "has taken a fork");
    print_status(philo, "is eating");
    pthread_mutex_lock(&philo->meal_time);
    philo->last_meal = get_time_stamp() - philo->table->time_start;
    pthread_mutex_unlock(&philo->meal_time);
    smart_sleep(philo->table->time_to_eat);
    pthread_mutex_unlock(&philo->l_fork->lock);
    pthread_mutex_unlock(&philo->r_fork->lock);
    print_status(philo, "is sleeping");
    smart_sleep(philo->table->time_to_sleep);
    print_status(philo, "is thinking");
}

void *test_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if(philo->name % 2 != 0)
    {
        print_status(philo, "is thinking");
        smart_sleep(philo->table->time_to_eat);
    }

    while(1)
        {
            if(philo->table->nb_of_philos == 1)
                break;

            pthread_mutex_lock(&philo->table->mutex_kill);
            if(philo->table->is_dead == 1)
            {
                pthread_mutex_unlock(&philo->table->mutex_kill);
                break;
            }
            pthread_mutex_unlock(&philo->table->mutex_kill);
            eat_routine(philo);
        }
    return(NULL);

}

int check_if_dead(t_table *round)
{
    unsigned int i = 0;

    while(i < round->nb_of_philos)
        {
            pthread_mutex_lock(&round->philos[i]->meal_time);
            if(check_death(round->philos[i]) == 1)
            {
                pthread_mutex_unlock(&round->philos[i]->meal_time);
                return(1);
            }
            pthread_mutex_unlock(&round->philos[i]->meal_time);
            i++;
        }
    return(0);
}

void *reaper_routine(void *args)
{
    t_table *round;

    round = (t_table *)args;
    while (1)
        {
            if (check_if_dead(round) == 1)
                return(NULL);
            //    if (check_if_full(round == 1))
            //      return(NULL);
            usleep(100);
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

void lets_join(t_table *round)
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
        return(-1); // precisa retornar erro
    if(argc < 5)
        help();
    if(ft_checkargs(argc, argv) != 0)
        help();
    if(ft_ignite(round, argc, argv) == 0)
    {
        lets_start(round);
        pthread_create(&round->reaper, NULL, &reaper_routine, round);
        lets_join(round);
        pthread_join(round->reaper, NULL);


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
