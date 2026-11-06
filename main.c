#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id[10];
    char titulo[80];
    char artista[60];
    int duracao;  
} Musica;

typedef struct {
    Musica *dados;
    int quantidade;
} Playlist;

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
}