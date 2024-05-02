#include "Student.hpp"
#include <iostream>
#include<thread>

#define SLOT_NAME "\\\\.\\mailslot\\mailbox"

// win api header
#include <windows.h>

int main()
{

	HANDLE handle = CreateMailslot(SLOT_NAME, 0, MAILSLOT_WAIT_FOREVER, NULL);
	
	if (handle == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();

		std::cout << "err : " << err << std::endl;
	}


	// mail slot 

	std::thread receive([&]() -> void {

		if (handle == INVALID_HANDLE_VALUE) return;


		shm_student message ;
		int readsize = -1;
		while (TRUE)
		{
			if (!ReadFile(handle, &message, sizeof(shm_student), (DWORD*)&readsize, NULL))
			{
				DWORD err = GetLastError();
				std::cout << "read err : " << err << std::endl;
			}
			else
			{
				std::cout << message.id << " " << message.age << " " <<
					message.grade << " " << message.scoure << std::endl;

				std::this_thread::sleep_for(std::chrono::seconds(3));

			}
		}
	});

	receive.join();
	return 0;
}
