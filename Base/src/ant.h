#pragma once
#include <string>
#include <cstdint>

class Tape;

enum class Direction { Up, Right, Down, Left };

class Ant {
 public:
  Ant(std::string type, int x, int y, Direction dir, const char* ansi_color)
      : type_(std::move(type)), x_(x), y_(y), dir_(dir), ansi_color_(ansi_color) {}

  virtual ~Ant() = default;
  virtual void Step(Tape& tape) = 0;

  const std::string& type() const { return type_; }
  int x() const { return x_; }
  int y() const { return y_; }
  Direction dir() const { return dir_; }
  const char* color() const { return ansi_color_; }

  char Symbol() const;

 protected:
  void TurnRight();
  void TurnLeft();
  void MoveForward(const Tape& tape);

  std::string type_;
  int x_;
  int y_;
  Direction dir_;
  const char* ansi_color_;
};