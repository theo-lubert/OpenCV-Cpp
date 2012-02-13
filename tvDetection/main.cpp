#include <stdio.h>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "CV/Window.hpp"
#include "CV/Test/AdaptiveThresholdTestWindow.hpp"
#include "CV/Test/ThresholdTestWindow.hpp"
#include "CV/Test/LineTestWindow.hpp"
#include "CV/Test/ContourTestWindow.hpp"
#include "CV/Camera.hpp"


typedef IplImage* (*callback_prototype)(IplImage*);

 
CvScalar target_color[4] = { // in BGR order
  {{   0,   0, 255,   0 }},  // red
  {{   0, 255,   0,   0 }},  // green
  {{ 255,   0,   0,   0 }},  // blue
  {{   0, 255, 255,   0 }}   // yellow
};

void	drawThreshold(IplImage *frame, IplImage *gray)
{
      CvSeq* contours = 0;
      CvMemStorage* g_storage = cvCreateMemStorage(0);
      cvAdaptiveThreshold(gray, gray, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 7);
           cvThreshold(gray, gray, 25, 255, CV_THRESH_BINARY);
      cvFindContours(gray, g_storage, &contours);
      if( contours ){
      	cvDrawContours(
      		       gray,
      		       contours,
      		       cvScalarAll(255),
      		       cvScalarAll(255),
      		       100 );

      	CvScalar red = CV_RGB(250,0,0);
      	CvScalar blue = CV_RGB(0,0,250);
      	cvDrawContours(
      		       frame,
      		       contours,
      		       red,// Red
      		       blue,// Blue
      		       1,// Vary max_level and compare results
      		       2,
      		       8 );
      }
      cvReleaseMemStorage(&g_storage);
}

void	drawCorners(IplImage *frame, IplImage *gray)
{
  IplImage* eig_image = cvCreateImage(cvGetSize(frame), 8, 1);
  IplImage* temp_image = cvCreateImage(cvGetSize(frame), 8, 1);

  const int MAX_CORNERS = 1000;
  CvPoint2D32f corners[MAX_CORNERS] = {0};
  int corner_count = MAX_CORNERS;
  double quality_level = 0.1;
  double min_distance = 10;
  int eig_block_size = 5;
  int use_harris = true;
 
  cvGoodFeaturesToTrack(gray,
			eig_image,                    // output
			temp_image,
			corners,
			&corner_count,
			quality_level,
			min_distance,
			NULL,
			eig_block_size,
			use_harris);
  cvScale(eig_image, eig_image, 100, 0.00);
  //  cvShowImage("test", eig_image);

  std::cout << "Corner count: " << corner_count << std::endl;
  for( int i = 0; i < corner_count; i++) {
    int radius = frame->height/50;
    cvCircle(frame,
	     cvPoint((int)(corners[i].x + 0.5f),(int)(corners[i].y + 0.5f)),
	     radius,
	     target_color[0]);
  }

      cvReleaseImage(&temp_image);
}

int g_switch_value = 0;
int filterInt = 1;
int lastfilterInt = -1;

void switch_callback( int position ){
  filterInt = 1 + (1 * position);
}

void	drawLines(IplImage *frame, IplImage *gray)
{
  CvSeq* lines = 0;
  IplImage* final = cvCreateImage(cvGetSize(gray), 8, 3);
  IplImage* dst = cvCreateImage(cvGetSize(gray), 8, 1);
  IplImage* color_dst = cvCreateImage(cvGetSize(gray), 8, 3);
  CvMemStorage* storage = cvCreateMemStorage(0);
  int i;

  cvSet(final, cvScalar(0,0,0));
  cvCanny(gray, dst, 50, 200, 3);
  cvCvtColor(gray, color_dst, CV_GRAY2BGR);
  lines = cvHoughLines2( dst,
			 storage,
			 CV_HOUGH_PROBABILISTIC,
			 filterInt,
			 CV_PI/180,
			 100,
			 10,
			 10 );
  for( i = 0; i < lines->total; i++ )
    {
      CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
      cvLine( final, line[0], line[1], CV_RGB(255,255,255), 3, 8 );
      cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 1, 8 );
    }


  cvCvtColor(final, dst, CV_BGR2GRAY);
   drawThreshold(color_dst, dst);
   // drawCorners(color_dst, dst);
  // cvShowImage("Final", dst);
  cvShowImage("Lines", color_dst);

  // Create trackbar
  cvCreateTrackbar( "FILTER", "Lines", &g_switch_value, 5, switch_callback );

      cvReleaseImage(&final);
      cvReleaseImage(&dst);
      cvReleaseImage(&color_dst);
      cvReleaseMemStorage(&storage);
}


/*
 * process_video: retrieves frames from camera and executes a callback to do individual frame processing.
 * Keep in mind that if your callback takes too much time to execute, you might loose a few frames from 
 * the camera.
 */
void process_video(callback_prototype custom_cb)
{           
  // Initialize camera
  CvCapture *capture = 0;
  capture = cvCaptureFromCAM(1 + CV_CAP_V4L);
  if (!capture) 
    {
      fprintf(stderr, "!!! Cannot open initialize webcam!\n" );
      return;
    }

  // Create a window for the video 
  cvNamedWindow("result", CV_WINDOW_AUTOSIZE);

  IplImage* frame = 0;
  char key = 0;
  while (key != 27) // ESC
    {    
      frame = cvQueryFrame(capture);
      if(!frame) 
	{
          fprintf( stderr, "!!! cvQueryFrame failed!\n" );
          break;
	}

      // Execute callback on each frame
      IplImage* gray = cvCreateImage(cvGetSize(frame), 8, 1);

      cvCvtColor(frame, gray, CV_BGR2GRAY);
      // cvEqualizeHist(gray, gray);
      // cvSmooth(gray, gray);

      // drawThreshold(frame, gray);
      // drawLines(frame, gray);
      // drawCorners(frame, gray);

      // Display processed frame
      cvShowImage("result", frame);
      //      cvShowImage("Gray", gray);

      // Release resources
      cvReleaseImage(&gray);

      // Exit when user press ESC
      key = cvWaitKey(10);
    }

  // Free memory
  cvDestroyWindow("result");
  cvReleaseCapture(&capture);
}

int				main(int ac, char **av)
{
  cvInitSystem(ac, av);

  CV::AdaptiveThresholdTestWindow	win(255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 15);
  CV::LineTestWindow		lwin(CV_HOUGH_PROBABILISTIC,
				     1,
				     CV_PI * 180,
				     1,
				     5,
				     5);
  CV::ContourTestWindow		cwin(CV_RETR_TREE, CV_CHAIN_APPROX_TC89_KCOS);
  CV::Camera			cam(1);

  CV::Image			*frame;
  char				key = 0;
  while (key != 27) // ESC
    {
      if ((frame = cam.queryFrame()) != NULL)
	{
	  CV::Image			*gray = frame->convertColor(CV_BGR2GRAY, 8, 1);

	  cvSmooth(gray->getIplImage(), gray->getIplImage());
	  win.showImage(gray);
	  cwin.showImage(frame, win.getImage());
	  lwin.showImage(win.getImage());
	  delete gray;
	  delete frame;
	}
      key = cvWaitKey(10);
    }

  return 0;
}
