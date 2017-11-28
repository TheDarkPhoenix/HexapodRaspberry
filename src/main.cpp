#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include "tcpacceptor.h"
#include "robotcontroler.h"

using namespace std;
using namespace cv;

struct key
{
    char key;
    mutex own;
};

void tcpkey(key* k)
{
    TCPStream* stream = NULL;
    unique_ptr<TCPAcceptor> acceptor = make_unique<TCPAcceptor>(8080);

    if (acceptor->start() != 0)
        return;

    while(1)
    {
        stream = acceptor->accept();
        if (stream != NULL) 
        { 
            while(k->key != 27)
            {
                unique_lock<mutex> lck(k->own);
                stream->receive(&(k->key), sizeof(k->key));
            }
        }
        delete stream;
    }
    
}

int main()
{
    key k;
    k.key = 'm';

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

    thread t1 {tcpkey, &k};

    ///Tryby:
    ///1 - stanie w miejscu i ruch translacyjny
    ///2 - stanie w miesjscu i obroty
    ///3 - poruszanie siê manualne
    ///4 - poruszanie siê automatyczne
    ///5 - automatyczne z poprawioną płynnością
    ///6 - automatyczne z płynnym chodzeniem do przodu i zakręcaniem

    int mode = 6;

    
    while(1)
    {
        unique_lock<mutex> lck(k.own);
        rob.control(k.key);
    }
    return 0;
}
