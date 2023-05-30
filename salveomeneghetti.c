#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "salveomeneghetti.h"
#include "mapa.h"
#include "ui.h"
 //Como compilar: gcc ./salveomeneghetti.c ./mapa.c ./ui.c -o ./salveomeneghetti.exe
MAPA m;
POSICAO heroi;
int tempilula = 0;
int venceu = 0;

void abertura() {
    printf("            BEM-VINDO AO SALVE O MENEGHETTI\n");
    printf("    Você tem a gloriosa missão de salvar o mestre Meneghetti\n\n");
    printf("__________________|      |____________________________________________\n");
    printf("     ,--.    ,--.          ,--.   ,--.\n");
    printf("    |oo  | _  \\  `.       | oo | |  oo|\n");
    printf("o  o|~~  |(_) /   ;       | ~~ | |  ~~|o  o  o  o  o  o  o  o  o  o  o\n");
    printf("    |/\\/\\|   '._,'        |/\\/\\| |/\\/\\|\n");
    printf("__________________        ____________________________________________\n");
    printf("                  |      |\n\n");
    printf("Comandos do jogo: \n");
    printf("CIMA - W\n");
    printf("DIREITA - D\n");
    printf("BAIXO - S\n");
    printf("ESQUERDA - A\n\n");
    printf("OBS: é necessário digitar um comando e em seguida apertar enter\n");
    printf("Digitar mais de um comando antes do enter resultará em movimentações consecutivas\n");
}

int praondeofantasmavai(int xatual, int yatual, int* xdestino, int* ydestino) {
    int opcoes[4][2] = { {xatual, yatual+1},
                        {xatual + 1, yatual},
                        {xatual, yatual-1},
                        {xatual-1, yatual}};

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int posicao = rand() % 4;

        if (podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1]) &&
            !ehpilula(&m, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
    }
    return 0;
}

//Localiza os fantasmas no mapa e os movimenta um bloco para a direita, caso seja válido
void fanstasmas() {
    MAPA copia;
    copiamapa(&copia, &m);

    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            if (copia.matriz[i][j] == FANTASMA) {

                int xdestino, ydestino;
                int encontrou = praondeofantasmavai(i, j, &xdestino, &ydestino);
                if (encontrou) {
                    andanomapa(&m, i, j, xdestino, ydestino);
                }
            }
        }
    }
    liberamapa(&copia);
}

int ehdirecao(char direcao) {
    return direcao == ESQUERDA ||
        direcao == CIMA ||
        direcao == BAIXO ||
        direcao == DIREITA;
}

void move(char direcao) {
    //Verifica se o usuário digitou teclas válidas
    if (!ehdirecao(direcao))
        return;
    
    //Guarda a posição inicial (ou anterior) do Mestre Meneghetti
    int proximox = heroi.x;
    int proximoy = heroi.y;
    
    //Realiza a movimentação do Mestre Meneghetti
    switch (direcao)
    {
    case ESQUERDA:
        proximoy--;
        break;
    case CIMA:
        proximox--;
        break;
    case BAIXO:
        proximox++;
        break;
    case DIREITA:
        proximoy++;
        break;
    }
    
    // Verifica se a movimentação foi válida (nao passou por cima de nenhuma parede nem limites do jogo)
    if (!podeandar2(&m, FANTASMA, proximox, proximoy))
        return;

    if (ehpersonagem(&m, PILULA, proximox, proximoy)) {
        tempilula = 1;
    }
    //Caso válida, a movimentação será feita e o mapa e a posição do Mestre Meneghetti serão atualizados
    andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;
}

int acabou() {
    POSICAO pos;
    int mestremeneghetti = encontraheroi(&m, &pos, HEROI);
    return !mestremeneghetti;
}

int ganhou() {
    POSICAO pos;
    int fantasmas = encontraheroi(&m, &pos, FANTASMA);
    if (fantasmas == 0) venceu++;
    return !fantasmas;
}

void explodepilula() {
    if (!tempilula) return;
    explodepilula2(heroi.x, heroi.y, 0, 1, 3);
    explodepilula2(heroi.x, heroi.y, 0, -1, 3);
    explodepilula2(heroi.x, heroi.y, 1, 0, 3);
    explodepilula2(heroi.x, heroi.y, -1, 0, 3);

    tempilula = 0;
}

void explodepilula2(int x, int y, int somax, int somay, int qtd) {
    if (qtd == 0) return;
    
    int novox = x + somax;
    int novoy = y + somay;
    if (!ehvalida(&m, novox, novoy)) return;
    if (ehparede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explodepilula2(novox, novoy, somax, somay, qtd-1);
}

int main () {
    setlocale(LC_ALL, "Portuguese");
    abertura();
    system("pause");
    lemapa(&m);
    encontraheroi(&m, &heroi, HEROI);
    do {
        printf("Tem pílula: %s\n", tempilula ? "SIM" : "NÃO");
        imprimemapa(&m);

        //Registra o comando que indicará a movimentação do Meneghetti na função move,
        //em seguida o laço de repetição reimprime o mapa com a nova posição do Meneghetti...
        char comando;
        scanf(" %c", &comando);
        move(comando);
        if (comando == BOMBA) explodepilula();
        fanstasmas();
        system("cls");
    } while (!acabou() && !ganhou());
    system("cls");
    
     if (venceu > 0) {
        printf("\nOBRIGADO POR ME SALVAR, ESTÁ APROVADO!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else {
        printf("\nVOCÊ FALHOU! SEU INFAME, VOCÊ ACHOU QUE EU MORRERIA?\n");
        printf("Está reprovado!\n");

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
    system("pause");
    //Liberando a memória
    liberamapa(&m);
}