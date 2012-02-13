
#include			"CaptureFile.hpp"

using namespace			CV;

CaptureFile::CaptureFile(const std::string &_name)
  : name(_name)
{
}

CaptureFile::CaptureFile(const char *_name)
  : name(_name)
{
}

CaptureFile::~CaptureFile(void)
{
}
