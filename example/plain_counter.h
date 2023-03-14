#pragma once

#include "ascii.h"

class PlainCounter {
public:
  void up(int amount, Color color);
  void down(int amount, Color color);

  int value() const { return value_; }

private:
  int value_{0};
};
