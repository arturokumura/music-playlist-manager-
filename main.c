#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[10];
    char titulo[80];
    char artista[60];
    char duracao[10];  
} Musica;

typedef struct {
    Musica *dados;
    int quantidade;
} Playlist;

void printarOperacoes() {
    printf("-------------------------------\n");
    printf("1. Cadastrar musica\n");
    printf("2. Listar musicas\n");
    printf("3. Buscar musica\n");
    printf("4. Ordenar por duracao\n");
    printf("5. Ordenar por id\n");
    printf("6. Remover música\n");
    printf("7. Duracao total\n");
    printf("8. Salvar\n");
    printf("0. Sair\n");
    printf("-------------------------------\n");
}

void iniciarPlaylist(Playlist *playlist) {
    playlist->dados = nullptr;
    playlist->quantidade = 0;
}

int carregarDados(Playlist *playlist) {
    FILE *arq = fopen("playlists.bin", "rb");
    if(arq == NULL) {
        printf("Erro ao abrir arquivo!\n");
        fclose(arq);
        return 0;
    }

    fread(&playlist->quantidade, sizeof(int), 1 , arq);

    if(playlist->quantidade == 0) {
        return 0;
    }

    playlist->dados = malloc(playlist->quantidade * sizeof(Musica));
    if(playlist->dados == NULL) {
        printf("Erro ao alocar memoria!\n");
        free(playlist->dados);
        return 0;
    }
    
    fclose(arq);
    return 1;
                break;
}