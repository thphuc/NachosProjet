#ifdef CHANGED

#include "syscall.h"

void print(char c)
{
	PutString("test print\n");
#if 1
	PutChar(c);
	PutChar('\n');
#endif
	ThreadExit();
}

int main()
{
	PutString("test main\n");
	ThreadCreate(print, 'r');
	//PutChar('\n'); // erreur dans la partie I
	return 0;
}

#endif // CHANGED
