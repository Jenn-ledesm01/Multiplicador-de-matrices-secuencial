#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rellenarMatriz(int **matriz, int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			matriz[i][j] = rand() % 20;  // Valores aleatorios entre 0 y 19
		}
	}
}

void multiplicarMatrices(int **matrizA, int **matrizB, int **matrizResultado, int filasA, int columnasA, int columnasB) {
	for (int i = 0; i < filasA; i++) {
		for (int j = 0; j < columnasB; j++) {
			matrizResultado[i][j] = 0;
			for (int k = 0; k < columnasA; k++) {
				matrizResultado[i][j] += matrizA[i][k] * matrizB[k][j];
			}
		}
	}
}

// Función para medir el tiempo de ejecución de una función que toma argumentos
double medirTiempo(void (*funcion)(int **, int **, int **, int, int, int), int **matrizA, int **matrizB, int **matrizResultado, int filasA, int columnasA, int columnasB) {
	clock_t inicio = clock();
	funcion(matrizA, matrizB, matrizResultado, filasA, columnasA, columnasB);
	clock_t fin = clock();
	return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

int main() {
	int filasA, columnasA, filasB, columnasB;
	
	printf("Ingrese el número de filas de la matriz A: ");
	scanf("%d", &filasA);
	
	printf("Ingrese el número de columnas de la matriz A: ");
	scanf("%d", &columnasA);
	
	printf("Ingrese el número de filas de la matriz B: ");
	scanf("%d", &filasB);
	
	printf("Ingrese el número de columnas de la matriz B: ");
	scanf("%d", &columnasB);
	
	if (columnasA != filasB) {
		printf("No se pueden multiplicar las matrices. El número de columnas de A debe ser igual al número de filas de B.\n");
		return 1;
	}
	
	int **matrizA, **matrizB, **matrizResultado;
	
	matrizA = (int **)malloc(filasA * sizeof(int *));
	for (int i = 0; i < filasA; i++) {
		matrizA[i] = (int *)malloc(columnasA * sizeof(int));
	}
	
	matrizB = (int **)malloc(filasB * sizeof(int *));
	for (int i = 0; i < filasB; i++) {
		matrizB[i] = (int *)malloc(columnasB * sizeof(int));
	}
	
	matrizResultado = (int **)malloc(filasA * sizeof(int *));
	for (int i = 0; i < filasA; i++) {
		matrizResultado[i] = (int *)malloc(columnasB * sizeof(int));
	}
	
	// Inicializar el generador de números aleatorios con la hora actual
	srand(time(NULL));
	
	rellenarMatriz(matrizA, filasA, columnasA);
	printf("Matriz A con valores aleatorios:\n");
	for (int i = 0; i < filasA; i++) {
		for (int j = 0; j < columnasA; j++) {
			printf("%d ", matrizA[i][j]);
		}
		printf("\n");
	}
	
	rellenarMatriz(matrizB, filasB, columnasB);
	printf("Matriz B con valores aleatorios::\n");
	for (int i = 0; i < filasB; i++) {
		for (int j = 0; j < columnasB; j++) {
			printf("%d ", matrizB[i][j]);
		}
		printf("\n");
	}
	
	// Medir el tiempo de ejecución de la multiplicación de matrices
	double tiempo = medirTiempo(multiplicarMatrices, matrizA, matrizB, matrizResultado, filasA, columnasA, columnasB);
	
	printf("Resultado de la multiplicación:\n");
	for (int i = 0; i < filasA; i++) {
		for (int j = 0; j < columnasB; j++) {
			printf("%d ", matrizResultado[i][j]);
		}
		printf("\n");
	}
	
	for (int i = 0; i < filasA; i++) {
		free(matrizA[i]);
	}
	
	for (int i = 0; i < filasB; i++) {
		free(matrizB[i]);
	}
	
	for (int i = 0; i < filasA; i++) {
		free(matrizResultado[i]);
	}
	
	free(matrizA);
	free(matrizB);
	free(matrizResultado);
	
	printf("Tiempo de ejecución: %lf segundos\n", tiempo);
	
	return 0;
}


