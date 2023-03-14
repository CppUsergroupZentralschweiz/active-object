#pragma once

#include "method.h"

#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <thread>

class Scheduler {
public:
  ~Scheduler();

  void enqueue(std::unique_ptr<Method> &&method);

  void start();
  void stop();

private:
  void run();

  std::unique_ptr<Method> dequeue();

  std::deque<std::unique_ptr<Method>> queue_{};
  std::mutex mutex_{};
  std::condition_variable cv_;

  std::thread activation_{};
};
