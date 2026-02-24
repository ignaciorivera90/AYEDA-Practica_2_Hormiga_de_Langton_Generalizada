#pragma once
#include "ant.h"

class Ant_DI : public Ant {
 public:
  Ant_DI(int x, int y, Direction dir, const char* ansi_color)
      : Ant("DI", x, y, dir, ansi_color) {}

  void Step(Tape& tape) override;
};