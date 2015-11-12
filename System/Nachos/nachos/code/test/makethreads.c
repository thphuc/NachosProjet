#ifdef CHANGED

#include "syscall.h"

void print(char *c)
{
	PutChar('\n');
	PutString(c);
#if 1
	PutChar('\n');
	PutChar('\n');
#endif
	ThreadExit();
}

void print2(char *c)
{
	PutChar('\n');
	PutString(c);
	PutChar('\n');
	ThreadExit();
}

int main()
{
	ThreadCreate(print, "test thread 0");
	PutChar('t');
	PutChar('-');
	PutChar('\n');
	ThreadExit();
}

#endif // CHANGED
