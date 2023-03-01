#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//lucas Deodato 

typedef struct carta {//------------------------------------------------------------------------struct da carta
	int numero;
	int naipe;
	int valor;//---------------------------------------------------------------------------------referencia para saber qual carta é a maior na função "confere"
} carta;

typedef struct pilha {//-------------------------------------------------------------------------struct pilha onde vai ser armazendos as cartas 
	int topo;
	carta vetor [ 40 ];//------------------------------------------------------------------------vetor de 40 posições para amarazenar apenas as 40 cartas
} pilha;//----------------------------------------------------------------------------------------no caso PILHA é o baralho

typedef struct lista{//--------------------------------------------------------------------------struct para ser a mão do jogador
	carta vetor[5];//-----------------------------------------------------------------------------vetor de 5 posição pois vai ser apenas 5 cartas na mão
	int fim;//------------------------------------------------------------------------------------marcar a posição final
}lista;//----------------------------------------------------------------------------------------no caso LISTA será a mão do jogador

typedef struct jogador {//----------------------------------------------------------------------struct do jogador
	char nome[10];//----------------------------------------------------------------------------nome do jogador até 10 caracteres
	int vida;//----------------------------------------------------------------------------------vida do jogador no game
	lista *l;//----------------------------------------------------------------------------------aqui é a mão do jogador
	carta mesa[1];//----------------------------------------------------------------------------usarei lista mesa para ser armazenada as cartas que foram selecionadas pelos jogadores durante as rodadas
	int faz;//----------------------------------------------------------------------------------será armazenada a quantidade de feitos pelo jogador 
} jogador;//------------------------------------------------------------------------------------struct jogador

pilha*pcria ( );//---------------------------------------------------------------------------função para criar pilha
int vazia ( pilha *p );//---------------------------------------------------------------------função para saber se a pilha está vazia
int cheia ( pilha*p );//----------------------------------------------------------------------função para saber se a pilha está cheia
void plibera( pilha*p);//---------------------------------------------------------------------função para liberar a pilha
void empilha ( pilha*p, int num, int naipe );//-----------------------------------------------função para empilhar
void desempilha ( pilha*p, int *num, int *naipe, int *valor );//------------------------------função para desempilhar
void criabaralho ( pilha*p );//---------------------------------------------------------------função para criar pilha que será o baralho
void comparavalorcartas ( pilha*p );//--------------------------------------------------------função para ser inseridos os valores de cada carta do maior para o menor
void imprime(pilha*p);//----------------------------------------------------------------------função para imprimir o baralho
void embaralha( pilha*p );//------------------------------------------------------------------função para embaralhar o a pilha(baralho)
int players ( );//----------------------------------------------------------------------------saber quantos players no jogo
jogador*alocaJogador ( int quant );//---------------------------------------------------------funçãoa para alocar 
jogador*dadosjogadores( jogador*x, int quant );//---------------------------------------------função para criar os jogadores inserir nomes e etc.
void libera ( lista*l );//--------------------------------------------------------------------função para liberar lista
lista*lcria ( );//----------------------------------------------------------------------------função para criar lista
int lvazia ( lista *l );//--------------------------------------------------------------------função para saber se a lista está vazia 
int lcheia ( lista*l ); //--------------------------------------------------------------------função para saber se a lista está cheia
void llistar ( lista*l, int num, int naipe,int valor);//--------------------------------------função para listar( enlistar)
void desenlistar ( lista*l, int num, int naipe );//-------------------------------------------função para desenlistar
void desenlistapos(lista *l,int num, int naipe, int pos);//-----------------------------------função para desenlistar de acordo com a posição que o jogador escolher
void limprime ( lista*l );//------------------------------------------------------------------função para imprimir a lista
int lquantidade ( lista*l );//----------------------------------------------------------------função para saber a quantidade de cartas
void distribuicartas ( lista*l, pilha*p);//---------------------------------------------------função que distribui cartas para os jogadores
void iniciagame ( jogador*j,pilha*p, int quant );//-------------------------------------------função com as rodadas
void jogadoresfazem( jogador*j, int quant );//------------------------------------------------função que contem as perguntas de quantas rodadas fazem
void confere ( jogador*j, pilha *p,int quant, int posmaior, int posmenor );//-----------------função que confere qual carta possui o valor maior
void escolhacarta( jogador*j, pilha*baralho, pilha*cartamesa, int quant );//------------------função que o jogador escolhe a carta que deseja jogar

int main () {
	
    pilha*baralho, *cartamesa;
    jogador *j;
	int i,k,quant,rodada=0;
	
	
	baralho = pcria();//--------------------------criado o baralho(pilha)
	cartamesa = pcria();//------------------------criado onde o jogador vai jogar as cartas que irão ser comparadas

	//imprime( p );
	
	quant = players( );//---------------------------quantidade de jogadores no jogo
	j = alocaJogador( quant );//---------------------alocando os jogadores
	j = dadosjogadores( j, quant );//----------------inserindo os dados dos jogadores
	
	for( k=0;k<quant; k++ ){
		j[k].l = lcria();//--------------------------criar a mão dos jogadores
	}
	
	criabaralho ( baralho );//------------------------onde será armazenado cartas com naipes e numeros
	comparavalorcartas ( baralho );//-----------------função que compara valor
	embaralha( baralho );//---------------------------função para embaralhar
	
	iniciagame ( j, baralho, quant );//----------------onde os jogadores recebem as cartas
	
	while(1){//----------------------------------------comando de repetição enquanto não há jogadores vitorioso
		
		jogadoresfazem(  j, quant );
		escolhacarta( j, baralho, cartamesa, quant );
			
	}
	
	return 0;
}

pilha*pcria ( ) {
	pilha*p;
	p = ( pilha* ) malloc ( sizeof ( pilha ) );
	p->topo = 0;
	return p;
}

int vazia ( pilha *p ) {
	if( p->topo == 0 ) {
		return 1;
	}
	else {
		return 0;
	}
}

int cheia ( pilha*p ) {
	if( p->topo == 40 ){
		return 1;
	}
	else {
		return 0;
	}
}

void plibera( pilha*p) {
	free(p);
}

void empilha ( pilha*p, int num, int naipe ) {
	p->vetor[p->topo].numero = num;
	p->vetor[p->topo].naipe = naipe;
	p->topo++;
}

void desempilha ( pilha*p, int *num, int *naipe, int *valor ) {
	p->topo--;
	*num = p->vetor[p->topo].numero;
	*naipe = p->vetor[p->topo].naipe;
	*valor = p->vetor[p->topo].valor;
}

void criabaralho ( pilha*p ) {
	srand( time( NULL ) );
	int x,y;
	for( x=1; x<=10; x++ ){
		for( y=3; y<=6; y++ ){
			p->vetor[x].numero ;
			p->vetor[y].naipe ; 
			empilha ( p,x,y );
		}
	}
}

void comparavalorcartas ( pilha*p ) {
	int i;
	for ( i=0; i< p->topo; i++ ){
		if ( p->vetor[i].numero == 4 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 39;
		}
		if ( p->vetor[i].numero == 7 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 38;
		}
		if ( p->vetor[i].numero == 1 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 37;
		}
		if ( p->vetor[i].numero == 7 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 36;
		}
		if ( p->vetor[i].numero == 3 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 35; 
		}
		if ( p->vetor[i].numero == 3 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 34;
		}
		if ( p->vetor[i].numero == 3 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 33;
		}
		if ( p->vetor[i].numero == 3 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 32;
		}
		if ( p->vetor[i].numero == 2 && p->vetor[i].naipe == 3 ){ 
			p->vetor[i].valor = 31;
		}
		if ( p->vetor[i].numero == 2 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 30;
		}
		if ( p->vetor[i].numero == 2 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 29;
		}
		if ( p->vetor[i].numero == 2 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 28;
		}
		if ( p->vetor[i].numero == 1 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 27;
		}
		if ( p->vetor[i].numero == 1 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 26;
		}
		if ( p->vetor[i].numero == 1 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 25;
		}
		if ( p->vetor[i].numero == 10 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 24;
		}
		if ( p->vetor[i].numero == 10 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 23;
		}
		if ( p->vetor[i].numero == 10 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 22;
		}
		if ( p->vetor[i].numero == 10 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 21;
		}
		if ( p->vetor[i].numero == 9 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 20;
		}
		if ( p->vetor[i].numero == 9 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 19;
		}
		if ( p->vetor[i].numero == 9 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 18;
		}
		if ( p->vetor[i].numero == 9 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 17;
		}
		if ( p->vetor[i].numero == 8 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 16;
		}
		if ( p->vetor[i].numero == 8 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 15;
		}
		if ( p->vetor[i].numero == 8 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 14;
		}
		if ( p->vetor[i].numero == 8 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 13;
		}
		if ( p->vetor[i].numero == 7 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 12;
		}
		if ( p->vetor[i].numero == 7 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 11;
		}
		if ( p->vetor[i].numero == 6 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 10;
		}
		if ( p->vetor[i].numero == 6 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 9;
		}
		if ( p->vetor[i].numero == 6 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 8;
		}
		if ( p->vetor[i].numero == 6 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 7;
		}
		if ( p->vetor[i].numero == 5 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 6;
		}
		if ( p->vetor[i].numero == 5 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 5;
		}
		if ( p->vetor[i].numero == 5 && p->vetor[i].naipe == 5 ){
			p->vetor[i].valor = 4;
		}
		if ( p->vetor[i].numero == 5 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 3;
		}
		if ( p->vetor[i].numero == 4 && p->vetor[i].naipe == 3 ){
			p->vetor[i].valor = 2;
		}
		if ( p->vetor[i].numero == 4 && p->vetor[i].naipe == 4 ){
			p->vetor[i].valor = 1;
		}
		if ( p->vetor[i].numero == 4 && p->vetor[i].naipe == 6 ){
			p->vetor[i].valor = 0;
		}	
	}
}

void imprime(pilha*p){
	int i;
	//printf("%d", p->topo);
	for( i = 0; i <p->topo; i++ ) {
		printf("%d %c\n",p->vetor[i].numero,p->vetor[i].naipe);
	}
}

void embaralha( pilha*p ){
	srand( time( NULL ) );
	int i,x,j,r,n,temp;
	for(i=0;i<p->topo;i++){
		r = rand() % p->topo;
		temp = p->vetor[i].numero;
		p->vetor[i].numero = p->vetor[r].numero;
		p->vetor[r].numero = temp;
		
		temp = p->vetor[i].naipe;
		p->vetor[i].naipe = p->vetor[r].naipe;
		p->vetor[r].naipe = temp;
		
		temp = p->vetor[i].valor;
		p->vetor[i].valor = p->vetor[r].valor;
		p->vetor[r].valor = temp;
	}
}

int players ( ) {
	int i,op;
	printf("Digite a quantidade de jogadores:");
	scanf("%d",&op);
	return op;
}

jogador*alocaJogador ( int quant ){
	jogador *x ;
	x = ( jogador* ) malloc ( quant*sizeof ( jogador ) );
	
	if( x == NULL ) {
		exit(1);
	}
	x->vida = 5;
	return x;	
}

jogador*dadosjogadores( jogador*x, int quant ) {
	int i;
	for( i=0; i<quant; i++ ){
		printf("Digite o nome do jogador: ");
		scanf("%s",x[i].nome);
		x[ i ].vida = 5;
		//printf("\njogador %s com %d de vida\n\n",x[i].nome,x[i].vida);
	}
	return x;	
}

void libera ( lista*l ) { 	
	free(l); 
}
 
lista*lcria () { 	
	lista*l; 	
	l = ( lista* ) malloc ( sizeof ( lista ) ); 
	l->fim = 0; 	
	return l; 
}
 
int lvazia ( lista *l ) { 	
	if(l->fim == 0){ 		
		return 1;
	} 	
	else { 		
		return 0; 	
	} 
}
 
int lcheia ( lista*l ) {
	if(l->fim == 5){ 		
		return 1; 	
	} else { 		
		return 0; 	
	} 
} 

void llistar ( lista*l, int num, int naipe,int valor) {
	l->vetor[l->fim].numero = num;
	l->vetor[l->fim].naipe = naipe;
	l->vetor[l->fim].valor = valor;
	l->fim++; 
}

void desenlistar ( lista*l, int num, int naipe ) { 	 
	l->fim--; 	
	l->vetor[l->fim].numero = num;
	l->vetor[l->fim].naipe = naipe; 
} 

void desenlistapos(lista *l,int num, int naipe, int pos){
	int i, *valor, val;
	if(pos >= 0 && pos< l->fim){
		*valor = l->vetor[pos].numero= num;
		*valor = l->vetor[pos].naipe = naipe;
		*valor = l->vetor[pos].valor = val;
		l->fim--;
		for(i=pos;i<l->fim;i++){
			l->vetor[i].numero = l->vetor[i+1].numero;
			l->vetor[i].naipe = l->vetor[i+1].naipe;
			l->vetor[i].valor = l->vetor[i+1].valor;
		}
	}	
}

void limprime ( lista*l ){
	int i; //num,  naipe;
	for (i = 0; i < l->fim; i++){
		printf (/*l->vetor*/"[%d] = %d %c\n"/*valor %d*/,i,l->vetor[i].numero,l->vetor[i].naipe/*, l->vetor[i].valor */);
	}	
}

int lquantidade ( lista*l ) {
	int i, cont = 0;
	for ( i=0; i< l->fim; i++) {
		cont ++;
	}
	return cont;
}

void distribuicartas ( lista*l, pilha*p){
	int k;
	for( k=0; k<5; k++ ) {
		desempilha ( p, &p->vetor[k].numero,&p->vetor[k].naipe, &p->vetor[k].valor );
		llistar ( l, p->vetor[k].numero, p->vetor[k].naipe, p->vetor[k].valor);
		//printf("%d %d %c\n",k,p->vetor[k].numero,p->vetor[k].naipe);
	}
}

void iniciagame ( jogador*j,pilha*p, int quant ){
	int k,rodada=0,i=0;
	
	for(k=0;k<quant; k++){
		 j[k].faz = 0;
	}
	
	for(k=0;k<quant; k++){
		distribuicartas ( j[k].l, p);	
	}
	
	/*for ( i=0; i<quant; i++) {
		printf("\ncartas na mao de %s\n",j[i].nome);
		limprime ( j[i].l );	
	}*/					
}

void jogadoresfazem( jogador*j, int quant ){
	int i;
	
	for(i=0;i<quant;i++) {
		printf("\ncartas na mao de %s\n",j[i].nome);
		//fprintf(arquivo,"\ncartas na mao de %s\n",j[i].nome);
		limprime ( j[i].l );			
		printf("\n%s faz quantas:",j[i].nome);
		scanf("%d",&j[i].faz);
		//fprintf(arquivo,"\njogador%s disse que faz %d quantas:",j[i].nome,j[i].faz );		
		while( j[i].faz > j[i].l->fim){
			printf("\n******************Quantidade superior a cartas da mao nao pode, mano!!\nnao trole o game %s******************\n",j[i].nome);
			printf("(sem gracinhas dessa vez por favor)\n%s faz quantas rodadas:",j[i].nome);
			scanf("%d",&j[i].faz);
			//fprintf(arquivo,"jogaodor fez gracinha e retornou pergunta",j[i].nome);
		}
	}		
}

void confere ( jogador*j, pilha *p,int quant, int posmaior, int posmenor ) {
	int maior=0, menor=0,i;
	maior = p->vetor[i].valor;
	menor = p->vetor[i].valor;
		
	for(i= 0;i< p->topo;i++){
		if ( p->vetor[i].valor > maior ) {
			maior =  p->vetor[i].valor;
			posmaior= i;
		}
		/*else {
			j[i].vida--;
			printf("\n%s = %d vidas",j[i].nome,j[i].vida);	
			
		}*/
	}
	for(i= 0;i< quant;i++){
		if ( p->vetor[i].valor != maior ) {
			j[i].vida--;	
		}
		printf("%s = %d vidas\n",j[i].nome, j[i].vida);
	}
	
	
	//printf("O maior eh: %d",maior);
	//printf("\nO menor eh: %d",menor);
	
	printf("O maior eh: %d %c DE %s\n\n",p->vetor[posmaior].numero, p->vetor[posmaior].naipe,j[posmaior].nome);	
	//fprintf(arquivo,"a maior carta da rodada foi de %s: %d %c\n\n",p->vetor[posmaior].numero, p->vetor[posmaior].naipe,j[posmaior].nome);	
}

void escolhacarta( jogador*j, pilha*baralho, pilha*cartamesa, int quant ){
	int i, k, m, maior=0, posmaior,posmenor;
	for(i=0;i<quant;i++) {
		printf("\n%s escolha uma carta para tirar: ",j[i].nome);
		scanf("%d",&m);
		printf (/*l->vetor*/"[%d] = %d %c\n",m,j[i].l->vetor[m].numero, j[i].l->vetor[m].naipe/*, j[i].l->vetor[m].valor*/  );
		//fprintf (arquivo,/*l->vetor*/"jogador %s  escolheu a carta de posicao [%d] = %d %c\n",j[i].nome, m, j[i].l->vetor[m].numero, j[i].l->vetor[m].naipe/*, j[i].l->vetor[m].valor*/  );
		empilha ( cartamesa, j[i].l->vetor[m].numero, j[i].l->vetor[m].naipe );
		desenlistapos(j[i].l,j[i].l->vetor[m].numero, j[i].l->vetor[m].naipe, m);	
	}
	
	printf("\n---------------CARTAS JOGADAS NA MESA---------------\n\n");
	imprime(cartamesa);
	printf("\n-----------------------------------------------------\n\n");
	
	
	comparavalorcartas ( cartamesa );
	confere ( j, cartamesa, quant, posmaior, posmenor );
	for( i=0; i<quant; i++) {
		desempilha ( cartamesa, &cartamesa->vetor[i].numero, &cartamesa->vetor[i].naipe, &cartamesa->vetor[i].valor );
	}
}


	
