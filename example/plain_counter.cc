#include "plain_counter.h"

#include <chrono>
#include <iostream>
#include <thread>

void PlainCounter::up(int amount, Color color) {
  std::cout << color << "Counting ...";
  for (int i = 0; i < amount; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ++value_;
    std::cout << " " << value_ << std::flush;
  }
  std::cout << Color::None << "\n";
}

void PlainCounter::down(int amount, Color color) {
  std::cout << color << "Counting ...";
  for (int i = 0; i < amount; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    --value_;
    std::cout << " " << value_ << std::flush;
  }
  std::cout << Color::None << "\n";
}
