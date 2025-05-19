# Documentación del Juego de Slimes en C

## Descripción General

Este proyecto es un juego de rol por turnos realizado en lenguaje **C** (compatible con ZinjaI y C estándar básico "Dev-C++"), donde el usuario controla un “slime” que lucha contra enemigos al salir de un refrigerador, subiendo de nivel, recolectando monedas, usando objetos y enfrentando subjefes y un jefe final. El juego incluye diferentes dificultades y un sistema de registro de ganadores.

---

## Estructura del Código

### Archivos

- **Prototipo2.c**: Código fuente principal del juego.
- **ganadores.txt**: Archivo generado automáticamente para almacenar el nombre de los jugadores ganadores, cantidad de muertes y dificultad.

---

## Principales Estructuras

### Slime

```c
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
    int inventario[8];
    int platoNivel;
    int proteinaNivel;
    int dificultad;
} Slime;
```
- Representa al jugador.
- El inventario almacena la cantidad de ítems (frutas, grenetina, hielo, etc.).

### Enemigo

```c
typedef struct {
    char nombre[50];
    int vida;
    int ataque;
    int defensa;
} Enemigo;
```
- Representa a los enemigos (incluyendo subjefes y jefe final).

---

## Flujo del Programa

### 1. **Entrada**

- Se inicializa la semilla de números aleatorios.
- El usuario crea su slime: elige nombre (o uno aleatorio) y color.
- Se inicializan las estadísticas base y el inventario.

### 2. **Proceso**

- El usuario interactúa con un **menú principal** que permite:
    1. Ver estadísticas del slime.
    2. Iniciar batalla (sube de nivel si gana).
    3. Visitar la tienda (comprar ítems y mejoras).
    4. Ver la lista de ganadores.
    5. Reiniciar el juego.
    6. Cambiar dificultad (Fácil, Normal, Difícil, Extrema).
    7. Salir (con confirmación).

- **Batallas**:
    - El jugador lucha contra enemigos generados según el nivel y dificultad.
    - En niveles especiales (5, 10, 15), aparecen subjefes o jefe final y se muestra una historia especial.
    - Puede usar ítems, atacar o intentar huir (no posible en subjefes/jefe).

- **Tienda**:
    - Compra objetos para batalla y mejoras permanentes (defensa/plato, ataque/proteína).
    - Los precios escalan con el nivel y mejoras previas.

- **Registro de ganadores**:
    - Si el jugador vence el nivel final, se guarda su nombre, muertes y dificultad en `ganadores.txt`.
    - Se muestra la tabla de ganadores, indicando la dificultad en texto.

### 3. **Salida**

- Toda la salida se muestra por consola.
- El archivo `ganadores.txt` persiste entre ejecuciones.
- Al elegir salir, se advierte al usuario que no se guardará el progreso actual (solo los ganadores se guardan).

---

## Principales Funciones

- **mostrarHistoria**: Muestra la introducción del juego.
- **crearSlime**: Permite al usuario crear su personaje slime.
- **menuJuego**: Controla el menú principal y la navegación entre opciones.
- **verEstadisticas**: Muestra las estadísticas actuales del slime.
- **iniciarBatalla**: Lógica para combate contra enemigos, subjefes y jefe final.
- **tienda**: Permite al usuario comprar ítems y mejoras permanentes.
- **guardarGanador**: Escribe (o actualiza) el registro de ganadores en el archivo.
- **mostrarGanadores**: Muestra la tabla de ganadores con su dificultad.
- **seleccionarDificultad**: Permite cambiar la dificultad del juego.
- **dificultadTexto**: Convierte el valor numérico de dificultad a texto.
- **generarNumeroAleatorio**: Devuelve un número aleatorio en un rango.

---

## Dificultades

- **Fácil**: Menos experiencia y monedas, enemigos más débiles.
- **Normal**: Estadísticas estándar.
- **Difícil**: Más experiencia y monedas, enemigos más fuertes.
- **Extrema**: Mucha más experiencia y monedas, enemigos muy poderosos.

---

## Inventario e Ítems

- **Lanzamiento de fruta**: Aumenta ataque en batalla.
- **Grenetina / Grenetina Premium**: Aumentan la defensa en batalla.
- **Hielo / Hielo Polo Sur**: Recuperan vida durante la batalla.
- **Plato**: Mejora permanente de defensa.
- **Proteína**: Mejora permanente de ataque.

---

## Registro y Visualización de Ganadores

- Cada vez que el usuario termina el juego, su nombre, muertes y dificultad se guardan (o actualizan si mejora).
- El listado de ganadores se muestra con el formato:  
  `NOMBRE: X muertes | Dificultad: TEXTO`

---

## Confirmación al Salir

Al seleccionar la opción 7 del menú:
- El usuario debe confirmar con un menú numérico intuitivo antes de salir.
- Si se confirma, el juego termina; si no, regresa al menú.

---

## Requisitos y Compatibilidad

- **Compatible con ZinjaI** y compiladores estándar de C (Dev-C++).
- Se utilizan los temas y buenas prácticas vistas en clase. 
- El código está organizado y comentado para facilitar su comprensión y mantenimiento.

---

## Ejecución

1. Compilar el archivo `Prototipo2.c` en ZinjaI o usando un compilador estándar de C.
2. Ejecutar el programa desde la terminal o el entorno ZinjaI.
3. Seguir las instrucciones que aparecen en pantalla.

---

## Créditos

Juego de ejemplo desarrollado para nuestro proyecto de programación estructurada en lenguaje C, se ha utilizado los temas y buenas prácticas vistas en clase (Joyanes, capítulos 1-13).
