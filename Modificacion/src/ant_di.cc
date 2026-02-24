/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Practica 2: Hormiga de Langton Generalizada
 *
 * Autor: Ignacio Andres Rivera Barrientos
 * Correo: alu0101675053@ull.edu.es
 * Fecha: 22/02/2026
 *
 * Archivo: ant_di.cc
 * Descripcion: Implementacion del comportamiento especifico de la
 *              hormiga con regla "DI".
 * Referencias:
 *   - Enunciado oficial de la practica 2.
 *   - Documentacion de C++ (std::vector, std::string, etc.).
 *
 * Historial de revisiones:
 *   22/02/2026 - Creacion inicial de la practica 2.
 */

#include "ant_di.h"
#include "tape.h"



/**
 * @brief Executes one simulation step for the DDID rule.
 * 
 * Rule:
 *  Color 0 -> Turn Right
 *  Color 1 -> Turn Left
 *
 * Then the cell color is updated cyclically and the ant moves forward.
 */
void Ant_DI::Step(Tape& tape) {
  uint8_t c = tape.GetColor(x_, y_);  // 0..1

  if (c == 0) TurnRight();  // D
  else        TurnLeft();   // I

  tape.SetColor(x_, y_, tape.NextColor(c));
  MoveForward(tape);
}