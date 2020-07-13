#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <chrono>
#include <thread>
//#include <wiringPi.h>
//#include <wiringSerial.h>
#include <atomic>

using namespace std;
using namespace cv;
using namespace std::chrono;

//global varbles
int fd;
const char* deviseBT = "/dev/rfcomm0";
const int videoDevise = 0;
const string result("LineVideo");
VideoCapture cap;
VideoWrite out_video;
int baut = 57600;
const int frame_width = 320;
const int frame_height = 240;
const double fps = 90;

std::atomic_bool isCmd = false;
//commands
const char cmdLFR = 'l';
const char cmdLFRW = 'w';
const char cmdTest = 't';
const char cmdEditParam = 'e';
const char cmdExit = 'x';
const char cmdStop = 's';
const char cmdQuit = 'q';
//flags for Lfr()
const uint8_t LFR = 0x1;
const uint8_t LFR_W = 0x2;
const uint8_t LFR_Test = 0x3;
//function declarations
std::pair<bool,cv::Point> findCenterLine(const Mat& mat);
void waitCmd(char cmd);
bool setupDevices();
void LFR_CV(unsigned char flag = LFR);
void LFR_Edit();
bool setupDevises(){
	if(wiringPiSetup() == -1){
		cout<< "\nFatal Eror wiring pi\n\n";
		return false;
	}
	if((fd = serialOpen(deviseBT, baud)) < 0)){
		cout<<"serial error\n";
		return 0;
	}else{
		cout<< "serial devise <"<<deviseBT<<"> (Blutuoth)";
	}
	cap.open(videoDevice);
	if(!cap.isOpened()){
		cout<<"error video";
		return false;
	}
	return 1;
}

void waitCmd(char cmd){
	
}

void LFR_CV(unsigned char flag = LFR);
  cout<<"start line\n";
  if(flag & LFR_W){
    out_video.open(result, VideoWriter::fourcc('D','I','V','X'),
fps,Size(frame_width,frame_height),true);
  if(!out_video.isOpened()){
    cout<<"output video error\n"
    return -1;
  }
  }
  delay(1000);
  serialPutchar(fd,cmdLFR);
  if(!(flag & LFR_Test)){
    serialPutchar(fd,cmdLFR);
  }isCmd = false;
  std::thread thr(waitCmd, cmdStop)
  double lastAngle = 0;
  
  for (;;) {
    Mat line_gray, line_bin;
    cap >> src_line;
    if (src_line.empty()) {
      cout << "The end of the stream" << endl;
      break;
    }		

    cvtColor(src_line, line_gray, COLOR_BGR2GRAY);
    threshold(line_gray, line_bin,
              th, 255, cv::THRESH_BINARY_INV);
    auto[is_line, cp] = findCenterLine(line_bin);




    // calculate angel 
    double angle = 0;
    if (is_line) {
			// on line
      int dx = cp.x - (line_bin.cols - 1) / 2;
      int dy = (line_bin.rows - 1) - cp.y; 
      
      if (dy != 0) {
        angle = atan2(dy, dx) * 180 / CV_PI - 90;	
      } else {
      // +90/-90
        angle = (dx > 0) ? 90 : -90; 
        cp = (dx > 0) ? Point(0,line_bin.rows-1) :
                        Point(line_bin.cols-1, line_bin.rows-1);
      }
      lastAngle = angle; 		
    } else {   
      angle = (lastAngle > 0) ? 90 : -90; 
      cp = (lastAngle > 0) ? Point(0, line_bin.rows-1) :
                            Point(line_bin.cols-1, line_bin.rows-1 );  
    }
    if(!(flag & LFR_Test)){
    angle = round(angle * 100);
    cout << "angle : " << angle/100.0 << endl;
    }

    //send angle
    //serialPutchar(fd, (unsigned char) (angle & 0xFF));
    //serialPutchar(fd, (unsigned char) ((angle >> 8) & 0xFF));
    //serialPutchar(fd, '\n');
    
    if (flag & LFR_W) {
      out_video << scr_line;
    }
    if(isCmd){
	serialPutchar(fd,cmdStop);
	thr.join();
	break;
    }
  }
  
  delay(5);

}
if(flag & LFR_W){
	cout<<"end"
	out_video.release();
}
// finding center of mass of binary image

std::pair<bool,cv::Point> findCenterLine(const Mat& mat){
 int cx = 0, cy = 0, cnt = 0;
 for (int x = 0; x < mat.rows; ++x) {
   int counter = 0;
 	 for (int y = 0; y < mat.cols; ++y) {
     if (mat.at<uchar>(x,y)) {
       ++counter;
       cx += y;
       cy += x;
     }
   }
   cnt += counter;
 }
 if (cnt != 0) {
   cx /= cnt;
   cy /= cnt;
 }
 return {cnt, Point(cx,cy)};           
}

int main(int, char**) {
  // disable the synchronization between the C and C++ standard streams 
  std::cout.sync_with_stdio(false);

  if (!setupDevices())  {
	return 1;
  }

  while(true){
	cout << "Command : \n";
	cout << "t - test LFR\n";
	cout << "l - start LFR\n";
	cout << "w - start LFR and writing video\n";
        cout << "e - edit LFR parameters\n";
	cout << "x - exit\n";
	char cmd;
	cin >> cmd;
	bool isCmdDone = true;
    while(!isCmdDone){
	switch (cmd) {
		case cmdLFR:
			LFR_CV();
			break;
		case cmdLFRW:
			LFR_CV(LFR_W);
			break;
		case cmdLFR_Test:
			LFR_CV(LFR_Test);
			break;
		case cmdEdit:
			LFR_Edit();
			break;
		case cmdExit:
			cout << "Exit LFR_CV\n";
			cap.release();
			return 0;
			break;
		default:
			isCmdDone = false;
			cout<< "not command!\n";
	}
    }
  }//while isCmdDone ^


}
