// Reference: https://stackoverflow.com/questions/26561604/create-named-pipe-c-windows

#include <Windows.h>
#include <stdio.h>

#define BUFSIZE 1024

int main()
{
	HANDLE hPipe;
	char buffer[BUFSIZE];
	DWORD dwRead;

	hPipe = CreateNamedPipeA(
		TEXT("\\\\.\\pipe\\Pipe"),
		PIPE_ACCESS_INBOUND /* | FILE_FLAG_FIRST_PIPE_INSTANCE */,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		1,
		BUFSIZE * 16,
		BUFSIZE * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL
	);

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Failed to open server.\n");
		return -1;
	}

	while (hPipe != INVALID_HANDLE_VALUE)
	{
		// Wait for client to connect
		if (ConnectNamedPipe(hPipe, NULL))
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL))
			{
				// Add terminating zero
				buffer[dwRead] = '\0';

				printf("%s\n", buffer);
			}
		}

		DisconnectNamedPipe(hPipe);
	}

	return 0;
}
