#pragma once

#include "ascii.h"

#include <future>

class Scheduler;

class AoCounter {
public:
  AoCounter(std::shared_ptr<Scheduler> scheduler) : scheduler_{scheduler} {}

  std::future<void> up(int amount, Color color);
  std::future<void> down(int amount, Color color);

  std::future<int> value() const;

private:
  void up_impl(int amount, Color color);
  void down_impl(int amount, Color color);
  int value_impl() const;

  int value_{};

  std::shared_ptr<Scheduler> scheduler_;
};
