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
3. Instalar SDL con el comando `sudo apt install libsdl2-dev && sudo apt install libsdl2-image-dev && sudo apt install libsdl2-ttf-dev`
4. Instalar QT5 con el comando `sudo apt install qt5-default`
5. Ingresar a worms/src/tests, y ejecutar el comando `cxxtestgen --error-printer -o tests.cpp MyTestSuite.h`
6. Volver a la carpeta worms/. Ejecutar el script compile.sh, indicando como parámetro el directorio en el que se quiere 
7. En una consola abrir el servidor con el comando
  `$ ./worms_server [port] [number-of-players] [scenario-filename]`
8. En otras consolas ingresar los clientes con el comando
  `$ ./worms_client [port]`


#### Teclas para jugar
* key_left-> mover a la izquierda.
* key_right-> mover a la derecha.
* key_down-> dejar de moverse.
* key_up-> saltar hacia adelante.
* space_bar-> saltar hacia atrás.
* d-> activa dinamita
* r-> activa teledirigido (además hay que ingresar una coordenada x, luego la y)
* t-> activa teletransportación (además hay que ingresar una coordenada x, luego la y)
* q-> cerrar el juego (tanto cliente como servidor)

## Links útiles
* Informe: https://docs.google.com/document/d/1z8gO7SBtF2PPZrYFyjVvekyE1n3bp_KuHaufdjVa_4s/edit?usp=sharing
