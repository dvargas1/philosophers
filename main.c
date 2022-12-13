#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


void* routine2(void* x)
{
    *(int*)x += 10;
    printf("TESTE MOSTRANDO OUTRO VALOR = %d\n", *(int*)x);
}

void* routine(void* x)
{
    printf("Valor de X = %d\n", *(int*)x);
}
int main()
{
    int x = 0;
    x++;
    x++;
    pthread_t t1;
    printf("%d\n", x);
    x++;
    x++;
    x++;
    pthread_create(&t1, NULL, &routine2, (void*)&x);
    printf("%d\n", x);
    x++;
    pthread_join(t1, NULL);


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