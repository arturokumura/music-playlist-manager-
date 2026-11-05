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

