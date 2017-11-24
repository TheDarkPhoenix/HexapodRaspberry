#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tcpacceptor.h"
#include "robot.h"

#define SCALE 0.017453

using namespace std;
using namespace cv;


int main()
{
    char key = 'm';

    Robot rob(Point3f(0, 17 ,100), Point3f(0,0,0), 11.8, 36.5, Point3f(3.7, 5.8, 16.3));

    float transStep = 1;
    float rotStep = 0.05;

    bool walking = false;

    float walkStep = 5;

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

    /*if (acceptor->start() == 0) 
    {
        while (1) ??????????????
        {
            stream = acceptor->accept();
            if (stream != NULL) 
            {
                char l;
                while (stream->receive(&l, sizeof(l)) > 0) 
                {
                    cout << l << endl;
                }
                delete stream;
            }
        }
    }*/

    if (acceptor->start() == 0) 
    {
        while(1)
        {
	        stream = acceptor->accept();
	        if (stream != NULL) 
	        { 
	            while(key != 27)
	            {
	                if(mode == 1)
	                {
	                    switch(key)
	                    {
	                        case 'D':
	                            rob.move(Point3f(transStep,0,0));
	                            break;
	                        case 'A':
	                            rob.move(Point3f(-transStep,0,0));
	                            break;
	                        case 'Q':
	                            rob.move(Point3f(0,0,transStep));
	                            break;
	                        case 'E':
	                            rob.move(Point3f(0,0,-transStep));
	                            break;
	                        case 'S':
	                            rob.move(Point3f(0,transStep,0));
	                            break;
	                        case 'W':
	                            rob.move(Point3f(0,-transStep,0));
	                            break;
	                        case 'R':
	                            rob.restart(Point3f(0, 17 ,100), Point3f(0,0,0));
	                            break;
	                    }
	                }
	                else if(mode == 2)
	                {
	                    switch(key)
	                    {
	                        case 'W':
	                            rob.rotate(Point3f(0,rotStep,0));
	                            break;
	                        case 'S':
	                            rob.rotate(Point3f(0,-rotStep,0));
	                            break;
	                        case 'A':
	                            rob.rotate(Point3f(rotStep,0,0));
	                            break;
	                        case 'D':
	                            rob.rotate(Point3f(-rotStep,0,0));
	                            break;
	                        case 'Q':
	                            rob.rotate(Point3f(0,0,rotStep));
	                            break;
	                        case 'E':
	                            rob.rotate(Point3f(0,0,-rotStep));
	                            break;
	                        case 'R':
	                            rob.restart(Point3f(0, 17 ,100), Point3f(0,0,0));
	                            break;
	                    }
	                }
	                else if(mode == 3)
	                {
	                    switch(key)
	                    {
	                        case 'D':
	                            rob.walk(Point3f(walkStep,0,0));
	                            break;
	                        case 'A':
	                            rob.walk(Point3f(-walkStep,0,0));
	                            break;
	                        case 'W':
	                            rob.walk(Point3f(0,0,walkStep));
	                            break;
	                        case 'S':
	                            rob.walk(Point3f(0,0,-walkStep));
	                            break;
	                        case 'Q':
	                            rob.walkRot(0.05);
	                            break;
	                        case 'E':
	                            rob.walkRot(-0.05);
	                            break;
	                        case 'R':
	                            rob.restart(Point3f(0, 17 ,100), Point3f(0,0,0));
	                            break;
	                    }
	                }
	                else if(mode == 4)
	                {
	                    switch(key)
	                    {
	                        case 'D':
	                            rob.walkC(Point3f(walkStep,0,0));
	                            break;
	                        case 'A':
	                            rob.walkC(Point3f(-walkStep,0,0));
	                            break;
	                        case 'W':
	                            rob.walkC(Point3f(0,0,walkStep));
	                            break;
	                        case 'S':
	                            rob.walkC(Point3f(0,0,-walkStep));
	                            break;
	                        case 'E':
	                            rob.walkRotC(0.18);
	                            break;
	                        case 'Q':
	                            rob.walkRotC(-0.18);
	                            break;
	                        case 'R':
	                            rob.restart(Point3f(0, 17 ,100), Point3f(0,0,0));
	                            break;
	                    }
	                }
	                else if(mode == 5)
	                {
	                    switch(key)
	                    {
	                        case 'D':
	                            rob.walkC(Point3f(walkStep,0,0));
	                            break;
	                        case 'A':
	                            rob.walkC(Point3f(-walkStep,0,0));
	                            break;
	                        case 'W':
	                            rob.walk2C(Point3f(0,0,walkStep));
	                            break;
	                        case 'S':
	                            rob.walk2C(Point3f(0,0,-walkStep));
	                            break;
	                        case 'E':
	                            rob.walkRotC(0.18);
	                            break;
	                        case 'Q':
	                            rob.walkRotC(-0.18);
	                            break;
	                        case 'R':
	                            rob.restart(Point3f(0, 17 ,100), Point3f(0,0,0));
	                            break;
	                    }
	                }
	                else if(mode == 6)
	                {
	                    switch(key)
	                    {
	                        case 'D':
	                            rob.walk3C(Point3f(walkStep,0,0));
	                            break;
	                        case 'A':
	                            rob.walk3C(Point3f(-walkStep,0,0));
	                            break;
	                        case 'W':
	                            rob.walk3C(Point3f(0,0,walkStep));
	                            break;
	                        case 'S':
	                            rob.walk3C(Point3f(0,0,-walkStep));
	                            break;
	                        case 'E':
	                            rob.walkRot3C(0.18);
	                            break;
	                        case 'Q':
	                            rob.walkRot3C(-0.18);
	                            break;
	                        case 'R':
	                            rob.restart(Point3f(0, 17 ,100), Point3f(0,0,0));
	                            break;
	                    }
	                }

	                switch(key)
	                {
	                    case '1':
	                        mode = 1;
	                        break;
	                    case '2':
	                        mode = 2;
	                        break;
	                    case '3':
	                        mode = 3;
	                        break;
	                    case '4':
	                        mode = 4;
	                        break;
	                    case '5':
	                        mode = 5;
	                        break;
	                    case '6':
	                        mode = 6;
	                        break;
	                }
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
