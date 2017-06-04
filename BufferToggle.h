#ifndef BUFFERTOGGLE_H_
#define BUFFERTOGGLE_H_

#include <termios.h>
#include <unistd.h>

namespace std
{
	class BufferToggle
	{
		public:
			BufferToggle();
			virtual ~BufferToggle();
			void on(void);
			void off(void);

		private:
			struct termios t;
	};
}

#endif
