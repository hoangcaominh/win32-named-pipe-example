// Reference: https://stackoverflow.com/questions/26561604/create-named-pipe-c-windows

#include <Windows.h>
#include <stdio.h>

int main()
{
	HANDLE hPipe;
	DWORD dwWritten;

	hPipe = CreateFile(
		TEXT("\\\\.\\pipe\\Pipe"),
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Failed to open client.\n");
		return -1;
	}

	WriteFile(hPipe, "Hello World\n", 13, &dwWritten, NULL);
	CloseHandle(hPipe);

	return 0;
}
