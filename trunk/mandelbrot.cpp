#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace std;

int main(int argc, char** argv){
  IplImage* pic, *pic2;
  int pixel, line, i, g, l, maxi = 1000;
  float  x, y, x1, y1, xstart, ystart;
  float xinc, yinc, xscale, yscale, temp, bout;
  uchar *data;

  if (argc < 7){
    cout <<"\nMandelbrot Generator\n\n" 
	 <<"usage: mandelbrot [xsize] [ysize] [xstart] [ystart] [xscale]" 
	 <<" [yscale] [filename]\n"
	 <<"[xsize] - the size of the image x axis\n"
	 <<"[ysize] - the size of the image y axis\n"
	 <<"[xstart] - the position along the x axis to start\n"
	 <<"[ystart] - the position along the y axis to start\n"
	 <<"[xscale] - the distance along the xaxis to go\n"
	 <<"[yscale] - the distance along the y axit to go\n"
	 <<"[filename] - the name of the file to save to. Optional\n\n"
	 <<"NOTE: It is reccomended that [xsize]:[ysize]\n"
	 <<"matches [xscale]:[yscale] for best output\n\n"
	 <<"To start, try: 'mandelbrot 600 400 -2 -1 3 2 fractal.png'\n\n";
    return -1;  
  } 

  pixel = atoi(argv[1]);
  line = atoi(argv[2]);
  xstart = atof(argv[3]);
  ystart = atof(argv[4]);
  xscale = atof(argv[5]);
  yscale = atof(argv[6]);
  bout = 4;
  xinc = xscale/pixel;
  yinc = yscale/line;
  l = line/75;
  pic = cvCreateImage(
		      cvSize(pixel, line), 
		      IPL_DEPTH_8U, 3);
  pic2 = cvCreateImage(
		      cvSize(pixel, line), 
		      IPL_DEPTH_8U, 3);
  cvNamedWindow("Mandelbrot fractal", CV_WINDOW_AUTOSIZE); 	

  pixel = line = 0;

  for(y=ystart;line<pic->height;y+=yinc){
    for(x=xstart;pixel<pic->width;x+=xinc){

      x1 = y1 = i = 0.0;

      while((x1*x1 + y1*y1 <= (bout)) and (i < maxi)){
	
	temp = (x1*x1) - (y1*y1) +x;
	y1 = (2*x1*y1)+y;
	x1 = temp;

	i++;
	}

	if(i==maxi){

	  (pic->imageData + pic->widthStep*(line))[pixel*3]=0;

	}else{


	  //output in the h channel
	  (pic->imageData + pic->widthStep*(pic->height-line))[pixel*3]=i;
	  //add some garish green...
	  (pic->imageData + pic->widthStep*(pic->height-line))[pixel*3+2]=127;
	  (pic->imageData + pic->widthStep*(pic->height-line))[pixel*3+1]=255;
	}
	pixel++;
    }
    cvCvtColor(pic, pic2, CV_HSV2BGR);
    cvShowImage("Mandelbrot fractal", pic2);

    pixel = 0;
    cout << (char)0x0d << "Current line: " << line++ << flush;
    //line++;
     
  }

    cout << (char)0x0d << "Current line: " << line << endl;

  cvShowImage("Mandelbrot fractal", pic2);

  // wait for a key and save if asked...
  if (argc == 8){
	if(!cvSaveImage(argv[7],pic2)) printf("Could not save: %s\n",argv[7]);
  }
  cvWaitKey(0);
  // release the image
  cvReleaseImage(&pic );
  return 0;
}
