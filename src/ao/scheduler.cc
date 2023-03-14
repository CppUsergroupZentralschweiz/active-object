#include "scheduler.h"

#include <concepts>
#include <memory>

Scheduler::~Scheduler() { stop(); }

void Scheduler::enqueue(std::unique_ptr<Method> &&method) {
  std::unique_lock<std::mutex> lock{mutex_};
  queue_.push_front(std::move(method));
  cv_.notify_one();
}

void Scheduler::start() {
  activation_ = std::thread([this] { run(); });
}

void Scheduler::stop() {
  enqueue({});
  if (activation_.joinable()) {
    activation_.join();
  }
}

void Scheduler::run() {
  for (;;) {
    auto method = dequeue();
    if (not method) {
      break;
    }
    method->call();
  }
}

std::unique_ptr<Method> Scheduler::dequeue() {
  std::unique_lock<std::mutex> lock(mutex_);
  cv_.wait(lock, [this] { return not queue_.empty(); });

  auto method = std::move(queue_.back());
  queue_.pop_back();

  return method;
}
