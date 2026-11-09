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
    playlist->dados = NULL;
    playlist->quantidade = 0;
}

int carregarDados(Playlist *playlist) {
    FILE *arq = fopen("playlists.bin", "rb");
    if(arq == NULL) {
        return 0;
    }

    if(fread(&playlist->quantidade, sizeof(int), 1, arq) != 1) {
        fclose(arq);
        return 0;
    }

    if(playlist->quantidade == 0) {
        fclose(arq);
        return 0;
    }

    playlist->dados = malloc(playlist->quantidade * sizeof(Musica));
    if(playlist->dados == NULL) {
        printf("Erro ao alocar memoria!\n");
        fclose(arq);
        return 0;
    }

    if(fread(playlist->dados, sizeof(Musica), playlist->quantidade, arq) != playlist->quantidade) {
        fclose(arq);
        return 0;
    }
    
    fclose(arq);
    return 1;
}

int cadastrarMusica(Playlist *playlist, Musica *musica) {
    if(playlist == NULL || musica == NULL) {
        printf("Erro ao cadastrar musica\n");
        return 0;
    }

    if(musica->id[0] == '\0') {
        printf("O id nao pode ser vazio!\n");
        return 0;
    }

    for(int i = 0; i < playlist->quantidade; i++) {
        if(strcmp(playlist->dados[i].id, musica->id) == 0) {
            printf("Ja existe uma musica com esse id!\n");
            return 0;
        }
    }


    Musica *playlist_temp = realloc(playlist->dados, (playlist->quantidade + 1) * sizeof(Musica));
    if(playlist_temp == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 0;
    }

    playlist->dados = playlist_temp;
    playlist->dados[playlist->quantidade] = *musica;
    playlist->quantidade++;
    return 1;
}

void listarMusicas(Playlist *playlist) {
    if(playlist->quantidade == 0) {
        printf("Nenhuma musica cadastrada!\n");
    } else {
        printf("=================================\n");
        for(int i=0; i<playlist->quantidade; i++) {
            printf("=================================\n");
            printf("Id: %s\n", playlist->dados[i].id);
            printf("Titulo: %s\n", playlist->dados[i].titulo);
            printf("Artista: %s\n", playlist->dados[i].artista);
            printf("Duracao: %smin\n", playlist->dados[i].duracao);
        }
    }
}

void ordenarPorId(Playlist *playlist) {
    for(int i=0; i<playlist->quantidade-1; i++) {
        int menor_ind = i;
        for(int j=i+1; j<playlist->quantidade; j++) {
            if(strcmp(playlist->dados[j].id , playlist->dados[menor_ind].id) < 0){
                menor_ind = j;
            }
        }
        Musica temp = playlist->dados[i];
        playlist->dados[i] = playlist->dados[menor_ind];
        playlist->dados[menor_ind] = temp;
    }
}

void ordenarPorDuracao(Playlist *playlist) {
    for(int i=0; i<playlist->quantidade-1; i++) {
        int swipped = 0;
        for(int j=0; j<playlist->quantidade-i-1; j++) {
            if(strcmp(playlist->dados[j].duracao , playlist->dados[j+1].duracao) > 0) {
                Musica temp = playlist->dados[j];
                playlist->dados[j] = playlist->dados[j+1];
                playlist->dados[j+1] = temp;
                swipped = 1;
            }
        }
        if(swipped == 0) {
            break;
        }
    }
    printf("Ordenacao realizada com sucesso!\n");
}

Musica* buscarMusica(Playlist *playlist, char id[]) {
    ordenarPorId(playlist);
    int inicio = 0;
    int fim = playlist->quantidade -1;
    int meio;
    int achou = 0;

    while(fim >= inicio) {
        meio = (inicio + fim) / 2;

        if(strcmp(playlist->dados[meio].id , id) == 0) {
            achou = 1;
            break;
        }

        if(strcmp(playlist->dados[meio].id , id) > 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    if(achou == 1) {
        return &playlist->dados[meio];
    }
    return NULL;
}

int removerMusica(Playlist *playlist, char id[], Musica *musica) {
    int ind = -1;
    for(int i=0; i<playlist->quantidade; i++) {
        if(strcmp(playlist->dados[i].id , id) == 0) {
            ind = i;
            break;
        }
    }

    if(ind == -1) {
        printf("Musica nao encontrada!\n");
        return 0; 
    }

    *musica = playlist->dados[ind];

    for(int j= ind; j<playlist->quantidade-1; j++) {
        playlist->dados[j] = playlist->dados[j+1];
    }
    playlist->quantidade--;

    if(playlist->quantidade == 0) {
        free(playlist->dados);
        playlist->dados = NULL;
    } else {
        Musica *playlist_temp = realloc(playlist->dados, playlist->quantidade * sizeof(Musica));

        if(playlist_temp != NULL) {
            playlist->dados = playlist_temp;
        }
    }
    return 1;
}

                break;
}