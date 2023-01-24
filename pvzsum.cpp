#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
int main() {
	HWND h = ::FindWindow(NULL, L"Plants vs. Zombies");	//	寻找并打开进程
	DWORD processid;
	GetWindowThreadProcessId(h, &processid);
	HANDLE hprocess = 0;
	hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);

	if (hprocess == 0) {	//	对应处理
		printf("打开进程失败!\n");
		return 1;
	}
	else {
		printf("打开进程成功!\n");

		int sumnum;
		int xiugai;
		LPCVOID mbase = (LPCVOID)(0x00755E0C);   //定义静态变量  阳光的静态地址
		LPVOID mbuffer = (LPVOID)&sumnum;	   //定义存储阳光值得变量
		::ReadProcessMemory(hprocess, mbase, mbuffer, 4, 0);
		mbase = (LPCVOID)(sumnum + 0x868);
		::ReadProcessMemory(hprocess, mbase, mbuffer, 4, 0);
		mbase = (LPCVOID)(sumnum + 0x5578);
		::ReadProcessMemory(hprocess, mbase, mbuffer, 4, 0);
		printf("当前阳光数量:%d\n", sumnum);
		while (true){
			scanf("%d", &xiugai);
			WriteProcessMemory(hprocess, (LPVOID)mbase, &xiugai, 4, 0);
			printf("修改成功，当前阳光数量：%d", xiugai);
			printf("\n");
		}
		
	}
}