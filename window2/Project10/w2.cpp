#include<stdio.h>
#include<windows.h>
int main()
{
	TCHAR szSystemDir[MAX_PATH];
	GetSystemDirectory(szSystemDir, MAX_PATH);
	printf("%s\n", szSystemDir);
	HANDLE hFile;
	DWORD dwWritten;
	hFile = CreateFile("systemroot.txt",
		GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		if (!WriteFile(hFile, szSystemDir, lstrlen(szSystemDir), &dwWritten, NULL))
		{
			return GetLastError();
		}
	}
	CloseHandle(hFile);
	printf("ok\n");
	system("pause");
	return 0;

}