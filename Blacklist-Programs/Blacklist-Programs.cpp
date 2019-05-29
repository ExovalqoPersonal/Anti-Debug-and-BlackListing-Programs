// Blacklist-Programs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <time.h>

using namespace std;

const wchar_t* yourOwnProcess = L"UpdatedCrackMe.exe";
DWORD procId = NULL;

bool isYourProcessRunning()
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (_wcsicmp(entry.szExeFile, yourOwnProcess) == 0)
			{
				!procId ? procId = entry.th32ProcessID: procId;
				return true;
			}

	CloseHandle(snapshot);
	return false;

}

void ifProcessRunning(const wchar_t* processName)
{

	
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (_wcsicmp(entry.szExeFile, processName) == 0)
			{
				wstring sProcess(processName);
				wcout << "[" << sProcess << "]" << " Illegal Process" << endl;
				HANDLE yourProcess = OpenProcess(PROCESS_TERMINATE, false, procId);
				TerminateProcess(yourProcess, 1);
				CloseHandle(yourProcess);
			}

	CloseHandle(snapshot);
	HANDLE yourProcess = OpenProcess(PROCESS_ALL_ACCESS, false, procId);
	BOOL remoteDebugger = FALSE;
	CheckRemoteDebuggerPresent(yourProcess, &remoteDebugger);
	if(remoteDebugger)
	{
		wcout << "Remote Debugger Attached [ShutDown]" << endl;
		TerminateProcess(yourProcess, 1);
	}
	CloseHandle(yourProcess);
	

}

//Needs Updating (Converts char* to wchar_t*)
/*const wchar_t* getWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs_s(&cSize, wc, c, cSize);

	return wc;
}*/

int main(int argc, char* argv[])
{
	//if (argc == 1)
		//cout << "Usage: Please Enter Application Name" << endl;
	//else{

		//yourOwnProcess = getWC(argv[1]);

		//wcout << yourOwnProcess << endl;
		if (isYourProcessRunning())
		{
			wcout << "Attached to Process: " << yourOwnProcess << endl;
			while (isYourProcessRunning())
			{
				ifProcessRunning(L"Fiddler.exe");
				ifProcessRunning(L"Wireshark.exe");
				ifProcessRunning(L"JustDecompile.exe");
				ifProcessRunning(L"ILSpy.exe");
				ifProcessRunning(L"dumpcap.exe");
				ifProcessRunning(L"Cain.exe");
				ifProcessRunning(L"rpcapd.exe");
				ifProcessRunning(L"Procmon.exe");
				ifProcessRunning(L"Procmon64.exe");
				ifProcessRunning(L"ollydbg.exe");
				ifProcessRunning(L"ollydbg64.exe");
				//ifProcessRunning(L"x32dbg.exe");
				//ifProcessRunning(L"x64dbg.exe");
				ifProcessRunning(L"HxD.exe");
				ifProcessRunning(L"Charles.exe");
				ifProcessRunning(L"ida64.exe");
				ifProcessRunning(L"Taskmgr.exe");
				ifProcessRunning(L"dnSpy-x86.exe");
				ifProcessRunning(L"dnSpyx64.exe");
				ifProcessRunning(L"FolderChangesView.exe");
				ifProcessRunning(L"ProcessHacker.exe");
				ifProcessRunning(L"MegaDumper.exe");

			}
			wcout << yourOwnProcess << " Was Terminated... Shutting Down" << endl;
		}
		else {

			clock_t start = clock();
			wcout << "Process Not Found.... Waiting 5 Seconds Until Shutdown" << endl;
			while (true)
			{
				clock_t testTime = clock();
				clock_t timePassed = testTime - start;
				double secondsPassed = timePassed / (double)CLOCKS_PER_SEC;
				if (secondsPassed >= 5)
					break;
				if (isYourProcessRunning())
				{
					main(argc, argv);
					break;
				}
			}

		}
	//}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
