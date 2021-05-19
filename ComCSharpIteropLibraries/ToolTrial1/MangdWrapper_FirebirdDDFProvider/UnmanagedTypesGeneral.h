#include <Windows.h>
#include <iostream>
#include <comdef.h>

extern "C"
{
	typedef HRESULT(__stdcall *DLLGETCLASSFUNPTR)(const CLSID& clsid, REFIID iid, void** ppv);
}

void print(const CHAR* msg)
{
	std::cout << msg << std::endl;
}