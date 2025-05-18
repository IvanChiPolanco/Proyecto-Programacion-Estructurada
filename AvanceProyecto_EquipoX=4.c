/*
Equipo X = 4;
Chi Polanco Ivan Alejandro, Castillo Manchado Oswaldo, Osorio Muñoz Jaime Armando, Dzib Pech Luis Gilberto
Implementación de Videojuegos de Rol por Turnos en C "Dungeons-C"
Compilador: Zinjai
Ver. 1.0
12 de Mayo de 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> /* Para inicializar la semilla de aleatoriedad */
#include <locale.h>

#define EXPERIENCIA_SUBIR_NIVEL   (20)
#define INCREMENTO_ATAQUE         (2)
#define INCREMENTO_DEFENSA        (1)
#define INCREMENTO_VIDA           (10)

/* Estructura que define al personaje */
typedef struct {
	char nombre[30];
	int vida, ataque, defensa, experiencia, nivel;
} personaje_t;

/* Estructura que define al enemigo */
typedef struct {
	char nombre[30];
	int vida, ataque, defensa;
} enemigo_t;

/* Mostrar estadísticas del personaje */
void mostrar_estadisticas(personaje_t personaje) {
	printf("\n--- %s ---\n", personaje.nombre);
	printf("Vida: %d\nAtaque: %d\nDefensa: %d\nExperiencia: %d\nNivel: %d\n",
		   personaje.vida, personaje.ataque, personaje.defensa,
		   personaje.experiencia, personaje.nivel);
}

/* Generar enemigo con atributos aleatorios */
enemigo_t generar_enemigo() {
	enemigo_t enemigo;
	strcpy(enemigo.nombre, "Goblin salvaje");
	enemigo.vida = rand() % 20 + 10;
	enemigo.ataque = rand() % 5 + 3;
	enemigo.defensa = rand() % 3 + 1;
	return enemigo;
}

/* Subir de nivel al personaje */
personaje_t subir_nivel(personaje_t jugador) {
	if (jugador.experiencia >= EXPERIENCIA_SUBIR_NIVEL) {
		jugador.nivel++;
		jugador.ataque += INCREMENTO_ATAQUE;
		jugador.defensa += INCREMENTO_DEFENSA;
		jugador.vida += INCREMENTO_VIDA;
		jugador.experiencia = 0;
		printf("\u00a1Subiste a nivel %d!\n", jugador.nivel);
	}
	return jugador;
}

/* Proceso de combate entre jugador y enemigo */
personaje_t combatir(personaje_t jugador, enemigo_t enemigo) {
	printf("\n\u00a1Un %s aparece!\n", enemigo.nombre);
	
	while (jugador.vida > 0 && enemigo.vida > 0) {
		printf("\nTu vida: %d | Vida del %s: %d\n", jugador.vida, enemigo.nombre, enemigo.vida);
		printf("1. Atacar\n2. Huir\nElige una opcion: ");
		
		int opcion = 0;
		scanf("%d", &opcion);
		
		if (opcion == 1) {
			int danio_jugador = jugador.ataque - enemigo.defensa;
			if (danio_jugador < 1) danio_jugador = 1;
			enemigo.vida -= danio_jugador;
			printf("Le hiciste %d de danio al %s.\n", danio_jugador, enemigo.nombre);
			
			if (enemigo.vida <= 0) {
				printf("\u00a1Has derrotado al %s!\n", enemigo.nombre);
				jugador.experiencia += 10;
				jugador = subir_nivel(jugador);
				break;
			}
			
			int danio_enemigo = enemigo.ataque - jugador.defensa;
			if (danio_enemigo < 1) danio_enemigo = 1;
			jugador.vida -= danio_enemigo;
			printf("El %s te hizo %d de danio.\n", enemigo.nombre, danio_enemigo);
			
		} else if (opcion == 2) {
			printf("\u00a1Huiste del combate!\n");
			break;
		} else {
			printf("Opcion invalida.\n");
		}
	}
	
	if (jugador.vida <= 0) {
		printf("\nHas sido derrotado. Game Over.\n");
	}
	
	return jugador;
}

/* Función principal */
int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	
	personaje_t jugador = { .vida = 30, .ataque = 8, .defensa = 3, .experiencia = 0, .nivel = 1 };
	
	printf("Ingresa el nombre de tu personaje: ");
	fgets(jugador.nombre, sizeof(jugador.nombre), stdin);
	jugador.nombre[strcspn(jugador.nombre, "\n")] = '\0';
	
	int opcion = 0;
	do {
		printf("\n=== MENU ===\n");
		printf("1. Ver estadisticas\n");
		printf("2. Buscar pelea\n");
		printf("3. Salir del juego\n");
		printf("Elige una opcion: ");
		scanf("%d", &opcion);
		getchar();
		
		switch (opcion) {
		case 1:
			mostrar_estadisticas(jugador);
			break;
		case 2:
			jugador = combatir(jugador, generar_enemigo());
			break;
		case 3:
			printf("\u00a1Gracias por jugar!\n");
			break;
		default:
			printf("Opcion invalida.\n");
		}
		
	} while (opcion != 3 && jugador.vida > 0);
	
	return 0;
}
