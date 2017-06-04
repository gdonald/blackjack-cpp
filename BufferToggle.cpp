#include "BufferToggle.h"

namespace std
{
	void BufferToggle::off(void)
	{
		tcgetattr(STDIN_FILENO, &t);
		t.c_lflag &= ~ICANON;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}

	void BufferToggle::on(void)
	{
		tcgetattr(STDIN_FILENO, &t);
		t.c_lflag |= ICANON;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}

	BufferToggle::BufferToggle()
	{
	}

	BufferToggle::~BufferToggle()
	{
	}
}
