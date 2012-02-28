
#include	"HandDetector.hpp"

using namespace			CV;

std::vector<Hand *>   &HandDetector::getHands(void)
{
	return (hands);
}

HandDetector::HandDetector(Image *image)
{
	CV::MemStorage		defectst;

	CvSeq				*defect;
	CvSeq				*convexhull;

	cvFindContours(*image, st, &contour);
	contour = cvApproxPoly(contour, sizeof(CvContour), st, CV_POLY_APPROX_DP, 20, 1);
	while (contour)
	{
      	convexhull = cvConvexHull2(contour, NULL,
      		CV_COUNTER_CLOCKWISE,
      		0);

      	CvScalar color = cvScalarAll(255);
      	defect = cvConvexityDefects(contour,
      		convexhull,
      		defectst);

    	if (defect->total >= 1)
			hands.push_back(new Hand(contour, defectst, defect, convexhull));
		contour = contour->h_next;
	}
}

HandDetector::~HandDetector(void)
{
}
