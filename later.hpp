#ifndef LATER_HPP									// Sentinel (Wächter)
#define LATER_HPP 

#include <functional>
#include <chrono>
#include <future>

class Later {
  public:
    template <class callable, class... arguments>
    Later(int after, bool async, callable&& f, arguments&&... args) {
      std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f),
            std::forward<arguments>(args)...));

      if (async) {
        std::thread([after, task]() {
          std::this_thread::sleep_for(std::chrono::milliseconds(after));
          task();
        }).detach();
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(after));
        task();
      }
    }
};

#endif
