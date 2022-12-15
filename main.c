/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:36:29 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/15 08:13:42 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int ft_ignite(t_philo *philo, int argc, char **argv)
{
    if(ft_checkargs(argc, argv) != 0)
        help();
    philo->philo_id = ft_littleatoi(argv[1]);
    philo-> time_to_die = ft_littleatoi(argv[2]);
    philo-> time_to_eat = ft_littleatoi(argv[3]);
    philo->time_to_sleep = ft_littleatoi(argv[4]);
    philo-> many_eats = ft_littleatoi(argv[5]);
    return (0);
}

int main(int argc, char **argv)
{
    t_philo aristoteles;

    if(argc < 6)
        help();
    if(ft_ignite(&aristoteles, argc, argv) == 0)
    {
        printf("Hi, i'm the first Philosofer of this function\n");
        printf("My ID is: %d\n", aristoteles.philo_id);
        printf("I will die in: %dms\n", aristoteles.time_to_die);
        printf("I will sleep for: %dms\n", aristoteles.time_to_sleep);
        printf("I will eat for: %dms\n", aristoteles.time_to_eat);
        printf("I will eat %d times\n", aristoteles.many_eats);
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
*/
