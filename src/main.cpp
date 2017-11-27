#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tcpacceptor.h"
#include "robotcontroler.h"

#define SCALE 0.017453

using namespace std;
using namespace cv;


int main()
{
    char key = 'm';

    Point3f robotPosition(0, 17, 100);
    Point3f robotAngles(0,0,0);
    float robotWidth = 11.8;
    float robotLength = 36.5;
    Point3f robotLegLenghts(3.7, 5.8, 16.3);

    float walkStep = 5;
    float rotStep = 0.3;
    float sMoveStep = 1;
    float sRotStep = 0.05;

    RobotControler rob(walkStep, rotStep, sMoveStep, sRotStep, robotPosition, robotAngles, robotWidth, robotLength, robotLegLenghts);

    ///Tryby:
    ///1 - stanie w miejscu i ruch translacyjny
    ///2 - stanie w miesjscu i obroty
    ///3 - poruszanie siê manualne
    ///4 - poruszanie siê automatyczne
    ///5 - automatyczne z poprawioną płynnością
    ///6 - automatyczne z płynnym chodzeniem do przodu i zakręcaniem

    int mode = 6;

    TCPStream* stream = NULL;
    TCPAcceptor* acceptor = NULL;
    acceptor = new TCPAcceptor(8080);

    if (acceptor->start() == 0) 
    {
        while(1)
        {
	        stream = acceptor->accept();
	        if (stream != NULL) 
	        { 
	            while(key != 27)
	            {
	                rob.control(key);
	                if (stream->receive(&key, sizeof(key)) > 0) 
	                {
	                    cout << key << endl;
	                }
	            }
	        }
            delete stream;
        }
    }
    return 0;
}
