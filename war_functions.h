#ifndef WAR_FUNCTIONS_H
#define WAR_FUNCTIONS_H

#define MAX_TERRITORIOS 10
#define MAX_NOME 30
#define MAX_JOGADORES 2

// Estrutura do território
typedef struct {
    int id;
    char nome[MAX_NOME];
    int exercitos;
    int jogador; 
} Territorio;

// Estrutura do jogo
typedef struct {
    Territorio territorios[MAX_TERRITORIOS];
    int total_territorios;
    int jogador_atual;
    int game_over;
} JogoWar;

// Funções básicas
void inicializar_jogo(JogoWar *jogo);
void exibir_mapa(JogoWar *jogo);
void distribuir_territorios(JogoWar *jogo);
void reforcar_territorio(JogoWar *jogo, int territorio_id);
int atacar(JogoWar *jogo, int origem_id, int alvo_id);
int jogador_venceu(JogoWar *jogo, int jogador);
void proximo_turno(JogoWar *jogo);

#endif
