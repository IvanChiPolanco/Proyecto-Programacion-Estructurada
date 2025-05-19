/* Nombre del programa: Prototipo2.c
Proposito/Objetivo: Código fuente completo de “Dungeons C”.
Autor: EQUIPO X=4;
Fecha: 19/05/2025
Versión: 1.0
Compilador: ZinjaI*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definición de estructuras */
typedef struct {
	char nombre[30];
	char color[15];
	int vida;
	int ataque;
	int defensa;
	int nivel;
	int experiencia;
	int monedas;
	int muertes;
	int inventario[8]; /* 0-3: Frutas, 4: Grenetina, 5: Grenetina Premium, 6: Hielo, 7: Hielo Polo Sur */
	int platoNivel;
	int proteinaNivel;
	int dificultad; /* 1: Fácil, 2: Normal, 3: Difícil, 4: Extrema */
} Slime;

/* Estructura para los enemigos */
typedef struct {
	char nombre[50];
	int vida;
	int ataque;
	int defensa;
} Enemigo;

/* Constantes */
#define MAX_NIVEL 15
#define MAX_ITEMS 6
#define MAX_ITEMS_SUBJEFE 4
#define MAX_ITEMS_JEFE 3
#define MAX_FRUTAS 4
#define VIDA_BASE 85
#define ATAQUE_BASE 17
#define DEFENSA_BASE 10
#define AUMENTO_DEFENSA_PLATO 3
#define AUMENTO_ATAQUE_NIVEL 3
#define AUMENTO_DEFENSA_NIVEL 1
#define AUMENTO_VIDA_NIVEL 5
#define EXPERIENCIA_POR_NIVEL 100

/* Prototipos de funciones */
void mostrarHistoria();
Slime crearSlime();
void menuJuego(Slime *jugador);
void verEstadisticas(Slime *jugador);
void iniciarBatalla(Slime *jugador);
void tienda(Slime *jugador);
void guardarGanador(Slime jugador);
void mostrarGanadores();
int generarNumeroAleatorio(int limite);
void seleccionarDificultad(Slime *jugador);
const char* dificultadTexto(int dificultad);

/* Función principal */
int main() {
	/* Entrada */
	srand(12345);
	/* Proceso */
	Slime jugador = crearSlime();
	menuJuego(&jugador);
	/* Salida */
	return 0;
}

/* Función para mostrar la historia */
void mostrarHistoria() {
	printf("Muestra un refrigerador y se abre...\n");
	printf("Dentro del refrigerador se muestra un slime.\n");
}

/* Función para crear el slime */
Slime crearSlime() {
	Slime jugador;
	mostrarHistoria();
	
	printf("Ingrese nombre del personaje (Si ingresa '1', el nombre será aleatorio): ");
	scanf(" %[^\n]", jugador.nombre);
	
	if (strcmp(jugador.nombre, "1") == 0) {
		const char* opciones[] = {"Gelatin", "Blobby", "Slimo", "Jelly"};
		strcpy(jugador.nombre, opciones[generarNumeroAleatorio(4)]);
	}
	
	printf("Seleccione un color (1. Azul, 2. Verde, 3. Amarillo, 4. Morado, 5. Rojo): ");
	int colorOpcion;
	scanf("%d", &colorOpcion);
	const char* colores[] = {"Azul", "Verde", "Amarillo", "Morado", "Rojo"};
	strcpy(jugador.color, colores[colorOpcion - 1]);
	
	jugador.vida = VIDA_BASE;
	jugador.ataque = ATAQUE_BASE;
	jugador.defensa = DEFENSA_BASE;
	jugador.nivel = 1;
	jugador.experiencia = 0;
	jugador.monedas = 0;
	jugador.muertes = 0;
	jugador.platoNivel = 0;
	jugador.proteinaNivel = 0;
	jugador.dificultad = 2; /* Normal por defecto */
	int i;
	for ( i = 0; i < 8; i++) {
		jugador.inventario[i] = 0;
	}
	
	return jugador;
}

/* Función para devolver el texto de la dificultad */
const char* dificultadTexto(int dificultad) {
	switch (dificultad) {
	case 1: return "Facil";
	case 2: return "Normal";
	case 3: return "Dificil";
	case 4: return "Extrema";
	default: return "Desconocida";
	}
}

/* Función para guardar el nombre del ganador */
void guardarGanador(Slime jugador) {
	FILE *archivo = fopen("ganadores.txt", "a+");
	if (archivo == NULL) {
		printf("Error al abrir el archivo ganadores.txt\n");
		return;
	}
	
	char linea[120];
	char ganadores[100][120];
	int numGanadores = 0;
	
	rewind(archivo);
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		strcpy(ganadores[numGanadores], linea);
		numGanadores++;
	}
	
	int i, encontrado = 0;
	for ( i = 0; i < numGanadores; i++) {
		char nombreArchivo[30];
		int muertesArchivo;
		int dificultadArchivo;
		sscanf(ganadores[i], "%[^:]: %d muertes | Dificultad: %d", nombreArchivo, &muertesArchivo, &dificultadArchivo);
		if (strcmp(nombreArchivo, jugador.nombre) == 0 && dificultadArchivo == jugador.dificultad) {
			if (jugador.muertes < muertesArchivo) {
				sprintf(ganadores[i], "%s: %d muertes | Dificultad: %d\n", jugador.nombre, jugador.muertes, jugador.dificultad);
			}
			encontrado = 1;
			break;
		}
	}
	
	if (!encontrado) {
		sprintf(ganadores[numGanadores], "%s: %d muertes | Dificultad: %d\n", jugador.nombre, jugador.muertes, jugador.dificultad);
		numGanadores++;
	}
	
	fclose(archivo);
	archivo = fopen("ganadores.txt", "w");
	if (archivo == NULL) {
		printf("Error al abrir el archivo ganadores.txt\n");
		return;
	}

	for ( i = 0; i < numGanadores; i++) {
		fprintf(archivo, "%s", ganadores[i]);
	}
	
	fclose(archivo);
	
	printf("¡Felicidades! Tu nombre ha sido guardado en la lista de ganadores.\n");
	mostrarGanadores();
}

/* Función para mostrar la lista de ganadores */
void mostrarGanadores() {
	FILE *archivo = fopen("ganadores.txt", "r");
	if (archivo == NULL) {
		printf("Aún no hay ganadores registrados.\n");
		return;
	}
	
	printf("\n--- Lista de Ganadores ---\n");
	char linea[120];
	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		char nombre[30];
		int muertes, dificultad;
		int leidos = sscanf(linea, "%[^:]: %d muertes | Dificultad: %d", nombre, &muertes, &dificultad);
		if (leidos == 3) {
			printf("%s: %d muertes | Dificultad: %s\n", nombre, muertes, dificultadTexto(dificultad));
		}
	}
	fclose(archivo);
	printf("-------------------------\n");
}

/* Función para iniciar batalla */
void iniciarBatalla(Slime *jugador) {
	Enemigo enemigo;
	int nivel = jugador->nivel;
	int itemsUsados = 0;
	int defensa_buff = 0;
	int ataque_buff = 0;
	int subioNivel = 0;
	float factorExperiencia = 1.0;
	float factorMonedas = 1.0;
	
	switch (jugador->dificultad) {
	case 1:
		factorExperiencia = 0.8;
		factorMonedas = 0.7;
		break;
	case 2:
		factorExperiencia = 1.0;
		factorMonedas = 1.0;
		break;
	case 3:
		factorExperiencia = 1.2;
		factorMonedas = 1.3;
		break;
	case 4:
		factorExperiencia = 1.4;
		factorMonedas = 1.5;
		break;
	}
	
	if (nivel == 5 || nivel == 10 || nivel == 15) {
		if (nivel == 5) {
			strcpy(enemigo.nombre, "Slime oscuro");
			enemigo.vida = 170 + nivel * 3;
			enemigo.ataque = 27 + nivel * 2;
			enemigo.defensa = 13 + nivel;
			/* Historia para subjefe nivel 5 */
			printf("\nUn aura oscura llena el refrigerador... ¡Un Slime oscuro aparece!\n");
			printf("Este es el primer gran reto de tu aventura.\n");
		} else if (nivel == 10) {
			strcpy(enemigo.nombre, "Barra de mantequilla");
			enemigo.vida = 220 + nivel * 3;
			enemigo.ataque = 32 + nivel * 2;
			enemigo.defensa = 16 + nivel;
			/* Historia para subjefe nivel 10 */
			printf("\nLa temperatura sube y una figura dorada se desliza...\n");
			printf("¡La Barra de mantequilla te desafía a una batalla resbaladiza!\n");
		} else {
			strcpy(enemigo.nombre, "El Refrigerador Original");
			enemigo.vida = 270 + nivel * 3;
			enemigo.ataque = 37 + nivel * 2;
			enemigo.defensa = 19 + nivel;
			/* Historia para jefe final nivel 15 */
			printf("\nEl ambiente se congela, el tiempo se detiene...\n");
			printf("Frente a ti está El Refrigerador Original, el guardián final de este mundo.\n");
		}
	} else {
		const char* tiposCubiertos[] = {"Cuchillo", "Tenedor", "Cuchara", "Espatula"};
		const char* tiposEnemigos[] = {"Comun", "Especial", "Epico", "Legendario"};
		int tipoEnemigoIndex;
		
		if (nivel >= 1 && nivel <= 4) {
			tipoEnemigoIndex = 0;
		} else if (nivel >= 6 && nivel <= 9) {
			tipoEnemigoIndex = 1;
		} else if (nivel >= 11 && nivel <= 14) {
			tipoEnemigoIndex = 2;
		} else {
			tipoEnemigoIndex = 3;
		}
		
		sprintf(enemigo.nombre, "%s %s", tiposCubiertos[generarNumeroAleatorio(4)], tiposEnemigos[tipoEnemigoIndex]);
		enemigo.vida = 50 + nivel * 8;
		enemigo.ataque = 10 + nivel * 3;
		enemigo.defensa = 5 + nivel * 2;
	}
	
	/* Ajustar estadísticas del enemigo según la dificultad */
	if (jugador->dificultad == 3) {
		enemigo.vida = enemigo.vida * 11 / 10;
		enemigo.ataque = enemigo.ataque * 11 / 10;
		enemigo.defensa = enemigo.defensa * 11 / 10;
	} else if (jugador->dificultad == 1) {
		enemigo.vida = enemigo.vida * 9 / 10;
		enemigo.ataque = enemigo.ataque * 9 / 10;
		enemigo.defensa = enemigo.defensa * 9 / 10;
	} else if (jugador->dificultad == 4) {
		enemigo.vida = enemigo.vida * 13 / 10;
		enemigo.ataque = enemigo.ataque * 13 / 10;
		enemigo.defensa = enemigo.defensa * 13 / 10;
	}
	
	printf("\nUn %s aparece!\n", enemigo.nombre);
	
	int opcion;
	while (enemigo.vida > 0 && jugador->vida > 0) {
		printf("\nNivel: %d\n", nivel);
		printf("Vida del slime %s: %d | Vida del enemigo: %d\n", jugador->nombre, jugador->vida, enemigo.vida);
		printf("1. Atacar\n2. Usar item\n3. Huir\nSeleccione una opcion: ");
		scanf("%d", &opcion);
		
		if (opcion == 1) {
			int dano = (jugador->ataque + ataque_buff) - enemigo.defensa;
			if (dano < 0) dano = 1;
			enemigo.vida -= dano;
			printf("El slime ataco y causo %d de dano!\n", dano);
		} else if (opcion == 2) {
			int maxItems;
			if (nivel == 5 || nivel == 10) {
				maxItems = MAX_ITEMS_SUBJEFE;
			} else if (nivel == 15) {
				maxItems = MAX_ITEMS_JEFE;
			} else {
				maxItems = MAX_ITEMS;
			}
			
			if (itemsUsados >= maxItems) {
				printf("Has alcanzado el limite de items para este combate.\n");
				continue;
			}
			
			printf("\nSeleccione un item:\n");
			printf("1. Lanzamiento de fruta (%d disponibles)\n", jugador->inventario[0]);
			printf("2. Grenetina (%d disponibles)\n", jugador->inventario[4]);
			printf("3. Grenetina Premium (%d disponibles)\n", jugador->inventario[5]);
			printf("4. Hielo (%d disponibles)\n", jugador->inventario[6]);
			printf("5. Hielo del Polo Sur (%d disponibles)\n", jugador->inventario[7]);
			printf("6. Cancelar\n");
			
			int itemOpcion;
			scanf("%d", &itemOpcion);
			
			switch (itemOpcion) {
			case 1:
				if (jugador->inventario[0] > 0) {
					jugador->inventario[0]--;
					itemsUsados++;
					int frutaAleatoria = generarNumeroAleatorio(3) + 1;
					float porcentajeAtaque;
					const char* nombreFruta;
					
					switch (frutaAleatoria) {
					case 1:
						porcentajeAtaque = 0.20;
						nombreFruta = "Sandia Picada";
						break;
					case 2:
						porcentajeAtaque = 0.40;
						nombreFruta = "Melon Picado";
						break;
					default:
						porcentajeAtaque = 0.60;
						nombreFruta = "Uvas";
						break;
					}
					
					ataque_buff += jugador->ataque * porcentajeAtaque;
					printf("Usaste %s! Tu ataque aumenta en %.2f!\n", nombreFruta, jugador->ataque * porcentajeAtaque);
				} else {
					printf("No tienes Lanzamiento de fruta disponibles.\n");
					continue;
				}
				break;
			case 2:
				if (jugador->inventario[4] > 0) {
					jugador->inventario[4]--;
					itemsUsados++;
					defensa_buff += (int)(jugador->defensa * 0.4);
					printf("Usaste Grenetina! Tu defensa aumenta en 40%%!\n");
				} else {
					printf("No tienes Grenetina disponibles.\n");
					continue;
				}
				break;
			case 3:
				if (jugador->inventario[5] > 0) {
					jugador->inventario[5]--;
					itemsUsados++;
					defensa_buff += (int)(jugador->defensa * 0.8);
					printf("Usaste Grenetina Premium! Tu defensa aumenta en 80%%!\n");
				} else {
					printf("No tienes Grenetina Premium disponibles.\n");
					continue;
				}
				break;
			case 4:
				if (jugador->inventario[6] > 0) {
					jugador->inventario[6]--;
					jugador->vida += (int)(VIDA_BASE * 0.4);
					if (jugador->vida > VIDA_BASE) jugador->vida = VIDA_BASE;
					printf("Usaste Hielo! Curaste 40%% de tu vida.\n");
					itemsUsados++;
				} else {
					printf("No tienes Hielo disponibles.\n");
					continue;
				}
				break;
			case 5:
				if (jugador->inventario[7] > 0) {
					jugador->inventario[7]--;
					jugador->vida = (int)(VIDA_BASE * 0.9);
					printf("Usaste Hielo del Polo Sur! Curaste tu vida al 90%%.\n");
					itemsUsados++;
				} else {
					printf("No tienes Hielo del Polo Sur disponibles.\n");
					continue;
				}
				break;
			case 6:
				printf("Accion cancelada.\n");
				continue;
			default:
				printf("Opcion invalida.\n");
				continue;
			}
		} else if (opcion == 3) {
			int huirExito = 0;
			if (nivel == 5 || nivel == 10 || nivel == 15) {
				printf("No se puede huir de %s...\n", enemigo.nombre);
				continue;
			} else {
				int probabilidadHuir;
				if (nivel >= 1 && nivel <= 4) {
					probabilidadHuir = 90 - (nivel * 5);
				} else if (nivel >= 6 && nivel <= 9) {
					probabilidadHuir = 65 - (nivel * 5);
				} else if (nivel >= 11 && nivel <= 14) {
					probabilidadHuir = 40 - (nivel * 5);
				} else {
					probabilidadHuir = 0;
				}
				
				if (generarNumeroAleatorio(100) < probabilidadHuir) {
					huirExito = 1;
					printf("¡Huiste exitosamente!\n");
					return;
				} else {
					printf("No se ha podido huir de %s\n", enemigo.nombre);
				}
			}
			if (!huirExito) {
				int danoRecibido = enemigo.ataque - (jugador->defensa + defensa_buff);
				if (danoRecibido < 0) danoRecibido = 1;
				jugador->vida -= danoRecibido;
				printf("%s ataco y causo %d de dano!\n", enemigo.nombre, danoRecibido);
			}
		} else {
			printf("Opcion invalida.\n");
			continue;
		}
		
		if (enemigo.vida > 0 && opcion != 3) {
			int danoRecibido = enemigo.ataque - (jugador->defensa + defensa_buff);
			if (danoRecibido < 0) danoRecibido = 1;
			jugador->vida -= danoRecibido;
			printf("%s ataco y causo %d de dano!\n", enemigo.nombre, danoRecibido);
		}
	}
	
	if (jugador->vida > 0) {
		printf("¡Has ganado la batalla!\n");
		int monedasGanadas = (int)(nivel * factorMonedas);
		jugador->monedas += monedasGanadas;
		int experienciaGanada = (int)((25 + nivel * 5) * factorExperiencia);
		jugador->experiencia += experienciaGanada;
		printf("Ganaste %d monedas y %d de experiencia!\n", monedasGanadas, experienciaGanada);
		
		if (nivel == 5 || nivel == 10 || nivel == 15) {
			int aumentoAtaque = AUMENTO_ATAQUE_NIVEL;
			int aumentoDefensa = AUMENTO_DEFENSA_NIVEL;
			int aumentoVida = AUMENTO_VIDA_NIVEL;
			
			jugador->nivel++;
			jugador->ataque += aumentoAtaque;
			jugador->defensa += aumentoDefensa;
			jugador->vida += aumentoVida;
			subioNivel = 1;
			
			printf("¡Derrotaste al subjefe/jefe! Subiste al nivel %d automaticamente.\n", jugador->nivel);
			printf("Ataque aumentado en %d, Defensa aumentada en %d, Vida aumentada en %d\n", aumentoAtaque, aumentoDefensa, aumentoVida);
		} else if (jugador->experiencia >= EXPERIENCIA_POR_NIVEL && jugador->nivel < MAX_NIVEL) {
			int aumentoAtaque = AUMENTO_ATAQUE_NIVEL;
			int aumentoDefensa = AUMENTO_DEFENSA_NIVEL;
			int aumentoVida = AUMENTO_VIDA_NIVEL;
			
			jugador->nivel++;
			jugador->experiencia -= EXPERIENCIA_POR_NIVEL;
			jugador->ataque += aumentoAtaque;
			jugador->defensa += aumentoDefensa;
			jugador->vida += aumentoVida;
			subioNivel = 1;
			
			printf("¡Subiste de nivel! Ahora eres nivel %d\n", jugador->nivel);
			printf("Ataque aumentado en %d, Defensa aumentada en %d, Vida aumentada en %d\n", aumentoAtaque, aumentoDefensa, aumentoVida);
		}
		
		jugador->vida = VIDA_BASE + (jugador->nivel * AUMENTO_VIDA_NIVEL);
		
		ataque_buff = 0;
		defensa_buff = 0;
		
		if (nivel == MAX_NIVEL) {
			guardarGanador(*jugador);
			printf("¡Felicidades! Has completado el juego.\n");
			printf("No puedes continuar el progreso, pero puedes jugar de nuevo desde el principio.\n");
		}
	} else {
		printf("Has sido derrotado... Reiniciando el juego.\n");
		jugador->muertes++;
		*jugador = crearSlime();
	}
	
	if ((nivel == 5 || nivel == 10) && jugador->vida > 0 && !subioNivel) {
		int aumentoAtaque = AUMENTO_ATAQUE_NIVEL;
		int aumentoDefensa = AUMENTO_DEFENSA_NIVEL;
		int aumentoVida = AUMENTO_VIDA_NIVEL;
		
		jugador->nivel++;
		jugador->ataque += aumentoAtaque;
		jugador->defensa += aumentoDefensa;
		jugador->vida += aumentoVida;
		
		printf("¡Derrotaste al subjefe! Subiste al nivel %d automaticamente.\n", jugador->nivel);
		printf("Ataque aumentado en %d, Defensa aumentada en %d, Vida aumentada en %d\n", aumentoAtaque, aumentoDefensa, aumentoVida);
	}
}

/* Función de la tienda */
void tienda(Slime *jugador) {
	int precioLanzamientoFruta = 3 + (jugador->nivel / 3);
	int precioGrenetina = 2 + (jugador->nivel / 4);
	int precioGrenetinaPremium = 4 + (jugador->nivel / 3);
	int precioHielo = 2 + (jugador->nivel / 4);
	int precioHieloPoloSur = 5 + (jugador->nivel / 3);
	int precioPlato = jugador->platoNivel + 1 + (jugador->nivel / 2);
	int precioProteina = jugador->proteinaNivel + 1 + (jugador->nivel / 2);
	
	printf("\nBienvenido a la tienda. Tienes %d monedas.\n", jugador->monedas);
	printf("1. Lanzamiento de fruta (%d monedas, %d disponibles) - Aumenta el ataque en batalla\n", precioLanzamientoFruta, MAX_FRUTAS - jugador->inventario[0]);
	printf("2. Grenetina (%d monedas, %d disponibles) - Aumenta la defensa en batalla\n", precioGrenetina, jugador->inventario[4]);
	printf("3. Grenetina Premium (%d monedas, %d disponibles) - Aumenta mucho la defensa en batalla\n", precioGrenetinaPremium, jugador->inventario[5]);
	if (jugador->platoNivel < 5) {
		printf("4. Plato (%d monedas) - Aumenta la defensa permanentemente en %d\n", precioPlato, AUMENTO_DEFENSA_PLATO);
	}
	printf("5. Hielo (%d monedas, %d disponibles) - Cura 40%% de la vida en batalla\n", precioHielo, jugador->inventario[6]);
	printf("6. Hielo del Polo Sur (%d monedas, %d disponibles) - Cura 90%% de la vida en batalla\n", precioHieloPoloSur, jugador->inventario[7]);
	if (jugador->proteinaNivel < 5) {
		printf("7. Proteina (%d monedas) - Aumenta el ataque permanentemente\n", precioProteina);
	}
	printf("8. Salir\nSeleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	
	if (opcion == 1 && jugador->monedas >= precioLanzamientoFruta && jugador->inventario[0] < MAX_FRUTAS) {
		jugador->monedas -= precioLanzamientoFruta;
		jugador->inventario[0]++;
		printf("Compraste Lanzamiento de fruta. Tienes %d.\n", jugador->inventario[0]);
	} else if (opcion == 2 && jugador->monedas >= precioGrenetina) {
		jugador->monedas -= precioGrenetina;
		jugador->inventario[4]++;
		printf("Compraste Grenetina.\n");
	} else if (opcion == 3 && jugador->monedas >= precioGrenetinaPremium) {
		jugador->monedas -= precioGrenetinaPremium;
		jugador->inventario[5]++;
		printf("Compraste Grenetina Premium.\n");
	} else if (opcion == 4 && jugador->platoNivel < 5 && jugador->monedas >= precioPlato) {
		jugador->monedas -= precioPlato;
		jugador->platoNivel++;
		jugador->defensa += AUMENTO_DEFENSA_PLATO;
		printf("Compraste Plato de ");
		switch (jugador->platoNivel) {
		case 1: printf("Hoja.\n"); break;
		case 2: printf("Ceramica.\n"); break;
		case 3: printf("Plata.\n"); break;
		case 4: printf("Oro.\n"); break;
		case 5: printf("Glorioso.\n"); break;
		}
		printf("Tu defensa aumento en %d permanentemente.\n", AUMENTO_DEFENSA_PLATO);
	} else if (opcion == 5 && jugador->monedas >= precioHielo && jugador->inventario[6] < 5) {
		jugador->monedas -= precioHielo;
		jugador->inventario[6]++;
		printf("Compraste Hielo.\n");
	} else if (opcion == 6 && jugador->monedas >= precioHieloPoloSur && jugador->inventario[7] < 5) {
		jugador->monedas -= precioHieloPoloSur;
		jugador->inventario[7]++;
		printf("Compraste Hielo del Polo Sur.\n");
	} else if (opcion == 7 && jugador->proteinaNivel < 5 && jugador->monedas >= precioProteina) {
		jugador->monedas -= precioProteina;
		jugador->proteinaNivel++;
		float aumentoAtaque = 0.1 * jugador->proteinaNivel;
		jugador->ataque += (int)(ATAQUE_BASE * aumentoAtaque);
		printf("Compraste Proteina ");
		switch (jugador->proteinaNivel) {
		case 1: printf("Comun.\n"); break;
		case 2: printf("Rara.\n"); break;
		case 3: printf("Ultra.\n"); break;
		case 4: printf("Extra Plus.\n"); break;
		case 5: printf("Premium Fortificada.\n"); break;
		}
		printf("Tu ataque aumento en %.2f permanentemente.\n", ATAQUE_BASE * aumentoAtaque);
	} else {
		printf("No tienes suficientes monedas o opcion invalida.\n");
	}
}

/* Función para ver las estadísticas del jugador */
void verEstadisticas(Slime *jugador) {
	printf("Nombre: %s\n", jugador->nombre);
	printf("Color: %s\n", jugador->color);
	printf("Vida: %d\n", jugador->vida);
	printf("Ataque: %d\n", jugador->ataque);
	printf("Defensa: %d\n", jugador->defensa);
	printf("Nivel: %d\n", jugador->nivel);
	printf("Experiencia: %d\n", jugador->experiencia);
	printf("Monedas: %d\n", jugador->monedas);
	printf("Muertes: %d\n", jugador->muertes);
	printf("Inventario:\n");
	printf("  Lanzamiento de fruta: %d\n", jugador->inventario[0]);
	printf("  Grenetina: %d\n", jugador->inventario[4]);
	printf("  Grenetina Premium: %d\n", jugador->inventario[5]);
	printf("  Hielo: %d\n", jugador->inventario[6]);
	printf("  Hielo del Polo Sur: %d\n", jugador->inventario[7]);
	printf("Dificultad: %s\n", dificultadTexto(jugador->dificultad));
}

/* Función para seleccionar la dificultad */
void seleccionarDificultad(Slime *jugador) {
	printf("\nSeleccione la dificultad:\n");
	printf("1. Facil (Menos experiencia y monedas)\n");
	printf("2. Normal (Experiencia y monedas estandar)\n");
	printf("3. Dificil (Mas experiencia y monedas)\n");
	printf("4. Extrema (Mucho mas experiencia y monedas, enemigos mas poderosos)\n");
	printf("Seleccione una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	
	if (opcion >= 1 && opcion <= 4) {
		jugador->dificultad = opcion;
		printf("Dificultad establecida a %s.\n", dificultadTexto(jugador->dificultad));
	} else {
		printf("Opcion invalida. Se mantiene la dificultad actual (%s).\n", dificultadTexto(jugador->dificultad));
	}
}

/* Menú principal */
void menuJuego(Slime *jugador) {
	int opcion;
	while (1) {
		printf("\nMenu principal:\n");
		printf("1. Ver estadisticas\n");
		printf("2. Batalla (Nivel %d)\n", jugador->nivel);
		if (jugador->nivel > 0) {
			printf("3. Tienda\n");
		}
		printf("4. Mostrar Ganadores\n");
		printf("5. Reiniciar Juego\n");
		printf("6. Seleccionar Dificultad\n");
		printf("7. Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		
		if (opcion == 1) {
			verEstadisticas(jugador);
		} else if (opcion == 2) {
			iniciarBatalla(jugador);
		} else if (opcion == 3 && jugador->nivel > 0) {
			tienda(jugador);
		} else if (opcion == 4) {
			mostrarGanadores();
		} else if (opcion == 5) {
			*jugador = crearSlime();
			printf("Juego reiniciado.\n");
		} else if (opcion == 6) {
			seleccionarDificultad(jugador);
		} else if (opcion == 7) {
			int confirmar;
			printf("¿Estás seguro de que quieres salir del juego?\n");
			printf("¡No se guardará el progreso actual!\n");
			printf("1. Sí, salir y perder progreso\n");
			printf("2. No, regresar al menú\n");
			printf("Seleccione una opción: ");
			scanf("%d", &confirmar);
			if (confirmar == 1) {
				printf("Saliendo del juego. ¡No se guardará el progreso actual!\n");
				break;
			} else {
				printf("No se ha salido del juego. Continuando...\n");
			}
		} else {
			printf("Opcion invalida.\n");
		}
	}
}

/* Función para generar un número aleatorio dentro de un límite */
int generarNumeroAleatorio(int limite) {
	return rand() % limite;
}
