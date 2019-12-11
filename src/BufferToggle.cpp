#include "BufferToggle.h"

BufferToggle::~BufferToggle() = default;

BufferToggle::BufferToggle() = default;

void BufferToggle::off() {
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void BufferToggle::on() {
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
