#ifdef CHANGED

#include "syscall.h"

void print(char *s)
{
#if 1
	PutString(s);
#endif
	ThreadExit();
}

int main()
{
	ThreadCreate(print, "Test makeThread\n");
	return 0;
}

#endif // CHANGED