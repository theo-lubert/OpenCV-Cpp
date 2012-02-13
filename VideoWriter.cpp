
#include			"VideoWriter.hpp"

using namespace			CV;

int				VideoWriter::writeFrame(const IplImage *image)
{
  return (cvWriteFrame(writer, image));
}

VideoWriter::VideoWriter(const char *name, int fourcc, double fps, CvSize frame_size, int is_color)
  : writer(NULL)
{
  writer = cvCreateVideoWriter(name, fourcc, fps, frame_size, is_color);
}

VideoWriter::~VideoWriter(void)
{
  if (writer)
    cvReleaseVideoWriter(&writer);
}
