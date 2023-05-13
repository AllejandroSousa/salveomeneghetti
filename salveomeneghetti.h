#ifndef _SALVEOMENEGHETTI_H_
#define _SALVEOMENEGHETTI_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'

int acabou();
void move(char comando);
int ehdirecao(char direcao);
void explodepilula();
void explodepilula2(int x, int y, int somax, int somay, int qtd);

#endif