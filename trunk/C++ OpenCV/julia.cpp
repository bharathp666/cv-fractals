#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace std;

int main(int argc, char** argv){
  IplImage* pic, *pic2;
  int pixel, line, i, g, l, maxi = 10000;
  double  x, y, x1, y1, xstart, ystart, xinc, yinc, xscale, yscale, temp, bout;
  uchar *data;

  if (argc < 9){
    cout <<"\nJulia Generator\n\n" 
	 <<"usage: julia [xsize] [ysize] [xstart] [ystart] [xscale]" 
	 <<" [yscale] [xseed] [yseed] [filename]\n"
	 <<"[xsize] - the size of the image x axis\n"
	 <<"[ysize] - the size of the image y axis\n"
	 <<"[xstart] - the position along the x axis to start\n"
	 <<"[ystart] - the position along the y axis to start\n"
	 <<"[xscale] - the distance along the xaxis to go\n"
	 <<"[yscale] - the distance along the y axit to go\n"
	 <<"[xseed] - the real part of the Julia seed\n"
	 <<"[yseed] - the imaginary part of the Julia seed\n"
	 <<"[filename] - the name of the file to save to. Optional\n\n"
	 <<"NOTE: It is reccomended that [xsize]:[ysize]\n"
	 <<"matches [xscale]:[yscale] for best output\n\n"
	 <<"To start, try: 'julia 800 400 -2 -1 4 2 -0.4 0.6 fractal.png'\n\n";
    return -1;  
  } 

  pixel = atoi(argv[1]);
  line = atoi(argv[2]);
  xstart = atof(argv[3]);
  ystart = atof(argv[4]);
  xscale = atof(argv[5]);
  yscale = atof(argv[6]);
  x = atof(argv[7]);
  y = atof(argv[8]);
  bout = 4;
  xinc = xscale/pixel;
  yinc = yscale/line;
  pic = cvCreateImage(
		      cvSize(pixel, line), 
		      IPL_DEPTH_8U, 3);
  pic2 = cvCreateImage(
		      cvSize(pixel, line), 
		      IPL_DEPTH_8U, 3);
  cvNamedWindow("Julia fractal", CV_WINDOW_AUTOSIZE); 	

  pixel = line = 0;

  for(y1=ystart;line<pic->height;y1+=yinc){
    for(x1=xstart;pixel<pic->width;x1+=xinc){
      //reuse variables so that zn=zn-1^2+c
      //where zn=0 is the pixel and c is a constant
      //xscale is zreal
      //yscale is zimaginary
      xscale = x1;
      yscale = y1;
      //x1 = pixel;
      //y1 = line;
      i = 0.0;

      while((xscale*xscale + yscale*yscale <= (bout)) and (i < maxi)){
	
	temp = (xscale*xscale) - (yscale*yscale) +x;
	yscale = (2*xscale*yscale)+y;
	xscale = temp;

	i++;
	}

	if(i>=maxi){
	 
	  (pic->imageData + pic->widthStep*(pic->height-line))[pixel*3]=0;

	}else{

	  //output in the h channel
	  (pic->imageData + pic->widthStep*(pic->height-line))[pixel*3]=i;
	  //add some garish green...
	  (pic->imageData + pic->widthStep*(pic->height-line))[pixel*3+2]=255;
	  (pic->imageData + pic->widthStep*(pic->height-line))[pixel*3+1]=255;

	}
	//cout << i << endl;
	pixel++;
    }
    cvCvtColor(pic, pic2, CV_HSV2BGR);
    cvShowImage("Julia fractal", pic2);

    pixel = 0;
    cout << (char)0x0d << "Current line: " << line++ << flush;
    //line++;
     
  }

    cout << (char)0x0d << "Current line: " << line << endl;

  cvShowImage("Julia fractal", pic2);

  // wait for a key and save if asked...
  if (argc == 10){
    cout << "Saving image " << argv[9] << endl;
    if(!cvSaveImage(argv[9],pic2)) printf("Could not save: %s\n",argv[9]);
  }
  cvWaitKey(0);
  // release the image
  cvReleaseImage(&pic );
  return 0;
}
