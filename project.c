/* iaed-23 - ist199656 - project2 */

/*
------------------------------------------------------------------------------
Ficheiro: project.c
Autor: Diogo Guerreiro
Descrição: Projeto carreiras, paragens e ligações de uma rede de autocarros
------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define NAO_EXISTE -1 /*codigo de erro*/

#define TRUE 1 /*true*/
#define FALSE 0 /*false*/



/*Estruturas de dados*/

/*Estrutura de dados para as linked lists de strings
Utilizadas para as paragens das carreiras e para as carreiras das 
paragens*/

typedef struct str_node  {
    struct str_node *next, *previous;
    char *c;
} no_string;

typedef struct  {
    struct str_node *head, *last;
} lista_strings;


/* Estrutura de dados para as Paragens*/
typedef struct{
    char *nome;
    double latitude;
    double longitude;
    lista_strings *carreiras_da_paragem;
    int tamanho_carreiras_da_paragem;
} Paragem;

/* Estrutura de dados para as Carreiras*/
typedef struct{
    char *nome;
    Paragem *origem; 
    Paragem *destino;
    int num_paragens;
    int num_ligacoes;
    double duracao_carreira;
    double custo_carreira;
    lista_strings *paragens_da_carreira ;
} Carreira;


/*Estritura de dados para as ligações*/
typedef struct{
    char *nome_carreira;
    Paragem *origem;
    Paragem *destino;
    double custo;
    double duracao;
} Ligacao;

/*Estrututa de dados para a linked list das carreiras*/

typedef struct str_node_carreira  {
    struct str_node_carreira *next, *previous;
    Carreira *c;
} no_carreira;

typedef struct  {
    struct str_node_carreira *head, *last;
} lista_carreira;

/*Estrutura de dados para a linked list de paragens*/

typedef struct str_node_paragem  {
    struct str_node_paragem *next, *previous;
    Paragem *c;
} no_paragem;

typedef struct  {
    struct str_node_paragem *head, *last;
} lista_paragem;

/*Estrutura de dados para a linked list de ligações*/

typedef struct str_node_ligacao  {
    struct str_node_ligacao *next, *previous;
    Ligacao *c;
} no_ligacao;

typedef struct  {
    struct str_node_ligacao *head, *last;
} lista_ligacao;



/* Headers */


void free_list_string(lista_strings* ls);
void apaga_string (char *nome_string, lista_strings *_paragens_da_carreira);


/*Funções da Linked List das carreiras*/


/*---------------------------------------------------------------------------
A função mk_list_carreira não recebe argumentos e devolve um ponteiro para
uma lista_carreira.
A função é responsável por inicializar a linked list das carreiras cujo
endereço de memória foi passado como argumento.

----------------------------------------------------------------------------*/

lista_carreira* mk_list_carreira(){

    lista_carreira* ls =(lista_carreira*) malloc (sizeof(lista_carreira));
    ls->head= ls->last =NULL;
    return ls;
}

/*---------------------------------------------------------------------------
A função add_last_carreira recebe um ponteiro para uma lista_carreira e um 
ponteiro para uma carreira e não devolve nada.

A função adiciona uma carreira no final da linked list das carreiras cujo
endereço de memória foi passado como argumento.

----------------------------------------------------------------------------*/

void add_last_carreira(lista_carreira* ls, Carreira *c ){
    no_carreira* new = (no_carreira*) malloc(sizeof(no_carreira));
    new->c=c;
    new->next= NULL;
    new->previous =ls->last;
    if (ls->last != NULL){
        ls->last->next= new;
    }
    ls->last= new;
    if (ls->head == NULL){
        ls->head = new;
    }
}

/*---------------------------------------------------------------------------
A função add_first_carreira recebe um ponteiro para uma lista_carreira e um 
ponteiro para uma carreira e não devolve nada.

A função adiciona uma carreira no inicio da linked list das carreiras cujo
endereço de memória foi passado como argumento.

----------------------------------------------------------------------------*/

void add_first_carreira(lista_carreira* ls, Carreira *c) {
    no_carreira* new = (no_carreira*) malloc(sizeof(no_carreira));
    new->c = c;
    new->next = ls->head;
    new->previous = NULL;
    if (ls->head != NULL) {
        ls->head->previous = new;
    }
    ls->head = new;
    if (ls->last == NULL) {
        ls->last = new;
    }
}

/*---------------------------------------------------------------------------
A função free_list_carreira recebe um ponteiro para uma lista_carreira
e não devolve nada. A função é responsável por eliminar toda a memória
alocada à linked list das carreiras excepto a própria lista.

----------------------------------------------------------------------------*/

void free_list_carreira(lista_carreira* ls){
    while (ls->head){
        no_carreira* a = ls->head->next;
        free(ls->head->c->nome);
        free_list_string(ls->head->c->paragens_da_carreira);
        free(ls->head->c);
        free(ls->head);
        ls->head=a;
    }
    ls->head = NULL;
    ls->last = NULL;
}


/* Funções para a Linked List das paragens */


/*---------------------------------------------------------------------------
A função mk_list_paragem não recebe argumentos e devolve um ponteiro para
uma lista_paragem.
A função é responsável por inicializar a linked list das paragens cujo
endereço de memória foi passado como argumento.


----------------------------------------------------------------------------*/

lista_paragem* mk_list_paragem(){

    lista_paragem* ls =(lista_paragem*) malloc (sizeof(lista_paragem));
    ls->head= ls->last =NULL;
    return ls;
}

/*---------------------------------------------------------------------------
A função add_last_paragem recebe um ponteiro para uma lista_paragem e um 
ponteiro para uma Paragem e não devolve nada.

A função adiciona uma Paragem no final da linked list das Paragens cujo
endereço de memória foi passado como argumento.


----------------------------------------------------------------------------*/

void add_last_paragem (lista_paragem* ls, Paragem *c ){
    no_paragem* new = (no_paragem*) malloc(sizeof(no_paragem));
    new->c=c;
    new->next= NULL;
    new->previous =ls->last;
    if (ls->last != NULL){
        ls->last->next= new;
    }
    ls->last= new;
    if (ls->head == NULL){
        ls->head = new;
    }
}

/*---------------------------------------------------------------------------
A função add_first_paragem recebe um ponteiro para uma lista_paragem e um 
ponteiro para uma Paragem e não devolve nada.

A função adiciona uma Paragem no inicio da linked list das Paragens cujo
endereço de memória foi passado como argumento.


----------------------------------------------------------------------------*/

void add_first_paragem(lista_paragem* ls, Paragem *c) {
    no_paragem* new = (no_paragem*) malloc(sizeof(no_paragem));
    new->c = c;
    new->next = ls->head;
    new->previous = NULL;
    if (ls->head != NULL) {
        ls->head->previous = new;
    }
    ls->head = new;
    if (ls->last == NULL) {
        ls->last = new;
    }
}

/*---------------------------------------------------------------------------
A função free_list_paragem recebe um ponteiro para uma lista_paragem
e não devolve nada. A função é responsável por eliminar toda a memória
alocada à linked list das paragens excepto a própria lista.


----------------------------------------------------------------------------*/


void free_list_paragem(lista_paragem* ls){
    while (ls->head){
        no_paragem* a = ls->head->next;
        free(ls->head->c->nome);
        free_list_string(ls->head->c->carreiras_da_paragem);
        free(ls->head->c);
        free(ls->head);
        ls->head=a;
    }
    ls->head = NULL;
    ls->last = NULL;
}


/* Funções para a Linked List das paragens */


/*---------------------------------------------------------------------------
A função mk_list_paragem não recebe argumentos e devolve um ponteiro para
uma lista_strings.
A função é responsável por inicializar a linked list das strings cujo
endereço de memória foi passado como argumento.


----------------------------------------------------------------------------*/

lista_strings* mk_list_string(){

    lista_strings* ls =(lista_strings*) malloc (sizeof(lista_strings));
    ls->head= ls->last =NULL;
    return ls;
}

/*---------------------------------------------------------------------------
A função add_last_string recebe um ponteiro para uma lista_strings e um 
ponteiro para uma Paragem e não devolve nada.

A função adiciona uma string no final da linked list das strings que foi
passada como argumento.

----------------------------------------------------------------------------*/

void add_last_string(lista_strings* ls, const char *c ){
    no_string* new = (no_string*) malloc(sizeof(no_string));
    new->c= (char*) malloc(sizeof(char)* (strlen(c)+1));
    strcpy(new->c, c);
    new->next= NULL;
    new->previous =ls->last;
    if (ls->last != NULL){
        ls->last->next= new;
    }
    ls->last= new;
    if (ls->head == NULL){
        ls->head = new;
    }
}

/*---------------------------------------------------------------------------
A função add_first_string recebe um ponteiro para uma lista_strings e um 
ponteiro para uma string e não devolve nada.

A função adiciona uma string no inicio da linked list das strings cujo
endereço de memória foi passado como argumento.


----------------------------------------------------------------------------*/

void add_first_string(lista_strings* ls, const char *c) {
    no_string* new = (no_string*) malloc(sizeof(no_string));
    new->c= (char*) malloc(sizeof(char)* (strlen(c)+1));
    strcpy(new->c, c);
    new->next = ls->head;
    new->previous = NULL;
    if (ls->head != NULL) {
        ls->head->previous = new;
    }
    ls->head = new;
    if (ls->last == NULL) {
        ls->last = new;
    }
}

/*---------------------------------------------------------------------------
A função free_list_string recebe um ponteiro para uma lista_strings
e não devolve nada. A função é responsável por eliminar toda a memória
alocada à linked list das strings excepto a própria lista.


----------------------------------------------------------------------------*/

void free_list_string(lista_strings* ls){
    while (ls->head){
        no_string* a = ls->head->next;
        free(ls->head->c);
        free(ls->head),
        ls->head=a;
    }
    free(ls);
}

/*Linked List das ligações*/

/*---------------------------------------------------------------------------
A função mk_list_ligacao não recebe argumentos e devolve um ponteiro para
uma lista_ligacao.
A função é responsável por inicializar a linked list das ligações cujo
endereço de memória foi passado como argumento.


----------------------------------------------------------------------------*/

lista_ligacao* mk_list_ligacao(){

    lista_ligacao* ls =(lista_ligacao*) malloc (sizeof(lista_ligacao));
    ls->head= ls->last =NULL;
    return ls;
}

/*---------------------------------------------------------------------------
A função add_last_ligacao recebe um ponteiro para uma lista_ligacao e um 
ponteiro para uma Ligacao e não devolve nada.

A função adiciona uma Ligacao no final da linked list das ligações que foi
passada como argumento.


----------------------------------------------------------------------------*/

void add_last_ligacao(lista_ligacao* ls, Ligacao *c ){
    no_ligacao* new = (no_ligacao*) malloc(sizeof(no_ligacao));
    new->c= (Ligacao*) malloc (sizeof(Ligacao));
    new->c=c;
    new->next= NULL;
    new->previous =ls->last;
    if (ls->last != NULL){
        ls->last->next= new;
    }
    ls->last= new;
    if (ls->head == NULL){
        ls->head = new;
    }
}

/*---------------------------------------------------------------------------
A função free_list_string recebe um ponteiro para uma lista_strings
e não devolve nada. A função é responsável por eliminar toda a memória
alocada à linked list das strings excepto a própria lista.

----------------------------------------------------------------------------*/


void free_list_ligacao(lista_ligacao* ls){
    while (ls->head){
        no_ligacao* a = ls->head->next;
        free(ls->head->c->nome_carreira);
        free(ls->head->c);
        free(ls->head);
        ls->head=a;
    }
    ls->head = NULL;
    ls->last = NULL;
}


/*Funções de Leitura*/

/*---------------------------------------------------------------------------
A função leProximaPalavra recebe um char [] e devolve um inteiro.
A função vai ler uma palavra do input e vai guardar no char [] passado como
argumento.
Caso a função encontre uma aspa, só para de ler quando encontarar outra aspa.
Dá return de 1 se encontrou o final da linha e return de -1 caso não leia
nenhuma palavra
----------------------------------------------------------------------------*/


int leProximaPalavra(char linha[]) {
    char c = getchar();
    int i = 0;
    int nao_le_palavra = 1; /* flag que indica se nenhuma palavra foi lida*/
    
    /* Ignora espaços em branco e tabs*/
    while (c == ' ' || c == '\t')
        c = getchar();
    
    /* Se o primeiro caractere é uma aspa vai ler outra aspa*/
    if (c == '"') {
        c = getchar(); /* Lê o próximo char*/
        while (c != '"' && c != '\n') { /* Continua a ler até encontrar*/
            linha[i++] = c;             /*outra aspa ou então um \n*   */
            c = getchar();
        }
        linha[i] = '\0'; /* Adiciona o \0 no final da string*/
        nao_le_palavra = 0; /* como lemos uma palavra metemos a flag a 0 */
        c = getchar();
        return (c == '\n'); /* Return 1 se encontrou o fim da linha*/
    }
    else { /* Se o primeiro char não é uma aspa leio como uma palavra normal*/
        while (c != ' ' && c != '\t' && c != '\n') {
            linha[i++] = c;
            c = getchar();
        }
        linha[i] = '\0'; /* Adiciona o \0 no final da string*/
        if (i > 0) /* indica que uma palavra foi lida*/
            nao_le_palavra = 0;
        if (nao_le_palavra && c == '\n') /* se não leu nenhuma palavra e*/
            return -1;                   /* chegou ao fim da linha      */
        else
            return (c == '\n'); /* return 1 se encontrou o fim da linha*/
    }
}
/*-----------------------------------------------------------------------------
A função lePalavraAteFimDeLinha recebe como argumento um char [] e não
devolve nada. A Função é responsável por ler o input dado até encontrar um
\n e guardando o que foi lido no char [] passado como argumento
-----------------------------------------------------------------------------*/

void lePalavraAteFimDeLinha(char str[]) {
	char c = getchar();
	int i = 0;
	while (c == ' ' || c == '\t')
		c = getchar();
	while (c != '\n') {
		str[i++] = c;
		c = getchar();
	}
	str[i] = '\0';
}

/*-----------------------------------------------------------------------------
A função leAteFimDeLinha não recebe argumentos e não devolve nada.
É responsável por descartar o input até encontrar um \n.

-----------------------------------------------------------------------------*/
void leAteFimDeLinha() {
	char c = getchar();
	while (c != '\n')
		c = getchar();
}


/*Funções das Carreiras*/

/*-----------------------------------------------------------------------------
A função encontraCarreira recebe um ponteiro para uma lista_carreira
e um ponteiro para uma string e devolve um ponteiro para uma carreira.
A função vai percorrer todos os nos da linked list da lista_carreiras 
e se encontrar o nome da carreira passado como argumento, devolve a carreira

-----------------------------------------------------------------------------*/

Carreira* encontraCarreira(char *nome, lista_carreira *_carreiras){
    
    no_carreira* no = _carreiras->head;
    if (_carreiras->head == NULL && _carreiras->last == NULL){
        return NULL;
    }

    while (no != NULL){
        if (strcmp(no->c->nome, nome ) == 0){
            return no->c;
        }else{
            no = no->next;
        }
    }
    return NULL;
}


/*-----------------------------------------------------------------------------
A função adicionaCarreira recebe um ponteiro para uma string, um ponteiro
para uma lista_carreira e não devolve nada.
A função vai adicionar uma carreira no final da linked list das carreiras

-----------------------------------------------------------------------------*/

void adicionaCarreira(char *nome, lista_carreira* _carreiras){
    Carreira *a= (Carreira*) malloc(sizeof(Carreira));
    a->nome = (char*) malloc (sizeof(char) * (strlen(nome) +1));
    strcpy(a->nome, nome);
    a->custo_carreira=0;
    a->duracao_carreira=0;
    a->num_ligacoes=0;
    a->num_paragens=0;
    a->destino = NULL;
    a->origem = NULL;

    a->paragens_da_carreira = mk_list_string();
    add_last_carreira(_carreiras, a);
    
}

/*-----------------------------------------------------------------------------
A função temLigacoes recebe um ponteiro para uma Carreira e devolve 
um inteiro.
Caso a carreira tenha ligações devolve 1, caso contrário devolve 0.

-----------------------------------------------------------------------------*/

int temLigacoes(Carreira *c){
    if (c->num_ligacoes==0){
        return FALSE;
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
A função mostraCarreira_comLigacoes recebe um ponteiro para uma Carreira
e não devolve nada.
Dá print de uma carreira com ligações.

-----------------------------------------------------------------------------*/

void mostraCarreira_comLigacoes (Carreira *c){
    if (c->origem == NULL || c->destino == NULL){
        return;
    }else{
        printf("%s %s %s %d %.2f %.2f\n", c->nome,c->origem->nome,\
         c->destino->nome,\
        c->num_paragens, c->custo_carreira,c->duracao_carreira);
    }
}

/*-----------------------------------------------------------------------------
A função mostraCarreira_semLigacoes recebe um ponteiro para uma Carreira
e não devolve nada.
Dá print de uma carreira sem ligações.

-----------------------------------------------------------------------------*/

void mostraCarreira_semLigacoes (Carreira *c){
    printf("%s %d 0.00 0.00\n", c->nome,c->num_paragens);
}

/*-----------------------------------------------------------------------------
A função listaTodasCarreiras recebe um ponteiro para uma lista_carreira e
não devolve nada.
A função vai dar print de todas as Carreiras que estão na linked list
das carreiras.

-----------------------------------------------------------------------------*/

void listaTodasCarreiras(lista_carreira *_carreiras){
    no_carreira* no = _carreiras->head;
    
    if (_carreiras->head == NULL && _carreiras->last == NULL){
        return;
    }

    
    while (no != NULL){
        if (strlen(no->c->nome) < 6){
            if (temLigacoes(no->c)){
                mostraCarreira_comLigacoes(no->c);
            }else{
                mostraCarreira_semLigacoes(no->c);
            }
        }
        no = no->next;
    }
}


/*-----------------------------------------------------------------------------
A função mostraCarreira recebe um ponteiro para as paragens_da_carreira e 
não devolve nada. Primeiro verifica se a carreira em questão tem ligações.
Caso tenha, dá print das paragens da carreira por ordem.

-----------------------------------------------------------------------------*/

void mostraCarreira (lista_strings *paragens_da_carreira){ 
    no_string* no = paragens_da_carreira->head;
    if (paragens_da_carreira->head == NULL && \
    paragens_da_carreira->last == NULL){
        return;
    }
    while (no != NULL){
        if (no->next == NULL){
            printf("%s\n", no->c);
            break;
        }else{
            printf("%s, ", no->c);
        }
        no = no->next;
    }
}


/*-----------------------------------------------------------------------------
A função mostraCarreiraInversa recebe um ponteiro para uma lista_strings
que represennta as paragens de uma carreira e não devolve nada.

A função vai dar print das paragens da carreira por ordem inversa.

-----------------------------------------------------------------------------*/

void mostraCarreiraInversa (lista_strings *paragens_da_carreira){
    no_string* no = paragens_da_carreira->last;
    if (paragens_da_carreira->head == NULL\
     && paragens_da_carreira->last == NULL){
        return;
    }
    while (no != NULL){
        if (no->previous == NULL){
            printf("%s\n", no->c);
        }else{
            printf("%s, ", no->c);
        }
        no = no->previous;
    }
}


/* Funcoes Paragens */

/*-----------------------------------------------------------------------------
A função encontraParagem recebe um ponteiro para uma string que vai ser
o nome de uma paragem. Vai percorrer a linked list das paragens e quando
encontrar aquela que corresponde com o nome delvolve. Caso contrário
devolve NULL.

-----------------------------------------------------------------------------*/


Paragem* encontraParagem (char *nome, lista_paragem *_paragens){ 
    no_paragem* no = _paragens->head;

    if (_paragens->head == NULL && _paragens->last == NULL){
        return NULL;
    }

    while (no != NULL){
        if (strcmp(no->c->nome, nome) == 0){
            return no->c;
        }else{
            no = no->next;
        }
    }
    return NULL;
}




/*-----------------------------------------------------------------------------
A função paragemExiste recebe um ponteiro para uma string e um ponteiro para
uma lista_paragem.

A função vai percorrer a linked list das paragens e vai devolver 1 caso
encontre uma paragem com o nome do valor do ponteiro recebido e 0 caso
contrário.

-----------------------------------------------------------------------------*/

int paragemExiste (char *nome,lista_paragem *_paragens){
    no_paragem* no = _paragens->head;

    if (_paragens->head == NULL && _paragens->last == NULL){
        return 0;
    }

    while (no != NULL){
        if (strcmp(no->c->nome, nome) == 0){
            return 1;
        }else{
            no = no->next;
        }
    }
    return 0;
}

/*-----------------------------------------------------------------------------
A função confirma_inverso recebe um char [] e devolve um inteiro.
A função verifica se o char [] passado como argumento é uma das opções
de prefixo da palavra inverso.
Os prefixos aceites são: "inverso", "invers", "inver", "inve" e "inv".

-----------------------------------------------------------------------------*/

int confirma_inverso(char inverso[8]){
    if (strcmp(inverso, "inverso")==0 || strcmp(inverso, "invers")==0 \
    || strcmp(inverso, "inver")==0 || strcmp(inverso, "inve")==0\
    || strcmp(inverso, "inv")==0){
        return 1;
    }else{
        return 0;
    }
}

/*p <nome paragem> <latitude> <longitude>*/

/*-----------------------------------------------------------------------------
A função adicionaParagem recebe um ponteiro para uma string, uma lista_paragem
e dois valores reais. A string representa o nome da paragem e os valores reais
a latitude e a longitude e não devolve nada.

A função vai adicionar a paragem no final da linked list das paragens.

-----------------------------------------------------------------------------*/

void adicionaParagem(char *nome_paragem, double latitude,\
 double longitude, lista_paragem *_paragens){
    Paragem *a = (Paragem*) malloc(sizeof(Paragem));
    if (paragemExiste(nome_paragem, _paragens)){
        printf("%s: stop already exists.\n", nome_paragem);
        free(a);
        return;
    }
    a->nome = (char*) malloc(sizeof(char) * (strlen(nome_paragem)+1));
    strcpy(a->nome, nome_paragem);
    a->latitude=latitude;
    a->longitude=longitude;
    a->tamanho_carreiras_da_paragem=0;
    a->carreiras_da_paragem = mk_list_string();
    add_last_paragem(_paragens, a);
}


/*-----------------------------------------------------------------------------
A função listaTodasParagens recebe um ponteiro para uma lista_paragem e não
devolve nada.

A função vai percorrer a linked list das paragens e vai dar print delas uma
a uma (nome, latitude e longitude).

-----------------------------------------------------------------------------*/

void listaTodasParagens (lista_paragem *_paragens){
    no_paragem* no = _paragens->head;

    if (_paragens->head == NULL && _paragens->last == NULL){
        return;
    }

    while (no != NULL){
        printf("%s: %16.12f %16.12f %d\n",\
         no->c->nome, no->c->latitude,no->c->longitude,\
         no->c->tamanho_carreiras_da_paragem);
        no = no->next;
    }
}

/*-----------------------------------------------------------------------------
A função mostraParagem recebe uma string e um ponteiro para uma lista_paragem
e não devolve nada. 

A função vai primeiro verificar se já existe na linked list das paragens uma
paragem com o nome indicado. Caso não exista imprime uma mensagem de erro
e caso haja imprime a sua latitude e longitude.

-----------------------------------------------------------------------------*/

void mostraParagem(char nome[], lista_paragem *_paragens){

    if (_paragens->head == NULL && _paragens->last == NULL){
        printf("%s: no such stop.\n", nome);
    }

    else if(paragemExiste(nome, _paragens) == FALSE){
        printf("%s: no such stop.\n", nome);
    }else{
        Paragem *p= encontraParagem(nome, _paragens);
        printf("%16.12f %16.12f\n", p->latitude,\
         p->longitude);

    }
}

/*-----------------------------------------------------------------------------
A função esta_na_lista receve um char [] e um inteiro e devolve um inteiro.
O char [] passado como argumento é o nome de uma carreira e o inteiro
é o index da paragem no array global de paragens que estamos a analisar.
A função vai percorrer o array de carreiras_da_paragem da paragem 
correspondente ao index dado, e vai dar return 1 se a carreira pertencer 
a essa lista e 0, caso contraŕio.

A função esta_na_lista recebe uma string e um ponteiro para uma lista_strings
que representa as carreiras de uma paragem. 

A função vai devolver 1 se o nome passado como argumento é o nome de uma das
strings que pertence à linked list de strings e 0 caso contrário.

-----------------------------------------------------------------------------*/

int esta_na_lista(lista_strings *carreiras_da_paragem, char nome[]){

    no_string* no = carreiras_da_paragem->head;

    if (carreiras_da_paragem->head == NULL &&\
     carreiras_da_paragem->last ==NULL){
        return 0;
    }

    while (no != NULL){
        if (strcmp(no->c, nome)==0){
            return 1;
        }
        no = no->next;
    }
    return 0;
}


/*-----------------------------------------------------------------------------
A função valida_restricoes recebe três char [] e dois doubles e devolve um
inteiro.
A função vai ver se os argumentos passados verificam ou não as condições;
carreira existir, paragem de origem existir, paragem de destino existir e
custo e duração serem positivos.
Caso entre em algum dos erros a função da return de 1, caso contrário dá
return de 0.

-----------------------------------------------------------------------------*/


int valida_restricoes (char nome_carreira[],\
char nome_origem[], char nome_destino[],\
double custo, double duracao, lista_carreira *_carreiras,\
lista_paragem *_paragens){

    if (encontraCarreira(nome_carreira, _carreiras) == NULL){
        printf("%s: no such line.\n", nome_carreira);
        return 1;
    }
    if (encontraParagem(nome_origem, _paragens) ==  NULL){
        printf("%s: no such stop.\n", nome_origem);
        return 1;
    }
    if (encontraParagem(nome_destino, _paragens) ==  NULL){
        printf("%s: no such stop.\n", nome_destino);
        return 1;
    }
    if (custo<0 || duracao<0){
        printf("negative cost or duration.\n");
        return 1;
    }

    return 0;
}

/*-----------------------------------------------------------------------------
A função insere_ordenado recebe um ponteiro para uma string e um ponteiro
para uma Paragem e não devolve nada.

A função vai adicionar de maneira ordenada (alfabeticamente) o valor do
ponteiro para uma string na linked list de strings de carreiras da paragem.

-----------------------------------------------------------------------------*/


void insere_ordenado (char *nome_carreira, Paragem *p){
    no_string* new;
    no_string *no = p->carreiras_da_paragem->head;
    no_string *prev = NULL; /* Adicionar um ponteiro para o nó anterior*/
    p->tamanho_carreiras_da_paragem++;

    /* Caso a lista esteja vazia, adicionar no início*/
    if (no == NULL){
        add_first_string(p->carreiras_da_paragem, nome_carreira);
        return; /* Retornar após adicionar*/
    }

    /* Percorrer a lista até encontrar a posição correta*/
    while (no != NULL){
        /* Se encontrou posição correta, inserir antes do nó atual*/
        if (strcmp(no->c, nome_carreira) > 0){
            new = (no_string*) malloc(sizeof(no_string));
            new->c = (char*) malloc (sizeof(char) * (strlen(nome_carreira)+1));
            strcpy(new->c, nome_carreira);
            new->next = no;
            new->previous = prev;
            if (prev == NULL) {
                /* Se prev for nulo inserimos no inicio da lista*/
                p->carreiras_da_paragem->head = new;
            } else {
                prev->next = new;
            }
            no->previous = new;
            break;
        }
        prev = no; /* Atualizar o nó anterior antes de avançar*/
        no = no->next;
    }

    /* Se não encontrou posição correta, adicionar no final */
    if (no == NULL){
        add_last_string(p->carreiras_da_paragem, nome_carreira);
    }
}


/*-----------------------------------------------------------------------------
A função adiciona_primeira_ligacao, recebe todos os argumentos que são
necessários para criar uma ligação: dois valores reais que são o custo e
a duração. Ainda recebe um ponteiro para uma Carreira e outros dois
ponteiros para a paragem de origem e destino.

Esta função é chamada quando a ligação a ser adicionada é a primeira,
ou seja o num_paragens e o num_ligacoes da carreira ainda são os dois igual
a 0. Vai adicionar o nome das duas paragens na linked list das paragens
da carreira.

-----------------------------------------------------------------------------*/

void adiciona_primeira_ligacao (double custo, double duracao,\
Carreira *c, Paragem *origem, Paragem *destino){

    c->num_ligacoes++;
    c->custo_carreira += custo;
    c->duracao_carreira += duracao;
    c->num_paragens += 2;
    c->origem = origem;
    c->destino = destino;
    add_last_string(c->paragens_da_carreira, origem->nome);
    add_last_string(c->paragens_da_carreira, destino->nome);
}

/*-----------------------------------------------------------------------------
A função adiciona_ligacao_circular, recebe todos os argumentos que são
necessários para criar uma ligação: dois valores reais que são o custo e
a duração. Ainda recebe um ponteiro para uma Carreira e outros dois
ponteiros para a paragem de origem e destino.

Esta função é chamada quando a ligação a ser adicionada é circular. 
Vai adicionar o nome da paragem de destino na linked list das paragens
da carreira.

-----------------------------------------------------------------------------*/

void adiciona_ligacao_circular (double custo, double duracao,\
Carreira *c, Paragem *destino){

    c->num_ligacoes ++;
    c->custo_carreira += custo;
    c->duracao_carreira += duracao;
    c->origem = destino;
    c->destino = destino;
    add_last_string(c->paragens_da_carreira, destino->nome);
    c->num_paragens ++;

}

/*-----------------------------------------------------------------------------
A função adiciona_ligacao_final, recebe todos os argumentos que são
necessários para criar uma ligação: dois valores reais que são o custo e
a duração. Ainda recebe um ponteiro para uma Carreira e outros dois
ponteiros para a paragem de origem e destino.

Esta função é chamada quando a ligação a ser adicionada é feita no final. 
Vai adicionar o nome da paragem de destino na linked list das paragens
da carreira no final da mesma.

-----------------------------------------------------------------------------*/

void adiciona_ligacao_final (double custo, double duracao,\
Carreira *c, Paragem *destino){

    c->destino = destino;
    c->num_ligacoes ++;
    c->custo_carreira += custo;
    c->duracao_carreira += duracao;
    add_last_string(c->paragens_da_carreira, destino->nome);
    c->num_paragens++;

}

/*-----------------------------------------------------------------------------
A função adiciona_ligacao_final, recebe todos os argumentos que são
necessários para criar uma ligação: dois valores reais que são o custo e
a duração. Ainda recebe um ponteiro para uma Carreira e outros dois
ponteiros para a paragem de origem e destino.

Esta função é chamada quando a ligação a ser adicionada é feita no inicio. 
Vai adicionar o nome da paragem de destino na linked list das paragens
da carreira no inicio da mesma.

-----------------------------------------------------------------------------*/

void adiciona_ligacao_inicio (double custo, double duracao,\
 Carreira *c, Paragem *origem){

    c->origem= origem;
    c->num_ligacoes++;
    c->custo_carreira += custo;
    c->duracao_carreira += duracao;
    add_first_string(c->paragens_da_carreira, origem->nome);
    c->num_paragens++;
}

/*-----------------------------------------------------------------------------
A função adiciona_ligação_inicio, recebe todos os argumentos que são
necessários para criar uma ligação. Os inteiros recebidos são:
indice-> posição da carreira no array global de carreiras
j e jj-> posição das paragens de origem e destino no array global de ligacões
Como é a paragem é adicionada no inicio da carreira temos que dar shift
das paragens já existentes e depois inserir no início.

A função adiciona_ligação_inicio recebe um ponteiro para uma string que
é o nome da carreira e dois ponteiros para duas Paragens: origem e destino
de uma ligação.

A função vai verificar se o nome das carreiras já está contido na linked list
de strings (tanto para a paragem de origem como de destino) e caso não esteja
adiciona.

-----------------------------------------------------------------------------*/

void atualizar_carreiras_da_paragem(char *nome_carreira,\
Paragem *origem, Paragem *destino){
    
    /*Atualizamos origem*/
    if (esta_na_lista(origem->carreiras_da_paragem, nome_carreira) == 0){
        insere_ordenado(nome_carreira, origem);
    }
    /*Atualizamos destino*/
    if (esta_na_lista(destino->carreiras_da_paragem, nome_carreira) == 0){
        insere_ordenado(nome_carreira,destino);
    }

}

/*---------------------------------------------------------------------------
A função encontra_ligacao recebe 3 ponteiros para strings cujo valor
representa o nome da carreira, o nome da origem e o nome de destino e ainda
um ponteiro para uma lista_ligacao cujo valor é a linked list das ligações e
devolve um ponteiro para uma Ligação.

A função vai percorrer todas as ligações e caso encontre uma ligação
que todas as condições sejam respeitadas (nomeda carreira, nome da paragem
e nome de destino) então devolve um ponteiro para essa ligação. Caso contrário
devolve NULL.


----------------------------------------------------------------------------*/

Ligacao* encontra_ligacao( char *nome_carreira,char *nome_origem,\
 char *nome_destino, lista_ligacao *_ligacoes){
    no_ligacao *no = _ligacoes->head;
    while (no != NULL){
        if (strcmp(no->c->origem->nome, nome_origem) == 0 &&\
         strcmp(no->c->destino->nome, nome_destino)==0 && \
         strcmp(no->c->nome_carreira, nome_carreira) ==0){
            return no->c;
        }else{
            no = no->next;
        }
    }
    return NULL;

}




/*-----------------------------------------------------------------------------
A função AddLigacao recebe 3 ponteiros para strings cujo valor
representa o nome da carreira, o nome da origem e o nome de destino e ainda
um ponteiro para uma lista_ligacao cujo valor é a linked list das ligações e
devolve um ponteiro para uma Ligação, dois valores reais que são o custo e a 
duração da ligação e ainda mais dois ponteiros de uma lista_carreira e outro
de uma lista_paragem.

A função primeiro vai analisar se existe algum erro com os dados fornecidos.
De seguida vai perceber se a ligação a ser adicionada é a primeira da
carreira ou se já existem ligações anteriores.
O comportamento para cada um destes casos vai ser diferente.

-----------------------------------------------------------------------------*/

void AddLigacao (char *nome_carreira, char *nome_origem, char *nome_destino,\
double custo, double duracao,lista_carreira *_carreiras,\
 lista_paragem *_paragens,\
lista_ligacao *_ligacoes){
    Ligacao *a = (Ligacao*) malloc (sizeof(Ligacao));
    /* Encontra os indices nos respetivos arrays globais e guarda os valores*/

    Carreira *c= encontraCarreira(nome_carreira, _carreiras);
    Paragem *origem= encontraParagem(nome_origem, _paragens);
    Paragem *destino= encontraParagem(nome_destino, _paragens);

    /*Verifica as restrições*/
    if (valida_restricoes(nome_carreira,nome_origem,\
    nome_destino,custo,duracao, _carreiras, _paragens) == 1){
        return;
    }
    
    /*Caso ainda nao haja nenhuma ligacao*/
    if (c->num_ligacoes==0 && c->num_paragens ==0){
       adiciona_primeira_ligacao (custo,duracao,c,origem,destino);
    /*Caso a carreira ja tenha ligacoes*/
    }else{
        /*Mensagem de erro caso nao coincida com origem e destino*/
        if (strcmp(nome_origem, c->destino->nome)\
         && strcmp(nome_destino, c->origem->nome)){
            printf("link cannot be associated with bus line.\n");
            return;
        }
        /*Se for circular*/
        if (strcmp(nome_destino, c->origem->nome)==0 \
        && strcmp(nome_origem, c->destino->nome)==0){
            adiciona_ligacao_circular (custo,duracao,c,destino);
        }

        /* A nova ligacao é adicionada no final*/
        else if (strcmp(nome_origem, c->destino->nome)==0){
            adiciona_ligacao_final (custo,duracao,c,destino);
        }
        /*A nova ligacao é adicionada no inicio*/
        else if (strcmp(nome_destino, c->origem->nome)==0){
            adiciona_ligacao_inicio (custo,duracao,c,origem);
        }
    }
    /*Temos que atualizar as paragens que tem mais que uma carreira*/
    atualizar_carreiras_da_paragem(nome_carreira,origem,destino);
    

    a->nome_carreira = (char*) malloc (sizeof(char) * (strlen(nome_carreira)+1));
    strcpy(a->nome_carreira, nome_carreira);
    a->custo=custo;
    a->duracao=duracao;
    a->origem = encontraParagem(nome_origem, _paragens);
    a->destino = encontraParagem(nome_destino,_paragens);
    add_last_ligacao(_ligacoes, a);
}

/*-----------------------------------------------------------------------------
A função intersecao_carreiras recebe uma lista_paragem como argumento
e não devolve nada.
A função vai percorrer a linked list de paragens e para cada uma delas, vai
verificar sse o tamanho_carreiras_da_paragem é >= 2. Caso seja, percorrer o
array carreiras_da_paragem e vai dar print das carreiras lá existentes.

Não é preciso preocupar-nos com a ordem alfabética, porque já garantimos
que são inseridos por ordem alfabética.

-----------------------------------------------------------------------------*/

void intersecao_carreiras (lista_paragem *_paragens){

    no_paragem *no_p = _paragens->head;
    no_string *no_s;
    while (no_p != NULL){
        if (no_p->c->tamanho_carreiras_da_paragem >=2){
            printf("%s %d: ", no_p->c->nome,\
             no_p->c->tamanho_carreiras_da_paragem);
            no_s= no_p->c->carreiras_da_paragem->head;
            while(no_s != NULL){
                if (no_s->next == NULL){
                    printf("%s", no_s->c);
                }else{
                    printf("%s ", no_s->c);
                }
                no_s = no_s->next;
            }
            printf("\n");
        }
        no_p = no_p->next;
    }
}

/*-----------------------------------------------------------------------------
A função apaga_string recebe como argumentos um ponteiro para uma string
e um ponteiro para uma lista_strings e não devolve nada.

A função vai percorrer a linked list das paragens de uma carreira e caso
uma string com o mesmo nome do valor do ponteiro passado como argumento
vai apagá-lo. 

A forma como apaga depende da posição onde se encontra. Existem 4
possibilidades: Ser o único elemento, ser o primeiro elemento, ser o último
elemento e ser um elemento do meio.

-----------------------------------------------------------------------------*/


void apaga_string (char *nome_string, lista_strings *_paragens_da_carreira){
    no_string *no = _paragens_da_carreira->head;
    no_string *apaga;

    if (no == NULL){
        return;
    }
    while (no != NULL){
        if (strcmp(no->c, nome_string) == 0){
            /*quer dizer que só há um elemento na linked list*/
            if (no->next == NULL && no->previous == NULL){ 
                _paragens_da_carreira->head = NULL;
                _paragens_da_carreira->last = NULL;
                apaga = no;
                no = no->next;
                free(apaga->c);
                free(apaga);


            }else if (strcmp(no->c, _paragens_da_carreira->head->c)==0){
                _paragens_da_carreira->head = no->next;
                no->next->previous = NULL;
                apaga = no;
                no = no->next;
                free(apaga->c);
                free(apaga);
                

            }else if (strcmp(no->c, _paragens_da_carreira->last->c)==0){
                _paragens_da_carreira->last = no->previous;
                no->previous->next=NULL;
                apaga = no;
                no = no->next;
                free(apaga->c);
                free(apaga);
                

            }else{
                no->previous->next = no->next;
                no->next->previous = no->previous;
                apaga = no;
                no = no->next;
                free(apaga->c);
                free(apaga);
                

            }
        }else{
            no=no->next;
        }
        
    }

}

/*----------------------------------------------------------------------------
A função atualiza_intersecao_paragens recebe como argumentos um ponteiro para
uma string e uma lista_paragem e não devolve nada.

A função vai percorrer a linked list das paragens e vai verificar se
o nome da carreira que foi passado como argumento está contido na
linked list de strings das carreiras da paragem de cada uma das paragens.

Caso encontre, utiliza a função anterior para retirar a string e caso não
encontre não devolve nada.


------------------------------------------------------------------------------*/

void atualiza_intersecao_paragens (char *nome_carreira,\
 lista_paragem *_paragens){
    no_paragem *no = _paragens->head;
    no_string *no_s;
    while (no != NULL){
        no_s = no->c->carreiras_da_paragem->head;
        while (no_s != NULL){
            if (strcmp(no_s->c, nome_carreira)){
                apaga_string(nome_carreira, no->c->carreiras_da_paragem);
                no->c->tamanho_carreiras_da_paragem -= 1;
                break;
            }
            no_s = no_s->next;
        }
        no = no->next;
    }

}

/*----------------------------------------------------------------------------
A função apaga_carreira_da_ll recebe como argumentos um ponteiro para
uma string e uma lista_carreira e não devolve nada.

A função vai percorrer a linked list das carreiras e vai verificar se
o nome da carreira que foi passado como argumento está contido nessa linked
list.

Caso encontre, retira a nó com a Carreira. Existem 4 possibilidades para
retirar a Carreira: Ser o único elemento, ser o primeiro elemento, ser o último
elemento e ser um elemento do meio


------------------------------------------------------------------------------*/

void apaga_carreira_da_ll (char *nome_carreira, lista_carreira *_carreiras){
    no_carreira *no = _carreiras->head;

    while (no != NULL){
        if (strcmp(nome_carreira, no->c->nome) == 0){
            if (no->previous == NULL && no->next == NULL){
                _carreiras->head = NULL;
                _carreiras->last = NULL;
                free(no->c->nome);
                free_list_string(no->c->paragens_da_carreira);
                free(no->c);
                free(no);
                break;
            }else if (no->previous == NULL && no->next != NULL) {
                _carreiras->head = no->next;
                no->next->previous = NULL;
                free(no->c->nome);
                free_list_string(no->c->paragens_da_carreira);
                free(no->c);
                free(no);
                break;
            }else if (no->next == NULL && no->previous != NULL){
                _carreiras->last = no->previous;
                no->previous->next = NULL;
                free(no->c->nome);
                free_list_string(no->c->paragens_da_carreira);
                free(no->c);
                free(no);
                break;
            }else{
                no->previous->next = no->next;
                no->next->previous = no->previous;
                free(no->c->nome);
                free_list_string(no->c->paragens_da_carreira);
                free(no->c);
                free(no);
                break;
            }
        }
        no = no->next;
    }
}

/*---------------------------------------------------------------------------
A função recebe como argumentos um ponteiro para uma string e um ponteiro
para uma lista_paragem e não devolve nada.

A função vai percorrer a linked list das paragens e para cada paragem vai
percorrer a linked list de strings e verificar se o valor passado no
ponteiro como argumento está presente na lista de carreiras da paragem.

Caso esteja, o nó com a string é apagado e caso não esteja nada acontece.
Pode apagar de 4 maneiras diferentes: Ser o único elemento, ser o primeiro
elemento, ser o último elemento e ser um elemento do meio


----------------------------------------------------------------------------*/

void atualiza_carreiras_da_paragem (char *nome_carreira,\
 lista_paragem *_paragens){
    no_paragem *no_p = _paragens->head;
    no_string *no_s;
    while (no_p != NULL){
        no_s = no_p->c->carreiras_da_paragem->head;
        while (no_s != NULL){
            if (strcmp (nome_carreira, no_s->c) == 0){
                if (no_s->previous == NULL && no_s->next == NULL){
                no_p->c->carreiras_da_paragem->head = NULL;
                no_p->c->carreiras_da_paragem->last = NULL;
                no_p->c->tamanho_carreiras_da_paragem -=1;
                free(no_s->c);
                free(no_s);
                break;
            }else if (no_s->previous == NULL && no_s->next != NULL) {
                no_p->c->carreiras_da_paragem->head = no_s->next;
                no_s->next->previous = NULL;
                no_p->c->tamanho_carreiras_da_paragem -=1;
                free(no_s->c);
                free(no_s);
                break;

            }else if (no_s->next == NULL && no_s->previous != NULL){
                no_p->c->carreiras_da_paragem->last = no_s->previous;
                no_s->previous->next = NULL;
                no_p->c->tamanho_carreiras_da_paragem -=1;
                free(no_s->c);
                free(no_s);
                break;
            }else{
                no_s->previous->next = no_s->next;
                no_s->next->previous = no_s->previous;
                no_p->c->tamanho_carreiras_da_paragem -=1;
                free(no_s->c);
                free(no_s);
                break;
                }
            }
        no_s = no_s->next;
        }
    no_p = no_p->next;
    }
}

/*---------------------------------------------------------------------------
A função remove_ligacao_carreira recebe um ponteiro para uma string e uma
lista_ligacao.

A função vai percorrer a linked list das ligações e eliminar cada uma das
ligações que cujo nome da carreira coincida com o valor do ponteiro para
string passado como argumento.

----------------------------------------------------------------------------*/

void remove_ligacao_carreira(char *nome_carreira, lista_ligacao *_ligacoes) {
    no_ligacao *no = _ligacoes->head;
    no_ligacao *apagar;

    while (no != NULL) {
        if (strcmp(nome_carreira, no->c->nome_carreira) == 0) {
            /* só há um elemento na linked list */
            if (no->next == NULL && no->previous == NULL) { 
                _ligacoes->head = NULL;
                _ligacoes->last = NULL;
                apagar = no;
                free(apagar->c->nome_carreira);
                free(apagar->c);
                free(apagar);
                no = NULL; /* define no como NULL para sair do loop */

            } else if (no->previous == NULL && no->next != NULL) {
                _ligacoes->head = no->next;
                no->next->previous = NULL;
                apagar = no;
                no = no->next; /* avança para o próximo nó */
                free(apagar->c->nome_carreira);
                free(apagar->c);
                free(apagar);
                

            } else if (no->next == NULL && no->previous != NULL) {
                _ligacoes->last = no->previous;
                no->previous->next = NULL;
                apagar = no;
                no = NULL; /* define no como NULL para sair do loop */
                free(apagar->c->nome_carreira);
                free(apagar->c);
                free(apagar);
                

            } else {
                no->previous->next = no->next;
                no->next->previous = no->previous;
                apagar = no;
                no = no->next; /* avança para o próximo nó */
                free(apagar->c->nome_carreira);
                free(apagar->c);
                free(apagar);
                
            }
        } else {
            no = no->next; /* avança para o próximo nó */
        }
    }
}

/*---------------------------------------------------------------------------
A função apaga_carreira recebe um ponteiro para uma string e 3 ponteiros
cada um para as linked list das paragens, carreiras e ligacoes e não devolve
nada.

Esta função é chamada quando o input começa com a palavra "r". Chama 3
funções que vão apagar uma carreira e todas as operações necessárias para
atualizar os restantes dados.

----------------------------------------------------------------------------*/

void apaga_carreira (char *nome_carreira, lista_carreira *_carreiras,\
 lista_paragem *_paragens, lista_ligacao *_ligacoes){
    atualiza_carreiras_da_paragem (nome_carreira, _paragens);
    remove_ligacao_carreira(nome_carreira, _ligacoes);
    apaga_carreira_da_ll(nome_carreira, _carreiras);


}

/*---------------------------------------------------------------------------
A função apagar_paragem_ll recebe um ponteiro para uma string e um ponteiro
para uma lista_paragem e não devolve nada.

A função vai percorrer a linked list das paragens e vai apagar a paragem que
coincide com o nome dado. Quando encontrar há 4 hipóteses de apagar:
Ser o único elemento, ser o primeiro elemento, ser o último elemento e 
ser um elemento do meio


----------------------------------------------------------------------------*/

void apagar_paragem_ll (char  *nome_paragem, lista_paragem *_paragens){
    no_paragem *no = _paragens->head;

        while (no != NULL){
        if (strcmp(nome_paragem, no->c->nome) == 0){
            if (no->previous == NULL && no->next == NULL){
                _paragens->head = NULL;
                _paragens->last = NULL;

                free(no->c->nome);
                free_list_string(no->c->carreiras_da_paragem);
                free(no->c);
                free(no);
                break;
            }else if (no->previous == NULL && no->next != NULL) {
                _paragens->head = no->next;
                no->next->previous = NULL;
                free(no->c->nome);
                free_list_string(no->c->carreiras_da_paragem);
                free(no->c);
                free(no);
                break;
            }else if (no->next == NULL && no->previous != NULL){
                _paragens->last = no->previous;
                no->previous->next = NULL;
                free(no->c->nome);
                free_list_string(no->c->carreiras_da_paragem);
                free(no->c);
                free(no);
                break;
            }else{
                no->previous->next = no->next;
                no->next->previous = no->previous;
                free(no->c->nome);
                free_list_string(no->c->carreiras_da_paragem);
                free(no->c);
                free(no);
                break;
            }
        }
        no = no->next;
    }
}

/*---------------------------------------------------------------------------
A função elimina_ligacao recebe 3 ponteiros para strings cujo valor
corresponde ao nome de uma carreira, nome da paragem de origem e nome
da paragem de destinoe um ponteiro lista_ligacao e não devolve nada.

A função vai percorrer a linked list das ligações e quando encontrar
a ligação com o mesmo nome da carreira, paragem de origem e paragem de destino
vai apagar a mesma.


----------------------------------------------------------------------------*/

void elimina_ligacao (char *nome_carreira, char *nome_origem,\
 char * nome_destino, lista_ligacao *_ligacoes ){
    no_ligacao *no = _ligacoes->head;

        if (no == NULL){
        return;
    }
    while (no != NULL){
        if (strcmp(no->c->nome_carreira, nome_carreira) == 0 && \
        strcmp(no->c->origem->nome, nome_origem )== 0\
        && strcmp(no->c->destino->nome, nome_destino) ==0){
            /*quer dizer que só há um elemento na linked list*/
            if (no->next == NULL && no->previous == NULL){ 
                _ligacoes->head = NULL;
                _ligacoes->last = NULL;
                free(no->c->nome_carreira);
                free(no->c);
                free(no);
                break;

            }else if (strcmp(no->c->destino->nome,\
             _ligacoes->head->c->destino->nome)==0\
            && strcmp(no->c->origem->nome,\
             _ligacoes->head->c->origem->nome)==0\
            && strcmp(no->c->nome_carreira,\
             _ligacoes->head->c->nome_carreira)==0){
                _ligacoes->head = no->next;
                no->next->previous = NULL;
                free(no->c->nome_carreira);
                free(no->c);
                free(no);
                break;

            }else if (strcmp(no->c->destino->nome,\
             _ligacoes->last->c->destino->nome)==0\
            && strcmp(no->c->origem->nome, \
            _ligacoes->last->c->origem->nome)==0\
            && strcmp(no->c->nome_carreira,\
             _ligacoes->last->c->nome_carreira)==0){
                _ligacoes->last = no->previous;
                no->previous->next=NULL;
                free(no->c->nome_carreira);
                free(no->c);
                free(no);
                break;

            }else{
                no->previous->next = no->next;
                no->next->previous = no->previous;
                free(no->c->nome_carreira);
                free(no->c);
                free(no);
                break;

            }
        }  
        no = no->next;
    }
}

/*---------------------------------------------------------------------------
A função adiciona_ligacao_meio recebe 3 ponteiros para strings cujo
valor representa o nome da carreira, o nome de uma paragem de destino,
o nome de uma paragem de origem, dois valores reais que são o custo e a duração
e ainda dois ponteiros para a lista_ligacao e lista_paragem e não devolve nada.

A função vai adicionar a ligação que resulta de eliminar uma paragem.


----------------------------------------------------------------------------*/

void adiciona_ligacao_meio (char *nome_carreira, char *nome_origem,\
 char *nome_destino, double custo, double duracao,\
  lista_ligacao *_ligacoes, lista_paragem *_paragens){
    Ligacao *a = (Ligacao*) malloc (sizeof(Ligacao));
    a->nome_carreira = (char*) malloc (sizeof(char) * \
    (strlen(nome_carreira)+1));
    strcpy(a->nome_carreira, nome_carreira);
    a->custo=custo;
    a->duracao=duracao;
    a->origem = encontraParagem (nome_origem, _paragens);
    a->destino = encontraParagem (nome_destino, _paragens);
    add_last_ligacao(_ligacoes, a);
}

/*---------------------------------------------------------------------------
A função atualizar_custo_duracao_carreiras recebe um ponteiro para uma string
cujo valor é o nome de uma paragem e 3 ponteiros para as listas que são as
linked lists das ligações, paragens e carreiras.

A função vai percorrer a linked list das carreiras e para cada carreira vai
percorrer a linked list das paragens da carreira. Nesta linked list temos a
ordem das paragens da carreira. A função vai eliminar a paragem dessa linked
list, atualizar o custo e a duração caso a paragem a eliminar seja de uma
das extremidades, eliminar as ligações da linked list das ligações das 
ligações associadas à paragem a eliminar. Caso a ligação seja removida do meio
ainda adiciona uma nova ligação que resulta da retirar a paragem.


----------------------------------------------------------------------------*/


void atualizar_custo_duracao_carreiras (char *nome_paragem,\
 lista_carreira *_carreiras, lista_ligacao *_ligacoes,\
  lista_paragem *_paragens){
    no_carreira *no_c = _carreiras->head;
    no_string *no_s, *apagar;

    double custo, duracao, custo1, custo2, duracao1, duracao2;

    while (no_c != NULL){
        no_s = no_c->c->paragens_da_carreira->head;
        while (no_s != NULL){
            if (strcmp(nome_paragem, no_s->c) == 0){
                if (no_s->next == NULL && no_s->previous == NULL){
                    no_c->c->destino = NULL;
                    no_c->c->origem = NULL;
                    no_c->c->paragens_da_carreira->head = NULL;
                    no_c->c->paragens_da_carreira->last = NULL;
                    no_c->c->num_paragens -= 1;
                    apagar = no_s;
                    no_s = NULL;
                    free(apagar->c);
                    free(apagar);
                    

                }else if (no_s->previous == NULL && no_s->next != NULL){
                    no_c->c->paragens_da_carreira->head = no_s->next;
                    no_s->next->previous = NULL;
                    no_c->c->origem = encontraParagem(no_s->next->c,\
                     _paragens);
                    custo = encontra_ligacao(no_c->c->nome, no_s->c,\
                     no_s->next->c, _ligacoes)->custo;
                    duracao = encontra_ligacao(no_c->c->nome, no_s->c,\
                     no_s->next->c, _ligacoes)->duracao;
                    no_c->c->custo_carreira -= custo;
                    no_c->c->duracao_carreira -=duracao;
                    no_c->c->num_ligacoes -=1;
                    no_c->c->num_paragens -=1;
                    elimina_ligacao (no_c->c->nome, no_s->c, no_s->next->c,\
                     _ligacoes);
                    apagar = no_s;
                    no_s = no_s->next;
                    free(apagar->c);
                    free(apagar);
                    

                }else if (no_s->next == NULL && no_s->previous != NULL){
                    no_s->previous->next= NULL;
                    no_c->c->destino = encontraParagem(no_s->previous->c,\
                     _paragens);
                    no_c->c->paragens_da_carreira->last = no_s->previous;
                    custo = encontra_ligacao(no_c->c->nome, no_s->previous->c,\
                     no_s->c, _ligacoes)->custo;
                    duracao = encontra_ligacao(no_c->c->nome,\
                     no_s->previous->c, no_s->c, _ligacoes)->duracao;
                    no_c->c->custo_carreira -= custo;
                    no_c->c->duracao_carreira -=duracao;
                    no_c->c->num_ligacoes -=1;
                    no_c->c->num_paragens -=1;
                    elimina_ligacao (no_c->c->nome, no_s->previous->c,\
                     no_s->c, _ligacoes);
                    apagar = no_s;
                    no_s = NULL;
                    free(apagar->c);
                    free(apagar);
                    

                }else{
                    
                    
                    no_s->next->previous = no_s->previous;
                    no_s->previous->next = no_s->next;
                    no_c->c->num_ligacoes -=1;
                    no_c->c->num_paragens -=1;

                    custo1 = encontra_ligacao(no_c->c->nome,\
                     no_s->previous->c, no_s->c, _ligacoes)->custo;
                    duracao1 = encontra_ligacao(no_c->c->nome,\
                     no_s->previous->c, no_s->c, _ligacoes)->duracao;

                    custo2 = encontra_ligacao(no_c->c->nome, \
                    no_s->c, no_s->next->c, _ligacoes)->custo;
                    duracao2 = encontra_ligacao(no_c->c->nome,\
                     no_s->c, no_s->next->c, _ligacoes)->duracao;

                    custo = custo1 + custo2;
                    duracao = duracao1 + duracao2;


                    elimina_ligacao (no_c->c->nome, no_s->previous->c,\
                     no_s->c, _ligacoes);
                    elimina_ligacao (no_c->c->nome, no_s->c, no_s->next->c,\
                     _ligacoes);
            

                    
                    adiciona_ligacao_meio (no_c->c->nome, no_s->previous->c,\
                     no_s->next->c, custo, duracao, _ligacoes, _paragens);
                    apagar = no_s;
                    no_s = no_s->next;
                    free(apagar->c);
                    free(apagar);
                    
                }

            }else{
                no_s= no_s->next;
            }   
        }
        no_c = no_c->next;

    }

}

/*---------------------------------------------------------------------------
A função apaga_paragem recebe um ponteiro para uma string cujo valor é o nome
de uma paragem e 3 ponteiros para as linked lists das carreiras, paragens e
ligações e não devolve nada.

A função vai ser chamada quando o input dado é "e" e vai chamar 2 outras
funções que são responsáveis por eliminar a paragem e fazer tudo o que é
preciso para atualizar os restantes dados.


----------------------------------------------------------------------------*/

void apaga_paragem (char* nome_paragem, lista_carreira *_carreiras,\
 lista_paragem *_paragens, lista_ligacao *_ligacoes){
    atualizar_custo_duracao_carreiras(nome_paragem, _carreiras,\
     _ligacoes, _paragens);
    apagar_paragem_ll (nome_paragem, _paragens);
    
}




/*-----------------------------------------------------------------------------
A função commandCarreira recebe um ponteiro para uma lista_carreira 
e não devolve nada.
Esta função é responsável por comandar o programa quando no input é 
inserido um caracter "c".
Vai armazenar as palavras do input em variáveis e chamar as funções
necessárias.

-----------------------------------------------------------------------------*/

void commandCarreira(lista_carreira *_carreiras){
    char nome_carreira[BUFSIZ];
    char inverso[BUFSIZ]; 
    Carreira *c;
    int res = leProximaPalavra(nome_carreira);
    /*Se res == -1 quer dizer que a função não chegou a ler nenhuma palavra
    pelo que o input foi apenas um "c"                                    */                               
    if (res == -1){
        listaTodasCarreiras(_carreiras);
    }
    /*Se res == 1 quer dizer que a função, depois de ler a última palavra
    encontrou um \n. Significa que o input foi do tipo "c <nome_carreira>"*/
    else if (res == 1){
        if (encontraCarreira(nome_carreira, _carreiras) ==  NULL){
            adicionaCarreira(nome_carreira, _carreiras);
        }else{
            Carreira *c = encontraCarreira(nome_carreira, _carreiras);
            mostraCarreira(c->paragens_da_carreira);
        }
    }
    /*Caso contrário o input foi do tipo "c <nome_carreira> <inverso>"*/
    else{
        lePalavraAteFimDeLinha(inverso);
        if (confirma_inverso(inverso)){
            if (_carreiras->head == NULL && _carreiras->last == NULL){
                return;
            }
            c = encontraCarreira(nome_carreira, _carreiras);
            mostraCarreiraInversa(c->paragens_da_carreira);
        }else{
            printf("incorrect sort option.\n");
        }
    }
}

/*-----------------------------------------------------------------------------
A função commandParagem recebe como argumento uma lista_paragem e
não devolve nada.
Esta função é responsável por comandar o programa quando no input é 
inserido um caracter "p".
Vai armazenar as palavras do input em variáveis e chamar as funções
necessárias.

-----------------------------------------------------------------------------*/

void commandParagem(lista_paragem *_paragens){
    double longitude;
    double latitude;
    char longitude_str[BUFSIZ];
    char latitude_str[BUFSIZ];
    char nome_paragem[BUFSIZ];
    int res= leProximaPalavra(nome_paragem);
    /*Se res == -1 quer dizer que a função não chegou a ler nenhuma palavra
    pelo que o input foi apenas um "p"                                   */  
    if (res == -1){
        listaTodasParagens(_paragens);
    }
    /*Se res == 1 quer dizer que a função, depois de ler a última palavra
    encontrou um \n. Significa que o input foi do tipo "c <nome_paragem>"*/
    else if (res == 1){
        mostraParagem(nome_paragem, _paragens);
    /*Caso contrário o input foi do tipo 
    "c <nome_paragem> <latitude> <longitude>" */
    }else{
        leProximaPalavra(latitude_str);
        lePalavraAteFimDeLinha(longitude_str);
        latitude= strtod(latitude_str,NULL);
        longitude= strtod(longitude_str, NULL);
        if (latitude >=-90 && latitude <= 90 && longitude >= -180 && longitude <=180){
            adicionaParagem(nome_paragem,latitude,longitude, _paragens);
        }else{
            printf("invalid location.\n");
        }
    }

}

/*-----------------------------------------------------------------------------
A função commandLigacao recebe como argumento 3 ponteiros para listas
uma lista_carreira, uma lista_paragem e uma lista_ligacao  e não devolve nada.
Esta função é responsável por comandar o programa quando no input é 
inserido um caracter "l".
Vai armazenar as palavras do input em variáveis e chamar as funções
necessárias.

-----------------------------------------------------------------------------*/


void commandLigacao (lista_carreira* _carreiras, lista_paragem*_paragens,\
 lista_ligacao *_ligacoes){

    /*Neste caso só há uma opção de input*/
    char nome_carreira[BUFSIZ];
    char nome_origem[BUFSIZ];
    char nome_destino[BUFSIZ];
    char custo_str [BUFSIZ];
    char duracao_str [BUFSIZ];
    double custo;
    double duracao;
    leProximaPalavra(nome_carreira);
    leProximaPalavra(nome_origem);
    leProximaPalavra(nome_destino);
    leProximaPalavra(custo_str);
    lePalavraAteFimDeLinha(duracao_str);
    custo= strtod (custo_str,NULL);
    duracao= strtod (duracao_str, NULL);
    AddLigacao(nome_carreira, nome_origem, nome_destino, custo, duracao,\
     _carreiras, _paragens, _ligacoes);
}

/*-----------------------------------------------------------------------------
A função commandIntersecao recebe como argumento uma lista_paragem e
não devolve nada.
Esta função é responsável por comandar o programa quando no input é 
inserido um caracter "i".
Vai apenas chamar a função intersecao_carreiras.

-----------------------------------------------------------------------------*/

void commandIntersecao (lista_paragem *_paragens){
    leAteFimDeLinha();
    intersecao_carreiras(_paragens);
}

/*---------------------------------------------------------------------------
A função commandR recebe 3 ponteiros para as linked list de carreiras,
paragens e ligações e não devolve nada.

A função é chamada quandp o  input dado é do tipo "r".
Vai chamar as funções necessárias para controlar o input.


----------------------------------------------------------------------------*/

void commandR (lista_carreira *_carreiras , lista_paragem *_paragens,\
 lista_ligacao *_ligacoes){
    char nome_carreira[BUFSIZ];
    lePalavraAteFimDeLinha(nome_carreira);
    if (encontraCarreira(nome_carreira, _carreiras) == NULL){
        printf("%s: no such line.\n", nome_carreira);
    }else{
        apaga_carreira (nome_carreira, _carreiras, _paragens, _ligacoes);
    }
}

/*---------------------------------------------------------------------------
A função commandE recebe 3 ponteiros para as linked list de carreiras,
paragens e ligações e não devolve nada.

A função é chamada quandp o  input dado é do tipo "e".
Vai chamar as funções necessárias para controlar o input.


----------------------------------------------------------------------------*/

void commandE (lista_carreira *_carreiras, lista_paragem *_paragens, \
lista_ligacao *_ligacoes){
    char nome_paragem [BUFSIZ];
    lePalavraAteFimDeLinha(nome_paragem);
    if (encontraParagem(nome_paragem, _paragens) == NULL ){
        printf("%s: no such stop.\n", nome_paragem);
    }else{
        apaga_paragem(nome_paragem, _carreiras, _paragens, _ligacoes);
    }
}

/*---------------------------------------------------------------------------
A função commandA recebe 3 ponteiros para as linked list de carreiras,
paragens e ligações e não devolve nada.

A função é chamada quandp o  input dado é do tipo "a".
Vai dar free do conteúdo de todas as linked lists e eliminar as linked
lists de strings que são atributos. Não dá free das listas em si.

----------------------------------------------------------------------------*/

void commandA (lista_carreira *_carreiras, lista_paragem *_paragens,\
 lista_ligacao *_ligacoes){
    leAteFimDeLinha();
    free_list_paragem(_paragens);
    free_list_carreira(_carreiras);
    free_list_ligacao(_ligacoes);
}

/*---------------------------------------------------------------------------
A função commandQ recebe 3 ponteiros para as linked list de carreiras,
paragens e ligações e não devolve nada.

A função é chamada quandp o  input dado é do tipo "q".
Vai dar free do conteúdo de todas as linked lists e eliminar as linked
lists de strings que são atributos. Vai dar free das listas.


----------------------------------------------------------------------------*/

void commandQ (lista_carreira *_carreiras, lista_paragem *_paragens,\
 lista_ligacao *_ligacoes){
    free_list_paragem(_paragens);
    free_list_carreira(_carreiras);
    free_list_ligacao(_ligacoes);
    free(_carreiras);
    free(_ligacoes);
    free(_paragens);
}

/*---------------------------------------------------------------------------
A função verifica_memoria recebe 3 ponteiros para as linked list de carreiras,
paragens e ligações e não devolve nada.

A função vai testar alocar memória. Caso a memória seja alocada com sucesso,
vai dar free do contéudo alocado e continuar o programa. Caso contrário vai
interromper o programa e antes disso dar free te toda a memória alocada.


----------------------------------------------------------------------------*/

void verifica_memoria (lista_carreira *_carreiras, lista_paragem *_paragens,\
 lista_ligacao *_ligacoes){
    char teste_ [10] ="teste";
        char *teste = (char*) malloc(sizeof(char) * (strlen(teste_)+1));
        if (teste == NULL){
            commandQ(_carreiras, _paragens, _ligacoes);
            free(_carreiras);
            free(_ligacoes);
            free(_paragens);
            free(teste);
            printf("No memory.\n");
            exit(1);
        }else{
            free(teste);
        }
}

void mostra_carreiras_com_destino (char *nome_paragem, lista_carreira *_carreiras){
    int contador =0;
    no_carreira *no = _carreiras->head;
    while (no != NULL){
        if (no->c->destino != NULL){
            if (strcmp(nome_paragem, no->c->destino->nome) == 0){
                if (contador == 0){
                    printf("%s", no->c->nome);
                }else{
                    printf(" %s", no->c->nome);
                }
                contador++;
            } 
        }
        no = no->next;
    }
    if (contador != 0){
        printf("\n");
    }
}




void commandF (lista_carreira *_carreiras, lista_paragem *_paragens){
    char nome_paragem[BUFSIZ];
    lePalavraAteFimDeLinha(nome_paragem);
    if (encontraParagem(nome_paragem, _paragens) == NULL){
        printf("%s: no such stop.\n", nome_paragem);
    }else{
        mostra_carreiras_com_destino(nome_paragem, _carreiras);
    }

}



int main() {
    int c;
    lista_carreira* _carreiras =mk_list_carreira();
    lista_paragem* _paragens =mk_list_paragem();
    lista_ligacao* _ligacoes = mk_list_ligacao();
 	while ((c = getchar()) != EOF) {


		switch (c) {
		case 'q': commandQ (_carreiras, _paragens, _ligacoes);
            return 0;

		case 'c': commandCarreira(_carreiras);
			break;
		case 'p': commandParagem(_paragens);
			break;
		case 'l': commandLigacao(_carreiras, _paragens, _ligacoes);
			break;
		case 'i': commandIntersecao(_paragens);
			break;
        case 'r': commandR (_carreiras, _paragens, _ligacoes);
            break;
        case 'e': commandE (_carreiras, _paragens, _ligacoes);
             break;
        case 'a': commandA (_carreiras, _paragens, _ligacoes);
            break;
        case 'f' : commandF (_carreiras, _paragens);
            break;
		default: printf("Invalid command: %c\n", c);
		}
	}
    return 0;
}