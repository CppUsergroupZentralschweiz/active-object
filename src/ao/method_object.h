#pragma once

#include "method.h"
#include "scheduler.h"

#include <concepts>
#include <future>

template <typename T> class MethodObject : public Method {
public:
  MethodObject(std::promise<T> &&promise, std::invocable auto call)
      : promise_{std::move(promise)}, call_{call} {}

  void call() override { promise_.set_value(call_()); }

  std::future<T> static enqueue(std::shared_ptr<Scheduler> scheduler,
                                std::invocable auto call) {
    std::promise<T> promise{};
    auto future = promise.get_future();

    scheduler->enqueue(
        std::make_unique<MethodObject<T>>(std::move(promise), call));

    return future;
  }

private:
  std::promise<T> promise_;
  std::function<T()> call_;
};

template <> inline void MethodObject<void>::call() {
  call_();
  promise_.set_value();
}
