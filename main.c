#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

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

typedef struct s_philo
{
    int philo_id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int many_eats;
}   t_philo;

int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return(0);
}
int ft_littleatoi(char *s)
{
    int i;
    long int nb;

    nb = 0;
    i = 0;
    while(s[i] && ft_isdigit(s[i]))
    {
        nb *= 10;
		nb += s[i] - '0';
        i++;
    }
    if(nb > 2147483647)
        help();
    return((int)nb);
}

int ft_isallnum(char *s)
{
    int i;

    i = 0;
    while(s[i])
    {
        if(s[i] < '0' || s[i] > '9')
            return(1);
        i++;
    }
    return(0);

}

int ft_checkargs(int argc, char **argv)
{
    int i;

    i = 1;
    while(i < argc)
    {
        if(ft_isallnum(argv[i]) != 0)
            help2();
        i++;
    }
    return(0);
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
    if(ft_ignite(&aristoteles, argc, argv) == 0);
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
        cirar timestamps que serao impressos
        criar threads dos filosofos chamando a funcao que coordena eles
            criar rotina pensar
            criar rotina comer
            criar rotina dormir
            criar rotina morrer ? ou criar entidade que mata eles
        escolher qual filosofo vai começar comendo na mesa (ideia la do iniciar garfos )
    Terminar banquete
*/