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

/*2) Implemente a função abaixo para inicializar a playlist, dizendo que ela está criada e pronta para receber músicas*/
void iniciarPlaylist(Playlist *playlist) {
    playlist->dados = nullptr;
    playlist->quantidade = 0;
}