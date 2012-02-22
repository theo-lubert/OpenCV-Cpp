
#include	"MemStorage.hpp"

using namespace			CV;

CvMemStorage			*MemStorage::getMemStorage(void)
{
	return (mem);
}

MemStorage::operator	CvMemStorage*()
{
	return (getMemStorage());
}

MemStorage::MemStorage(int _blockSize)
  : blockSize(_blockSize), mem(cvCreateMemStorage(blockSize))
{
}

MemStorage::~MemStorage(void)
{
	cvReleaseMemStorage(&mem);
}
