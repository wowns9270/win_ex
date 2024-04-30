#include "Student.hpp"
#include<thread>

// win api header
#include <windows.h>
#include <WinBase.h>
#include <Winnt.h>
#include <iostream>

int main()
{

	/// Create 
	HANDLE create_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(shm_student), "shm_student");
	if (create_handle == NULL)
	{
		std::cout << "file mapping create fail" << std::endl;
	}

	/// Open 
	HANDLE open_handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, "shm_student");
	if (open_handle == NULL)
	{
		std::cout << "file mapping open fail" << std::endl;
	}

	/// link  , 반환값은 매핑된 view의 시작주소 
	shm_student* ptr = nullptr;
	void* void_ptr = MapViewOfFile(open_handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(shm_student));
	if (void_ptr == nullptr)
	{
		std::cout << "file mapping fail" << std::endl;
	}
	ptr = static_cast<shm_student*>(void_ptr);


	/// update
	while (1) {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::cout << "sleep" << std::endl;

		ptr->id++;
		ptr->age++;
		ptr->grade++;
		ptr->scoure++;

	}

	UnmapViewOfFile(static_cast<void*>(void_ptr));
	CloseHandle(open_handle);
	std::cout << "end" << std::endl;

}
