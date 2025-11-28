#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "war_functions.h"

void inicializar_jogo(JogoWar *jogo) {
    // Territórios básicos do Brasil
    strcpy(jogo->territorios[0].nome, "Amazonas");
    strcpy(jogo->territorios[1].nome, "São Paulo");
    strcpy(jogo->territorios[2].nome, "Rio de Janeiro");
    strcpy(jogo->territorios[3].nome, "Minas Gerais");
    strcpy(jogo->territorios[4].nome, "Bahia");
    strcpy(jogo->territorios[5].nome, "Rio Grande do Sul");
    strcpy(jogo->territorios[6].nome, "Parana");
    strcpy(jogo->territorios[7].nome, "Ceara");
    strcpy(jogo->territorios[8].nome, "Pernambuco");
    strcpy(jogo->territorios[9].nome, "Goias");
    
    jogo->total_territorios = 10;
    jogo->jogador_atual = 1;
    jogo->game_over = 0;
    
    // Inicializar territórios
    for(int i = 0; i < jogo->total_territorios; i++) {
        jogo->territorios[i].id = i;
        jogo->territorios[i].exercitos = 0;
        jogo->territorios[i].jogador = 0; // Neutro
    }
    
    srand(time(NULL)); // Para números aleatórios
}

void exibir_mapa(JogoWar *jogo) {
    printf("\n=== MAPA DO WAR ===\n");
    for(int i = 0; i < jogo->total_territorios; i++) {
        printf("ID: %d | %s | Exercitos: %d | Jogador: %d\n", 
               jogo->territorios[i].id,
               jogo->territorios[i].nome,
               jogo->territorios[i].exercitos,
               jogo->territorios[i].jogador);
    }
    printf("===================\n");
}

void distribuir_territorios(JogoWar *jogo) {
    printf("\nDistribuindo territorios...\n");
    
    for(int i = 0; i < jogo->total_territorios; i++) {
        // Alterna entre jogador 1 e 2
        jogo->territorios[i].jogador = (i % 2) + 1;
        jogo->territorios[i].exercitos = 1; // 1 exército inicial
    }
    
    printf("Territorios distribuidos!\n");
}

void reforcar_territorio(JogoWar *jogo, int territorio_id) {
    if(territorio_id < 0 || territorio_id >= jogo->total_territorios) {
        printf("Territorio invalido!\n");
        return;
    }
    
    if(jogo->territorios[territorio_id].jogador != jogo->jogador_atual) {
        printf("Voce nao controla este territorio!\n");
        return;
    }
    
    jogo->territorios[territorio_id].exercitos++;
    printf("Reforco adicionado ao territorio %s! Total: %d exercitos\n",
           jogo->territorios[territorio_id].nome,
           jogo->territorios[territorio_id].exercitos);
}

int atacar(JogoWar *jogo, int origem_id, int alvo_id) {
    // Verificações básicas
    if(origem_id == alvo_id) {
        printf("Nao pode atacar o proprio territorio!\n");
        return 0;
    }
    
    if(jogo->territorios[origem_id].jogador != jogo->jogador_atual) {
        printf("Voce nao controla o territorio de origem!\n");
        return 0;
    }
    
    if(jogo->territorios[alvo_id].jogador == jogo->jogador_atual) {
        printf("Voce ja controla este territorio!\n");
        return 0;
    }
    
    if(jogo->territorios[origem_id].exercitos <= 1) {
        printf("Precisa de pelo menos 2 exercitos para atacar!\n");
        return 0;
    }
    
    // Simulação simples de batalha
    int forca_ataque = jogo->territorios[origem_id].exercitos - 1;
    int forca_defesa = jogo->territorios[alvo_id].exercitos;
    
    printf("\n=== BATALHA ===\n");
    printf("Atacante: %s (%d exercitos)\n", jogo->territorios[origem_id].nome, forca_ataque);
    printf("Defensor: %s (%d exercitos)\n", jogo->territorios[alvo_id].nome, forca_defesa);
    
    // Batalha simples - quem tem mais exercitos vence
    if(forca_ataque > forca_defesa) {
        printf("VITORIA! Territorio conquistado!\n");
        jogo->territorios[alvo_id].jogador = jogo->jogador_atual;
        jogo->territorios[alvo_id].exercitos = forca_ataque - forca_defesa;
        jogo->territorios[origem_id].exercitos = 1; // Mantém 1 no território original
        return 1;
    } else {
        printf("DERROTA! Ataque repelido.\n");
        jogo->territorios[origem_id].exercitos = 1;
        return 0;
    }
}

int jogador_venceu(JogoWar *jogo, int jogador) {
    for(int i = 0; i < jogo->total_territorios; i++) {
        if(jogo->territorios[i].jogador != jogador) {
            return 0; // Ainda tem território de outro jogador
        }
    }
    return 1; // Todos os territórios são do jogador
}

void proximo_turno(JogoWar *jogo) {
    jogo->jogador_atual = (jogo->jogador_atual == 1) ? 2 : 1;
    printf("\n=== TURNO DO JOGADOR %d ===\n", jogo->jogador_atual);
}
