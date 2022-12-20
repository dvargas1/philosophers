/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:36:29 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/19 07:54:04 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/types/struct_timeval.h>
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

int    check_death(t_philo *philo, long current_time)
{
    long    meal_check;


    meal_check = current_time - philo->last_meal;
    if (meal_check > philo->table->time_to_die)
    {
        pthread_mutex_lock(&philo->print);
        print_status(philo, "is dead");
        pthread_mutex_unlock(&philo->print);

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
    smart_sleep(philo->table->time_to_eat);
    pthread_mutex_lock(&philo->meal_time);
    philo->last_meal = get_time_stamp() - philo->table->time_start;
    pthread_mutex_unlock(&philo->meal_time);
    pthread_mutex_unlock(&philo->l_fork->lock);
    pthread_mutex_unlock(&philo->r_fork->lock);
    print_status(philo, "is sleeping");
    smart_sleep(philo->table->time_to_sleep);
}

void *test_routine(void *arg)
{
    t_philo *philo;
    long current_time;

    philo = (t_philo *)arg;

    while(1)
        {
            current_time = get_time_stamp() - philo->table->time_start;
            if(check_death(philo, current_time) == 1)
                break;
            if(philo->name % 2 != 0)
            {
                print_status(philo, "is thinking");
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
        lets_join(round);


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
