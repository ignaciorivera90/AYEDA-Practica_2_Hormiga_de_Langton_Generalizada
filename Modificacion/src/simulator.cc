/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Practica 2: Hormiga de Langton Generalizada
 *
 * Autor: Ignacio Andres Rivera Barrientos
 * Correo: alu0101675053@ull.edu.es
 * Fecha: 22/02/2026
 *
 * Archivo: simulator.cc
 * Descripcion: Implementacion del motor principal de la simulacion,
 *              incluyendo menu, ejecucion paso a paso y gestion de eventos.
 * Referencias:
 *   - Enunciado oficial de la practica 2.
 *   - Documentacion de C++ (std::vector, std::string, etc.).
 *
 * Historial de revisiones:
 *   22/02/2026 - Creacion inicial de la practica 2.
 */

#include "simulator.h"
#include "colors.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <cctype>

// hormigas concretas
#include "ant_di.h"
#include "ant_ddid.h"
#include "ant_ddii.h"
#include "ant_idid.h"
#include "ant_ddid_inv.h"



/**
 * @brief Builds a simulation reading the initial state from a file.
 * @param input_file Input file path.
 * @throws std::runtime_error if the file cannot be opened or the format is invalid.
 */
Simulator::Simulator(const std::string& input_file) {
  LoadFromFile(input_file);
}



/**
 * @brief Destroys the simulator and releases all dynamically allocated ants.
 *
 * This class stores ants as raw pointers (Ant*), so it is responsible
 * for deleting them to avoid memory leaks.
 */
Simulator::~Simulator() {
  for (Ant* a : ants_) delete a;
  ants_.clear();
}



/**
 * @brief Converts an orientation character into a Direction enum.
 * @param c Orientation character ('^', 'v', '<', '>').
 * @return Parsed Direction.
 * @throws std::runtime_error if the character is not valid.
 */
Direction Simulator::ParseDir(char c) {
  switch (c) {
    case '^': return Direction::Up;
    case '>': return Direction::Right;
    case 'v': return Direction::Down;
    case '<': return Direction::Left;
    default: throw std::runtime_error("Invalid orientation char (use ^ > v <)");
  }
}



/**
 * @brief Converts an orientation character into a Direction enum.
 * @param c Orientation character ('^', 'v', '<', '>').
 * @return Parsed Direction.
 * @throws std::runtime_error if the character is not valid.
 */
Ant* Simulator::Factory(const std::string& type, int x, int y, Direction dir, const char* ansi) {
  if (type == "DI")   return new Ant_DI(x, y, dir, ansi);
  if (type == "DDID") return new Ant_DDID(x, y, dir, ansi);
  if (type == "DDII") return new Ant_DDII(x, y, dir, ansi);
  if (type == "IDID") return new Ant_IDID(x, y, dir, ansi);
  if (type == "DDIDr") return new Ant_DDID_INV(x, y, dir, ansi);
  throw std::runtime_error("Unknown ant type: " + type);
}



/**
 * @brief Loads the simulation state from a file.
 * @param input_file Path to input file.
 * @throws std::runtime_error if file format is invalid.
 *
 * Expected format:
 *  Line 1: size_x size_y num_colors
 *  Line 2: TYPE x y ORIENT ; TYPE x y ORIENT ; ...
 *  Line 3..n: x y color
 */
void Simulator::LoadFromFile(const std::string& input_file) {
  std::ifstream in(input_file);
  if (!in) throw std::runtime_error("Cannot open input file: " + input_file);

  std::string line;

  // Linea 1: sizeX sizeY numColors
  if (!std::getline(in, line)) throw std::runtime_error("Missing line 1");
  {
    std::istringstream iss(line);
    int sx, sy, ncolors;
    if (!(iss >> sx >> sy >> ncolors)) throw std::runtime_error("Bad line 1 format");
    tape_ = Tape(sx, sy, ncolors);
  }

  // Linea 2: TIPO x y ORIENT ; TIPO x y ORIENT ; ...
  if (!std::getline(in, line)) throw std::runtime_error("Missing line 2");
  {
    // colores de texto por hormiga
    const char* palette[] = { YELLOW };
    int palette_i = 0;

    std::istringstream all(line);
    std::string token;
    while (std::getline(all, token, ';')) {
      std::istringstream iss(token);
      std::string type;
      int x, y;
      char orient;
      if (!(iss >> type >> x >> y >> orient)) continue;

      if (!tape_.InBounds(x, y)) throw std::runtime_error("Ant out of bounds in input");

      const char* ansi = palette[palette_i % (sizeof(palette) / sizeof(palette[0]))];
      palette_i++;

      ants_.push_back(Factory(type, x, y, ParseDir(orient), ansi));
    }
    if (ants_.empty()) throw std::runtime_error("No ants defined in line 2");
  }

  // Lineas 3..: x y color (solo celdas != 0 normalmente)
  while (std::getline(in, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    int x, y, col;
    if (!(iss >> x >> y >> col)) continue;
    if (!tape_.InBounds(x, y)) throw std::runtime_error("Cell out of bounds in input");
    if (col < 0 || col >= tape_.num_colors()) throw std::runtime_error("Cell color out of range");
    tape_.SetColor(x, y, static_cast<uint8_t>(col));
  }
}



/**
 * @brief Creates an ant instance depending on the rule type string.
 * @param type Ant rule identifier (e.g., "DI", "DDID", "DDII", "IDID").
 * @param x Initial x position.
 * @param y Initial y position.
 * @param dir Initial direction.
 * @param ansi ANSI color code used to print the ant.
 * @return Pointer to a dynamically allocated ant (caller owns it).
 * @throws std::runtime_error if the type is unknown.
 */
const char* Simulator::BgForCell(int color) const {
  // mapa simple de fondos; si num_colors > 8, reusa
  switch (color % 8) {
    case 0: return BG_WHITE;  
    case 1: return BG_BLACK;
    case 2: return BG_GREEN;
    case 3: return BG_YELLOW;
    case 4: return BG_BLUE;
    case 5: return BG_MAGENTA;
    case 6: return BG_CYAN;
    case 7: return BG_WHITE;
  }
  return BG_WHITE;
}



/**
 * @brief Prints the current world state on screen.
 * Shows:
 *  - Cell colors as background.
 *  - Ants as yellow arrows.
 *  - '*' if multiple ants share a cell.
 */
void Simulator::Print() const {
  // conteo hormigas y referencia primera
  std::vector<std::vector<int>> count(tape_.size_y(), std::vector<int>(tape_.size_x(), 0));
  std::vector<std::vector<const Ant*>> first(tape_.size_y(), std::vector<const Ant*>(tape_.size_x(), nullptr));

  for (const Ant* a : ants_) {
    if (!tape_.InBounds(a->x(), a->y())) continue;
    int& c = count[a->y()][a->x()];
    c++;
    if (c == 1) first[a->y()][a->x()] = a;
  }

  std::cout << GRAY << "Steps: " << steps_done_ << RESET << "\n\n";

  for (int y = 0; y < tape_.size_y(); ++y) {
    for (int x = 0; x < tape_.size_x(); ++x) {
      int cell = tape_.GetColor(x, y);
      const char* bg = BgForCell(cell);

      if (count[y][x] >= 2) {
        // colisión
        std::cout << bg << WHITE << "* " << RESET;
      } else if (count[y][x] == 1) {
        const Ant* a = first[y][x];
        std::cout << bg << a->color() << a->Symbol() << ' ' << RESET;
      } else {
        // celda sin hormiga: imprimimos dos espacios "coloreados"
        // (si quieres mostrar el número, cambia "  " por (digit + ' '))
        std::cout << bg << "  " << RESET;
      }
    }
    std::cout << "\n";
  }

  std::cout << "\n" << GRAY
            << "Legend: cell colors shown as background, ants as arrows, collision='*'"
            << RESET << "\n";
}



/**
 * @brief Executes one step for all ants in the simulation.
 * @throws std::out_of_range if any ant leaves the board.
 */
void Simulator::StepAll() {
  for (Ant* a : ants_) {
    a->Step(tape_);
  }
  steps_done_++;
}



/**
 * @brief Clears the terminal screen.
 *
 * Uses "cls" on Windows and "clear" on Unix-like systems.
 */
void Simulator::ClearScreen() const {
  // Igual que práctica 1 (portable básico)
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}



/**
 * @brief Clears the terminal screen.
 *
 * Uses "cls" on Windows and "clear" on Unix-like systems.
 */
void Simulator::PressAnyKey() const {
  std::cout << GRAY << "Press ENTER to continue..." << RESET;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}



/**
 * @brief Reads an integer from standard input within a range.
 * @param msg Prompt message.
 * @param minv Minimum allowed value.
 * @param maxv Maximum allowed value.
 * @return Valid integer in [minv, maxv].
 */
int Simulator::AskInt(const std::string& msg, int minv, int maxv) const {
  while (true) {
    std::cout << msg;
    int v;
    if (std::cin >> v && v >= minv && v <= maxv) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return v;
    }
    std::cout << RED << "Invalid number.\n" << RESET;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}



/**
 * @brief Reads a full line from standard input.
 * @param msg Prompt message.
 * @return The read line (may be empty).
 */
std::string Simulator::AskString(const std::string& msg) const {
  std::cout << msg;
  std::string s;
  std::getline(std::cin, s);
  if (s.empty()) std::getline(std::cin, s);
  return s;
}



/**
 * @brief Saves the current simulation state to a file.
 * @param output_file Path to output file.
 */
void Simulator::SaveToFile(const std::string& output_file) const {
  std::ofstream out(output_file);
  if (!out) throw std::runtime_error("Cannot open output file: " + output_file);

  out << tape_.size_x() << ' ' << tape_.size_y() << ' ' << tape_.num_colors() << "\n";

  for (size_t i = 0; i < ants_.size(); ++i) {
    const Ant* a = ants_[i];
    out << a->type() << ' ' << a->x() << ' ' << a->y() << ' ' << a->Symbol();
    if (i + 1 != ants_.size()) out << " ; ";
  }
  out << "\n";

  for (int y = 0; y < tape_.size_y(); ++y) {
    for (int x = 0; x < tape_.size_x(); ++x) {
      int cell = tape_.GetColor(x, y);
      if (cell != 0) out << x << ' ' << y << ' ' << cell << "\n";
    }
  }
}



/**
 * @brief Main interactive menu loop.
 * Handles user options:
 *  1) Show state
 *  2) Step by step execution
 *  3) Execute N steps
 *  4) Save state
 *  0) Exit
 */
void Simulator::MenuLoop() {
  while (true) {
    ClearScreen();

    std::cout << "\n===== Hormiga de Langton =====\n";
    std::cout << "1) Mostrar estado actual del mundo\n";
    std::cout << "2) Mostrar recorrido paso a paso (ENTER / q)\n";
    std::cout << "3) Ejecutar n pasos\n";
    std::cout << "4) Guardar estado\n";
    std::cout << "0) Salir\n";
    std::cout << "==================================\n";

    int op = ReadInt("Introduce un numero > ");
    ClearScreen();

    if (op == 1) {
      Print();
      std::cout << "\nPulsa ENTER para continuar...";
      std::string dummy;
      std::getline(std::cin, dummy);
      continue;
    }

    if (op == 2) {
      while (true) {
        ClearScreen();
        Print();
        std::cout << "\nPulsa ENTER para el siguiente paso, o 'q' + ENTER para volver al menu: ";
        int action = ReadUserActionStep();

        if (action == 1) {  // q
          break;
        } else if (action == 2) {  // ENTER
          try {
            StepAll();
          } catch (const std::out_of_range&) {
            MarkFinished();
          }
        } else {
          ClearScreen();
          std::cout << "Opcion no valida.\n";
          std::cout << "Pulsa ENTER para continuar...";
          std::string dummy;
          std::getline(std::cin, dummy);
          continue;
        }

        if (Finished()) {
          ClearScreen();
          Print();
          std::cout << "\n[FIN] Simulacion terminada.\n";

          if (AskYesNo("¿Deseas guardar el estado final?")) {
            std::string out = ReadLine("Fichero de salida: ");
            if (!out.empty()) SaveToFile(out);
          }

          std::cout << "Pulsa ENTER para salir...";
          std::string dummy;
          std::getline(std::cin, dummy);
          return;
        }
      }
      continue;
    }

    if (op == 3) {
      unsigned long n = ReadULong("N pasos: ");

      for (unsigned long i = 0; i < n && !Finished(); ++i) {
        try {
          StepAll();
        } catch (const std::out_of_range&) {
          MarkFinished();
        }
      }

      if (Finished()) {
        ClearScreen();
        Print();
        std::cout << "\n[FIN] Simulacion terminada.\n";

        if (AskYesNo("¿Deseas guardar el estado final?")) {
          std::string out = ReadLine("Fichero de salida: ");
          if (!out.empty()) SaveToFile(out);
        }

        std::cout << "Pulsa ENTER para salir...";
        std::string dummy;
        std::getline(std::cin, dummy);
        return;
      }

      // tras N pasos, mostrar donde quedó y volver al menú
      ClearScreen();
      Print();
      std::cout << "\nPulsa ENTER para continuar y volver al menu...";
      std::string dummy;
      std::getline(std::cin, dummy);
      continue;
    }

    if (op == 4) {
      ClearScreen();
      Print();
      std::string out = ReadLine("\nFichero de salida: ");

      if (out.empty()) {
        std::cout << "Nombre vacio. No se guarda.\n";
      } else {
        SaveToFile(out);
        std::cout << "Estado guardado en '" << out << "'\n";
      }

      std::cout << "Pulsa ENTER para volver al menu...";
      std::string dummy;
      std::getline(std::cin, dummy);
      continue;
    }

    if (op == 0) {
      ClearScreen();
      Print();

      if (AskYesNo("\n¿Deseas guardar el estado final antes de salir?")) {
        std::string out = ReadLine("Fichero de salida: ");
        if (!out.empty()) {
          SaveToFile(out);
          std::cout << "Estado guardado en '" << out << "'\n";
        }
      }

      std::cout << "Pulsa ENTER para salir...";
      std::string dummy;
      std::getline(std::cin, dummy);
      return;
    }

    ClearScreen();
    Print();
    std::cout << "\nOpcion no valida.\n";
    std::cout << "Pulsa ENTER para continuar...";
    std::string dummy;
    std::getline(std::cin, dummy);
  }
}



/**
 * @brief Reads a full line from standard input.
 * @param msg Prompt message.
 * @return The read line (may be empty).
 */
void Simulator::Run() {
  finished_ = false;
  MenuLoop();
}



/**
 * @brief Reads an integer from standard input using a full line.
 * @param msg Prompt message.
 * @return Parsed integer.
 *
 * This method keeps asking until a valid integer is provided.
 */int Simulator::ReadInt(const std::string& msg) const {
  while (true) {
    std::cout << msg;
    std::string line;
    std::getline(std::cin, line);
    if (line.empty()) continue;

    std::istringstream iss(line);
    int v;
    if (iss >> v) return v;

    std::cout << RED << "Entrada no valida.\n" << RESET;
  }
}



/**
 * @brief Reads an unsigned long integer from standard input using a full line.
 * @param msg Prompt message.
 * @return Parsed unsigned long value.
 */
unsigned long Simulator::ReadULong(const std::string& msg) const {
  while (true) {
    std::cout << msg;
    std::string line;
    std::getline(std::cin, line);
    if (line.empty()) continue;

    std::istringstream iss(line);
    unsigned long v;
    if (iss >> v) return v;

    std::cout << RED << "Entrada no valida.\n" << RESET;
  }
}



/**
 * @brief Reads a complete line from standard input.
 * @param msg Prompt message.
 * @return The line read from the user.
 */
std::string Simulator::ReadLine(const std::string& msg) const {
  std::cout << msg;
  std::string s;
  std::getline(std::cin, s);
  return s;
}



/**
 * @brief Reads the user action in step-by-step mode.
 * @return 2 if user pressed only ENTER, 1 if user typed 'q' + ENTER, 0 otherwise.
 */
int Simulator::ReadUserActionStep() const {
  std::string line;
  std::getline(std::cin, line);

  if (line.empty()) return 2; // solo ENTER
  if (line.size() == 1 && (line[0] == 'q' || line[0] == 'Q')) return 1;
  return 0;
}



/**
 * @brief Asks the user a yes/no question.
 * @param msg Prompt message (without "(s/n)").
 * @return true if user answers 's'/'S', false if user answers 'n'/'N'.
 */
bool Simulator::AskYesNo(const std::string& msg) const {
  while (true) {
    std::cout << msg << " (s/n): ";
    std::string line;
    std::getline(std::cin, line);
    if (line.empty()) continue;
    char c = line[0];
    if (c == 's' || c == 'S') return true;
    if (c == 'n' || c == 'N') return false;
    std::cout << RED << "Respuesta no valida.\n" << RESET;
  }
}