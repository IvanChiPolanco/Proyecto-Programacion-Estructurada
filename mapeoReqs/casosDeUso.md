# Casos de Uso
Se elaboraron los casos de uso para cada funcionalidad, donde se describa el proceso y las rutas de acción alternativas.

-  **Nombre: Crear Personaje**
    

	Actor: Usuario

	Propósito: Crear y registrar el personaje del usuario usando cadena de caracteres.

	Flujo:
	1.  El programa mostrará un texto inicial solicitando el nombre del usuario.
    

	2.  El usuario ingresará su nombre.
    

	3.  El sistema guardará el nombre como una cadena de caracteres.
    

-   **Nombre: Crear Atributos Iniciales**
    

	Actor: Administrador

	Propósito: El programa definirá las variables iniciales para que el usuario pueda jugar (vida, ataque, defensa, nivel y 			experiencia).

	Precondición: Haber registrado el nombre de usuario.

	Flujo:

	1.  El sistema genera las variables iniciales para el jugador.
    

	2.  Las variables son asignadas al jugador tras haber ingresado su nombre.
    

-   **Nombre: Generar Enemigos**
    

	Actor: Administrador

	Propósito: El sistema genera enemigos con vida y ataques definidos a medida que el jugador vaya avanzando.

	Precondición: El usuario ya debe haber registrado sus nombres y saber sus estadísticas iniciales asignadas por el programa.

	Flujo:

	1.  El programa irá generando el nombre de enemigos aleatorios.
    

	2.  Se asignará las estadísticas iniciales del enemigo.
    

-   **Nombre: Desplegar Menú**
    

	Actor: Usuario

	Propósito: El programa desplegará un menú de opciones donde el jugador elegirá lo que desea hacer en el turno.

	Precondición: El enemigo generado ya se mostrará en el programa para que el jugador pueda interactuar.

	Flujo:

	1.  El programa mostrará los datos del enemigo.
    

	2.  El programa desplegará un menú básico de opciones a realizar (Atacar, usar objeto, defender).
    

	3.  El usuario escogerá lo que desea realizar en el turno
    

-   **Nombre: Calcular Daño**
    

	Actor: Administrador

	Propósito: El programa calculará el daño infringido del jugador o del enemigo y lo mostrará en pantalla.

	Precondición: Tras haber sido desplegado el menú, el usuario eligió atacar.

	Flujo:

	1.  El usuario escogió la opción “Atacar”
    

	2.  El programa restará la salud del enemigo con el ataque que recibió.
    

	3.  El enemigo también podrá atacar, restando la vida del jugador con el ataque recibido.
    

	4.  La información será desplegada en pantalla.
