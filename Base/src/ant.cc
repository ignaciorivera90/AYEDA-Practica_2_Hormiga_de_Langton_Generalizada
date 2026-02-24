#include "ant.h"
#include "tape.h"
#include <stdexcept>

char Ant::Symbol() const {
  switch (dir_) {
    case Direction::Up: return '^';
    case Direction::Right: return '>';
    case Direction::Down: return 'v';
    case Direction::Left: return '<';
  }
  return '?';
}

void Ant::TurnRight() {
  dir_ = static_cast<Direction>((static_cast<int>(dir_) + 1) % 4);
}

void Ant::TurnLeft() {
  dir_ = static_cast<Direction>((static_cast<int>(dir_) + 3) % 4);
}

void Ant::MoveForward(const Tape& tape) {
  int nx = x_, ny = y_;
  switch (dir_) {
    case Direction::Up:    ny--; break;
    case Direction::Right: nx++; break;
    case Direction::Down:  ny++; break;
    case Direction::Left:  nx--; break;
  }
  if (!tape.InBounds(nx, ny)) {
    throw std::out_of_range("Ant moved out of bounds");
  }
  x_ = nx;
  y_ = ny;
}