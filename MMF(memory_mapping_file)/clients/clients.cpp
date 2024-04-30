#include "Student.hpp"
#include <iostream>
#include <thread>
// win api header
#include <windows.h>

int main()
{
	/// Create
	HANDLE create_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(shm_student), "shm_student");
	if (create_handle == NULL)
	{
		std::cout << "file mapping create fail" << std::endl;
	}

	/// Open
	HANDLE open_handle = OpenFileMapping(FILE_MAP_READ, false, "shm_student");
	if (open_handle == NULL)
	{
		std::cout << "file mapping open fail" << std::endl;
	}

	/// link  , ��ȯ���� ���ε� view�� �����ּ�
	shm_student *ptr = nullptr;
	void *void_ptr = MapViewOfFile(open_handle, FILE_MAP_READ, 0, 0, sizeof(shm_student));
	if (void_ptr == nullptr)
	{
		std::cout << "file mapping fail" << std::endl;
	}
	ptr = static_cast<shm_student *>(void_ptr);

	/// print
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::cout << "print:" << std::endl;
		std::cout << ptr->id << std::endl;
		std::cout << ptr->age << std::endl;
		std::cout << ptr->grade << std::endl;
		std::cout << ptr->scoure << std::endl;
	}
}