#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

SynchConsole::SynchConsole(const char *in, const char *out)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
	console = new Console(in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
}

void SynchConsole::SynchPutChar(int ch)
{
	console->PutChar(ch);
	writeDone->P();
}

int SynchConsole::SynchGetChar()
{
	readAvail->P();
	return console->GetChar();
}

void SynchConsole::SynchPutString(const char *s)
{
	int i = 0;
	while(s[i] != '\0')
	{
		SynchPutChar(s[i]);
		i++;
	}
}

void SynchConsole::SynchGetString(char *s, int n)
{
	int i = 0;
	char c;

	while(i < n && c != EOF && c != '\n')
	{
		c = SynchGetChar();
		s[i] = c;
		i++;
	}
	s[i] = '\0';
}


void SynchConsole::SynchPutInt(int n)
{
	char *buffer = (char *)malloc(sizeof(*buffer) * MAX_STRING_SIZE);
	snprintf(buffer, MAX_STRING_SIZE, "%d", n);
	SynchPutString(buffer);
}

void SynchConsole::SynchGetInt(int *n)
{
	char *buffer = (char *)malloc(sizeof(*buffer) * MAX_STRING_SIZE);
	SynchGetString(buffer, MAX_STRING_SIZE);
	sscanf(buffer, "%d", n);
}

#endif // CHANGED
