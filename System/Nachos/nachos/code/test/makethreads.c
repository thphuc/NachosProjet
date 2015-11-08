#ifdef CHANGED

#include "syscall.h"

void print(char *c)
{
	PutString("test print thread\n");
	PutString(c);
#if 1
	PutChar('\n');
	PutChar('\n');
#endif
	ThreadExit();
}

int main()
{
	ThreadCreate(print, "test thread 0");
	//PutChar('\n'); // erreur dans la partie I
	ThreadExit();
	return 0;
}

#endif // CHANGED
