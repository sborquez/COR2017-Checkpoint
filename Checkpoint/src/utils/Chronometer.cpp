#include "../../include/utils/Chronometer.hpp"

void Chronometer::start()
{
    running = true;
    start_time = std::chrono::high_resolution_clock::now();
    update();
}

int Chronometer::stop()
{
    update();
    running = false;
    return elapsed_milliseconds;
}

void Chronometer::update()
{
  if (running) {
    end_time = std::chrono::high_resolution_clock::now();
    elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()
  }
}

int Chronometer::get_time()
{
  return elapsed_milliseconds;
}
