# Parcheesi

Implementación del juego de Parcheesi en C++ para la asignatura de Programación Avanzada.

## Como compilar

Primero generar el proyecto con premake:

premake5.exe vs2022

Luego abrir el archivo .sln que se genera en la carpeta build/ con Visual Studio y darle a compilar.

El ejecutable se genera en build/bin/Debug/ o build/bin/Release/ dependiendo de la configuración.

## Como ejecutar


build/bin/Debug/Parcheesi.exe


## Estructura del proyecto


include/     -> Todos los .h
src/         -> Todos los .cc
lib/         -> Las librerías estáticas que se generan
build/       -> Donde se compila todo
docs/        -> Doxyfile para generar documentación


## Librerías

Se generan 2 librerías estáticas en la carpeta lib/:
- JPlayer.lib -> La lógica del jugador
- JTable.lib -> La lógica de la mesa

## Documentación

Si tienes doxygen instalado:

doxygen docs/Doxyfile


Y te genera la documentación en HTML en docs/html/index.html
