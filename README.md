# Irriapps - Runoff

Cálculo del coeficiente de escurrimiento para cuencas en estudio donde existen
diferentes tipos y usos de suelo, de acuerdo a la metodología de la norma
mexicana NOM-011-CONAGUA-2015. La cuenca se subdivide en zonas homogéneas para
calcular apropiadamente el coeficiente de escurrimiento.

## Características

Programa para calcular el coeficiente de escurrimiento con:

 * Método estándar (NOM-011-CONAGUA-2015)
 * Interfaz gráfica para agregar fácilmente áreas de características homogéneas
 * Programación en Qt5 y C++
 * Multiplataforma
 * Software Libre

## Tutorial de uso

### Instalación

Por el momento el programa se puede ejecutar directamente sin la necesidad de
instalarse, en Windows únicamente hay que usar el archivo ejecutable (.exe)
en macOS basta ejecutar el archivo app.

Para otros sistemas como GNU/Linux no se proporcionan binarios, para ejecutar el
programa es necesario compilar el código fuente usando Qt5.

### Entrada de datos

La entrada de los datos requeridos para calcular el coeficiente de escurrimiento
se realiza directamente en la ventana de la aplicación.

Las zonas con características homogéneas de la cuenca se pueden agregar (o
eliminar) de la siguiente manera:

 * **Agregar** sub área: Desde el menú Herramientas o en la barra de
   herramientas usar el comando **Agregar**
 * **Eliminar** sub área: Desde el menú Herramientas o en la barra de
   herramientas usar el comando **Eliminar**

## Licencia

Cálculo del coeficiente de escurrimiento de acuerdo a la norma oficial
mexicana NOM-011-CONAGUA-2015, Conservación del recurso agua.
Copyright (C) 2017 Eduardo Jiménez

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
59Temple Place, Suite 330, Boston, MA 02111-1307 USA
