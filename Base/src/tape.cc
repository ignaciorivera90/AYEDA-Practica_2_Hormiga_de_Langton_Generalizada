#include "tape.h"
#include <stdexcept>

Tape::Tape(int sx, int sy, int num_colors)
    : size_x_(sx), size_y_(sy), num_colors_(num_colors),
      world_(sy, std::vector<uint8_t>(sx, 0)) {
  if (sx <= 0 || sy <= 0) throw std::invalid_argument("Tape size must be > 0");
  if (num_colors < 2) throw std::invalid_argument("num_colors must be >= 2");
}

bool Tape::InBounds(int x, int y) const {
  return (x >= 0 && x < size_x_ && y >= 0 && y < size_y_);
}

uint8_t Tape::GetColor(int x, int y) const {
  return world_[y][x];
}

void Tape::SetColor(int x, int y, uint8_t c) {
  if (c >= static_cast<uint8_t>(num_colors_))
    throw std::out_of_range("Cell color out of range");
  world_[y][x] = c;
}

uint8_t Tape::NextColor(uint8_t c) const {
  return static_cast<uint8_t>((c + 1) % num_colors_);
}