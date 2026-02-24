#pragma once
#include "ant.h"

class Ant_IDID : public Ant {
 public:
  Ant_IDID(int x, int y, Direction dir, const char* ansi_color)
      : Ant("IDID", x, y, dir, ansi_color) {}

  void Step(Tape& tape) override;
};