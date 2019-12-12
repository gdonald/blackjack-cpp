#include "BufferToggle.h"
#include "Game.h"

int main()
{
  BufferToggle bt;
  int run = 0;

  bt.off();
  run = (new Game())->run();
  bt.on();

  return run;
}
