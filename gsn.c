/*
** UC: 21111 - Sistemas Operativos
** e-fólio A 2022-23 (gsn.c)
**
** Aluno: 2102995 - Caroline Araujo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {

    // Aqui checamos se temos os dois argumentos (nome do programa e número de bytes). Se não tiver exatamente 2, o programa termina.
    if (argc != 2) {
        printf("Erro na execução do programa.\n");
        exit(1);
    } else {
        int n = atoi(argv[1]); // Aqui, precisamos converter o vetor argv[1], que é uma string, para um inteiro para que possamos comparar com zero. Para isso, utilizamos a função da stdlib atoi().

        if (n <= 0) { // Checamos se o argumento fornecido (número aleatório de bytes) é diferente ou maior que zero. Se for igual ou menor que zero, o programa termina. Se for maior, o programa continua.
            printf("Erro: n <= 0!\n");
            exit(1);
        } else {
            printf("O argumento fornecido é: %d\n", n);
            int pidB = fork();

            if (pidB > 0) {
                // Código do processo pai (Processo A)
                printf("Processo A: PID=%d  PPID=%d\n", getpid(), getppid());
                wait(NULL);

                // Processo C - Executando hexdump no arquivo tmp.bin
                int pidC = fork();
                if (pidC == 0) {
                    printf("Processo C: PID=%d PPID=%d\n", getpid(), getppid());

                    // Redirecionando a saída padrão para o arquivo "tmp.txt"
                    FILE *saidaC = freopen("tmp.txt", "w", stdout);

                    // Verificando se a abertura do arquivo foi bem sucedida
                    if (saidaC == NULL) {
                        printf("Erro ao abrir o arquivo tmp.txt. Fim do programa!\n");
                        exit(1);
                    }

                    // Executando o comando hexdump no arquivo tmp.bin
                    execlp("hexdump", "hexdump", "tmp.bin", NULL);

                    // A linha abaixo só será executada se houver um erro na chamada do exec
                    printf("Erro no exec. Fim do programa!\n");
                    exit(1);

                } else {
                    wait(NULL);
                }
            } else if (pidB == 0) {
                // Código do processo filho (Processo B)
                printf("Processo B: PID=%d PPID=%d\n", getpid(), getppid());

                // Redirecionando a saída padrão para o arquivo "tmp.bin"
                FILE *saidaB = freopen("tmp.bin", "w", stdout);

                // Verificando se a abertura do arquivo foi bem sucedida
                if (saidaB == NULL) {
                    printf("Erro ao abrir o arquivo tmp.bin. Fim do programa!\n");
                    exit(1);
                }

                // Usando head para gerar a lista de bytes no arquivo
                execlp("head", "head", "-c", argv[1], "/dev/urandom", NULL);

                // Lendo o conteúdo do arquivo e imprimindo na tela
                char buffer[n];
                fread(buffer, sizeof(char), n, stdout);
                    for (int i = 0; i < n; i++) {
                        printf("%d ", buffer[i]);
                    }
                    printf("\n");

                // Fechando os arquivos
                fclose(saidaB);

                // A linha abaixo só será executada se houver um erro na chamada do exec
                printf("Erro no exec. Fim do programa!\n");
                exit(1);
            } else {
                printf("Erro no exec: %s. Fim do programa!\n", strerror(errno));
                exit(1);
                }
        }
    }
    return 0;
}
