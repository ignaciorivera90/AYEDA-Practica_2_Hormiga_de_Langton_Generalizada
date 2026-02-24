#pragma once
#include <vector>
#include <string>
#include "tape.h"
#include "ant.h"

class Simulator {
 public:
  explicit Simulator(const std::string& input_file);
  ~Simulator();

  Simulator(const Simulator&) = delete;
  Simulator& operator=(const Simulator&) = delete;

  void Run();  // <- ahora menú interactivo

 private:
  void LoadFromFile(const std::string& input_file);
  void SaveToFile(const std::string& output_file) const;

  Ant* Factory(const std::string& type, int x, int y, Direction dir, const char* ansi);  void StepAll();
  void Print() const;

  // menú / UI
  void MenuLoop();
  void ClearScreen() const;
  void PressAnyKey() const;
  int  AskInt(const std::string& msg, int minv, int maxv) const;
  std::string AskString(const std::string& msg) const;

  static Direction ParseDir(char c);

  // colores para celdas (background)
  const char* BgForCell(int color) const;

  Tape tape_;
  std::vector<Ant*> ants_;
  long long steps_done_{0};
  bool AskYesNo(const std::string& msg) const;
};
