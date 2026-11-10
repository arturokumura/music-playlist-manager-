# 🎵 Gerenciador de Playlist em C

Programa de terminal em C para gerenciar uma playlist de músicas. Os dados ficam em memória, em um **array dinâmico**, durante a execução e são salvos em **arquivo binário** para serem recuperados na próxima vez que o programa abrir.

Projeto desenvolvido para a disciplina de **Algoritmos e Programação 2 (APR2)** do IFSP, campus São Carlos.

##  Funcionalidades

| Opção | Descrição |
|---|---|
| 1. Cadastrar música | Insere uma música no final do array, redimensionando a memória com `realloc` |
| 2. Listar músicas | Exibe todas as músicas cadastradas |
| 3. Buscar música | Procura uma música pelo `id` com **busca binária** |
| 4. Ordenar por duração | Ordena pela duração usando **Bubble Sort** |
| 5. Ordenar por id | Ordena pelo `id` usando **Selection Sort** |
| 6. Remover música | Remove pelo `id`, deslocando os elementos seguintes para não deixar "buracos" |
| 7. Duração total | Soma a duração de todas as músicas da playlist |
| 8. Salvar | Grava os dados no arquivo binário |
| 0. Sair | Libera a memória e encerra o programa |

## 🧱 Estruturas de dados

```c
typedef struct {
    char id[10];
    char titulo[80];
    char artista[60];
    char duracao[10];   // formato "mm:ss"
} Musica;

typedef struct {
    Musica *dados;      // ponteiro para o array dinâmico
    int quantidade;     // número atual de músicas cadastradas
} Playlist;
```

## 🔧 Como compilar e executar

Requisitos: um compilador C, como o `gcc`.

```bash
gcc -o playlist main.c
./playlist
```

No Windows, execute `playlist.exe`.

## 💾 Persistência em arquivo binário

Ao iniciar, o programa tenta carregar os dados do arquivo `playlists.bin`. Se o arquivo não existir, a playlist começa vazia.

Formato do arquivo:

```
[ int quantidade ][ Musica 0 ][ Musica 1 ] ... [ Musica n-1 ]
```

Os dados só são gravados quando você escolhe a opção **8. Salvar**.

## 🖥️ Exemplo de uso

```
-------------------------------
1. Cadastrar musica
2. Listar musicas
3. Buscar musica
4. Ordenar por duracao
5. Ordenar por id
6. Remover musica
7. Duracao total
8. Salvar
0. Sair
-------------------------------
Opcao: 1
-----------------Cadastrar musica-----------------
Id: 101
Titulo: Imagine
Artista: John Lennon
Duracao (xx:yy): 03:03
Musica cadastrada com sucesso!
```

> 💡 Digite as durações sempre com dois dígitos nos minutos e nos segundos (`03:45`, `10:20`), para a ordenação por duração funcionar corretamente.


A função de busca ordena o array por `id` antes de procurar, então, do jeito que está, cada busca custa O(n²) por causa dessa ordenação.

## 📚 Conceitos praticados

- Alocação dinâmica de memória (`malloc`, `realloc`, `free`)
- Ponteiros e `struct`
- Algoritmos de ordenação (Selection Sort e Bubble Sort)
- Busca binária
- Leitura e escrita em arquivos binários (`fread`, `fwrite`)
- Manipulação de strings (`strcmp`, `fgets`, `sscanf`)
- Análise de complexidade de algoritmos

## 🚀 Possíveis melhorias

- Validar `id` duplicado e o formato da duração no cadastro
- Guardar a duração como `int` (em segundos)
- Editar uma música já cadastrada
- Buscar por título ou artista
- Trocar o array dinâmico por uma lista encadeada e comparar as complexidades

## 👤 Autor

Desenvolvido por **[seu nome]**. Contato: [LinkedIn](https://www.linkedin.com/in/seu-perfil)
