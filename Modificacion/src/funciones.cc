/**
  * Universidad de La Laguna
  * Escuela Superior de Ingenieria y Tecnologia
  * Grado en Ingenieria Informatica
  * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
  * Curso: 2º
  * Practica 1:  Hormiga de Langton
  * Autor: Ignacio Andres Rivera Barrientos
  * Correo: alu0101675053@ull.edu.es
  * Fecha: 05/02/2026

  * Archivo funciones.cc: Implementacion de funciones utiles.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  */


#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "funciones.h"



/**
 * @brief function that waits for the user to press any key
 */
void pressanykey() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  std::cin.get(); 
}



/**
 * @brief function that waits for the user to press enter
 */
void pressEnter() {
  std::string dummy;
  std::getline(std::cin, dummy);  // espera hasta que el usuario pulse ENTER
}



/**
 * @brief function to clear the standard ouput
 */
void clrscr() {
  system("clear");
}

