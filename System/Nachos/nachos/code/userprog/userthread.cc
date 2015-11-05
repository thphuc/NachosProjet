#ifdef CHANGED

#include "userthread.h"
#include "thread.h"
#include "addrspace.h"
#include "system.h"

static void StartUserThread (void *schmurtz);

static void
StartUserThread (void *schmurtz)
{
	printf("StartUserThread\n");
	int f = ((int *) schmurtz)[0];
	int arg = ((int *) schmurtz)[1];
	for (int i = 0; i < NumTotalRegs; i++)
		machine->WriteRegister (i, 0);

	int topAdress = currentThread->space->AllocateUserStack ();

	machine->WriteRegister (StackReg, topAdress);
	DEBUG ('x', "[DEBUG] Adress: %d\n", topAdress);
	printf ("[DEBUG] Adress: %d\n", topAdress);
	machine->WriteRegister (PCReg, f);
	DEBUG ('x', "[DEBUG] Function: %d\n", f);
	printf ("[DEBUG] Function: %d\n", f);
	machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);
	DEBUG ('x', "[DEBUG] NextPCReg: %d\n", machine->ReadRegister(PCReg) + 4);	
	printf ("[DEBUG] NextPCReg: %d\n", machine->ReadRegister(PCReg) + 4);	
	machine->WriteRegister (4, arg);
	DEBUG ('x', "[DEBUG] Arg: %d\n", arg);
	printf ("[DEBUG] Arg: %d\n", arg);

	machine->Run ();
	free (schmurtz);
}

int 
do_ThreadCreate (int f, int arg)
{
	int *schmurtz = (int *) malloc (sizeof (*schmurtz) * 2);
	schmurtz[0] = f;
	schmurtz[1] = arg;
	Thread *newThread = new Thread ("nouveauThread");
	newThread->Start (StartUserThread, schmurtz);
	printf("test\n");	
	return 0;
}

void 
do_ThreadExit ()
{
	currentThread->Finish (); // c'est fini
}

#endif // CHANGED
