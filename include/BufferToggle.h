#ifndef BUFFERTOGGLE_H
#define BUFFERTOGGLE_H

#include <termios.h>
#include <unistd.h>

class BufferToggle {
public:
  BufferToggle();

  virtual ~BufferToggle();

  void on();

  void off();

private:
  struct termios t{};
};

#endif
