#define _WINSOCK_DEPRECATED_NO_WARNINGS // ratio + don't care
#define _CRT_SECURE_NO_WARNINGS // ratio + don't care
#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <intrin.h>
#include <wininet.h>
#include <filesystem>
#include <fstream>
#include <array>
#include <map>
#include <unordered_map>
#include <tlhelp32.h>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "Ws2_32.lib")

#include "min_hook.hpp"
#include "bin.hpp"

void fix_imports()
{
	*reinterpret_cast<FARPROC*>(0x41146000) = GetProcAddress(LoadLibraryA("advapi32.dll"), "CryptAcquireContextA");
	*reinterpret_cast<FARPROC*>(0x41146004) = GetProcAddress(LoadLibraryA("advapi32.dll"), "CryptReleaseContext");
	*reinterpret_cast<FARPROC*>(0x41146008) = GetProcAddress(LoadLibraryA("advapi32.dll"), "CryptGenRandom");
	*reinterpret_cast<FARPROC*>(0x41146010) = GetProcAddress(LoadLibraryA("crypt32.dll"), "CertOpenStore");
	*reinterpret_cast<FARPROC*>(0x41146014) = GetProcAddress(LoadLibraryA("crypt32.dll"), "CertEnumCertificatesInStore");
	*reinterpret_cast<FARPROC*>(0x41146018) = GetProcAddress(LoadLibraryA("crypt32.dll"), "CertCloseStore");
	*reinterpret_cast<FARPROC*>(0x4114601C) = GetProcAddress(LoadLibraryA("crypt32.dll"), "CertFreeCRLContext");
	*reinterpret_cast<FARPROC*>(0x41146024) = GetProcAddress(LoadLibraryA("gdi32.dll"), "AddFontMemResourceEx");
	*reinterpret_cast<FARPROC*>(0x4114602C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetTickCount");
	*reinterpret_cast<FARPROC*>(0x41146030) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GlobalAlloc");
	*reinterpret_cast<FARPROC*>(0x41146034) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GlobalUnlock");
	*reinterpret_cast<FARPROC*>(0x41146038) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GlobalLock");
	*reinterpret_cast<FARPROC*>(0x4114603C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "RaiseException");
	*reinterpret_cast<FARPROC*>(0x41146040) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCurrentProcess");
	*reinterpret_cast<FARPROC*>(0x41146044) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetPriorityClass");
	*reinterpret_cast<FARPROC*>(0x41146048) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetPriorityClass");
	*reinterpret_cast<FARPROC*>(0x4114604C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "VirtualAlloc");
	*reinterpret_cast<FARPROC*>(0x41146050) = GetProcAddress(LoadLibraryA("kernel32.dll"), "VirtualFree");
	*reinterpret_cast<FARPROC*>(0x41146054) = GetProcAddress(LoadLibraryA("kernel32.dll"), "VirtualQuery");
	*reinterpret_cast<FARPROC*>(0x41146058) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapCreate");
	*reinterpret_cast<FARPROC*>(0x4114605C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapAlloc");
	*reinterpret_cast<FARPROC*>(0x41146060) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapReAlloc");
	*reinterpret_cast<FARPROC*>(0x41146064) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapFree");
	*reinterpret_cast<FARPROC*>(0x41146068) = GetProcAddress(LoadLibraryA("kernel32.dll"), "Sleep");
	*reinterpret_cast<FARPROC*>(0x4114606C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCurrentProcessId");
	*reinterpret_cast<FARPROC*>(0x41146070) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCurrentThreadId");
	*reinterpret_cast<FARPROC*>(0x41146074) = GetProcAddress(LoadLibraryA("kernel32.dll"), "OpenThread");
	*reinterpret_cast<FARPROC*>(0x41146078) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SuspendThread");
	*reinterpret_cast<FARPROC*>(0x4114607C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ResumeThread");
	*reinterpret_cast<FARPROC*>(0x41146080) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetThreadContext");
	*reinterpret_cast<FARPROC*>(0x41146084) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetThreadContext");
	*reinterpret_cast<FARPROC*>(0x41146088) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FlushInstructionCache");
	*reinterpret_cast<FARPROC*>(0x4114608C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "VirtualProtect");
	*reinterpret_cast<FARPROC*>(0x41146090) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CloseHandle");
	*reinterpret_cast<FARPROC*>(0x41146094) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateToolhelp32Snapshot");
	*reinterpret_cast<FARPROC*>(0x41146098) = GetProcAddress(LoadLibraryA("kernel32.dll"), "Thread32First");
	*reinterpret_cast<FARPROC*>(0x4114609C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "Thread32Next");
	*reinterpret_cast<FARPROC*>(0x411460A0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "MultiByteToWideChar");
	*reinterpret_cast<FARPROC*>(0x411460A4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitializeCriticalSection");
	*reinterpret_cast<FARPROC*>(0x411460A8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "EnterCriticalSection");
	*reinterpret_cast<FARPROC*>(0x411460AC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LeaveCriticalSection");
	*reinterpret_cast<FARPROC*>(0x411460B0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "DeleteCriticalSection");
	*reinterpret_cast<FARPROC*>(0x411460B4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ReleaseSemaphore");
	*reinterpret_cast<FARPROC*>(0x411460B8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WaitForSingleObject");
	*reinterpret_cast<FARPROC*>(0x411460BC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateSemaphoreA");
	*reinterpret_cast<FARPROC*>(0x411460C0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitOnceInitialize");
	*reinterpret_cast<FARPROC*>(0x411460C4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ReleaseSRWLockExclusive");
	*reinterpret_cast<FARPROC*>(0x411460C8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ReleaseSRWLockShared");
	*reinterpret_cast<FARPROC*>(0x411460CC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "AcquireSRWLockExclusive");
	*reinterpret_cast<FARPROC*>(0x411460D0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "AcquireSRWLockShared");
	*reinterpret_cast<FARPROC*>(0x411460D4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateThread");
	*reinterpret_cast<FARPROC*>(0x411460D8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetThreadPriority");
	*reinterpret_cast<FARPROC*>(0x411460DC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ResetEvent");
	*reinterpret_cast<FARPROC*>(0x411460E0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetEvent");
	*reinterpret_cast<FARPROC*>(0x411460E4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WriteFile");
	*reinterpret_cast<FARPROC*>(0x411460E8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateFileA");
	*reinterpret_cast<FARPROC*>(0x411460EC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WideCharToMultiByte");
	*reinterpret_cast<FARPROC*>(0x411460F0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetProcAddress");
	*reinterpret_cast<FARPROC*>(0x411460F4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleHandleA");
	*reinterpret_cast<FARPROC*>(0x411460F8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindNextFileA");
	*reinterpret_cast<FARPROC*>(0x411460FC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindFirstFileA");
	*reinterpret_cast<FARPROC*>(0x41146100) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindClose");
	*reinterpret_cast<FARPROC*>(0x41146104) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateDirectoryW");
	*reinterpret_cast<FARPROC*>(0x41146108) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WriteConsoleW");
	*reinterpret_cast<FARPROC*>(0x4114610C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetStdHandle");
	*reinterpret_cast<FARPROC*>(0x41146110) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreatePipe");
	*reinterpret_cast<FARPROC*>(0x41146114) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetExitCodeProcess");
	*reinterpret_cast<FARPROC*>(0x41146118) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleHandleW");
	*reinterpret_cast<FARPROC*>(0x4114611C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateDirectoryA");
	*reinterpret_cast<FARPROC*>(0x41146120) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapSize");
	*reinterpret_cast<FARPROC*>(0x41146124) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetProcessHeap");
	*reinterpret_cast<FARPROC*>(0x41146128) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FreeEnvironmentStringsW");
	*reinterpret_cast<FARPROC*>(0x4114612C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetEnvironmentStringsW");
	*reinterpret_cast<FARPROC*>(0x41146130) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCommandLineW");
	*reinterpret_cast<FARPROC*>(0x41146134) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCommandLineA");
	*reinterpret_cast<FARPROC*>(0x41146138) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetOEMCP");
	*reinterpret_cast<FARPROC*>(0x4114613C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetACP");
	*reinterpret_cast<FARPROC*>(0x41146140) = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsValidCodePage");
	*reinterpret_cast<FARPROC*>(0x41146144) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetTimeZoneInformation");
	*reinterpret_cast<FARPROC*>(0x41146148) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ReadConsoleW");
	*reinterpret_cast<FARPROC*>(0x4114614C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFileSizeEx");
	*reinterpret_cast<FARPROC*>(0x41146150) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetConsoleMode");
	*reinterpret_cast<FARPROC*>(0x41146154) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetConsoleOutputCP");
	*reinterpret_cast<FARPROC*>(0x41146158) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FlushFileBuffers");
	*reinterpret_cast<FARPROC*>(0x4114615C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "EnumSystemLocalesW");
	*reinterpret_cast<FARPROC*>(0x41146160) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetUserDefaultLCID");
	*reinterpret_cast<FARPROC*>(0x41146164) = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsValidLocale");
	*reinterpret_cast<FARPROC*>(0x41146168) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetLocaleInfoW");
	*reinterpret_cast<FARPROC*>(0x4114616C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LCMapStringW");
	*reinterpret_cast<FARPROC*>(0x41146170) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CompareStringW");
	*reinterpret_cast<FARPROC*>(0x41146174) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetTimeFormatW");
	*reinterpret_cast<FARPROC*>(0x41146178) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetDateFormatW");
	*reinterpret_cast<FARPROC*>(0x4114617C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFileType");
	*reinterpret_cast<FARPROC*>(0x41146180) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetStdHandle");
	*reinterpret_cast<FARPROC*>(0x41146184) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateProcessW");
	*reinterpret_cast<FARPROC*>(0x41146188) = GetProcAddress(LoadLibraryA("kernel32.dll"), "DuplicateHandle");
	*reinterpret_cast<FARPROC*>(0x4114618C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleFileNameW");
	*reinterpret_cast<FARPROC*>(0x41146190) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ExitProcess");
	*reinterpret_cast<FARPROC*>(0x41146194) = GetProcAddress(LoadLibraryA("kernel32.dll"), "DeleteFileW");
	*reinterpret_cast<FARPROC*>(0x41146198) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetEnvironmentVariableW");
	*reinterpret_cast<FARPROC*>(0x4114619C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetDriveTypeW");
	*reinterpret_cast<FARPROC*>(0x411461A0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FormatMessageA");
	*reinterpret_cast<FARPROC*>(0x411461A4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LocalFree");
	*reinterpret_cast<FARPROC*>(0x411461A8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetLocaleInfoEx");
	*reinterpret_cast<FARPROC*>(0x411461AC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCurrentDirectoryW");
	*reinterpret_cast<FARPROC*>(0x411461B0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateFileW");
	*reinterpret_cast<FARPROC*>(0x411461B4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindFirstFileW");
	*reinterpret_cast<FARPROC*>(0x411461B8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindFirstFileExW");
	*reinterpret_cast<FARPROC*>(0x411461BC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindNextFileW");
	*reinterpret_cast<FARPROC*>(0x411461C0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFileAttributesExW");
	*reinterpret_cast<FARPROC*>(0x411461C4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFullPathNameW");
	*reinterpret_cast<FARPROC*>(0x411461C8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetEndOfFile");
	*reinterpret_cast<FARPROC*>(0x411461CC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetFilePointerEx");
	*reinterpret_cast<FARPROC*>(0x411461D0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetTempPathW");
	*reinterpret_cast<FARPROC*>(0x411461D4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "AreFileApisANSI");
	*reinterpret_cast<FARPROC*>(0x411461D8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetLastError");
	*reinterpret_cast<FARPROC*>(0x411461DC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "MoveFileExW");
	*reinterpret_cast<FARPROC*>(0x411461E0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFileInformationByHandleEx");
	*reinterpret_cast<FARPROC*>(0x411461E4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "QueryPerformanceCounter");
	*reinterpret_cast<FARPROC*>(0x411461E8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "QueryPerformanceFrequency");
	*reinterpret_cast<FARPROC*>(0x411461EC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WaitForSingleObjectEx");
	*reinterpret_cast<FARPROC*>(0x411461F0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetExitCodeThread");
	*reinterpret_cast<FARPROC*>(0x411461F4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetNativeSystemInfo");
	*reinterpret_cast<FARPROC*>(0x411461F8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitializeCriticalSectionEx");
	*reinterpret_cast<FARPROC*>(0x411461FC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "EncodePointer");
	*reinterpret_cast<FARPROC*>(0x41146200) = GetProcAddress(LoadLibraryA("kernel32.dll"), "DecodePointer");
	*reinterpret_cast<FARPROC*>(0x41146204) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LCMapStringEx");
	*reinterpret_cast<FARPROC*>(0x41146208) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitOnceInitialize");
	*reinterpret_cast<FARPROC*>(0x4114620C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WakeConditionVariable");
	*reinterpret_cast<FARPROC*>(0x41146210) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WakeAllConditionVariable");
	*reinterpret_cast<FARPROC*>(0x41146214) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SleepConditionVariableCS");
	*reinterpret_cast<FARPROC*>(0x41146218) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SleepConditionVariableSRW");
	*reinterpret_cast<FARPROC*>(0x4114621C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetSystemTimeAsFileTime");
	*reinterpret_cast<FARPROC*>(0x41146220) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TryEnterCriticalSection");
	*reinterpret_cast<FARPROC*>(0x41146224) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetStringTypeW");
	*reinterpret_cast<FARPROC*>(0x41146228) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCPInfo");
	*reinterpret_cast<FARPROC*>(0x4114622C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitializeSListHead");
	*reinterpret_cast<FARPROC*>(0x41146230) = GetProcAddress(LoadLibraryA("kernel32.dll"), "UnhandledExceptionFilter");
	*reinterpret_cast<FARPROC*>(0x41146234) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetUnhandledExceptionFilter");
	*reinterpret_cast<FARPROC*>(0x41146238) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TerminateProcess");
	*reinterpret_cast<FARPROC*>(0x4114623C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsProcessorFeaturePresent");
	*reinterpret_cast<FARPROC*>(0x41146240) = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsDebuggerPresent");
	*reinterpret_cast<FARPROC*>(0x41146244) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetStartupInfoW");
	*reinterpret_cast<FARPROC*>(0x41146248) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetLastError");
	*reinterpret_cast<FARPROC*>(0x4114624C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FreeLibrary");
	*reinterpret_cast<FARPROC*>(0x41146250) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleFileNameA");
	*reinterpret_cast<FARPROC*>(0x41146254) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleHandleExA");
	*reinterpret_cast<FARPROC*>(0x41146258) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LoadLibraryA");
	*reinterpret_cast<FARPROC*>(0x4114625C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "RtlUnwind");
	*reinterpret_cast<FARPROC*>(0x41146260) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InterlockedPushEntrySList");
	*reinterpret_cast<FARPROC*>(0x41146264) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InterlockedFlushSList");
	*reinterpret_cast<FARPROC*>(0x41146268) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitializeCriticalSectionAndSpinCount");
	*reinterpret_cast<FARPROC*>(0x4114626C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TlsAlloc");
	*reinterpret_cast<FARPROC*>(0x41146270) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TlsGetValue");
	*reinterpret_cast<FARPROC*>(0x41146274) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TlsSetValue");
	*reinterpret_cast<FARPROC*>(0x41146278) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TlsFree");
	*reinterpret_cast<FARPROC*>(0x4114627C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LoadLibraryExW");
	*reinterpret_cast<FARPROC*>(0x41146280) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ReadFile");
	*reinterpret_cast<FARPROC*>(0x41146284) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ExitThread");
	*reinterpret_cast<FARPROC*>(0x41146288) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FreeLibraryAndExitThread");
	*reinterpret_cast<FARPROC*>(0x4114628C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleHandleExW");
	*reinterpret_cast<FARPROC*>(0x41146290) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateEventW");
	*reinterpret_cast<FARPROC*>(0x41146298) = GetProcAddress(LoadLibraryA("shell32.dll"), "SHParseDisplayName");
	*reinterpret_cast<FARPROC*>(0x4114629C) = GetProcAddress(LoadLibraryA("shell32.dll"), "SHOpenFolderAndSelectItems");
	*reinterpret_cast<FARPROC*>(0x411462A0) = GetProcAddress(LoadLibraryA("shell32.dll"), "SHGetFolderPathA");
	*reinterpret_cast<FARPROC*>(0x411462A8) = GetProcAddress(LoadLibraryA("user32.dll"), "EmptyClipboard");
	*reinterpret_cast<FARPROC*>(0x411462AC) = GetProcAddress(LoadLibraryA("user32.dll"), "GetKeyNameTextA");
	*reinterpret_cast<FARPROC*>(0x411462B0) = GetProcAddress(LoadLibraryA("user32.dll"), "MapVirtualKeyA");
	*reinterpret_cast<FARPROC*>(0x411462B4) = GetProcAddress(LoadLibraryA("user32.dll"), "SetCursor");
	*reinterpret_cast<FARPROC*>(0x411462B8) = GetProcAddress(LoadLibraryA("user32.dll"), "SetClipboardData");
	*reinterpret_cast<FARPROC*>(0x411462BC) = GetProcAddress(LoadLibraryA("user32.dll"), "GetAsyncKeyState");
	*reinterpret_cast<FARPROC*>(0x411462C0) = GetProcAddress(LoadLibraryA("user32.dll"), "GetFocus");
	*reinterpret_cast<FARPROC*>(0x411462C4) = GetProcAddress(LoadLibraryA("user32.dll"), "CallWindowProcA");
	*reinterpret_cast<FARPROC*>(0x411462C8) = GetProcAddress(LoadLibraryA("user32.dll"), "SetWindowLongA");
	*reinterpret_cast<FARPROC*>(0x411462CC) = GetProcAddress(LoadLibraryA("user32.dll"), "LoadCursorA");
	*reinterpret_cast<FARPROC*>(0x411462D0) = GetProcAddress(LoadLibraryA("user32.dll"), "IsClipboardFormatAvailable");
	*reinterpret_cast<FARPROC*>(0x411462D4) = GetProcAddress(LoadLibraryA("user32.dll"), "GetKeyState");
	*reinterpret_cast<FARPROC*>(0x411462D8) = GetProcAddress(LoadLibraryA("user32.dll"), "OpenClipboard");
	*reinterpret_cast<FARPROC*>(0x411462DC) = GetProcAddress(LoadLibraryA("user32.dll"), "CloseClipboard");
	*reinterpret_cast<FARPROC*>(0x411462E0) = GetProcAddress(LoadLibraryA("user32.dll"), "GetClipboardData");
	*reinterpret_cast<FARPROC*>(0x411462E8) = GetProcAddress(LoadLibraryA("winmm.dll"), "PlaySoundA");
	*reinterpret_cast<FARPROC*>(0x411462F0) = GetProcAddress(LoadLibraryA("wsock32.dll"), "select");
	*reinterpret_cast<FARPROC*>(0x411462F4) = GetProcAddress(LoadLibraryA("wsock32.dll"), "__WSAFDIsSet");
	*reinterpret_cast<FARPROC*>(0x411462F8) = GetProcAddress(LoadLibraryA("wsock32.dll"), "closesocket");
	*reinterpret_cast<FARPROC*>(0x411462FC) = GetProcAddress(LoadLibraryA("ws2_32.dll"), "recv");
	*reinterpret_cast<FARPROC*>(0x41146300) = GetProcAddress(LoadLibraryA("wsock32.dll"), "send");
	*reinterpret_cast<FARPROC*>(0x41146304) = GetProcAddress(LoadLibraryA("wsock32.dll"), "WSAStartup");
	*reinterpret_cast<FARPROC*>(0x41146308) = GetProcAddress(LoadLibraryA("wsock32.dll"), "WSAGetLastError");
	*reinterpret_cast<FARPROC*>(0x4114630C) = GetProcAddress(LoadLibraryA("wsock32.dll"), "connect");
	*reinterpret_cast<FARPROC*>(0x41146310) = GetProcAddress(LoadLibraryA("wsock32.dll"), "ioctlsocket");
	*reinterpret_cast<FARPROC*>(0x41146314) = GetProcAddress(LoadLibraryA("ws2_32.dll"), "setsockopt");
	*reinterpret_cast<FARPROC*>(0x41146318) = GetProcAddress(LoadLibraryA("wsock32.dll"), "socket");
	*reinterpret_cast<FARPROC*>(0x4114631C) = GetProcAddress(LoadLibraryA("ws2_32.dll"), "FreeAddrInfoW");
	*reinterpret_cast<FARPROC*>(0x41146320) = GetProcAddress(LoadLibraryA("ws2_32.dll"), "getaddrinfo");
}

SOCKET g_socket_used_in_cheat = 0;

decltype(&send) oSend;

int PASCAL FAR hooked_send(
	_In_ SOCKET s,
	_In_reads_bytes_(len) const char FAR* buf,
	_In_ int len,
	_In_ int flags)
{
	if (s == g_socket_used_in_cheat)
	{
		return len;
	}
	return oSend(s, buf, len, flags);
}

decltype(&recv) oRecv;

int PASCAL FAR hooked_recv(
	_In_ SOCKET s,
	_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR* buf,
	_In_ int len,
	_In_ int flags)
{
	if (s == g_socket_used_in_cheat)
	{
		auto return_value = oRecv(s, buf, len, flags);

		return return_value;
		//return len;
	}

	return oRecv(s, buf, len, flags);
}

decltype(&connect) oConnect;

int
WSAAPI
hooked_connect(
	_In_ SOCKET s,
	_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
	_In_ int namelen
)
{
	if (_ReturnAddress() >= reinterpret_cast<void*>(0x40B50000) && _ReturnAddress() < reinterpret_cast<void*>(0x40B50000 + sizeof(hack_bin)))
	{
		g_socket_used_in_cheat = s;
		//printf("[+] connect called!\n");
		return true;
	}

	return oConnect(s, name, namelen);
}

decltype(&GetCurrentProcessId) oGetCurrentProcessId;

DWORD
WINAPI
hooked_GetCurrentProcessId(
	VOID
)
{
	return 3936;
}

using find_pattern_t = int(__cdecl*)(void* dll_base, std::string& sig, int unk);
find_pattern_t ofind_pattern = 0;

int find_pattern_func(void* dll_base, const char* pattern, int offset = 0)
{
	// pattern to bytes
	int pattern_bytes[256];
	int pattern_bytes_size = 0;
	for (char* current = (const_cast<char*>(pattern)); current < (const_cast<char*>(pattern) + strlen(pattern)); current++) {
		if (*current == '?') {
			++current;
			if (*current == '?')
				++current;
			pattern_bytes[pattern_bytes_size] = -1;
			pattern_bytes_size++;
		}
		else {
			pattern_bytes[pattern_bytes_size] = strtoul(current, &current, 16);
			pattern_bytes_size++;
		}
	}

	BYTE* scan_address = static_cast<BYTE*>(dll_base);
	auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(scan_address);
	auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>((scan_address + dos_header->e_lfanew));
	int scan_size = nt_headers->OptionalHeader.SizeOfImage - pattern_bytes_size;

	// scan
	for (int i = 0; i < scan_size; i++)
	{
		bool found = true;
		for (int j = 0; j < pattern_bytes_size; ++j)
		{
			if (scan_address[i + j] != pattern_bytes[j] && pattern_bytes[j] != -1)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return reinterpret_cast<int>(&scan_address[i]) + offset;
		}
	}

	return 0;
}

int __cdecl hooked_find_pattern(void* dll, std::string & sig, int unk)
{
	//auto original = ofind_pattern(dll, sig, offset);
	int pattern = find_pattern_func(dll, sig.data());
	//printf("[+] find_pattern called -> %p -> %s -> %p\n", dll, sig.data(), pattern);
	if (!pattern)
	{
		printf("[-] find_pattern invalid...\n");
		system("pause");
	}
	return pattern;
}

// c&p from somewhere
typedef void* (*create_interface_fn)(const char* pName, int* pReturnCode);

create_interface_fn get_module_factory(HMODULE module)
{
	return reinterpret_cast<create_interface_fn>(GetProcAddress(module, "CreateInterface"));
}

void* get_interface(create_interface_fn f, const char* szInterfaceVersion)
{
	auto result = reinterpret_cast<void*>(f(szInterfaceVersion, nullptr));

	// error checking ?? loooooooooooooooooooool

	return result;
}

struct module_info_t
{
	uint32_t start = 0;
	uint32_t end = 0;
	std::string name = "";
	create_interface_fn interface_ = static_cast<create_interface_fn>(0);
};

std::vector<module_info_t> g_modules_dumped = { };

std::vector<module_info_t> g_sigs_dumped = { };


struct sig_struct_t
{
	const char* dll_name = 0;
	const char* sig = 0;
};

//hash & dll_name,sig
std::unordered_map<uint32_t, sig_struct_t> g_sig_addresses = {};

struct interface_struct_t
{
	const char* name = 0;
	bool is_sig = false;
	int offset = 0;
};

//address interface_name
std::unordered_map<int, interface_struct_t> g_interface_addresses = {};

void init()
{
	// Should name them name instead of sig lol ( too lazy it works anyway )
	g_interface_addresses.insert({ 0x61cf08c4, { "VGUI_Panel009" } });
	g_interface_addresses.insert({ 0x628847d0, { "VGUI_Surface031" } });
	g_interface_addresses.insert({ 0x2e6b7b18, { "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 8B 08", true, 2 } });
	g_interface_addresses.insert({ 0x5416d0f8, { "A1 ?? ?? ?? ?? B9 ?? ?? ?? ?? 56 6A 01", true, 1 } });
	g_interface_addresses.insert({ 0x2e6dce74, { "B9 ?? ?? ?? ?? A1 ?? ?? ?? ?? FF 50 ?? 8B C8 85 C9 74 07 8B 01 FF 50 ?? EB 02 33 C0 3B C6", true, 1 } });
	g_interface_addresses.insert({ 0x2eb17ed0, { "B9 ?? ?? ?? ?? 8B 87 64 33 00 00", true, 1 } });
	g_interface_addresses.insert({ 0x2eb1ade8, { "B9 ?? ?? ?? ?? 8B 40 38 FF D0 84 C0 74 17 A1 ?? ?? ?? ?? B9 ?? ?? ?? ?? 8B 40 3C FF D0 84 C0 0F 84 ?? ?? ?? ?? 8B 45 0C", true, 1 } });
	g_interface_addresses.insert({ 0x50e1d3e0, { "A1 ?? ?? ?? ?? B9 ?? ?? ?? ?? 8B 80 6C 01 00 00", true, 1 } });
	g_interface_addresses.insert({ 0x714ad310, { "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? B9 ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 0F 11 05", true, 2 } });
	g_interface_addresses.insert({ 0x5109c4c8, { "B9 ?? ?? ?? ?? A1 ?? ?? ?? ?? 6A 00 6A 00", true, 1 } });
	g_interface_addresses.insert({ 0x51004720, { "B9 ?? ?? ?? ?? 6A 00 FF 50 ?? A1 ?? ?? ?? ?? B9 ?? ?? ?? ?? FF 50 ?? 8B 0D", true, 1 } });
	g_interface_addresses.insert({ 0x62aa2ac8, { "B9 ?? ?? ?? ?? C7 46 20 00 00 00 00", true, 1 } });
	g_interface_addresses.insert({ 0x70ff6078, { "B9 ?? ?? ?? ?? F3 0F 59 C5", true, 1 } });
	g_interface_addresses.insert({ 0x50e273fc, { "B9 ?? ?? ?? ?? 68 03 40 00 00 50 A1 ?? ?? ?? ?? FF 50 ?? F3 0F 10 8C 24 C4 00 00 00", true, 1 } });
	g_interface_addresses.insert({ 0x50E2D558, { "A1 ?? ?? ?? ?? B9 ?? ?? ?? ?? FF 75 14", true, 1 } });
	g_interface_addresses.insert({ 0x50e1fea8, { "VDebugOverlay004" } });
	g_interface_addresses.insert({ 0x50dae654, { "IEngineSoundClient003" } });
	g_interface_addresses.insert({ 0x62788a70, { "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? B8 FF FF 00 00", true, 2 } });
	g_interface_addresses.insert({ 0x5567fe98, { "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? B8 ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05", true, 2 } });
	g_interface_addresses.insert({ 0x50e21d0c, { "VEngineRenderView014" } });
	g_interface_addresses.insert({ 0x50e2ee88, { "B9 ?? ?? ?? ?? 50 E8 ?? ?? ?? ?? 84 C0 0F 85", true, 1 } });
	g_interface_addresses.insert({ 0x2e6ecfc0, { "B9 ?? ?? ?? ?? C1 E8 0B 24 01 0F B6 C0 50 0F B7 87 72 02 00 00 50 A1 ?? ?? ?? ?? FF 50 ?? 8B 87 F0 00 00 00 B9 ?? ?? ?? ?? C1 E8 0C 24 01 0F B6 C0 50 0F B7 87 72 02 00 00 50 A1 ?? ?? ?? ?? FF 90 ?? ?? ?? ?? 5F", true, 1 } });
	g_interface_addresses.insert({ 0x70feaa5c, { "B9 ?? ?? ?? ?? FF 50 ?? F3 0F 10 45 08", true, 1 } });
	g_interface_addresses.insert({ 0x50e21cec, { "VEngineEffects001" } });
	g_interface_addresses.insert({ 0x69f64f18, { "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? C7 05", true, 2 } });
	g_interface_addresses.insert({ 0x71065388, { "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? B9 10 00 00 00", true, 2 } });

	g_sig_addresses.insert({ 0xc05c64c, {"client.dll", "55 8B EC 83 E4 F8 83 EC 70 56 57 8B F9 89 7C 24 14" } });
	g_sig_addresses.insert({ 0xc62aa8b3, {"client.dll", "8B B7 4C 29 00 00 89 74 24 20" } });
	g_sig_addresses.insert({ 0xf051208a, {"client.dll", "8D 8F 20 9B 00 00 6A 01" } });
	g_sig_addresses.insert({ 0x3ddb7621, {"client.dll", "8A 87 E1 35 00 00" } });
	g_sig_addresses.insert({ 0xb59e105e, {"client.dll", "55 8B EC 83 EC 10 53 56 57 8B 7D 10" } });
	g_sig_addresses.insert({ 0x78cce6d5, {"client.dll", "8B 35 ?? ?? ?? ?? FF 10 0F B7 C0 B9 ?? ?? ?? ?? 50 FF 56 ?? 85 C0" } });
	g_sig_addresses.insert({ 0x13d4aced, {"client.dll", "8D 87 68 0A 00 00 50 E8" } });
	g_sig_addresses.insert({ 0x8cc9ff64, {"client.dll", "89 86 10 29 00 00" } });
	g_sig_addresses.insert({ 0x9a0aaf49, {"client.dll", "8D 8F 70 CF 00 00" } });
	g_sig_addresses.insert({ 0x63aa2ad9, {"client.dll", "80 3D ?? ?? ?? ?? ?? 74 16 A1 ?? ?? ?? ?? 48 C7 81 28 29 00 00 FF FF 7F FF" } });
	g_sig_addresses.insert({ 0xb313bdd1, {"client.dll", "8B 35 ?? ?? ?? ?? 8D 4C 24 20" } });
	g_sig_addresses.insert({ 0xcc702117, {"client.dll", "55 8B EC 83 E4 F0 81 EC 58 01 00 00 33 D2" } });
	g_sig_addresses.insert({ 0xd78f23e8, {"client.dll", "FF B7 10 29 00 00" } });
	g_sig_addresses.insert({ 0xe6eaabdb, {"client.dll", "8B 89 90 29 00 00 8D 0C D1" } });
	g_sig_addresses.insert({ 0x321907d2, {"client.dll", "FF 15 ?? ?? ?? ?? 80 BE 74 02 00 00 00 0F 84 98 02 00 00" } });
	g_sig_addresses.insert({ 0xf3dac366, {"client.dll", "8B 8F 6C 26 00 00 89 4C 24 1C" } });
	g_sig_addresses.insert({ 0x5586ce17, {"client.dll", "8B 8E 60 99 00 00 85 C9" } });
	g_sig_addresses.insert({ 0x10081c3b, {"client.dll", "80 BF 14 9B 00 00 00 0F 84" } });
	g_sig_addresses.insert({ 0x1d72700c, {"client.dll", "55 8B EC 83 E4 F8 F3 0F 10 42 30" } });
	g_sig_addresses.insert({ 0x3720a12b, {"client.dll", "89 86 C0 03 01 00" } });
	g_sig_addresses.insert({ 0x8cb22e69, {"client.dll", "E8 ?? ?? ?? ?? 8B 47 60 83 B8 9C 29 00 00 00" } });
	g_sig_addresses.insert({ 0x99688ee0, {"client.dll", "8D 8F 50 1C 01 00" } });
	g_sig_addresses.insert({ 0x1b88ce21, {"client.dll", "55 8B EC 83 E4 F8 83 EC 2C 53 8B D9 56 57 8B 03" } });
	g_sig_addresses.insert({ 0xdbc96a68, {"engine.dll", "75 30 8B 87 30 4D 00 00" } });
	g_sig_addresses.insert({ 0xb7a8a31a, {"client.dll", "80 BF 14 9B 00 00 00 0F 84" } });
	g_sig_addresses.insert({ 0xec372476, {"client.dll", "55 8B EC 83 E4 F0 81 EC 98 05 00 00 8B 81 F8 0F 00 00" } });
	g_sig_addresses.insert({ 0x9732dac4, {"client.dll", "80 BF 2C 2A 00 00 00" } });
	g_sig_addresses.insert({ 0xcb0e7fef, {"client.dll", "83 BE E8 09 00 00 00 7F 67" } });
	g_sig_addresses.insert({ 0x978d6f27, {"client.dll", "E8 ?? ?? ?? ?? F3 0F 10 45 18 8D 84 24 90 00 00 00" } });
	g_sig_addresses.insert({ 0x630ba5f7, {"client.dll", "C6 86 70 33 00 00 01" } });
	g_sig_addresses.insert({ 0x9665b249, {"client.dll", "56 8B F1 0F 57 C0 C7 86 80 00 00 00 00 00 00 00" } });
	g_sig_addresses.insert({ 0x49626569, {"client.dll", "55 8B EC 81 EC 88 00 00 00 56 8B F1" } });
	g_sig_addresses.insert({ 0xe6d497f8, {"client.dll", "E8 ?? ?? ?? ?? FF 75 08 8B 8E 10 29 00 00" } });
	g_sig_addresses.insert({ 0x31512ec, {"client.dll", "53 8B D9 F6 C3 03 74 0B FF 15 ?? ?? ?? ?? 84 C0 74 01 CC C7 83 F0 0F 00 00 00 00 00 00" } });
	g_sig_addresses.insert({ 0xfc48a4be, {"client.dll", "E8 ?? ?? ?? ?? 83 7E 10 00 74 64" } });
	g_sig_addresses.insert({ 0xddcd38fa, {"client.dll", "E8 ?? ?? ?? ?? 8B 87 10 29 00 00" } });
	g_sig_addresses.insert({ 0x7bc3a8e, {"client.dll", "56 8B F1 57 8D 8E 10 10 00 00" } });
	g_sig_addresses.insert({ 0x953c420c, {"client.dll", "55 8B EC 83 EC 08 8B 45 08 56 57 8B F9 8D 8F FC 0F 00 00" } });
	g_sig_addresses.insert({ 0x96060043, {"server.dll", "8B 15 ?? ?? ?? ?? 33 C9 83 7A 18 01 7C 22 8B 52 60 85 D2 74 1B 8B 42 10 D1 E8 A8 01 75 12 8B 4A 1C 85 C9 74 09 8B 01 FF 50 ?? 8B C8 EB 02 33 C9 85 C9" } });
	g_sig_addresses.insert({ 0xbfbcf44e, {"client.dll", "55 8B EC 83 EC 10 53 8B D9 89 55 F8" } });
	g_sig_addresses.insert({ 0x596984ff, {"client.dll", "55 8B EC 83 E4 F0 B8 38 11 00 00" } });
	g_sig_addresses.insert({ 0xd112472a, {"client.dll", "55 8B EC 83 E4 F8 81 EC 90 00 00 00 8B C1" } });
	g_sig_addresses.insert({ 0x3ecb2b71, {"engine.dll", "74 0F 80 BF 48 4D 00 00 00" } });
	g_sig_addresses.insert({ 0x4911cf54, {"client.dll", "8B 0D ?? ?? ?? ?? BA ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 04" } });
	g_sig_addresses.insert({ 0xb8cc797c, {"client.dll", "55 8B EC 83 EC 14 53 56 57 FF 75 18" } });
	g_sig_addresses.insert({ 0xf870ddb4, {"client.dll", "8B 0D ?? ?? ?? ?? 8B 46 08 68" } });
	g_sig_addresses.insert({ 0xaf26a26c, {"client.dll", "B9 ?? ?? ?? ?? F3 0F 11 04 24 FF 50 ?? FF D7" } });
	g_sig_addresses.insert({ 0xf743cc72, {"client.dll", "89 35 ?? ?? ?? ?? F3 0F 10 48 20" } });
	g_sig_addresses.insert({ 0xac0a871d, {"client.dll", "83 3D ?? ?? ?? ?? ?? 7E 1C" } });
	g_sig_addresses.insert({ 0xe335ec62, {"client.dll", "A1 ?? ?? ?? ?? F6 44 F0 04 01" } });
	g_sig_addresses.insert({ 0xaf09d530, {"client.dll", "0F 11 05 ?? ?? ?? ?? 83 C8 01" } });
	g_sig_addresses.insert({ 0x1e63778c, {"client.dll", "A1 ?? ?? ?? ?? FF 10 A1 ?? ?? ?? ?? B9" } });
	g_sig_addresses.insert({ 0x15218c62, {"client.dll", "56 8D 51 3C BE 03 00 00 00" } });
	g_sig_addresses.insert({ 0x73dfc8e3, {"client.dll", "A3 ?? ?? ?? ?? 57 8B CB" } });
	g_sig_addresses.insert({ 0xa20084df, {"client.dll", "0F 11 05 ?? ?? ?? ?? 0F 10 87 60 05 00 00" } });
	g_sig_addresses.insert({ 0xc5391d89, {"engine.dll", "03 05 ?? ?? ?? ?? 83 CF 10" } });
	g_sig_addresses.insert({ 0x39f9e956, {"server.dll", "8D 87 FC 03 00 00 89 46 08 C7 46 0C 00 00 00 00 EB 06" } });
	g_sig_addresses.insert({ 0xa892eacf, {"client.dll", "A2 ?? ?? ?? ?? 8B 45 E8" } });
	g_sig_addresses.insert({ 0x53028691, {"server.dll", "8B 8F A8 2C 00 00 85 C9 74 06" } });
	g_sig_addresses.insert({ 0x76231ea1, {"engine.dll", "8B 1D ?? ?? ?? ?? 85 C0 74 16 FF B6 0C 01 00 00" } });
	g_sig_addresses.insert({ 0x7ebd80c5, {"client.dll", "55 8B EC A1 ?? ?? ?? ?? 83 EC 10 56 8B F1 B9" } });
	g_sig_addresses.insert({ 0xd4e84b87, {"server.dll", "FF 86 6C 12 00 00" } });
	g_sig_addresses.insert({ 0x115bb8b, {"client.dll", "B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 5D 08 85 C0" } });
	g_sig_addresses.insert({ 0x6bd5b6c, {"client.dll", "56 52 FF 50 ?? 89 44 24 14" } });
	g_sig_addresses.insert({ 0xb0df5d2b, {"client.dll", "3B 3D ?? ?? ?? ?? 75 4C" } });
	g_sig_addresses.insert({ 0x1bc424b9, {"engine.dll", "55 8B EC 83 EC 08 56 8B F1 8B 4D 04" } });
	g_sig_addresses.insert({ 0x8675e72a, {"shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 ?? 85 C0" } });
	g_sig_addresses.insert({ 0xf836ab50, {"client.dll", "55 8B EC 83 EC 1C 8B 0D ?? ?? ?? ?? 53" } });
	g_sig_addresses.insert({ 0x670a12b6, {"client.dll", "E8 ?? ?? ?? ?? FF 76 0C 8D 48 04" } });
	g_sig_addresses.insert({ 0x73baa13f, {"client.dll", "0F B7 05 ?? ?? ?? ?? 3D FF FF 00 00 74 3F" } });
	g_sig_addresses.insert({ 0x499832fe, {"engine.dll", "85 C0 74 12 53 FF 75 0C 68" } });
	g_sig_addresses.insert({ 0x73341dc1, {"engine.dll", "55 8B EC 83 E4 F0 B8 38 01 10 00" } });
	g_sig_addresses.insert({ 0x17603a3, {"engine.dll", "55 8B EC 83 E4 C0 81 EC B4 00 00 00 53 56 57 8B 7D 08 8B D9" } });
	g_sig_addresses.insert({ 0x6142d525, {"client.dll", "6A 00 FF 50 ?? 8B 0D ?? ?? ?? ?? FF B7 AC 01 00 00" } });
	g_sig_addresses.insert({ 0x594a61b, {"client.dll", "84 C0 74 17 8B 87 44 0A 00 00" } });
	g_sig_addresses.insert({ 0x2c787d88, {"client.dll", "E8 ?? ?? ?? ?? 5E 83 F8 FF" } });
	g_sig_addresses.insert({ 0x54a13745, {"client.dll", "E8 ?? ?? ?? ?? 8B F0 C6 44 24 0E 01" } });
	g_sig_addresses.insert({ 0x3e384190, {"client.dll", "0F 10 05 ?? ?? ?? ?? 8D 85 78 FE FF FF" } });
	g_sig_addresses.insert({ 0x59f94af0, {"client.dll", "FF D0 A1 ?? ?? ?? ?? B9" } });
	g_sig_addresses.insert({ 0x8add58a5, {"client.dll", "84 C0 75 38 8B 0D ?? ?? ?? ?? 8B 01 8B 80 48 01 00 00" } });
	g_sig_addresses.insert({ 0x38593d23, {"client.dll", "55 8B EC 56 8B F1 B9 14 00 00 00" } });
	g_sig_addresses.insert({ 0x7d1aae8a, {"client.dll", "84 C0 75 0D F6 87 28 0A 00 00 0A" } });
	g_sig_addresses.insert({ 0x3dbe64f, {"client.dll", "55 8B EC 83 E4 F8 8B 4D 08 BA ?? ?? ?? ?? E8 ?? ?? ?? ?? 85 C0 75 12" } });
	g_sig_addresses.insert({ 0x305a6de2, {"client.dll", "E8 ?? ?? ?? ?? F3 0F 10 4D F4 83 C4 08" } });
	g_sig_addresses.insert({ 0x12bbf342, {"client.dll", "55 8B EC 57 8B F9 8B 97 9C 29 00 00" } });
	g_sig_addresses.insert({ 0xe80b17ba, {"client.dll", "55 8B EC 83 EC 08 53 56 8B F1 57 89 75 F8" } });
	g_sig_addresses.insert({ 0xecfdb4d4, {"client.dll", "55 8B EC 56 57 8B F9 8B B7 E8 00 00 00" } });
	g_sig_addresses.insert({ 0xe23ab8c6, {"client.dll", "FF 90 ?? ?? ?? ?? FF 35 ?? ?? ?? ?? 8B 4C 24 3C" } });
	g_sig_addresses.insert({ 0x2bfe6e6a, {"client.dll", "FF 90 ?? ?? ?? ?? 8B 86 FC 00 00 00" } });
	g_sig_addresses.insert({ 0xfae77068, {"client.dll", "8B 0D ?? ?? ?? ?? 85 C0 74 0A 8B 01 FF 50 ?? 83 C0 54" } });
	g_sig_addresses.insert({ 0xbb57d72e, {"client.dll", "84 C0 75 05 B0 01" } });
	g_sig_addresses.insert({ 0x1019e968, {"client.dll", "FF 50 ?? 8B 4C 24 20 8B 54 24 1C" } });
	g_sig_addresses.insert({ 0x311eba0b, {"client.dll", "0F 82 ?? ?? ?? ?? FF 50" } });
	g_sig_addresses.insert({ 0x9ffa7202, {"client.dll", "FF B7 B0 01 00 00 8B 01 FF 90 ?? ?? ?? ?? 8B 4C 24 24" } });
	g_sig_addresses.insert({ 0x138a731c, {"engine.dll", "53 8A D9 8B 0D ?? ?? ?? ?? 56 57 8B B9 0C 10 00 00" } });
	g_sig_addresses.insert({ 0xf52f3daf, {"client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04" } });
	g_sig_addresses.insert({ 0xb52fc3ae, {"client.dll", "55 8B EC 51 33 C0 C7 45 FC FF FF FF FF 56 8B F1 81 26 00 00 00 FF C6 46 03 00 89 46 10 89 46 14 88 46 18 89 46 20 89 46 1C 89 46 24 89 46 04 89 46 08 89 46 0C FF 15 ?? ?? ?? ?? 6A 01 FF 75 08 8D 4D FC 8B 10 51 8B C8 FF 52 ?? 8B 0E 33 4D FC 81 E1 FF FF FF 00 31 0E 8B CE 6A 01 FF 75 0C 88 46 03 C1 F8 08 66 89 46 12 E8 ?? ?? ?? ?? 85 C0 74 0A FF 75 10 8B C8 E8 ?? ?? ?? ?? 8B C6" } });
	g_sig_addresses.insert({ 0x6ab01334, {"client.dll", "C6 05 ?? ?? ?? ?? ?? 89 47 70" } });
	g_sig_addresses.insert({ 0x421f595f, {"client.dll", "C6 05 ?? ?? ?? ?? ?? 88 81 ?? ?? ?? ?? F3 0F 10 4E 08" } });
	g_sig_addresses.insert({ 0x25e734a6, {"client.dll", "FF 90 ?? ?? ?? ?? 83 3D ?? ?? ?? ?? ?? 7E 1C" } });
	g_sig_addresses.insert({ 0x6957056, {"client.dll", "C7 87 24 30 00 00 00 00 00 00" } });
	g_sig_addresses.insert({ 0x13bbf3d9, {"client.dll", "FF 90 ?? ?? ?? ?? 8B 07 8B CF FF 90 ?? ?? ?? ?? 8B CF" } });
	g_sig_addresses.insert({ 0x53b94e91, {"client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8 ?? ?? ?? ?? 8B 7D 08" } });
	g_sig_addresses.insert({ 0x20277296, {"engine.dll", "56 57 8B F9 8D 4F 08 C7 07 ?? ?? ?? ?? E8 ?? ?? ?? ?? C7 07" } });
	g_sig_addresses.insert({ 0x4bde48a2, {"engine.dll", "55 8B EC 80 7D 0C 00 F3 0F 10 4D 08" } });
	g_sig_addresses.insert({ 0x50a6b538, {"client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1" } });
	g_sig_addresses.insert({ 0xcecc2b87, {"engine.dll", "55 8B EC 81 EC 64 01 00 00" } });
	g_sig_addresses.insert({ 0x5bfe5118, {"client.dll", "55 8B EC 51 56 8B F1 85 F6 74 68" } });
	g_sig_addresses.insert({ 0xe5193f4c, {"engine.dll", "55 8B EC 81 EC 34 01 00 00 56" } });
	g_sig_addresses.insert({ 0xb8a03746, {"client.dll", "56 6A 01 68 ?? ?? ?? ?? 8B F1" } });
	g_sig_addresses.insert({ 0xb79c175a, {"client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24 0C" } });
	g_sig_addresses.insert({ 0xc9707da1, {"engine.dll", "53 56 57 8B DA 8B F9 FF 15" } });
	g_sig_addresses.insert({ 0x99feee76, {"client.dll", "55 8B EC 53 8B 5D 08 56 8B F1 83 FB FF" } });
	g_sig_addresses.insert({ 0xefee5c50, {"client.dll", "E8 ?? ?? ?? ?? 80 BE F8 13 00 00 00" } });
	g_sig_addresses.insert({ 0x7a1307b, {"engine.dll", "E8 ?? ?? ?? ?? 84 C0 8B 45 08" } });
	g_sig_addresses.insert({ 0x2d81357e, {"client.dll", "55 8B EC 83 E4 F8 83 EC 0C 53 8B 5D 08 8B C3" } });
	g_sig_addresses.insert({ 0xd0ec62ed, {"client.dll", "E8 ?? ?? ?? ?? 8B CF E8 ?? ?? ?? ?? 8B 06" } });
	g_sig_addresses.insert({ 0x757b85ad, {"client.dll", "55 8B EC 83 EC 10 53 56 57 8B F9 8B 87 E8 00 00 00" } });
	g_sig_addresses.insert({ 0x29507176, {"client.dll", "56 8B F1 57 8B BE 5C 34 00 00" } });
	g_sig_addresses.insert({ 0xe644aae4, {"client.dll", "55 8B EC 83 EC 0C 53 56 8B 71 58" } });
	g_sig_addresses.insert({ 0x8a0c5015, {"client.dll", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28" } });
	g_sig_addresses.insert({ 0x25ae6768, {"client.dll", "53 8B DC 83 EC 08 83 E4 F8 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 83 EC 18 56 57 8B 7B 08" } });
	g_sig_addresses.insert({ 0xd34fe914, {"client.dll", "55 8B EC 83 E4 F8 83 EC 70 6A 58" } });
	g_sig_addresses.insert({ 0x1b1e1674, {"client.dll", "55 8B EC 83 E4 F8 51 53 56 8B D9" } });
	g_sig_addresses.insert({ 0xeb5eae36, {"engine.dll", "55 8B EC 53 8B 5D 08 56 8B F1 85 DB 74 57 8B 4E 14 83 F9 10 72 04 8B 06 EB 02 8B C6 3B D8 72 45 83 F9 10 72 04 8B 16 EB 02 8B D6 8B 46 10 03 C2 3B C3 76 31 83 F9 10 72 16 FF 75 0C 8B 06 8B CE 2B D8 53 56 E8 ?? ?? ?? ?? 5E 5B 5D C2 08 00 FF 75 0C 8B C6 8B CE 2B D8 53 56 E8 ?? ?? ?? ?? 5E 5B 5D C2 08 00 57" } });
	g_sig_addresses.insert({ 0x5342b4b9, {"client.dll", "55 8B EC 8B 45 08 57 8B F9 8B 4F 04 85 C9 75 15" } });
	g_sig_addresses.insert({ 0xf70e7841, {"client.dll", "55 8B EC 83 EC 48 53 8B 5D 08" } });
	g_sig_addresses.insert({ 0xbb70a21, {"client.dll", "E8 ?? ?? ?? ?? 8D 47 FC" } });
	g_sig_addresses.insert({ 0x3a5c86c0, {"client.dll", "55 8B EC 83 EC 08 8B 15 ?? ?? ?? ?? 0F 57 C0" } });
	g_sig_addresses.insert({ 0xdfdf2d44, {"client.dll", "E8 ?? ?? ?? ?? A1 ?? ?? ?? ?? F3 0F 10 45 F4" } });
	g_sig_addresses.insert({ 0xe46b563d, {"client.dll", "55 8B EC 83 E4 F0 83 EC 7C 56 52" } });
	g_sig_addresses.insert({ 0x5aa72a66, {"client.dll", "FF 50 ?? 8B 06 8D 4D F4 51 8B CE FF 90 ?? ?? ?? ?? 8B 7D 08" } });
	g_sig_addresses.insert({ 0x6876f4c3, {"client.dll", "8D 8A 1C 02 00 00" } });
	g_sig_addresses.insert({ 0x723e15e4, {"client.dll", "74 43 8B 81 58 01 00 00" } });
	g_sig_addresses.insert({ 0x1b89c3bc, {"client.dll", "A1 ?? ?? ?? ?? 56 8B F1 B9 ?? ?? ?? ?? FF 50 ?? 85 C0 0F 85 22 01 00 00" } });
	g_sig_addresses.insert({ 0xa876ae7d, {"client.dll", "56 8B F1 8B 8E 08 03 00 00 83 F9 FF 74 23" } });
	g_sig_addresses.insert({ 0x8004aed0, {"engine.dll", "8B 0D ?? ?? ?? ?? 8D 95 7C FD FF FF" } });
	g_sig_addresses.insert({ 0xc5793d88, {"engine.dll", "55 8B EC 81 EC 58 0B 00 00" } });
	g_sig_addresses.insert({ 0x60c4477d, {"client.dll", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 57 8B 56 60" } });
	g_sig_addresses.insert({ 0xbce6e7c4, {"client.dll", "55 8B EC 51 56 8B F1 80 BE 14 9B 00 00 00" } });
	g_sig_addresses.insert({ 0xd0eeaf62, {"shaderapidx9.dll", "55 8B EC 83 E4 F8 81 EC BC 00 00 00" } });
	g_sig_addresses.insert({ 0x123e9d18, {"client.dll", "55 8B EC 80 7D 08 00 B8 00 20 00 00" } });
	g_sig_addresses.insert({ 0xcb538045, {"client.dll", "55 8B EC 81 EC 8C 00 00 00 57 8B F9 8B 87 54 0E 00 00" } });
	g_sig_addresses.insert({ 0x3251114e, {"client.dll", "55 8B EC 83 E4 F8 83 EC 0C 53 56 8B F1 57 83 BE 50 29 00 00 00" } });
	g_sig_addresses.insert({ 0xa41c71e3, {"client.dll", "E8 ?? ?? ?? ?? 83 C4 10 EB 79" } });
	g_sig_addresses.insert({ 0x2575fe5f, {"client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 56 8B 75 08 33 DB" } });
	g_sig_addresses.insert({ 0x643339f, {"engine.dll", "E8 ?? ?? ?? ?? 84 DB 0F 84 95 00 00 00" } });
	g_sig_addresses.insert({ 0x863cf8f4, {"client.dll", "E8 ?? ?? ?? ?? 8B 87 44 0A 00 00" } });
	g_sig_addresses.insert({ 0xd2c3d726, {"client.dll", "E8 ?? ?? ?? ?? 80 BE 14 9B 00 00 00 0F 84 ?? ?? ?? ?? 83 BE 60 99 00 00 00 0F 84 ?? ?? ?? ?? B8 FF FF 00 00" } });
	g_sig_addresses.insert({ 0x24f63b92, {"client.dll", "E8 ?? ?? ?? ?? 5E 5D C2 10 00 32 C0" } });
	g_sig_addresses.insert({ 0x8a3b6999, {"client.dll", "55 8B EC 83 E4 F8 81 EC FC 00 00 00 53 56" } });
	g_sig_addresses.insert({ 0x4c344c58, {"engine.dll", "E8 ?? ?? ?? ?? FF 76 60" } });
	g_sig_addresses.insert({ 0x86772ad2, {"engine.dll", "55 8B EC 83 E4 C0 81 EC 74 01 00 00 53 56 8B D9" } });
	g_sig_addresses.insert({ 0x2c7b2313, {"vstdlib.dll", "55 8B EC 8B 01 56 FF 75 08 FF 50 3C 8B F0 85 F6 74 1E" } });
	g_sig_addresses.insert({ 0xf8bf90da, {"client.dll", "55 8B EC 51 A1 ?? ?? ?? ?? 53 56 8B D9" } });
	g_sig_addresses.insert({ 0x4b36571, {"client.dll", "55 8B EC 8B 45 10 F3 0F 10 81 B4 00 00 00" } });

	g_modules_dumped.push_back({ 0x009c0000,0x00bff000,"csgo" });
	g_modules_dumped.push_back({ 0x00d00000,0x00d4e000,"wintrust" });
	g_modules_dumped.push_back({ 0x26b30000,0x28d3a000,"nvwgf2um" });
	g_modules_dumped.push_back({ 0x298c0000,0x2edbf000,"client", get_module_factory(GetModuleHandleA("client.dll")) });
	g_modules_dumped.push_back({ 0x2eec0000,0x2fbb7000,"server" });
	g_modules_dumped.push_back({ 0x357c0000,0x35843000,"mss32" });
	g_modules_dumped.push_back({ 0x358d0000,0x3595e000,"XAudio2_7" });
	g_modules_dumped.push_back({ 0x3d010000,0x3d133000,"serverbrowser" });
	g_modules_dumped.push_back({ 0x50010000,0x500bd000,"panorama_text_pango" });
	g_modules_dumped.push_back({ 0x500c0000,0x501b0000,"cairo" });
	g_modules_dumped.push_back({ 0x501b0000,0x5022c000,"libswscale_3" });
	g_modules_dumped.push_back({ 0x50230000,0x502a6000,"libavutil_54" });
	g_modules_dumped.push_back({ 0x502b0000,0x50329000,"libavformat_56" });
	g_modules_dumped.push_back({ 0x50330000,0x50646000,"libavcodec_56" });
	g_modules_dumped.push_back({ 0x50650000,0x5087e000,"icui18n" });
	g_modules_dumped.push_back({ 0x50880000,0x54240000,"engine", get_module_factory(GetModuleHandleA("engine.dll")) });
	g_modules_dumped.push_back({ 0x542b0000,0x542e0000,"vaudio_celt" });
	g_modules_dumped.push_back({ 0x542e0000,0x5448b000,"icuuc" });
	g_modules_dumped.push_back({ 0x54490000,0x547ab000,"video" });
	g_modules_dumped.push_back({ 0x547b0000,0x54932000,"panoramauiclient" });
	g_modules_dumped.push_back({ 0x55150000,0x55176000,"dinput" });
	g_modules_dumped.push_back({ 0x55180000,0x5525e000,"v8_libbase" });
	g_modules_dumped.push_back({ 0x55260000,0x556be000,"studiorender" });
	g_modules_dumped.push_back({ 0x556c0000,0x55cf7000,"nvapi" });
	g_modules_dumped.push_back({ 0x55e00000,0x55e49000,"libgobject_2_0_0" });
	g_modules_dumped.push_back({ 0x618e0000,0x61b39000,"AcGenral" });
	g_modules_dumped.push_back({ 0x61be0000,0x61bf6000,"mssmp3" });
	g_modules_dumped.push_back({ 0x61c20000,0x61c88000,"libfontconfig_1" });
	g_modules_dumped.push_back({ 0x61c90000,0x61d0b000,"vgui2", get_module_factory(GetModuleHandleA("vgui2.dll")) });
	g_modules_dumped.push_back({ 0x62090000,0x620a9000,"vaudio_miles" });
	g_modules_dumped.push_back({ 0x62530000,0x6254a000,"scenefilecache" });
	g_modules_dumped.push_back({ 0x62550000,0x62567000,"libgmodule_2_0_0" });
	g_modules_dumped.push_back({ 0x625c0000,0x62633000,"WindowManagementAPI" });
	g_modules_dumped.push_back({ 0x62640000,0x62733000,"Windows_UI" });
	g_modules_dumped.push_back({ 0x62750000,0x6278e000,"localize" });
	g_modules_dumped.push_back({ 0x62790000,0x628d9000,"vguimatsurface", get_module_factory(GetModuleHandleA("vguimatsurface.dll")) });
	g_modules_dumped.push_back({ 0x628e0000,0x629b3000,"vscript" });
	g_modules_dumped.push_back({ 0x629c0000,0x62ad4000,"materialsystem" });
	g_modules_dumped.push_back({ 0x62ae0000,0x62b5f000,"dsound" });
	g_modules_dumped.push_back({ 0x62b60000,0x62c96000,"AudioSes" });
	g_modules_dumped.push_back({ 0x62ca0000,0x62ec2000,"nvspcap" });
	g_modules_dumped.push_back({ 0x62ed0000,0x64116000,"steamclient" });
	g_modules_dumped.push_back({ 0x64120000,0x641ad000,"comctl32" });
	g_modules_dumped.push_back({ 0x641b0000,0x641c5000,"samcli" });
	g_modules_dumped.push_back({ 0x641e0000,0x641e8000,"midimap" });
	g_modules_dumped.push_back({ 0x641f0000,0x64209000,"msacm32" });
	g_modules_dumped.push_back({ 0x64210000,0x6421a000,"msacm32_64210000" });
	g_modules_dumped.push_back({ 0x64220000,0x64228000,"avrt" });
	g_modules_dumped.push_back({ 0x64230000,0x64237000,"ksuser" });
	g_modules_dumped.push_back({ 0x64240000,0x6427a000,"wdmaud" });
	g_modules_dumped.push_back({ 0x64280000,0x642eb000,"MMDevAPI" });
	g_modules_dumped.push_back({ 0x642f0000,0x6430d000,"winmmbase" });
	g_modules_dumped.push_back({ 0x64470000,0x64488000,"amsi" });
	g_modules_dumped.push_back({ 0x64490000,0x64559000,"fastprox" });
	g_modules_dumped.push_back({ 0x64560000,0x64570000,"wbemsvc" });
	g_modules_dumped.push_back({ 0x64570000,0x6457d000,"wbemprox" });
	g_modules_dumped.push_back({ 0x64600000,0x64670000,"wbemcomn" });
	g_modules_dumped.push_back({ 0x64a30000,0x64a6c000,"imemanager" });
	g_modules_dumped.push_back({ 0x64b40000,0x64b46000,"mssds3d" });
	g_modules_dumped.push_back({ 0x64b50000,0x64ba6000,"libavresample_2" });
	g_modules_dumped.push_back({ 0x65210000,0x65232000,"msvfw32" });
	g_modules_dumped.push_back({ 0x65240000,0x6526c000,"DXCore" });
	g_modules_dumped.push_back({ 0x65270000,0x65289000,"parsifal" });
	g_modules_dumped.push_back({ 0x657a0000,0x6592f000,"twinapi_appcore" });
	g_modules_dumped.push_back({ 0x65930000,0x65b10000,"d3d11" });
	g_modules_dumped.push_back({ 0x65f40000,0x65f4d000,"XInput1_4" });
	g_modules_dumped.push_back({ 0x66fd0000,0x67058000,"vstdlib_s" });
	g_modules_dumped.push_back({ 0x67940000,0x679d9000,"tier0_s" });
	g_modules_dumped.push_back({ 0x68850000,0x69ce7000,"nvd3dum" });
	g_modules_dumped.push_back({ 0x69cf0000,0x69dd5000,"nvldumd" });
	g_modules_dumped.push_back({ 0x69e70000,0x69e76000,"shfolder" });
	g_modules_dumped.push_back({ 0x69e80000,0x69e9b000,"avifil32" });
	g_modules_dumped.push_back({ 0x69ea0000,0x69ef3000,"soundsystem" });
	g_modules_dumped.push_back({ 0x69f00000,0x69f7a000,"datacache" });
	g_modules_dumped.push_back({ 0x69f80000,0x6a3d6000,"wininet" });
	g_modules_dumped.push_back({ 0x6a3e0000,0x6a487000,"crashhandler" });
	g_modules_dumped.push_back({ 0x6a490000,0x6a498000,"wsock32" });
	g_modules_dumped.push_back({ 0x706e0000,0x70799000,"textinputframework" });
	g_modules_dumped.push_back({ 0x707e0000,0x70806000,"dwmapi" });
	g_modules_dumped.push_back({ 0x70810000,0x70846000,"valve_avi" });
	g_modules_dumped.push_back({ 0x70ad0000,0x70c5f000,"d3d9" });
	g_modules_dumped.push_back({ 0x70c60000,0x70c77000,"usp10" });
	g_modules_dumped.push_back({ 0x70e90000,0x70e9f000,"resourcepolicyclient" });
	g_modules_dumped.push_back({ 0x70ea0000,0x70edf000,"soundemittersystem" });
	g_modules_dumped.push_back({ 0x70ee0000,0x71015000,"vphysics" });
	g_modules_dumped.push_back({ 0x71020000,0x71097000,"inputsystem" });
	g_modules_dumped.push_back({ 0x710a0000,0x713e4000,"steamnetworkingsockets" });
	g_modules_dumped.push_back({ 0x713f0000,0x71467000,"filesystem_stdio" });
	g_modules_dumped.push_back({ 0x71470000,0x714b4000,"vstdlib" });
	g_modules_dumped.push_back({ 0x714c0000,0x717c7000,"tier0" });
	g_modules_dumped.push_back({ 0x717d0000,0x71919000,"gameoverlayrenderer" });
	g_modules_dumped.push_back({ 0x719b0000,0x71b21000,"WindowsCodecs" });
	g_modules_dumped.push_back({ 0x71d40000,0x71d64000,"devobj" });
	g_modules_dumped.push_back({ 0x71d70000,0x71e70000,"drvstore" });
	g_modules_dumped.push_back({ 0x71e70000,0x720ee000,"CoreUIComponents" });
	g_modules_dumped.push_back({ 0x720f0000,0x7218b000,"CoreMessaging" });
	g_modules_dumped.push_back({ 0x72190000,0x7226b000,"WinTypes" });
	g_modules_dumped.push_back({ 0x72270000,0x7235d000,"inputhost" });
	g_modules_dumped.push_back({ 0x72360000,0x72397000,"dinput8" });
	g_modules_dumped.push_back({ 0x72400000,0x72442000,"steam_api" });
	g_modules_dumped.push_back({ 0x72450000,0x72499000,"launcher" });
	g_modules_dumped.push_back({ 0x724a0000,0x724f9000,"FWPUCLNT" });
	g_modules_dumped.push_back({ 0x72500000,0x72508000,"rasadhlp" });
	g_modules_dumped.push_back({ 0x72510000,0x7251e000,"winrnr" });
	g_modules_dumped.push_back({ 0x72520000,0x72536000,"nlaapi" });
	g_modules_dumped.push_back({ 0x72540000,0x72550000,"wshbth" });
	g_modules_dumped.push_back({ 0x72550000,0x72566000,"pnrpnsp" });
	g_modules_dumped.push_back({ 0x72570000,0x72581000,"NapiNSP" });
	g_modules_dumped.push_back({ 0x72590000,0x72620000,"dnsapi" });
	g_modules_dumped.push_back({ 0x72910000,0x7291a000,"hid" });
	g_modules_dumped.push_back({ 0x72920000,0x72927000,"XINPUT9_1_0" });
	g_modules_dumped.push_back({ 0x729e0000,0x729f6000,"dhcpcsvc" });
	g_modules_dumped.push_back({ 0x72ec0000,0x72f82000,"dxgi" });
	g_modules_dumped.push_back({ 0x73a20000,0x73ae2000,"propsys" });
	g_modules_dumped.push_back({ 0x73cb0000,0x73cd1000,"sspicli" });
	g_modules_dumped.push_back({ 0x74260000,0x74285000,"userenv" });
	g_modules_dumped.push_back({ 0x74290000,0x7429a000,"secur32" });
	g_modules_dumped.push_back({ 0x742a0000,0x742d2000,"IPHLPAPI" });
	g_modules_dumped.push_back({ 0x742e0000,0x742f8000,"profapi" });
	g_modules_dumped.push_back({ 0x74300000,0x74373000,"winspool" });
	g_modules_dumped.push_back({ 0x74380000,0x7439e000,"gpapi" });
	g_modules_dumped.push_back({ 0x743a0000,0x743c8000,"winmm" });
	g_modules_dumped.push_back({ 0x743d0000,0x74558000,"dbghelp" });
	g_modules_dumped.push_back({ 0x74560000,0x74586000,"cryptnet" });
	g_modules_dumped.push_back({ 0x74590000,0x745a9000,"mpr" });
	g_modules_dumped.push_back({ 0x745b0000,0x745b8000,"version" });
	g_modules_dumped.push_back({ 0x745c0000,0x745ce000,"msasn1" });
	g_modules_dumped.push_back({ 0x745d0000,0x745da000,"cryptbase" });
	g_modules_dumped.push_back({ 0x745e0000,0x7460f000,"rsaenh" });
	g_modules_dumped.push_back({ 0x74610000,0x74623000,"cryptsp" });
	g_modules_dumped.push_back({ 0x74630000,0x74659000,"ntmarta" });
	g_modules_dumped.push_back({ 0x746e0000,0x74732000,"mswsock" });
	g_modules_dumped.push_back({ 0x74740000,0x7474d000,"umpdc" });
	g_modules_dumped.push_back({ 0x74750000,0x74794000,"powrprof" });
	g_modules_dumped.push_back({ 0x747a0000,0x747c7000,"wldp" });
	g_modules_dumped.push_back({ 0x74a60000,0x74b00000,"apphelp" });
	g_modules_dumped.push_back({ 0x74b00000,0x7510a000,"windows_storage" });
	g_modules_dumped.push_back({ 0x75110000,0x7511f000,"kernel_appcore" });
	g_modules_dumped.push_back({ 0x75120000,0x7534d000,"iertutil" });
	g_modules_dumped.push_back({ 0x75350000,0x7535b000,"netutils" });
	g_modules_dumped.push_back({ 0x75360000,0x7537d000,"srvcli" });
	g_modules_dumped.push_back({ 0x75380000,0x75529000,"urlmon" });
	g_modules_dumped.push_back({ 0x75530000,0x755a4000,"uxtheme" });
	g_modules_dumped.push_back({ 0x757c0000,0x75856000,"oleaut32" });
	g_modules_dumped.push_back({ 0x75860000,0x75c94000,"setupapi" });
	g_modules_dumped.push_back({ 0x75ca0000,0x75cb9000,"imagehlp" });
	g_modules_dumped.push_back({ 0x75cc0000,0x75cc6000,"psapi" });
	g_modules_dumped.push_back({ 0x75cd0000,0x75da4000,"msctf" });
	g_modules_dumped.push_back({ 0x75db0000,0x76365000,"shell32" });
	g_modules_dumped.push_back({ 0x76370000,0x763ab000,"cfgmgr32" });
	g_modules_dumped.push_back({ 0x76440000,0x76447000,"nsi" });
	g_modules_dumped.push_back({ 0x76450000,0x7650e000,"rpcrt4" });
	g_modules_dumped.push_back({ 0x76510000,0x76593000,"clbcatq" });
	g_modules_dumped.push_back({ 0x765b0000,0x7662b000,"msvcp_win" });
	g_modules_dumped.push_back({ 0x76630000,0x76750000,"ucrtbase" });
	g_modules_dumped.push_back({ 0x76750000,0x7680f000,"msvcrt" });
	g_modules_dumped.push_back({ 0x76810000,0x76886000,"sechost" });
	g_modules_dumped.push_back({ 0x76890000,0x768ef000,"bcryptPrimitives" });
	g_modules_dumped.push_back({ 0x76a00000,0x76ae3000,"ole32" });
	g_modules_dumped.push_back({ 0x76af0000,0x76d70000,"combase" });
	g_modules_dumped.push_back({ 0x76d70000,0x76f8c000,"KERNELBASE" });
	g_modules_dumped.push_back({ 0x76ff0000,0x77008000,"win32u" });
	g_modules_dumped.push_back({ 0x77070000,0x77089000,"bcrypt" });
	g_modules_dumped.push_back({ 0x77090000,0x770b6000,"imm32" });
	g_modules_dumped.push_back({ 0x770c0000,0x7713b000,"advapi32" });
	g_modules_dumped.push_back({ 0x772b0000,0x773aa000,"crypt32" });
	g_modules_dumped.push_back({ 0x77400000,0x774f0000,"kernel32" });
	g_modules_dumped.push_back({ 0x774f0000,0x77513000,"gdi32" });
	g_modules_dumped.push_back({ 0x77520000,0x77565000,"shlwapi" });
	g_modules_dumped.push_back({ 0x77570000,0x775f7000,"SHCore" });
	g_modules_dumped.push_back({ 0x77600000,0x77663000,"ws2_32" });
	g_modules_dumped.push_back({ 0x77670000,0x7780c000,"user32" });
	g_modules_dumped.push_back({ 0x77810000,0x778f0000,"gdi32full" });
	g_modules_dumped.push_back({ 0x778f0000,0x778fa000,"wow64cpu" });
	g_modules_dumped.push_back({ 0x77900000,0x77aa4000,"ntdll_77900000" });
	g_modules_dumped.push_back({ 0x77ad0000,0x77b21000,"libpangoft2_1_0_0" });
	g_modules_dumped.push_back({ 0x77b30000,0x77b88000,"libpango_1_0_0" });
	g_modules_dumped.push_back({ 0x77b90000,0x77c5e000,"shaderapidx9" });
	g_modules_dumped.push_back({ 0x77c60000,0x77d28000,"v8_libplatform" });
	g_modules_dumped.push_back({ 0x77d30000,0x77ff6000,"panorama" });
	g_modules_dumped.push_back({ 0x78990000,0x7a19d000,"phonon" });
	g_modules_dumped.push_back({ 0x7a1a0000,0x7ae7d000,"v8" });
	g_modules_dumped.push_back({ 0x7ae80000,0x7afcb000,"libglib_2_0_0" });
	g_modules_dumped.push_back({ 0x7afd0000,0x7b0bb000,"libfreetype_6" });
	g_modules_dumped.push_back({ 0x7b0c0000,0x7b113000,"stdshader_dbg" });
	g_modules_dumped.push_back({ 0x7b120000,0x7b24e000,"stdshader_dx9" });
	g_modules_dumped.push_back({ 0x7b2e0000,0x7baac000,"NvCamera32" });
	g_modules_dumped.push_back({ 0x7bab0000,0x7be06000,"d3dcompiler_47_32" });
	g_modules_dumped.push_back({ 0x7c310000,0x7c3ed000,"matchmaking" });

	g_sigs_dumped.push_back({ 0x00d20000,0x00f5f000,"csgo" });
	g_sigs_dumped.push_back({ 0x17cf0000,0x17fb6000,"panorama" });
	g_sigs_dumped.push_back({ 0x17fc0000,0x180b0000,"cairo" });
	g_sigs_dumped.push_back({ 0x27770000,0x27f3c000,"NvCamera32" });
	g_sigs_dumped.push_back({ 0x27f50000,0x282a6000,"d3dcompiler_47_32" });
	g_sigs_dumped.push_back({ 0x282b0000,0x2a4ba000,"nvwgf2um" });
	g_sigs_dumped.push_back({ 0x2b150000,0x3064f000,"client" });
	g_sigs_dumped.push_back({ 0x3bf00000,0x3bf30000,"vaudio_celt" });
	g_sigs_dumped.push_back({ 0x3d500000,0x3d623000,"serverbrowser" });
	g_sigs_dumped.push_back({ 0x50000000,0x5000f000,"resourcepolicyclient" });
	g_sigs_dumped.push_back({ 0x50010000,0x5004c000,"imemanager" });
	g_sigs_dumped.push_back({ 0x50050000,0x5036b000,"video" });
	g_sigs_dumped.push_back({ 0x50370000,0x504f2000,"panoramauiclient" });
	g_sigs_dumped.push_back({ 0x50500000,0x5057b000,"vgui2" });
	g_sigs_dumped.push_back({ 0x50580000,0x506c9000,"vguimatsurface" });
	g_sigs_dumped.push_back({ 0x506d0000,0x506f2000,"msvfw32" });
	g_sigs_dumped.push_back({ 0x50700000,0x50736000,"valve_avi" });
	g_sigs_dumped.push_back({ 0x50740000,0x50793000,"soundsystem" });
	g_sigs_dumped.push_back({ 0x507a0000,0x50873000,"vscript" });
	g_sigs_dumped.push_back({ 0x50880000,0x50cde000,"studiorender" });
	g_sigs_dumped.push_back({ 0x50ce0000,0x50d5a000,"datacache" });
	g_sigs_dumped.push_back({ 0x50d60000,0x50e74000,"materialsystem" });
	g_sigs_dumped.push_back({ 0x50e80000,0x50fb5000,"vphysics" });
	g_sigs_dumped.push_back({ 0x50fc0000,0x527cd000,"phonon" });
	g_sigs_dumped.push_back({ 0x527d0000,0x52b14000,"steamnetworkingsockets" });
	g_sigs_dumped.push_back({ 0x52b20000,0x564e0000,"engine" });
	g_sigs_dumped.push_back({ 0x564e0000,0x567e7000,"tier0" });
	g_sigs_dumped.push_back({ 0x569a0000,0x569b9000,"parsifal" });
	g_sigs_dumped.push_back({ 0x569c0000,0x56a37000,"inputsystem" });
	g_sigs_dumped.push_back({ 0x56a40000,0x56ab7000,"filesystem_stdio" });
	g_sigs_dumped.push_back({ 0x56ac0000,0x56b04000,"vstdlib" });
	g_sigs_dumped.push_back({ 0x56b10000,0x56b52000,"steam_api" });
	g_sigs_dumped.push_back({ 0x56b60000,0x56ca9000,"gameoverlayrenderer" });
	g_sigs_dumped.push_back({ 0x57370000,0x573af000,"soundemittersystem" });
	g_sigs_dumped.push_back({ 0x573c0000,0x579f7000,"nvapi" });
	g_sigs_dumped.push_back({ 0x57e90000,0x57eab000,"avifil32" });
	g_sigs_dumped.push_back({ 0x57eb0000,0x57ef9000,"launcher" });
	g_sigs_dumped.push_back({ 0x597b0000,0x597b8000,"midimap" });
	g_sigs_dumped.push_back({ 0x597c0000,0x597ca000,"msacm32_597c0000" });
	g_sigs_dumped.push_back({ 0x62bd0000,0x62d06000,"AudioSes" });
	g_sigs_dumped.push_back({ 0x62d10000,0x62d7c000,"MpOAV" });
	g_sigs_dumped.push_back({ 0x62d80000,0x62d87000,"ksuser" });
	g_sigs_dumped.push_back({ 0x62d90000,0x62dca000,"wdmaud" });
	g_sigs_dumped.push_back({ 0x62dd0000,0x62dd6000,"mssds3d" });
	g_sigs_dumped.push_back({ 0x62f70000,0x62fdb000,"MMDevAPI" });
	g_sigs_dumped.push_back({ 0x62fe0000,0x62fe6000,"shfolder" });
	g_sigs_dumped.push_back({ 0x62ff0000,0x6306f000,"dsound" });
	g_sigs_dumped.push_back({ 0x63cb0000,0x64ef6000,"steamclient" });
	g_sigs_dumped.push_back({ 0x64f00000,0x66397000,"nvd3dum" });
	g_sigs_dumped.push_back({ 0x663a0000,0x66580000,"d3d11" });
	g_sigs_dumped.push_back({ 0x666f0000,0x667e3000,"Windows_UI" });
	g_sigs_dumped.push_back({ 0x66bc0000,0x66bd8000,"amsi" });
	g_sigs_dumped.push_back({ 0x66be0000,0x66ca9000,"fastprox" });
	g_sigs_dumped.push_back({ 0x66cc0000,0x66cc8000,"avrt" });
	g_sigs_dumped.push_back({ 0x66cd0000,0x66ce0000,"wbemsvc" });
	g_sigs_dumped.push_back({ 0x66d40000,0x66db3000,"WindowManagementAPI" });
	g_sigs_dumped.push_back({ 0x67120000,0x67139000,"msacm32" });
	g_sigs_dumped.push_back({ 0x671b0000,0x671c7000,"usp10" });
	g_sigs_dumped.push_back({ 0x672b0000,0x672c5000,"samcli" });
	g_sigs_dumped.push_back({ 0x672d0000,0x67529000,"AcGenral" });
	g_sigs_dumped.push_back({ 0x67530000,0x6754d000,"winmmbase" });
	g_sigs_dumped.push_back({ 0x67550000,0x675c0000,"wbemcomn" });
	g_sigs_dumped.push_back({ 0x675c0000,0x675cd000,"wbemprox" });
	g_sigs_dumped.push_back({ 0x67630000,0x6765c000,"DXCore" });
	g_sigs_dumped.push_back({ 0x67660000,0x67882000,"nvspcap" });
	g_sigs_dumped.push_back({ 0x67890000,0x67975000,"nvldumd" });
	g_sigs_dumped.push_back({ 0x67980000,0x67b0f000,"d3d9" });
	g_sigs_dumped.push_back({ 0x67bf0000,0x67d61000,"WindowsCodecs" });
	g_sigs_dumped.push_back({ 0x683e0000,0x6846d000,"comctl32" });
	g_sigs_dumped.push_back({ 0x6e9b0000,0x6eb3f000,"twinapi_appcore" });
	g_sigs_dumped.push_back({ 0x6eb40000,0x6eb66000,"dwmapi" });
	g_sigs_dumped.push_back({ 0x6edf0000,0x6edfd000,"XInput1_4" });
	g_sigs_dumped.push_back({ 0x6fe40000,0x6fec8000,"vstdlib_s" });
	g_sigs_dumped.push_back({ 0x707b0000,0x70849000,"tier0_s" });
	g_sigs_dumped.push_back({ 0x71760000,0x71bb6000,"wininet" });
	g_sigs_dumped.push_back({ 0x71e90000,0x71e9a000,"hid" });
	g_sigs_dumped.push_back({ 0x71f50000,0x721ce000,"CoreUIComponents" });
	g_sigs_dumped.push_back({ 0x721d0000,0x722ab000,"WinTypes" });
	g_sigs_dumped.push_back({ 0x722b0000,0x7234b000,"CoreMessaging" });
	g_sigs_dumped.push_back({ 0x72350000,0x7243d000,"inputhost" });
	g_sigs_dumped.push_back({ 0x72440000,0x72477000,"dinput8" });
	g_sigs_dumped.push_back({ 0x72480000,0x724a4000,"devobj" });
	g_sigs_dumped.push_back({ 0x724b0000,0x725b0000,"drvstore" });
	g_sigs_dumped.push_back({ 0x725f0000,0x726a9000,"textinputframework" });
	g_sigs_dumped.push_back({ 0x72780000,0x72827000,"crashhandler" });
	g_sigs_dumped.push_back({ 0x72830000,0x72838000,"wsock32" });
	g_sigs_dumped.push_back({ 0x72a50000,0x72aa9000,"FWPUCLNT" });
	g_sigs_dumped.push_back({ 0x72ab0000,0x72ab8000,"rasadhlp" });
	g_sigs_dumped.push_back({ 0x72ac0000,0x72ace000,"winrnr" });
	g_sigs_dumped.push_back({ 0x72ad0000,0x72ae6000,"nlaapi" });
	g_sigs_dumped.push_back({ 0x72af0000,0x72b00000,"wshbth" });
	g_sigs_dumped.push_back({ 0x72b00000,0x72b16000,"pnrpnsp" });
	g_sigs_dumped.push_back({ 0x72b20000,0x72b31000,"NapiNSP" });
	g_sigs_dumped.push_back({ 0x72b40000,0x72bd0000,"dnsapi" });
	g_sigs_dumped.push_back({ 0x72bf0000,0x72c06000,"dhcpcsvc" });
	g_sigs_dumped.push_back({ 0x73160000,0x73222000,"dxgi" });
	g_sigs_dumped.push_back({ 0x73270000,0x737df000,"MessageBus" });
	g_sigs_dumped.push_back({ 0x738e0000,0x7394d000,"msvcp140" });
	g_sigs_dumped.push_back({ 0x73c00000,0x73cc2000,"propsys" });
	g_sigs_dumped.push_back({ 0x743f0000,0x74415000,"userenv" });
	g_sigs_dumped.push_back({ 0x74420000,0x74427000,"XINPUT9_1_0" });
	g_sigs_dumped.push_back({ 0x74450000,0x74471000,"sspicli" });
	g_sigs_dumped.push_back({ 0x74480000,0x744a8000,"winmm" });
	g_sigs_dumped.push_back({ 0x744c0000,0x74533000,"winspool" });
	g_sigs_dumped.push_back({ 0x74540000,0x74555000,"VCRUNTIME140" });
	g_sigs_dumped.push_back({ 0x74560000,0x74592000,"IPHLPAPI" });
	g_sigs_dumped.push_back({ 0x745a0000,0x74728000,"dbghelp" });
	g_sigs_dumped.push_back({ 0x74730000,0x7473a000,"secur32" });
	g_sigs_dumped.push_back({ 0x74740000,0x74748000,"version" });
	g_sigs_dumped.push_back({ 0x74750000,0x74768000,"profapi" });
	g_sigs_dumped.push_back({ 0x74770000,0x7478e000,"gpapi" });
	g_sigs_dumped.push_back({ 0x74790000,0x747b6000,"cryptnet" });
	g_sigs_dumped.push_back({ 0x747c0000,0x747ce000,"msasn1" });
	g_sigs_dumped.push_back({ 0x747d0000,0x747da000,"cryptbase" });
	g_sigs_dumped.push_back({ 0x747e0000,0x7480f000,"rsaenh" });
	g_sigs_dumped.push_back({ 0x74810000,0x74823000,"cryptsp" });
	g_sigs_dumped.push_back({ 0x74830000,0x74859000,"ntmarta" });
	g_sigs_dumped.push_back({ 0x748e0000,0x74932000,"mswsock" });
	g_sigs_dumped.push_back({ 0x74940000,0x7494d000,"umpdc" });
	g_sigs_dumped.push_back({ 0x74950000,0x74994000,"powrprof" });
	g_sigs_dumped.push_back({ 0x749a0000,0x749b9000,"mpr" });
	g_sigs_dumped.push_back({ 0x749c0000,0x749e7000,"wldp" });
	g_sigs_dumped.push_back({ 0x74c80000,0x7528a000,"windows_storage" });
	g_sigs_dumped.push_back({ 0x75290000,0x75330000,"apphelp" });
	g_sigs_dumped.push_back({ 0x75330000,0x7533f000,"kernel_appcore" });
	g_sigs_dumped.push_back({ 0x75340000,0x7534b000,"netutils" });
	g_sigs_dumped.push_back({ 0x75350000,0x7557d000,"iertutil" });
	g_sigs_dumped.push_back({ 0x75580000,0x7559d000,"srvcli" });
	g_sigs_dumped.push_back({ 0x755a0000,0x75749000,"urlmon" });
	g_sigs_dumped.push_back({ 0x75750000,0x757c4000,"uxtheme" });
	g_sigs_dumped.push_back({ 0x759e0000,0x75a25000,"shlwapi" });
	g_sigs_dumped.push_back({ 0x75b90000,0x75ba8000,"win32u" });
	g_sigs_dumped.push_back({ 0x75bb0000,0x75ca0000,"kernel32" });
	g_sigs_dumped.push_back({ 0x75ca0000,0x760d4000,"setupapi" });
	g_sigs_dumped.push_back({ 0x760e0000,0x76163000,"clbcatq" });
	g_sigs_dumped.push_back({ 0x76170000,0x76244000,"msctf" });
	g_sigs_dumped.push_back({ 0x762b0000,0x762eb000,"cfgmgr32" });
	g_sigs_dumped.push_back({ 0x762f0000,0x763d3000,"ole32" });
	g_sigs_dumped.push_back({ 0x763e0000,0x763f9000,"imagehlp" });
	g_sigs_dumped.push_back({ 0x76400000,0x76406000,"psapi" });
	g_sigs_dumped.push_back({ 0x76410000,0x7648b000,"advapi32" });
	g_sigs_dumped.push_back({ 0x76490000,0x7658a000,"crypt32" });
	g_sigs_dumped.push_back({ 0x76590000,0x76810000,"combase" });
	g_sigs_dumped.push_back({ 0x76810000,0x76886000,"sechost" });
	g_sigs_dumped.push_back({ 0x76890000,0x768b3000,"gdi32" });
	g_sigs_dumped.push_back({ 0x768c0000,0x768d9000,"bcrypt" });
	g_sigs_dumped.push_back({ 0x768e0000,0x76976000,"oleaut32" });
	g_sigs_dumped.push_back({ 0x76980000,0x769a6000,"imm32" });
	g_sigs_dumped.push_back({ 0x769b0000,0x76a90000,"gdi32full" });
	g_sigs_dumped.push_back({ 0x76a90000,0x76af3000,"ws2_32" });
	g_sigs_dumped.push_back({ 0x76b00000,0x76c9c000,"user32" });
	g_sigs_dumped.push_back({ 0x76ca0000,0x76cee000,"wintrust" });
	g_sigs_dumped.push_back({ 0x76f10000,0x76f8b000,"msvcp_win" });
	g_sigs_dumped.push_back({ 0x76f90000,0x771ac000,"KERNELBASE" });
	g_sigs_dumped.push_back({ 0x771b0000,0x77237000,"SHCore" });
	g_sigs_dumped.push_back({ 0x77240000,0x77247000,"nsi" });
	g_sigs_dumped.push_back({ 0x77250000,0x77805000,"shell32" });
	g_sigs_dumped.push_back({ 0x77810000,0x778ce000,"rpcrt4" });
	g_sigs_dumped.push_back({ 0x778d0000,0x7798f000,"msvcrt" });
	g_sigs_dumped.push_back({ 0x77990000,0x77ab0000,"ucrtbase" });
	g_sigs_dumped.push_back({ 0x77ab0000,0x77b0f000,"bcryptPrimitives" });
	g_sigs_dumped.push_back({ 0x77b10000,0x77b1a000,"wow64cpu" });
	g_sigs_dumped.push_back({ 0x77b20000,0x77cc4000,"ntdll_77b20000" });
	g_sigs_dumped.push_back({ 0x77cd0000,0x77ce7000,"libgmodule_2_0_0" });
	g_sigs_dumped.push_back({ 0x77cf0000,0x77f1e000,"icui18n" });
	g_sigs_dumped.push_back({ 0x77f20000,0x77ffe000,"v8_libbase" });
	g_sigs_dumped.push_back({ 0x78590000,0x7926d000,"v8" });
	g_sigs_dumped.push_back({ 0x79990000,0x79b3b000,"icuuc" });
	g_sigs_dumped.push_back({ 0x79b40000,0x79b96000,"libavresample_2" });
	g_sigs_dumped.push_back({ 0x79ba0000,0x79bde000,"localize" });
	g_sigs_dumped.push_back({ 0x79c70000,0x79d38000,"v8_libplatform" });
	g_sigs_dumped.push_back({ 0x79d40000,0x79e0e000,"shaderapidx9" });
	g_sigs_dumped.push_back({ 0x79e90000,0x79f3d000,"panorama_text_pango" });
	g_sigs_dumped.push_back({ 0x79f40000,0x79fa8000,"libfontconfig_1" });
	g_sigs_dumped.push_back({ 0x79fb0000,0x79ff9000,"libgobject_2_0_0" });
	g_sigs_dumped.push_back({ 0x7a000000,0x7a0eb000,"libfreetype_6" });
	g_sigs_dumped.push_back({ 0x7a0f0000,0x7a23b000,"libglib_2_0_0" });
	g_sigs_dumped.push_back({ 0x7a240000,0x7a298000,"libpango_1_0_0" });
	g_sigs_dumped.push_back({ 0x7a2a0000,0x7a2f1000,"libpangoft2_1_0_0" });
	g_sigs_dumped.push_back({ 0x7a340000,0x7a393000,"stdshader_dbg" });
	g_sigs_dumped.push_back({ 0x7a3a0000,0x7a4ce000,"stdshader_dx9" });
	g_sigs_dumped.push_back({ 0x7a4d0000,0x7a4f6000,"dinput" });
	g_sigs_dumped.push_back({ 0x7aa20000,0x7aa99000,"libavformat_56" });
	g_sigs_dumped.push_back({ 0x7acb0000,0x7afc6000,"libavcodec_56" });
	g_sigs_dumped.push_back({ 0x7afd0000,0x7b046000,"libavutil_54" });
	g_sigs_dumped.push_back({ 0x7b050000,0x7b0cc000,"libswscale_3" });
	g_sigs_dumped.push_back({ 0x7b220000,0x7b2fd000,"matchmaking" });
	g_sigs_dumped.push_back({ 0x7b300000,0x7bff7000,"server" });
	g_sigs_dumped.push_back({ 0x7c000000,0x7c01a000,"scenefilecache" });
	g_sigs_dumped.push_back({ 0x7c020000,0x7c039000,"vaudio_miles" });
	g_sigs_dumped.push_back({ 0x7c040000,0x7c0c3000,"mss32" });
	g_sigs_dumped.push_back({ 0x7c0d0000,0x7c0e6000,"mssmp3" });
	g_sigs_dumped.push_back({ 0x7c0f0000,0x7c17e000,"XAudio2_7" });

}

int __stdcall fix_sig_address(const char* dll_name, const char* sig)
{
	int fixed_address = find_pattern_func(LoadLibraryA(dll_name), sig);
	if (!fixed_address)
	{
		printf("FAILED TO FIND SIG %s->%s !!!\n", dll_name, sig);
		system("pause");
	}

	return fixed_address;
}

void* __stdcall fix_interface_address(int address)
{
	for (int i = 0; i < g_modules_dumped.size(); i++)
	{
		if (address >= g_modules_dumped[i].start && address < g_modules_dumped[i].end)
		{
			void* fixed_address = 0;

			auto it = g_interface_addresses.find(address);

			if (it->second.is_sig)
			{
				fixed_address = *reinterpret_cast<void**>(find_pattern_func(LoadLibraryA(g_modules_dumped[i].name.data()), it->second.name, it->second.offset));
			}
			else
			{
				fixed_address = get_interface(g_modules_dumped[i].interface_, it->second.name);
			}

			return fixed_address;
		}
	}

	printf("FAILED TO FIND %p !!!\n", address);
	system("pause");

	return 0;
}

void* g_interface_jmp_back = 0;

__declspec(naked) void rebase_interface_pointers()
{
	__asm
	{
		PUSHAD // save all registers
		push ebp // save for after call fix_address
		push eax // push arg
		call fix_interface_address // call
		pop ebp // get saved ebp
		mov[ebp - 0x40], eax // put fixed address
		POPAD // get all original registers
		push g_interface_jmp_back // jmp back
		ret // ret
	}
}

bool g_should_print = false;

using get_server_address_t = int(__cdecl*)(int hash);
get_server_address_t oget_server_address = 0;

int __cdecl hooked_get_server_address(int hash)
{
	static int j = 0;
	j++;
	int fixed_address = fix_sig_address(g_sig_addresses.find(hash)->second.dll_name, g_sig_addresses.find(hash)->second.sig);

	if (j == 123)
	{
		g_should_print = true;
	}

	return fixed_address;
}

// This is terrible but w/e was made in 5 sec XD
void* g_fix_username = 0;

int g_i = 0;

char fix_username()
{
	static const char* name = "PinkKing   "; // don't be cringe kid and change this ...
	char name_text = name[g_i];
	g_i++;
	if (g_i >= strlen(name))
	{
		g_i = 0;
	}
	__asm
	{
		mov al, name_text
		mov esp, ebp
		pop ebp
		ret
	}
}

__declspec(naked) void hooked_username() // 0x44F9A480
{
	__asm
	{
		call fix_username // call
		push g_fix_username // jmp back
		ret // ret
	}
}


void* g_fix_username2 = 0;

int g_i2 = 0;

char fix_username2()
{
	static const char* name = "PinkKing   "; // don't be cringe kid and change this ...
	char name_text = name[g_i2];
	g_i2++;
	if (g_i2 >= strlen(name))
	{
		g_i2 = 0;
	}
	__asm
	{
		mov dl, name_text
		mov esp, ebp
		pop ebp
		ret
	}
}

__declspec(naked) void hooked_username2() // 0x45029B40
{
	__asm
	{
		call fix_username2 // call
		push g_fix_username2 // jmp back
		ret // ret
	}
}

void main()
{
	/*
	printf("[+] allocating mem...\n");

	void* hack_address = VirtualAlloc(reinterpret_cast<void*>(0x40B50000), sizeof(hack_bin), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!hack_address)
	{
		printf("[-] failed to allocate memory (restart game and instantly inject)\n");
		Sleep(3000);
		TerminateProcess(reinterpret_cast<HANDLE>(-1), 0);
	}

	printf("[+] allocated mem!\n");
	*/

	MEMORY_BASIC_INFORMATION mem;
	if (!VirtualQuery(reinterpret_cast<void*>(0x40B50000), &mem, sizeof(mem)))
	{
		printf("[-] failed to query memory ( did u inject steam_module.dll into steam.exe ? )\n");
		Sleep(3000);
		TerminateProcess(reinterpret_cast<HANDLE>(-1), 0);
	}

	if (mem.RegionSize != 0x74C000)
	{
		printf("[-] failed to find memory ( did u inject steam_module.dll into steam.exe ? )\n");
		Sleep(3000);
		TerminateProcess(reinterpret_cast<HANDLE>(-1), 0);
	}

	void* hack_address = reinterpret_cast<void*>(0x40B50000);

	printf("[+] init...\n");
	init();
	memcpy(hack_address, hack_bin, sizeof(hack_bin));
	printf("[+] inited!\n");

	printf("[+] waiting for serverbrowser.dll ...\n");
	while (!GetModuleHandleA("serverbrowser.dll")) Sleep(100);
	printf("[+] found serverbrowser.dll !\n");

	printf("[+] patching...\n");

	// nop out "store result" since we will do it
	memset(reinterpret_cast<void*>(0x410335EB), 0x90, 3);

	// username
	memset(reinterpret_cast<void*>(0x40DC8D70), 0x90, 8);
	memset(reinterpret_cast<void*>(0x40E5C274), 0x90, 8);

	// stop process from exiting
	std::array<uint8_t, 6> patch1 = { 0xE9, 0x7A, 0x02, 0x00, 0x00, 0x90 };
	std::array<uint8_t, 6> patch2 = { 0xE9, 0x7A, 0x02, 0x00, 0x00, 0x90 };
	std::array<uint8_t, 6> patch3 = { 0xE9, 0xB0, 0x02, 0x00, 0x00, 0x90 };
	std::array<uint8_t, 6> patch4 = { 0xE9, 0x7C, 0x02, 0x00, 0x00, 0x90 };

	memcpy(reinterpret_cast<void*>(0x40FB8FDF), patch1.data(), patch1.size());
	memcpy(reinterpret_cast<void*>(0x40FB92CC), patch2.data(), patch2.size());
	memcpy(reinterpret_cast<void*>(0x40FBA4C3), patch3.data(), patch3.size());
	memcpy(reinterpret_cast<void*>(0x40FBB1DE), patch4.data(), patch4.size());

	// fix slow injection
	*reinterpret_cast<BYTE*>(0x40FB8F82) = 0xEB;
	*reinterpret_cast<BYTE*>(0x40FB926F) = 0xEB;

	std::array<uint8_t, 6> patch5 = { 0xE9, 0x8C, 0x00, 0x00, 0x00, 0x90 };

	memcpy(reinterpret_cast<void*>(0x40FBA42B), patch5.data(), patch5.size());

	*reinterpret_cast<BYTE*>(0x40FBB182) = 0xEB;

	// we init YES SIR
	*reinterpret_cast<bool*>(0x40DC8107) = 0;
	*reinterpret_cast<bool*>(0x40FCC462) = 0;
	*reinterpret_cast<bool*>(0x40FCC47B) = 0;

	printf("[+] patched!\n");

	printf("[+] creating hooks...\n");
	if (MH_Initialize() != MH_OK)
	{
		printf("[-] failed to initialize minhook\n");
		return;
	}

	// some of these hooks are useless such as recv but i don't care to remove it :DDDDDDDD

	if (MH_CreateHook(&connect, hooked_connect, reinterpret_cast<void**>(&oConnect)) != MH_OK)
	{
		printf("[-] failed to create hook at send\n");
		return;
	}

	if (MH_CreateHook(&send, hooked_send, reinterpret_cast<void**>(&oSend)) != MH_OK)
	{
		printf("[-] failed to create hook at send\n");
		return;
	}

	if (MH_CreateHook(&recv, hooked_recv, reinterpret_cast<void**>(&oRecv)) != MH_OK)
	{
		printf("[-] failed to create hook at recv\n");
		return;
	}

	if (MH_CreateHook(&GetCurrentProcessId, hooked_GetCurrentProcessId, reinterpret_cast<void**>(&oGetCurrentProcessId)) != MH_OK)
	{
		printf("[-] failed to create hook at GetCurrentProcessId\n");
		return;
	}

	if (MH_CreateHook(reinterpret_cast<void*>(0x4100B990), hooked_find_pattern, reinterpret_cast<void**>(&ofind_pattern)) != MH_OK)
	{
		printf("[-] failed to create hook at find_pattern\n");
		return;
	}

	if (MH_CreateHook(reinterpret_cast<void*>(0x410335EB), rebase_interface_pointers, reinterpret_cast<void**>(&g_interface_jmp_back)) != MH_OK)
	{
		printf("[-] failed to create hook at rebase_interface\n");
		return;
	}

	if (MH_CreateHook(reinterpret_cast<void*>(0x40DE8EC0), hooked_get_server_address, reinterpret_cast<void**>(&oget_server_address)) != MH_OK)
	{
		printf("[-] failed to create hook at get_server_address\n");
		return;
	}

	if (MH_CreateHook(reinterpret_cast<void*>(0x40DC8D70), hooked_username, reinterpret_cast<void**>(&g_fix_username)) != MH_OK)
	{
		printf("[-] failed to create hook at username\n");
		return;
	}

	if (MH_CreateHook(reinterpret_cast<void*>(0x40E5C274), hooked_username2, reinterpret_cast<void**>(&g_fix_username2)) != MH_OK)
	{
		printf("[-] failed to create hook at username2\n");
		return;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		printf("[-] failed to enable hooks\n");
		return;
	}

	printf("[+] created hooks!\n");

	printf("[+] fixing imports...\n");
	fix_imports();
	printf("[+] fixed imports!\n");

	printf("[+] calling dllmain...\n");

	uint32_t oep = 0x4103FFBF;

	__asm
	{
		push 0
		push 1
		push hack_address
		call oep
	}

	printf("[+] called dllmain!\n");
	printf("[+] doing magic...\n");
	while (!g_should_print)
	{
		Sleep(100);
	}
	printf("[+] finished!\n"); // pwned :DDDDDDDDDDDD
	printf("[+] owned by PinkKing#8199 & NiceL#0001 ( https://discord.gg/GHKuYjZrdM )\n");
}

bool __stdcall DllMain(HANDLE hinstDLL, uint32_t fdwReason, void* lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		AllocConsole();
		SetConsoleTitleA("pandora.gg crack ( updated 12/4/2022 )");
		freopen("CONOUT$", "w", stdout);
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), 0, 0, 0);
	}
	return true;
}