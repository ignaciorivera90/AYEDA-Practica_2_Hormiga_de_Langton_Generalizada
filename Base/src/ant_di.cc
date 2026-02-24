#include "ant_di.h"
#include "tape.h"

void Ant_DI::Step(Tape& tape) {
  uint8_t c = tape.GetColor(x_, y_);  // 0..1

  if (c == 0) TurnRight();  // D
  else        TurnLeft();   // I

  tape.SetColor(x_, y_, tape.NextColor(c));
  MoveForward(tape);
}