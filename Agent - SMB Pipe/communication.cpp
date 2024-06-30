#include "communication.h"

Communication::Communication(void* communication_object)
{
    this->com_object = (NamedPipe*)communication_object;

    int res = this->com_object->initialize();
    if (res == 0)
    {
        //printf2("Starting workers\n");
        //worker.start_worker();
        res = this->com_object->com_loop();
        printf2("Communication loop ended: %d\n", res);
    }
    else
        printf2("Initialization error: %d\n", res);

}

Communication::~Communication()
{

}
