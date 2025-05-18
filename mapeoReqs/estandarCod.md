# Definición del Estándar de Codificación
Para llevar a cabo un proceso de desarrollo sencillo, donde se puede garantizar un código legible y claro, se decidió por usar el estándar de calidad ANSI-C (C89/C90) para facilitar la modificación del código, que este siga una sola estructura y que cada integrante del equipo pueda seguirlo, además de añadir algunas libertades para poder especificar ciertas cosas que no se encuentran en el estándar y así que el código siga un solo estilo.

**Nombrado de variables:**

-   Utilizar la estructura snake_case para nombrar las variables; donde cada palabra de la variable es separada por un guión bajo, por ejemplo: vida_jugador, danio_enemigo, contador_tiempo.
    

-   Todas las variables del mismo tipo se declararán en la misma línea, no por separado. Ejemplo:
    

	Int a, b, c;

	Float e, f, g;

-   Las variables deben ser inicializadas en la misma línea donde se declaran. Ejemplo:
    

	Int a = 1, b = 2, c = 3;

-   En caso de usar variables globales, se debe denotar con una “g_” en su nombre.
    

**Macros y #define:**

-   Escribir las macros y #define usando mayúsculas y separando las palabras por un “_”.
    

-   Las macros deben escribirse en mayúscula y entre paréntesis.
    

-   El espacio antes y después de la macro puede ser cualquier espacio en blanco.
    

-   Si la macro es una expresión, enciérrela entre paréntesis. Si la macro tiene más de una sentencia, use ``do { ... } while (0)'' para que funcione el punto y coma final.
    

**Funciones:**

-   Las funciones seguirán el formato snake_case para los nombres.
    

-   Igualmente, las variables que se usen dentro de los paréntesis de las funciones seguirán la estructura  snake_case.
    

-   En caso de usar punteros, validar los nulos o valores inválidos al inicio. Ejemplo:
    

	if (variable == NULL) {

	return;

	}

**Archivos:**

-   Los archivos de código deben terminar en extensión .c
    

-   Seguir usando la estructura snake_case.
    

-   El archivo de código deberá llevar un encabezado donde se ponga el nombre del equipo, integrantes, objetivo del programa y el compilador.
    

-   Aplicar función main() para código principal.
    

**Bibliotecas:**

-   Incluir todas las bibliotecas a usar al inicio del programa.
    

-   De preferencia, especificar a través de comentarios para que se usará dicha biblioteca.
    

**Uso de comentarios:**

-   Utilizar “/* ... */” para realizar comentarios dentro del código.
    

-   En caso de realizar modificaciones a la parte de alguien más, especificar a través de un comentario que cambios se realizó para evitar confusiones.
    

-   Documentar de preferencia la mayoría de las líneas de código para que los demás puedan ver que se está haciendo.
    

-   Incluir al inicio del archivo, un comentario de cabecera con los datos necesarios del equipo y del programa.
    


Como equipo, hemos considerado usar estas reglas debido a que, en nuestra opinión, son prácticas y eficientes en términos de legibilidad del código, de igual manera es practico para poder dar mantenimiento al código. Además, retomando lo que se mencionó antes, los cambios hacia el código ANSI-C que se realizaron, fueron para una mejor comprensión por parte del equipo.
