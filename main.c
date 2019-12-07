#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 |
 |  CONSTANTES
 |
 */
#define BUF_SIZE 1024 // constante usado na função ler_linha()

/*
 |
 | VARIÁVEL GLOBAL
 | Variável global para representar os caracteres do alfabeto
 */
char alfabeto[25] = {
    'A','B','C','D','E',
    'F','G','H','I','J',
    'K','L','M','N','O',
    'P','Q','R','S','T',
    'U','V','W','X','Z'
};

/*
 |
 | IMPLEMENTACAO
 | Função que exibe um menuzinho bunitin
 |
 */
void menu() {
    printf("\n");
    printf("|++++++++++++++++++++++++++++++++++++++++++++++++++++++++++|\n");
    printf("|            _____      _       _         _____            |\n");
    printf("|           / ____|    (_)     | |       / ____|           |\n");
    printf("|          | |     _ __ _ _ __ | |_ ___ | |                |\n");
    printf("|          | |    | '__| | '_ \\| __/ _ \\| |                |\n");
    printf("|          | |____| |  | | |_) | || (_) | |____            |\n");
    printf("|           \\_____|_|  |_| .__/ \\__\\___/ \\_____|           |\n");
    printf("|                        | |                               |\n");
    printf("|                        |_|                               |\n");
    printf("|++++++++++++++++++++++++++++++++++++++++++++++++++++++++++|\n");
    printf("|                                                          |\n");
    printf("|             1 - Criptografar uma mensagem                |\n");
    printf("|                       2 - Sair                           |\n");
    printf("|                                                          |\n");
    printf("|++++++++++++++++++++++++++++++++++++++++++++++++++++++++++|\n");
    printf("Digite sua opção: ");
}

/*
 |
 | IMPLEMENTACAO
 | Função para ler linha de entrada
 |
 */
char* ler_linha() {
    int bufsize = BUF_SIZE, posicao = 0;
    int c;
    char* buffer = malloc(sizeof(char) * bufsize);

    // verifica se a alocação aconteceu de fato
    if(!buffer) {
        printf("Erro de alocação");
        exit(EXIT_FAILURE); // retorna erro
    }

    while(1) { // loop infinito
        //lê um caractere
        c = getchar();   

        /*
         |
         | Se tivermos um EOF ou um fim de linha, 
         | indicamos o fim da string e a retornanos
         |
         */
        if(c == EOF || c == '\n') {
            buffer[posicao] = '\0';
            return buffer;
        }
        else {
            buffer[posicao] = c;
        }
        posicao++;

        // se o buffer exceder, realocamos
        if(posicao >= bufsize) {
            bufsize += BUF_SIZE;
            buffer = realloc(buffer, bufsize);

            // verifica se a realocação aconteceu de fato
            if(!buffer) {
                printf("Erro de alocação!\n");
                exit(EXIT_FAILURE); // retorna erro
            }
        }
    }
}

/*
 |
 | IMPLEMENTACAO
 | Função para ler um arquivo txt
 |
 */
char* ler_arquivo(char *path) {
    FILE *file;  //ponteiro que irá apontar para o arquivo
    int bufsize = BUF_SIZE, posicao = 0; // tamanho do buffer
    char *dados, c; // ponteiro que guardará os dados

    file = fopen(path, "r"); //abre o arquivo

    // se não conseguir abrir o arquivo, retorna nulo
    if(file == NULL) {
        printf("Erro na abertura do arquivo!\n");
        printf("Talvez você tenha digitado o endereço de forma errada...\nTente novamente, por favor!");
        return NULL;
    }

    /*
     |
     | Se localizar o arquivo, mostra o aviso
     | Etapa de leitura dos dados dos arquivos começa
     |
     */
    printf("Arquivo localizado!\n");

    // aloca espaço na memória para os dados do arquivo
    dados = malloc(sizeof(char) * bufsize);

    // se não conseguir alocar, retorna nulo
    if(!dados) {
        printf("Erro de alocação!\n");
        return NULL;
    }

    do {
        c = getc(file);
        dados[posicao] = c;

        // essa função lê apenas uma linha
        if(c == '\n') { dados[posicao] = '\0'; break; }

        // se o tamanho da linha execeder
        if(posicao >= bufsize) {
            bufsize += BUF_SIZE;
            dados = realloc(dados, bufsize);

            // se houver erro de alocação
            if(!dados) {
                printf("Erro de alocação!\n");
                printf("Só conseguimos ler parte dos dados...\nMe desculpa!\n");
                return dados;
            }
        }
        posicao++;
    } while(c != EOF);

    // fecha o arquivo
    fclose(file);
    return dados;
}

/*
 |
 | IMPLEMENTACAO
 | Função para gravar uma string num arquivo txt
 |
 */
int gravar_arquivo(char *path, char *msg) {
    FILE * file; //ponteiro que irá apontar para o arquivo

    file = fopen(path, "w"); // abre o arquivo

    // verifica se o arquivo foi aberto
    if(file == NULL) {
        printf("Erro na abertura do arquivo!\n");
        printf("Talvez você tenha digitado o endereço de forma errada...\nTente novamente, por favor!");
        return 1; // indica erro arquivo não localizado
    }
    
    // grava os dados no arquivo
    fputs(msg, file);

    printf("Arquivo foi escrito com sucesso!\n");

    fclose(file); // fecha o arquivo
    return 0; // indica sucesso
}

/*
 |
 | IMPLEMENTAÇÃO
 | Função para deixar a string com tamanho par
 |
 */
void arredondar(char *str) {
    int tam = strlen(str);
    
    if(tam % 2 != 0) {
        str[tam++] = 'X'; // aqui adiciona o x para deixar par
        str[tam] = '\0'; // novo fim da string
    }
}

/*
 |
 | IMPLEMENTAÇÃO
 | Função para remover espaços existentes,
 |
 */
void limpar_espacos(char *str) {
    int contador = 0, tam = strlen(str);

    if(tam <= 0) {
        printf("Erro! String vazia!"); // string vazia
    }
    else {
        for(int i = 0; i < tam; i++) {
            if(str[i] != ' ') // pega o espaço
                str[contador++] = str[i]; // e joga fora
        }
        str[contador] = '\0';   
    }
}

/*
 |
 | IMPLEMENTAÇÃO
 | Função para touppar uma string
 |
 */

void touppar(char *str) {
    int tam = strlen(str);

    if(tam <= 0) {
        printf("Erro! String vazia!"); // string vazia
    }
    else {
        for(int i = 0; i < tam; i++) {
            if(str[i] = toupper(str[i])) {
                // pega os Y e substitui por X
                if(str[i] == 'Y')
                    str[i] = 'X';
            }
        }
    }
}

/*
 |
 | IMPLEMENTAÇÃO
 | Função para tirar caracteres repetidos
 |
 */
char* tirar_repetidos(char *str) {
    int count = 0, k = 0, tam = strlen(str);
    if(tam <= 0) return NULL; // string vazia
    // aloca um espaço para key formatada
    char *newStr = malloc(sizeof(char) * tam);

    for(int i = 0; i <= tam; i++) {
        for(int j = 0; j < tam; j++) {
            if(str[i] == newStr[j]) count++; // ele conta os caracteres repetidos
        }
        if(count >= 1) {
            for(int x = 0; x < tam; x++) 
                if(str[i] == newStr[x]) break; // achou o repetido, pula
            newStr[k] = str[i];
        }
        else {
            newStr[k] = str[i]; // se não for repetido, adiciona
            k++;
        }
        count = 0;
    }
    return newStr;
}

/*
 |
 | IMPLEMENTAÇÃO
 | Função para alocar matriz de caracteres
 |
 */
char** alocar_matriz(int linha, int coluna) {
    // primeiramente aloca espaço para as linhas
    char **matriz = (char **) malloc(sizeof(char *) * linha);
    
    // se houver erro de alocação no processo
    if(matriz == NULL) return NULL;

    for(int i = 0; i < coluna; i++) {
        // para cada linha, aloca espaço para as colunas
        matriz[i] = (char *) malloc(sizeof(char) * coluna);
    }
    
    // ao final, uma matriz LINHAxCOLUNA é gerada
    return matriz;
}

/*
 |
 | IMPLEMENTAÇÃO
 | Função para gerar a tabela com a chave
 |
 */
char** gerar_tabela(char *key, char *msg) {
    // tamanho da chave
    int tamKey = strlen(key);
    
    // tamanho da mensagem
    int tamMsg = strlen(msg);
    
    // tamanho do alfabeto (25 caracteres)
    int tamAlf = strlen(alfabeto);

    // essa função aloca memória para uma matriz 5x5
    char **tabela = alocar_matriz(5, 5); 

    if(tabela == NULL) return NULL; // erro de alocação

    // caso a chave ou mensagem for vazia, retorna nulo
    if(tamKey <= 0 || tamMsg <= 0) return NULL;

    // letras que comporam a matriz, exceto as que tem na key
    char letras[tamAlf]; 
    int i, j, k = 0, x = 0;
    for(i = 0; i < tamAlf; i++) {
        for(j = 0; j < tamKey; j++) {
            if(key[j] == alfabeto[i]) break; // se for igual, pula
        }
        if(j == tamKey) {
            // adiciona as demais letras
            // que não estão na chave
            letras[k] = alfabeto[i]; 
            k++;
        }
        // ao final, uma string será gerada
        // com todos os caracteres que não estão na chave
    } 

    // aqui a matriz é de fato gerada
    k = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(k < tamKey) {
                // aqui adiciona primeiro a chave dentro da matriz
                tabela[i][j] = key[k];
                k++;
            }
            else {
                // aqui adiciona a string anteriormente gerada
                tabela[i][j] = letras[x];
                x++;
            }
        }
    }
    // tabela gerada com sucesso
    return tabela;
}

/*
 |
 | IMPLEMENTAÇÃO
 | Função para procurar um caractere numa tabela
 |
 */
void procurar(char one, char two, char **tabela, int *array) {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(one == tabela[i][j]) {
                array[0] = i;
                array[1] = j;
            }
            else if(two == tabela[i][j]) {
                array[2] = i;
                array[3] = j;
            }
        }
    }
}

/*
 |
 | IMPLEMENTAÇÃO
 | Função que vai criptografar realmente
 |
 */
char* playfair(char *key, char *msg) {
    int i;
    int x, y; // variáveis temporárias
    // essa variável guardára a mensagem encriptada
    char *resultado = malloc(sizeof(char) * strlen(msg));
    
    // essa array guarda as posições dos caracteres
    // que estão dentro da tabela
    int *array = malloc(sizeof(int) * 4); 
    
    key = tirar_repetidos(key);
    touppar(key); // key agora é tudo maiúsculo
    touppar(msg); // agora a mensagem também é tudo maiúsculo
    limpar_espacos(msg); // limpa os espaços

    arredondar(msg); // arredonda a string para deixar com tamanho par

    // tabela gerada com a chave
    char **tabela = gerar_tabela(key, msg);

     // erro de alocação
    if(tabela == NULL || array == NULL) return NULL; 

    // aqui começa a encriptação
    for(i = 0; i < strlen(msg); i += 2) {
        procurar(msg[i], msg[i + 1], tabela, array);
        
        if(array[0] == array[2]) {
            // caracteres na mesmo linha
            // achando as colunas
            x = (array[1] + 1) % 5;
            y = (array[3] + 1) % 5;

            // encriptando dois caracteres por vez
            resultado[i] = tabela[array[0]][x];
            resultado[i + 1] = tabela[array[2]][y];
            // printf("%c %c ", resultado[i], resultado[i + 1]);
        }
        else if(array[1] == array[3]) {
            // caracteres na mesmo coluna
            // achando as linhas
            x = (array[0] + 1) % 5;
            y = (array[2] + 1) % 5;

            // encriptando dois caracteres por vez
            resultado[i] = tabela[array[1]][x];
            resultado[i + 1] = tabela[array[3]][y];
            // printf("%c %c ", resultado[i], resultado[i + 1]);
        }
        else {
            // encriptando dois caracteres por vez
            resultado[i] = tabela[array[0]][array[3]];
            resultado[i + 1] = tabela[array[2]][array[1]];
            // printf("%c %c ", resultado[i], resultado[i + 1]);
        }
    }
    resultado[i] = '\0';
    // ao final, uma string será gerada
    // com a mensagem encriptada
    return resultado;
}

/*
 |
 | Função Principal
 |
 */
int main() {
    int opcao, opcaoEscrita;
    char *caminhoLeitura = NULL, *caminhoEscrita = NULL; // path do arquivo (relativo ou não)
    char *mensagem = NULL; // a mensagem tirada do arquivo
    char *key = malloc(sizeof(char) * 25); // a chave do usuário
    char *mensagemEcriptada = NULL; // a mensagem encriptada

    do {
        menu();
        // lendo a opção do usuário
        scanf("%d", &opcao);

        if(opcao == 1) {
            getchar();

            // pegando o path que o usuário digitar
            printf("\n+++ ATENÇÃO +++\n");
            printf("Digite o caminho do arquivo onde está a mensagem. \nCaso queria testar, digite o nome do arquivo 'mensagem.txt'\n");
            printf("Digite aqui: ");
            caminhoLeitura = ler_linha();

            if(caminhoLeitura != NULL) {
                // lendo o arquivo através do path
                mensagem = ler_arquivo(caminhoLeitura);
                printf("Mensagem extraída do arquivo: %s\n", mensagem);

                printf("Pressione enter para continuar...");
                getchar();
                
                // usuário digitando a chave
                printf("\nDigite a sua chave: ");
                key = ler_linha();
                
                // aqui chama a função que realiza a encriptação
                mensagemEcriptada = playfair(key, mensagem);
                printf("Mensagem Encriptada: %s\n", mensagemEcriptada);

                getchar();
                // pegando o path do usuário para a escrita
                printf("+++ ATENÇÃO +++\n");
                printf("Se desejar especificar um arquivo onde escrever a mensagem encriptada, digite 0\n");
                printf("Se não, digite qualquer número que o algoritmo sobrescreverá o arquivo 'mensagem.txt'\n");
                scanf("%d", &opcaoEscrita);
                if(opcaoEscrita == 0) {
                    getchar();
                    printf("Digite o caminho: ");
                    caminhoEscrita = ler_linha();
                    gravar_arquivo(caminhoEscrita, mensagemEcriptada);
                }
                else gravar_arquivo(caminhoLeitura, mensagemEcriptada);
            }
        }
        else if(opcao != 2) {
            printf("\nOpção errada amigo...\nTente novamente, por favor!\n");
            getchar();
        }

    } while(opcao != 2);
    
    return 0;
}
