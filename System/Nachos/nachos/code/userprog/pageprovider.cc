#ifdef CHANGED

#include "pageprovider.h"
#include "machine.h"

PageProvider::PageProvider()
{
	bitmapPage = new BitMap (NumPhysPages);
}

PageProvider::~PageProvider()
{
	delete bitmapPage;
}

int
PageProvider::GetEmptyPage()
{
	int emptyPage = bitmapPage->Find();
	memset (&emptyPage, 0, PageSize);
	return emptyPage;
}

void
PageProvider::ReleasePage(int page)
{
	bitmapPage->Clear (page);
}

int
PageProvider::NumAvailPage()
{
	return bitmapPage->NumClear();
}

#endif // CHANGED