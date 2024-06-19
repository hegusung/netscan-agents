#pragma once
#ifndef MUTEX_H_INCLUDED
#define MUTEX_H_INCLUDED

#include <windows.h>

class mutex {
public:
    mutex() {
        // Create a new mutex object
        hMutex = CreateMutex(NULL, FALSE, NULL);
    }

    ~mutex() {
        // Close the mutex handle
        if (hMutex) {
            CloseHandle(hMutex);
        }
    }

    int lock() {
        // Wait for the mutex to be available
        DWORD dwWaitResult = WaitForSingleObject(hMutex, INFINITE);
        switch (dwWaitResult) {
            // The thread got ownership of the mutex
        case WAIT_OBJECT_0:
            return 0;

            // The thread got ownership of an abandoned mutex
            // The mutex was not released properly by the owning thread
        case WAIT_ABANDONED:
            return 1;

        default:
            return 2;
        }
    }

    int unlock() {
        // Release ownership of the mutex
        if (!ReleaseMutex(hMutex)) {
            return 1;
        }

        return 0;
    }

private:
    HANDLE hMutex;
};

#endif