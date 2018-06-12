# Trabajo Práctico 4: Worms
## Materia: Taller de Programación I
## Docente asignado: Matías Lafroce
### Alumnos:
* Joaquín Casal
* Tomás Accini

## Introducción
El presente trabajo práctico busca replicar el famoso juego multijugador Worms, en el cual cada jugador tiene un ejército de gusanos con diferentes armas, y el objetivo es eliminar a todos soldados los del equipo enemigo. El proyecto incluye un servidor multithreading que se comunica con los clientes a través de sockets TCP, desarrollado en C++, utilizando la librería Box2D para las simulaciones físicas; clientes con parte gráfica realizada en SDL y QT; y un editor de mapas en los cuales se desarrollarán las partidas, también hecho en QT. Un usuario podrá crear mapas a través del editor, que luego serán guardados en formato YAML. El servidor recibe por parámetro el mapa a utilizar y la cantidad de jugadores que espera conectar. Una vez se conectan los jugadores indicados, comienza el juego con un sistema de turnos. El juego finaliza cuando queda un solo jugador vivo.

## Instrucciones de uso
1. Clonar el repositorio
2. Instalar cxxtest con el comando `sudo apt install cxxtest`
3. Instalar SDL con el comando `sudo apt install libsdl2-dev`
4. Instalar SDL con el comando `sudo apt install libsdl2-image-dev`
5. Ingresar a worms/src/tests, y ejecutar el comando `cxxtestgen --error-printer -o tests.cpp MyTestSuite.h`
6. Volver a la carpeta worms/. Crear la carpeta build. Ingresar a dicha carpeta.
7. Abrir la terminal e ingresar los comandos
  `$ cmake.. && make && ./src/tests/tests`
   Si todo fue instalado correctamente, debe correr los tests y mostrar el mensaje OK al final.
8. Ingresar a la carpeta build/src.
9. En una consola abrir el servidor con el comando
  `$ ./server_executable [port] [number-of-players]`

  * NOTA1: Para le entrega agregar que el server reciba el scenario_path para levantarlo. Ahora está hardcodeado el path a ../scenarios/scenario.yaml, donde debe haber un escenario con ese nombre para que funcione.
  * NOTA2: Actualmente los escenarios estan en el directorio worms/src/scenarios. Copiar y pegar esa carpeta en build/src para que funcione  directamente.
10. En otras consolas ingresar los clientes con el comando
  `$ ./client_executable [port]`


#### Teclas para jugar
* a-> mover a la izquierda.
* d-> mover a la derecha.
* s-> dejar de moverse.
* w-> saltar hacia adelante.
* r-> saltar hacia atrás.
* 7-> activa dinamita
* 8-> activa teledirigido (además hay que ingresar una coordenada x, luego la y)
* 9-> activa teletransportación (además hay que ingresar una coordenada x, luego la y)
* q-> cerrar el juego (tanto cliente como servidor)

## Links útiles
* Informe: https://docs.google.com/document/d/1z8gO7SBtF2PPZrYFyjVvekyE1n3bp_KuHaufdjVa_4s/edit?usp=sharing
