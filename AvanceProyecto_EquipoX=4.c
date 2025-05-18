/*
Equipo X = 4;
Castillo Manchado Oswaldo, Chi Polanco Ivan Alejandro, Dzib Pech Luis Gilberto, Osorio Muñoz Jaime Armando
Implementaci�n de Videojuegos de Rol por Turnos en C "Dungeons-C"
Compilador: Zinjai
Ver. 1.0
18 de Mayo de 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> /* Para inicializar la semilla de aleatoriedad */
#include <locale.h>

/* === Mapeo del juego === */
char mapa[FILAS][COLS+1] = {
	"#########################",
		"#P    #    #   #     #  #",
		"# ## ##### ### # ### # ##",
		"#    #     #   # #   #  #",
		"#### # ####### # ### ####",
		"#  #   #         #      #",
		"#  ### #######  ####### #",
		"#   #     #     #      J#",
		"### ##### # ##### #######",
		"#     #   #   #         #",
		"# ### ### ### ######## ##",
		"#   #     #   #        F#",
		"# ### ####### ###########",
		"#            J          #",
		"#########################"
};


int jugador_x = 1, jugador_y = 1;
int monedas = 0;

/* === Estructura que define al personaje=== */
typedef struct {
	char nombre[30];
	int vida, ataque, defensa, experiencia, nivel;
	int ataque_extra;
	int defensa_extra;
	int pociones_vida;
	int pociones_ataque;
	int pociones_defensa;
} personaje_t;
/* === Estructura que define al enemigo=== */
typedef struct {
	char nombre[40];
	int vida, ataque, defensa;
} enemigo_t;
/* === Estructura que define mejoras del personaje=== */
typedef struct {
	char nombre[30];
	int mejora_ataque;
	int mejora_defensa;
	int cura_vida;
	int costo;
	int tipo; // 1 = arma/armadura, 2 = consumible
} objeto_t;

/* === Lista de enemigos y jefes === */
const enemigo_t enemigos_normales[] = {
	{"Goblin", 20, 5, 2},
{"Kobold", 18, 6, 1},
	{"Gnoll", 25, 7, 3},
{"Arania Gigante", 24, 6, 2},
	{"Orco", 28, 10, 2},
{"Esqueleto", 22, 6, 2},
};
const int num_enemigos = sizeof(enemigos_normales)/sizeof(enemigos_normales[0]);

enemigo_t jefe_intermedio() {
	int selector = rand() % 2;
	if (selector == 0)
		return (enemigo_t){"Ogro de Guerra", 100, 40, 6};
	else
		return (enemigo_t){"Beholder", 90, 50, 5}; 
}

enemigo_t jefe_final() {
	return (enemigo_t){"Lich Supremo", 300, 70, 30};
}

/* === Objetos de tienda === */
const objeto_t tienda[MAX_OBJETOS] = {
	{"Espada corta", 6, 0, 0, 10, 1},
{"Escudo madera", 0, 6, 0, 10, 1},
	{"Hacha orca", 7, 0, 0, 20, 1},
{"Armadura ligera", 0, 10, 0, 40, 1},
	{"Espada larga", 8, 1, 0, 35, 1},
{"Pocion vida", 0, 0, 20, 20, 2},
	{"Pocion ataque", 4, 0, 0, 15, 2},
{"Pocion defensa", 0, 4, 0, 15, 2}
};

/* === Funcion para moverte en el mapa === */
void mostrar_mapa() {
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (i == jugador_x && j == jugador_y) printf("P");
			else printf("%c", mapa[i][j]);
		}
		printf("\n");
	}
}
/* === Mostrar estadísticas del personaje ===*/
void mostrar_estadisticas(personaje_t pj) {
	printf("\n--- %s ---\n", pj.nombre);
	printf("Vida: %d\nAtaque: %d (+%d)\nDefensa: %d (+%d)\nNivel: %d\nMonedas: %d\nPociones (vida:%d ataque:%d defensa:%d)\n",
		   pj.vida, pj.ataque, pj.ataque_extra, pj.defensa, pj.defensa_extra, pj.nivel, monedas,
		   pj.pociones_vida, pj.pociones_ataque, pj.pociones_defensa);
}
/* === Generar enemigo con atributos aleatorios ===*/
enemigo_t generar_enemigo_aleatorio() {
	return enemigos_normales[rand() % num_enemigos];
}
/* === Usar consumibles ===*/
personaje_t usar_consumible(personaje_t *pj) {
	int op;
	printf("1. Usar pocion de vida\n2. Usar pocion de ataque\n3. Usar pocion de defensa\n4. Cancelar\n> ");
	scanf("%d", &op);
	switch (op) {
	case 1:
		if (pj->pociones_vida > 0) {
			pj->vida += 20;
			pj->pociones_vida--;
			printf("Te curaste 20 puntos.\n");
		}
		break;
	case 2:
		if (pj->pociones_ataque > 0) {
			pj->ataque_extra += 2;
			pj->pociones_ataque--;
			printf("Tu ataque aumento.\n");
		}
		break;
	case 3:
		if (pj->pociones_defensa > 0) {
			pj->defensa_extra += 2;
			pj->pociones_defensa--;
			printf("Tu defensa aumento.\n");
		}
		break;
	}
	return *pj;
}
/* === Funcion Tienda ===*/
void tienda_objetos(personaje_t *pj) {
	int op;
	printf("\n=== TIENDA ===\n");
	for (int i = 0; i < MAX_OBJETOS; i++) {
		printf("%d. %s (Atk+%d Def+%d Vida+%d) - %d monedas\n", i+1,
			   tienda[i].nombre, tienda[i].mejora_ataque, tienda[i].mejora_defensa,
			   tienda[i].cura_vida, tienda[i].costo);
	}
	printf("0. Cancelar\n> ");
	scanf("%d", &op);
	if (op >= 1 && op <= MAX_OBJETOS) {
		objeto_t obj = tienda[op-1];
		if (monedas >= obj.costo) {
			monedas -= obj.costo;
			if (obj.tipo == 1) {
				pj->ataque_extra += obj.mejora_ataque;
				pj->defensa_extra += obj.mejora_defensa;
				printf("Compraste y equipaste %s.\n", obj.nombre);
			} else {
				if (obj.cura_vida > 0) pj->pociones_vida++;
				else if (obj.mejora_ataque > 0) pj->pociones_ataque++;
				else if (obj.mejora_defensa > 0) pj->pociones_defensa++;
				printf("Compraste una %s.\n", obj.nombre);
			}
		} else printf("No tienes suficientes monedas.\n");
	}
}
/* === Proceso de combate entre jugador y enemigo ===*/
personaje_t combatir(personaje_t jugador, enemigo_t enemigo) {
	printf("\n\u00a1Te enfrentas al %s!\n", enemigo.nombre);
	while (jugador.vida > 0 && enemigo.vida > 0) {
		printf("\nTu vida: %d | Vida del %s: %d\n", jugador.vida, enemigo.nombre, enemigo.vida);
		printf("1. Atacar\n2. Usar pocion\n> ");
		int op;
		scanf("%d", &op);
		if (op == 1) {
			int dmg = (jugador.ataque + jugador.ataque_extra) - enemigo.defensa;
			if (dmg < 1) dmg = 1;
			enemigo.vida -= dmg;
			printf("Le hiciste %d de danio.\n", dmg);
		} else if (op == 2) {
			jugador = usar_consumible(&jugador);
			continue;
		}
		if (enemigo.vida > 0) {
			int dmg = enemigo.ataque - (jugador.defensa + jugador.defensa_extra);
			if (dmg < 1) dmg = 1;
			jugador.vida -= dmg;
			printf("El %s te hizo %d de danio.\n", enemigo.nombre, dmg);
		}
	}
	if (jugador.vida > 0) {
		printf("\u00a1Has ganado!\n");
		monedas += 10 + rand() % 10;
	} else {
		printf("Has muerto. Game Over.\n");
	}
	return jugador;
}

/* === Funcion principal === */
int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	
	personaje_t jugador;
	jugador.vida = 30;
	jugador.ataque = 8;
	jugador.defensa = 4;
	jugador.experiencia = 0;
	jugador.nivel = 1;
	jugador.ataque_extra = 0;
	jugador.defensa_extra = 0;
	jugador.pociones_vida = 1;
	jugador.pociones_ataque = 1;
	jugador.pociones_defensa = 1;
	
	printf("Ingresa el nombre de tu heroe: ");
	fgets(jugador.nombre, sizeof(jugador.nombre), stdin);
	jugador.nombre[strcspn(jugador.nombre, "\n")] = '\0';
	printf("P= Personaje ");
	printf(" = Espacio en blanco ");
	printf("#= Muro ");
	printf("J= Jefe intermedio ");
	printf("J= Jefe final \n");
	char cmd;
	while (jugador.vida > 0) {
		mostrar_mapa();
		mostrar_estadisticas(jugador);
		printf("Mover (WASD), T = tienda, U = usar pocion, Q = salir\n> ");
		scanf(" %c", &cmd);
		int dx = 0, dy = 0;
		if (cmd == 'w') dx = -1;
		else if (cmd == 's') dx = 1;
		else if (cmd == 'a') dy = -1;
		else if (cmd == 'd') dy = 1;
		else if (cmd == 'T' || cmd == 't') { tienda_objetos(&jugador); continue; }
		else if (cmd == 'U' || cmd == 'u') { jugador = usar_consumible(&jugador); continue; }
		else if (cmd == 'Q' || cmd == 'q') break;
		
		int nx = jugador_x + dx;
		int ny = jugador_y + dy;
		if (mapa[nx][ny] == '#') continue;
		
		jugador_x = nx;
		jugador_y = ny;
		
		if (mapa[nx][ny] == 'J') {
			jugador = combatir(jugador, jefe_intermedio());
			mapa[nx][ny] = ' ';
		} else if (mapa[nx][ny] == 'F') {
			jugador = combatir(jugador, jefe_final());
			mapa[nx][ny] = ' ';
		} else {
			int prob = rand() % 100;
			if (prob < PROB_ENEMIGO) {
				jugador = combatir(jugador, generar_enemigo_aleatorio());
			}
		}
	}
	
	return 0;
}
