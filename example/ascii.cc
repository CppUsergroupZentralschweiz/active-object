#include "ascii.h"

std::ostream &operator<<(std::ostream &os, Color color) {
  switch (color) {
  case Color::Red:
    os << "\033[91m";
    break;
  case Color::Green:
    os << "\033[92m";
    break;
  case Color::Yellow:
    os << "\033[93m";
    break;
  case Color::Blue:
    os << "\033[94m";
    break;
  case Color::Magenta:
    os << "\033[95m";
    break;
  case Color::Cyan:
    os << "\033[96m";
    break;
  case Color::None:
    os << "\033[m";
    break;
  }
  return os;
}
