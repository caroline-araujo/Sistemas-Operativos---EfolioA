/*
** UC: 21111 - Sistemas Operativos
** e-fólio A 2022-23 (gsn.c)
**
** Aluno: 2102995 - Caroline Araujo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    //Aqui checamos se temos pelo menos um argumento, além do nome do programa. Se não tiver, o programa termina. Também checamos se o número de argumento é maior que três, uma vez que só queremos que seja fornecido o nome do programa + 1 argumento (número de bytes). Se fornecer um argumento a mais, o programa apresenta erro de execução e termina. 
    if (argc < 2 || argc >= 3 ) { 
        printf("Erro na execução do programa.\n");
        exit(1);
    } else { //Checamos se o argumento fornecido (número aleatório de bytes) é diferente ou maior que zero. Se for igual ou menor que zero, o programa termina. Se for maior, o programa continua.
        int n = atoi(argv[1]); //Aqui, precisamos converter o vetor argv[1], que é uma string, para um inteiro para que possamos comparar com zero. Para isso, utilizamos a função da stdlib atoi(). 
        
        if (n <= 0) {
            printf("Erro: n <= 0!\n");
            exit(1);
        } else {
            printf("O argumento fornecido é: %s\n", argv[1]);
            return 0;
        }
    }
    return 0;
}
