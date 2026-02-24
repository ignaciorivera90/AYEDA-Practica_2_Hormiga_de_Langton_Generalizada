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
 * Archivo: ant_ddii.h
 * Descripcion: Declaracion de la clase Ant_DDII, hormiga con regla "DDII".
 * Referencias:
 *   - Enunciado oficial de la practica 2.
 *   - Documentacion de C++ (std::vector, std::string, etc.).
 *
 * Historial de revisiones:
 *   22/02/2026 - Creacion inicial de la practica 2.
 */

#pragma once
#include "ant.h"

class Ant_DDII : public Ant {
 public:
  Ant_DDII(int x, int y, Direction dir, const char* ansi_color)
      : Ant("DDII", x, y, dir, ansi_color) {}

  void Step(Tape& tape) override;
};