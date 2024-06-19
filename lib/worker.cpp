#include "worker.h"

Action::Action()
{

}

Worker::Worker()
{

}

void Worker::process_buffer(string buffer)
{
    printf("Processing incomming data: size: %d\n", buffer.length());

    // TODO checksum

    // parsing
    BSONObject* parsed = new BSONObject();
    parsed->parse(buffer.get());

    printf("%s\n", parsed->to_string().get());
}

void Worker::start_worker()
{
    DWORD ThreadId;
    CreateThread(NULL, 0, WorkerThread, (LPVOID)(this), 0, &ThreadId);
}

void Worker::worker_loop()
{
    while (true)
    {
        // Take and process actions
        // TODO
        Sleep(1000);
    }
}

DWORD WINAPI WorkerThread(LPVOID lpParam)
{
    Worker* worker = (Worker*)lpParam;

    worker->worker_loop();
}