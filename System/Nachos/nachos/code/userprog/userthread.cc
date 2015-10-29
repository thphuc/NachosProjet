#ifdef CHANGED
#include "userthread.h"
#include "thread.h"
#include "addrspace.h"
#include "system.h"

static void StartUserThread(void* schmurtz);

int 
do_ThreadCreate(int f, int arg)
{
	int *schmurtz = new int[2];
	schmurtz[0] = f;
	schmurtz[1] = arg;
	Thread *newThread = new Thread("nouveauThread");
	newThread->Start(StartUserThread, schmurtz);
	return 0;
}

static void
StartUserThread(void* schmurtz){
	int f = ((int*) schmurtz)[0];
	int arg = ((int*) schmurtz)[1];
	for (int i = 0; i < NumTotalRegs; i++)
		machine->WriteRegister (i, 0);

	int topAdress = currentThread->space->AllocateUserStack();

	machine->WriteRegister (StackReg, topAdress);
	DEBUG('x', "[DEBUG] Adress: %d\n", topAdress);
	machine->WriteRegister (PCReg, f);
	DEBUG('x', "[DEBUG] Function: %d\n", f);
	machine->WriteRegister (4, arg);
	DEBUG('x', "[DEBUG] Arg: %d\n", arg);

	machine->Run();
	free(schmurtz);

}

void 
do_ThreadExit(){

	currentThread->Finish(); // c'est fini
}

#endif // CHANGED