#pragma once
#include "ant.h"

class Ant_DDII : public Ant {
 public:
  Ant_DDII(int x, int y, Direction dir, const char* ansi_color)
      : Ant("DDII", x, y, dir, ansi_color) {}

  void Step(Tape& tape) override;
};