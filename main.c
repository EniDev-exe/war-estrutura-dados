#include <stdio.h>
#include "war_functions.h"

void mostrar_menu() {
    printf("\n=== MENU WAR ===\n");
    printf("1. Exibir mapa\n");
    printf("2. Reforcar territorio\n");
    printf("3. Atacar\n");
    printf("4. Passar turno\n");
    printf("5. Sair\n");
    printf("Escolha: ");
}

int main() {
    JogoWar jogo;
    int opcao, id, id_alvo;
    
    printf("=== DESAFIO WAR ESTRUTURADO ===\n");
    printf("Jogo simplificado de War para Estrutura de Dados\n");
    
    inicializar_jogo(&jogo);
    distribuir_territorios(&jogo);
    
    while(!jogo.game_over) {
        printf("\n--- Turno do Jogador %d ---\n", jogo.jogador_atual);
        mostrar_menu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                exibir_mapa(&jogo);
                break;
                
            case 2:
                printf("Digite o ID do territorio para reforcar: ");
                scanf("%d", &id);
                reforcar_territorio(&jogo, id);
                break;
                
            case 3:
                printf("Digite o ID do territorio de origem: ");
                scanf("%d", &id);
                printf("Digite o ID do territorio alvo: ");
                scanf("%d", &id_alvo);
                if(atacar(&jogo, id, id_alvo)) {
                    if(jogador_venceu(&jogo, jogo.jogador_atual)) {
                        printf("\n🎉 JOGADOR %d VENCEU O JOGO! 🎉\n", jogo.jogador_atual);
                        jogo.game_over = 1;
                    }
                }
                break;
                
            case 4:
                proximo_turno(&jogo);
                break;
                
            case 5:
                jogo.game_over = 1;
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
    }
    
    printf("\nJogo encerrado!\n");
    return 0;
}
