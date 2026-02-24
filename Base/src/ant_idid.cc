#include "ant_idid.h"
#include "tape.h"

void Ant_IDID::Step(Tape& tape) {
  uint8_t c = tape.GetColor(x_, y_);  // 0..3

  if (c == 0)      TurnLeft();  // I
  else if (c == 1) TurnRight(); // D
  else if (c == 2) TurnLeft();  // I
  else             TurnRight(); // D

  tape.SetColor(x_, y_, tape.NextColor(c));
  MoveForward(tape);
}