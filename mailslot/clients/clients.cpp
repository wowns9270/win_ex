#include "Student.hpp"
#include <iostream>
#include <thread>
// win api header
#include <windows.h>
#define SLOT_NAME "\\\\.\\mailslot\\mailbox"

int main()
{
	HANDLE handle = CreateFile(SLOT_NAME, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();

		std::cout << "err : " << err << std::endl;
	}

	shm_student p = { 1,2,3,4 };
	unsigned int writeSize = 0;

	while (TRUE)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));

		if (!WriteFile(handle, &p, sizeof(shm_student), (DWORD*)&writeSize, NULL))
		{
			DWORD err = GetLastError();
			std::cout << "err : " << err << std::endl;
			break;
		}

		p.id++;
		p.age++;
		p.grade++;
		p.scoure++;

		std::cout << "send event" << std::endl;
	}


}