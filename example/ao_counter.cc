#include "ao_counter.h"

#include <ao/method_object.h>

#include <iostream>
#include <thread>

std::future<void> AoCounter::up(int amount, Color color) {
  return MethodObject<void>::enqueue(scheduler_,
                                     [=,this] { up_impl(amount, color); });
}

std::future<void> AoCounter::down(int amount, Color color) {
  return MethodObject<void>::enqueue(scheduler_,
                                     [=,this] { down_impl(amount, color); });
}

std::future<int> AoCounter::value() const {
  return MethodObject<int>::enqueue(scheduler_,
                                    [this] { return value_impl(); });
}

void AoCounter::up_impl(int amount, Color color) {
  std::cout << color << "Counting ...";
  for (int i = 0; i < amount; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ++value_;
    std::cout << " " << value_ << std::flush;
  }
  std::cout << Color::None << "\n";
}

void AoCounter::down_impl(int amount, Color color) {
  std::cout << color << "Counting ...";
  for (int i = 0; i < amount; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    --value_;
    std::cout << " " << value_ << std::flush;
  }
  std::cout << Color::None << "\n";
}

int AoCounter::value_impl() const { return value_; }
