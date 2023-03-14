#pragma once

struct Method {
  virtual void call() = 0;
  virtual ~Method() = default;
};
