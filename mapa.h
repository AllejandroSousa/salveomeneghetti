#ifndef _MAPA_H_
#define _MAPA_H_

#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'
#define BOMBA 'b'

struct mapa {
    char** matriz;
    int linhas;
    int colunas;
};
typedef struct mapa MAPA;

struct posicao {
    int x;
    int y;
};
typedef struct posicao POSICAO;

void liberamapa(MAPA* m);
void alocamapa(MAPA* m);
void lemapa(MAPA* m);
int encontraheroi(MAPA* m, POSICAO* p, char c);
int ehvalida(MAPA* m, int x, int y);
int ehvazia(MAPA* m, int x, int y);
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiamapa(MAPA* destino, MAPA* origem);
void fanstasmas();
int praondeofantasmavai(int xatual, int yatual, int* xdestino, int* ydestino);
int podeandar(MAPA *m, char personagem, int x, int y);
int ehparede(MAPA *m, int x, int y);
int ehpersonagem(MAPA *m, char personagem, int x, int y);
int ehpilula(MAPA *m, int x, int y);
int podeandar2(MAPA *m, char personagem, int x, int y);

#endif






