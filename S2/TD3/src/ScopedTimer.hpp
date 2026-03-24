#pragma once

#include <chrono>
#include <functional>
#include <iostream>

static inline void display_elapsed(std::string const &name,
                                   double const duration_us) {
  double const ms{duration_us * 0.001};
  std::cout << name << " : " << duration_us << "us (" << ms << "ms)"
            << std::endl;
}

template <typename Period = std::micro> class ScopedTimer {
  using Clock = std::chrono::steady_clock;

public:
  ScopedTimer() : ScopedTimer("unnamed") {}

  ScopedTimer(const std::string name) : ScopedTimer(name, display_elapsed) {}

  ScopedTimer(const std::string name,
              std::function<void(std::string const &, double const &)> callback)
      : _last(Clock::now()), _callback(callback), _name(name) {}

  ~ScopedTimer() { _callback(_name, elapsed()); }

  void reset() { _last = Clock::now(); }

  double elapsed() const {
    return std::chrono::duration<double, Period>(Clock::now() - _last).count();
  }

private:
  std::chrono::time_point<Clock> _last;
  std::function<void(std::string const &, double const &)> _callback;
  std::string _name;
};
