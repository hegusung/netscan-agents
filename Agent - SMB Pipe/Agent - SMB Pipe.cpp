// Agent - SMB Pipe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../lib/NoCRT.h"
#include "../lib/BSON.h"
#include "../lib/NoCRT_string.h"
#include "../lib/NoCRT_list.h"
#include "../lib/NoCRT_mutex.h"

#include "../lib/worker.h"
#include "communication.h"
#include "com_namedpipe.h"

/*
DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    mutex* m = (mutex*)lpParam;

    Sleep(3000);

    printf("Thread\n");

    m->lock();

    printf("AAAAAAAAAAAAAAAAAAAAAAaa");

    return 0;
}
*/

int main()
{
    const char* pipe_name = "netscan_agent";
    printf("Pipe name: %s\n", pipe_name);

    // Start the Worker class
    Worker worker = Worker();
    worker.start_worker();

    // Communication class
    NamedPipe* com_pipe = new NamedPipe(pipe_name);
    //com_pipe->set_worker(&worker);

    Communication* communication = new Communication(com_pipe)

    int res = communication->initialize();
    if (res == 0)
    {
        printf("Starting workers\n");
        worker.start_worker();
        res = communication->com_loop();
        printf("Communication loop ended: %d\n", res);
    }
    else
        printf("Initialization error: %d\n", res);



    /*
    mutex m;

    DWORD ThreadId;
    CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        MyThreadFunction,       // thread function name
        (LPVOID)(&m),          // argument to thread function 
        0,                      // use default creation flags 
        &ThreadId);   // returns the thread identifier 

    printf("before lock\n");
    int a = m.lock();
    printf("locked: %d\n", a);

    Sleep(5000);

    m.unlock();
    printf("freedom\n");

    Sleep(10000);
    */

    printf("All done !\n");
}
