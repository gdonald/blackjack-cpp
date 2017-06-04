#include "BufferToggle.h"
#include "Game.h"
using namespace std;

int main(int argc, char* argv[])
{
	srand(unsigned(time(0)));
	BufferToggle bt;
	int run = 0;

	bt.off();
	run = (new Game())->run();
	bt.on();

	return run;
}
