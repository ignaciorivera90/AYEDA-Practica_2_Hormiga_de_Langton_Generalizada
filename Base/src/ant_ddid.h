#pragma once
#include "ant.h"

class Ant_DDID : public Ant {
 public:
  Ant_DDID(int x, int y, Direction dir, const char* ansi_color)
      : Ant("DDID", x, y, dir, ansi_color) {}

  void Step(Tape& tape) override;
};