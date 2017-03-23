#include <stdio.h>
#include <stdlib.h>
#include <time.h> //para la funcion rand
#include <conio.h> // para la funcion getche();

int puntos=0; //contador de puntos
FILE *ap;

//Protitipado de las funciones
void limpiarPantalla();
void Matriz ();
int Ganaste();
void Nuevo();
char Teclas();
void MatrizAleatoria();
void Tablero();
void Arriba();
void Abajo();
void Izquierda();
void Derecha();
void juego();
void instrucciones();

void main(){
    instrucciones();
    juego();
}

void limpiarPantalla(){ //cada movimiento
	system("cls");
}

void Matriz(int A[4][4]){  //Imprime el tablero cada que se hace un movimiento
	int i,j,x;
	printf("Puntos: %d\n\n",puntos);
	printf("\t:::::::::");
	for(x=0; x<2; x++ ){
		printf(":::::::::");
	}
	printf("::::::::::\n\t:");

	for(i=0; i<4; i++  ){

		for (j = 0; j < 4; j++){
			if ( A[i][j]==0 ){
				printf("        :");
			}else{
				if( A[i][j]<1000 ){
					printf("%5d   :",A[i][j]);
				}else{
					printf("%6d :",A[i][j]);
				}
			}
		}
		printf("\n");
		if (i< 3){
			printf("\t:::::::::");
			for(x=0; x<4-2; x++ ){
				printf(":::::::::");
			}
			printf("::::::::::\n\t:");
		}
	}
	printf("\t:::::::::");
	for(x=0; x<2; x++ ){
		printf(":::::::::");
	}
	printf("::::::::::\n\n\n");

}

int Ganaste(int A[4][4]){ //Funcion para comprobar si ganaste
	int i,j;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if( A[i][j]==0 ){
				return 1;
			}
		}
	}
	return 0;
}

void Nuevo(int n, int A[4][4]){ // genera un numero nuevo en la matriz
    ap=fopen("puntos.txt","w+");
	srand(time(NULL));
	int i,j;

	if( Ganaste(A) ){
		i = rand()%4;   //genera el numeero dos en una posicion de 0 a 4
		j = rand()%4;

    while( A[i][j] != 0 ){ //condicion para ver si está ocupada la casilla
			i = rand()%4;
			j = rand()%4;
		}
    A[i][j]=n;
	}else{
		printf("\nPartida Concluida, pulse n para iniciar una nueva partida o q para salir\n");
		fprintf(ap,"%d \n",puntos);
	}

    fclose(ap);

}

char Teclas(){ //función para leer las teclas con las cual se va a jugar
	char ch;
	ch = getche(); //hace lo mismo que getch pero imprime la tecla presionada
	return ch;

}

void MatrizAleatoria(int A[4][4]){ //Genera una matriz aleatoria (renglon y columna)
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			A[i][j]=rand()%2000;
		}
	}
}

void Tablero(int A[4][4]){
	srand(time(NULL)); //funcion para que no se repitan los numeros
	int i,j;
	puntos=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			A[i][j]=0;
		}
	}
	i = rand()%4; //se generan numeros aletorios
	j = rand()%4;
	A[i][j]=2;

}

void Arriba(int A[4][4]){ // metodo para cuando se hace un movimiento hacia arriba

	int i,j,k,tmp;
	for(j=0; j<4; j++){
		for(i=1; i<4; i++){
			if( A[i][j] > 0 ){
				tmp=A[i][j];//guarda la posicion
				A[i][j]=0; //a la posicion lo iguala a cero para indicar que hay algo
				k=i;
				while( A[k-1][j] == 0 && k>0 ){
					k--;
				}

				/* inicia fusionar hacia arriba */
				if( k>0 ){
					if( A[k-1][j] == tmp ){
						A[k][j]=0;
						A[k-1][j]=tmp*2;
						puntos=puntos+(tmp*2); //
					}else{
						A[k][j]=tmp;
					}
				}else{
					A[k][j]=tmp;
				}
				/* fin fusionar hacia arriba */

			}
		}
	}

}


void Abajo(int A[4][4]){  //metodo para cuando se hace un movimiento hacia abajo

	int i,j,k,tmp;
	for(j=0; j<4; j++){
		for(i=2; i>=0; i--){
			if( A[i][j] > 0 ){
				tmp=A[i][j];
				A[i][j]=0;
				k=i;
				while( A[k+1][j] == 0 && k<3 ){
					k++;
				}

				/* inicia fusionar hacia abajo */
				if( k<3 ){
					if( A[k+1][j] == tmp ){
						A[k][j]=0;
						A[k+1][j]=tmp*2;
						puntos=puntos+(tmp*2);
					}else{
						A[k][j]=tmp;
					}
				}else{
					A[k][j]=tmp;
				}
				/* fin fusionar hacia abajo */

			}
		}
	}

}

void Izquierda(int A[4][4]){ // metodo para cuando se hace un movimiento a la izquierda

	int i,j,k,tmp;
	for(i=0; i<4; i++){
		for(j=1; j<4; j++){
			if( A[i][j] > 0 ){
				tmp=A[i][j];
				A[i][j]=0;
				k=j;
				while( A[i][k-1] == 0 && k>0 ){
					k--;
				}
				/* inicia fusionar a la izquierda*/
				if( k>0 ){
					if( A[i][k-1] == tmp ){
						A[i][k]=0;
						A[i][k-1]=tmp*2;
						puntos=puntos+(tmp*2);
					}else{
						A[i][k]=tmp;
					}
				}else{
					A[i][k]=tmp;
				}
				/* fin fusionar a la izquierda */


			}
		}
	}

}

void Derecha(int A[4][4]){ //metodo para cuando se hace un movimiento a la derecha

	int i,j,k,tmp;
	for(i=0; i<4; i++){
		for(j=2; j>=0; j--){
			if( A[i][j] > 0 ){
				tmp=A[i][j];
				A[i][j]=0;
				k=j;
				while( A[i][k+1] == 0 && k<3 ){
					k++;
				}

				/* inicia fusionar hacia la derecha */
				if( k<3 ){
					if( A[i][k+1] == tmp ){
						A[i][k]=0;
						A[i][k+1]=tmp*2;
						puntos=puntos+(tmp*2);

					}else{
						A[i][k]=tmp;
					}
				}else{
					A[i][k]=tmp;
				}
				/* fin fusionar hacia la derecha */

			}
		}
	}
}

void juego(){ //meotdo principal del juego

	int A[4][4];
	char movimiento;
	srand(time(NULL)); //Este valor cambia si ejecutamos el programa en distinto instante de tiempo. Tendriamos que arrancar el programa dos veces en el mismo segundo para obtener la misma secuencia de números aleatorios.

	limpiarPantalla();
	Tablero(A); //se convocan las funciones tablero y matriz para la matriz A
	Matriz(A);

	while( movimiento != 'q' ){
		movimiento=Teclas();
		if(movimiento=='w'){ //condicion para mover hacia arriba
			//movimiento=='w'
			//printf("Arriba");
			limpiarPantalla(); //se limpia la pantalla
			Arriba(A); //se convoca la funcion hacia arriba
			Nuevo(2,A); // se introduce un nuevo numero en la matriz
			Matriz(A); //se convoca la funcion matriz para tener el tablero en la pantalla
		}else if(movimiento=='a'){ //Movimiento Izquierda
			//movimiento=='a'
			//printf("Izquierda");
			limpiarPantalla();
			Izquierda(A);
			Nuevo(2,A);
			Matriz(A);
		}else if(movimiento=='s'){ //Movimiento a la derecha
			//movimiento=='s'
			//printf("Derecha");
			limpiarPantalla();
			Derecha(A);
			Nuevo(2,A);
			Matriz(A);
		}else if(movimiento=='z'){ //Movimiento hacia abajo
			//movimiento=='z'
			//printf("Abajo");
			limpiarPantalla();
			Abajo(A);
			Nuevo(2,A);
			Matriz(A);
		}else if(movimiento=='n'){
			//printf("Nuevo");
			limpiarPantalla();
			Tablero(A);
			Matriz(A);
		}
	}

}
void instrucciones()
{system("cls");
printf("Presione w para mover hacia arriba\n");
printf("Presione z para mover hacia abajo\n");
printf("Presione s para mover hacia la derecha\n");
printf("Presione a para mover hacia la izquierda\n");
printf("Presione n para una nueva partida\n");
printf("Presione q para salir\n");
system("pause");
}
