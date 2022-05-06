#include <windows.h>

typedef NTSTATUS(NTAPI* NtResumeProcess)(IN HANDLE ProcessHandle);

static NtResumeProcess pfnNtResumeProcess = (NtResumeProcess)GetProcAddress(
	GetModuleHandle(L"ntdll"), "NtResumeProcess");

static inline NTSTATUS ResumeProcess(DWORD pid)
{
	HANDLE processHandle = OpenProcess(PROCESS_SUSPEND_RESUME, FALSE, pid);
	NTSTATUS status = pfnNtResumeProcess(processHandle);
	CloseHandle(processHandle);
	return status;
}

int main(int argc, char* argv[])
{
	if (argc == 2) {
		DWORD pid = atoi(argv[1]);
		return ResumeProcess(pid);
	}
}