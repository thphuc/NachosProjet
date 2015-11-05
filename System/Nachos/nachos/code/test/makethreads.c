#ifdef CHANGED

#include "syscall.h"

void print(char c)
{
#if 1
	PutChar(c);
	PutChar('\n');
#endif
	ThreadExit();
}

int main()
{
	ThreadCreate(print, 'a');
	//PutChar('\n'); // erreur dans la partie I
	return 0;
}

#endif // CHANGED