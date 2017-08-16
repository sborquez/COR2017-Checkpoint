#ifndef __CHRONOMETER__
#define __CHRONOMETER__

#include <chrono>

class Chronometer {
public:
  Chronometer () { running = false; }
  ~Chronometer () {}

  void start();

  int stop();

  void update();

  int get_time();

  inline bool isrunning() { return running;}

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
  std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
  bool running;
  int elapsed_milliseconds;
};

#endif
