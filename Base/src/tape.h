#pragma once
#include <vector>
#include <cstdint>

class Tape {
 public:
  Tape() = default;
  Tape(int sx, int sy, int num_colors);

  bool InBounds(int x, int y) const;

  uint8_t GetColor(int x, int y) const;
  void SetColor(int x, int y, uint8_t c);

  uint8_t NextColor(uint8_t c) const;

  int size_x() const { return size_x_; }
  int size_y() const { return size_y_; }
  int num_colors() const { return num_colors_; }

 private:
  int size_x_{0};
  int size_y_{0};
  int num_colors_{2};
  std::vector<std::vector<uint8_t>> world_;
};