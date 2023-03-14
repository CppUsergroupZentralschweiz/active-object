#include "ao_counter.h"
#include "plain_counter.h"

#include <ao/scheduler.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

void plain() {
  PlainCounter counter{};

  std::thread worker1{[&counter] {
    counter.up(23, Color::Red);
    counter.down(11, Color::Yellow);
    counter.up(13, Color::Red);
    counter.down(25, Color::Yellow);
  }};
  std::thread worker2{[&counter] {
    counter.up(42, Color::Green);
    counter.down(17, Color::Cyan);
    counter.down(13, Color::Green);
    counter.down(12, Color::Cyan);
  }};

  worker1.join();
  worker2.join();

  std::cout << "\n"
            << "Final: " << counter.value() << "\n";
}

void active_object() {
  auto scheduler = std::make_shared<Scheduler>();
  AoCounter counter{scheduler};

  scheduler->start();

  std::thread worker1{[&counter] {
    counter.up(23, Color::Red);
    counter.down(11, Color::Yellow);
    counter.up(13, Color::Red);
    counter.down(25, Color::Yellow);
  }};
  std::thread worker2{[&counter] {
    counter.up(42, Color::Green);
    counter.down(17, Color::Cyan);
    counter.down(13, Color::Green);
    counter.down(12, Color::Cyan);
  }};

  worker1.join();
  worker2.join();

  auto final = counter.value().get();

  std::cout << "\n"
            << "Final: " << final << "\n";

  scheduler->stop();
}

int main() {
  std::cout << Color::Blue << "=== Plain ==="
            << "\n\n";

  plain();

  std::cout << "\n"
            << Color::Blue << "=== Active Object ==="
            << "\n\n";

  active_object();

  std::cout << "\n";
}
