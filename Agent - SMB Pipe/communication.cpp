#include "communication.h"

Communication::Communication(void* communication_object)
{
    this->com_object = (NamedPipe*)communication_object;

    int res = this->com_object->initialize();
    if (res == 0)
    {
        //printf("Starting workers\n");
        //worker.start_worker();
        res = this->com_object->com_loop();
        printf("Communication loop ended: %d\n", res);
    }
    else
        printf("Initialization error: %d\n", res);

}

Communication::~Communication()
{

}
