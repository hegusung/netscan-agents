#include "com_namedpipe.h"

NamedPipe::NamedPipe(const char* pipe_name)
{
    // Switch to \\.\pipe\pipe_name
    this->pipe_path = (char*)malloc(10 + strlen(pipe_name));
    strcpy(this->pipe_path, "\\\\.\\pipe\\");
    strcat(this->pipe_path, pipe_name);

    printf("Pipe path: %s\n", this->pipe_path);

    this->security_attributes = { 0 };
    this->security_descriptor = { 0 };

    this->connected = false;
}

NamedPipe::~NamedPipe()
{
    this->pipe_handle = INVALID_HANDLE_VALUE;
}

int NamedPipe::initialize()
{
    // Prepare the security descriptor for the pipe
    if (!InitializeSecurityDescriptor(&(this->security_descriptor), SECURITY_DESCRIPTOR_REVISION))
    {
        return 1;
    }

    if (!SetSecurityDescriptorDacl(&(this->security_descriptor), TRUE, NULL, FALSE))
    {
        return 2;
    }

    this->security_attributes.bInheritHandle = FALSE;
    this->security_attributes.nLength = sizeof(SECURITY_DESCRIPTOR);
    this->security_attributes.lpSecurityDescriptor = &(this->security_descriptor);

    return 0;
}

int NamedPipe::create_named_pipe()
{
    this->pipe_handle = CreateNamedPipe(this->pipe_path, PIPE_ACCESS_DUPLEX, PIPE_WAIT | PIPE_TYPE_BYTE | PIPE_ACCEPT_REMOTE_CLIENTS, PIPE_UNLIMITED_INSTANCES, PIPE_SIZE, PIPE_SIZE, PIPE_TIMEOUT, &(this->security_attributes));
    if (this->pipe_handle == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    this->connected = true;

    return 0;
}

int NamedPipe::close_named_pipe()
{
    this->pipe_handle = NULL;
    this->connected = false;

    return 0;
}

int NamedPipe::com_loop()
{
    printf("Creating named pipe...\n");

    while ((this->create_named_pipe()) == 0)
    {
        printf("Waiting for a client\n");
        if (ConnectNamedPipe(this->pipe_handle, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            printf("Client connected\n");
            // We are connected !

            BSONArray l1 = BSONArray();
            l1.insert(new BSONObject(false));
            l1.insert(new BSONObject(42));
            l1.insert(new BSONObject(string("test")));

            BSONDict d1 = BSONDict();
            d1.set("test1", new BSONObject(false));
            d1.set("test2", new BSONObject(42));
            d1.set("test3", new BSONObject(string("test")));
            d1.set("list", new BSONObject(l1));

            BSONObject* d1_o = new BSONObject(d1);
            printf("%s\n", d1_o->to_string().get());

            string buffer = d1_o->create_structure();

            DWORD temp;
            WriteFile(this->pipe_handle, buffer.get(), buffer.length(), &temp, NULL);

            while (true)
            {
                printf("loop !\n");
                DWORD bytes_to_read;
                if ((PeekNamedPipe(this->pipe_handle, NULL, 0, NULL, &bytes_to_read, NULL)) == FALSE)
                {
                    // pipe is broken
                    printf("Pipe is broken\n");
                    this->close_named_pipe();
                    break;
                }

                printf("Bytes to read: %d\n", bytes_to_read);

                if (bytes_to_read == 0)
                {
                    // No data to read, sleep a bit
                    Sleep(10);
                    continue;
                }

                unsigned char* data = (unsigned char*)malloc(bytes_to_read);

                // Get the read lock
                //this->pipe_read_lock.lock();

                if ((ReadFile(this->pipe_handle, data, bytes_to_read, &bytes_to_read, NULL)) == FALSE)
                {
                    // pipe is broken
                    this->close_named_pipe();
                    free(data);
                    //this->pipe_read_lock.unlock();
                    break;
                }

                // Put the data in the buffer
                this->worker->process_buffer(string((char*)data, bytes_to_read));

                // destroy and free
                memset(data, 0, bytes_to_read);
                free(data);
            }
        }

        DisconnectNamedPipe(this->pipe_handle);
        
    }

    return 1;
}

