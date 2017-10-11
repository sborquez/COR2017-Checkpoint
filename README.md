# COR2017-Checkpoint

Cada año la Universidad Técnica Federico Santa María, celebra la _Robotics Week_, uno de sus eventos es la denominda [Competencia Robotica - UTFSM](http://www.competenciarobotica.cl/2017/)
donde se invita a estudiantes de diferentes partes del país y fuera de este a participar en la construcción de robots para completar diferentes desafíos.

## Checkpoint

### El problema 

Una de las competencias es la categoría de velocidad:[Competencia robotica - velocidad](http://www.competenciarobotica.cl/2017/velocidad/).
Esta consiste en una carrera contra reloj para los robot en un circuito.

Se desea optimizar el proceso de toma de tiempos, automatizandolo y mostrando el tiempo obtenido de manera inmediata para los competidores.


### La solución

Se diseñó una línea de meta capáz de detectar el paso de los robots, esto se comunica a una Raspberry Pi encargada de **identificar**, **cronometrar**, **mostrar** y **guardar** los tiempos medidos para cada equipo. 

## Requisitos

1 Software
	1 Python 3
	2 PyGame
	3 WiringPy o GPIO

2 Hardware
	1 Rasberry Pi 3
	2 Lector de códigos de barra usb
	3 Sensores Barrera (2)
	4 ...

## Installation

* Instalar sistema operativo Raspbian
* Clonar repositorio
* Ejecutar _setup.sh_

## TODO

* Imagenes para background
* Guardar tiempos de los equipos
* Permitir comunicación con base de datos externa (ej: google sheets) (2018)
