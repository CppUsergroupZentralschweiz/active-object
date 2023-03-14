#pragma once

#include <ostream>

enum class Color { Red, Green, Yellow, Blue, Magenta, Cyan, None };

std::ostream &operator<<(std::ostream &os, Color color);
