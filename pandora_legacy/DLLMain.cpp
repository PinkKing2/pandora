#define _WINSOCK_DEPRECATED_NO_WARNINGS
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

#include "bin.hpp"

void fix_imports()
{
	*reinterpret_cast<FARPROC*>(0x37553000) = GetProcAddress(LoadLibraryA("advapi32.dll"), "CryptAcquireContextA");
	*reinterpret_cast<FARPROC*>(0x37553004) = GetProcAddress(LoadLibraryA("advapi32.dll"), "CryptReleaseContext");
	*reinterpret_cast<FARPROC*>(0x37553008) = GetProcAddress(LoadLibraryA("advapi32.dll"), "CryptGenRandom");
	*reinterpret_cast<FARPROC*>(0x37553010) = GetProcAddress(LoadLibraryA("crypt32.dll"), "CertOpenStore");
	*reinterpret_cast<FARPROC*>(0x37553014) = GetProcAddress(LoadLibraryA("crypt32.dll"), "CertEnumCertificatesInStore");
	*reinterpret_cast<FARPROC*>(0x37553018) = GetProcAddress(LoadLibraryA("crypt32.dll"), "CertCloseStore");
	*reinterpret_cast<FARPROC*>(0x3755301C) = GetProcAddress(LoadLibraryA("crypt32.dll"), "CertFreeCRLContext");
	*reinterpret_cast<FARPROC*>(0x37553024) = GetProcAddress(LoadLibraryA("gdi32.dll"), "AddFontMemResourceEx");
	*reinterpret_cast<FARPROC*>(0x3755302C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetTickCount");
	*reinterpret_cast<FARPROC*>(0x37553030) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GlobalAlloc");
	*reinterpret_cast<FARPROC*>(0x37553034) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GlobalUnlock");
	*reinterpret_cast<FARPROC*>(0x37553038) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GlobalLock");
	*reinterpret_cast<FARPROC*>(0x3755303C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "RaiseException");
	*reinterpret_cast<FARPROC*>(0x37553040) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCurrentProcess");
	*reinterpret_cast<FARPROC*>(0x37553044) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetPriorityClass");
	*reinterpret_cast<FARPROC*>(0x37553048) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetPriorityClass");
	*reinterpret_cast<FARPROC*>(0x3755304C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "VirtualAlloc");
	*reinterpret_cast<FARPROC*>(0x37553050) = GetProcAddress(LoadLibraryA("kernel32.dll"), "VirtualFree");
	*reinterpret_cast<FARPROC*>(0x37553054) = GetProcAddress(LoadLibraryA("kernel32.dll"), "VirtualQuery");
	*reinterpret_cast<FARPROC*>(0x37553058) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapCreate");
	*reinterpret_cast<FARPROC*>(0x3755305C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapAlloc");
	*reinterpret_cast<FARPROC*>(0x37553060) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapReAlloc");
	*reinterpret_cast<FARPROC*>(0x37553064) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapFree");
	*reinterpret_cast<FARPROC*>(0x37553068) = GetProcAddress(LoadLibraryA("kernel32.dll"), "Sleep");
	*reinterpret_cast<FARPROC*>(0x3755306C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCurrentProcessId");
	*reinterpret_cast<FARPROC*>(0x37553070) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCurrentThreadId");
	*reinterpret_cast<FARPROC*>(0x37553074) = GetProcAddress(LoadLibraryA("kernel32.dll"), "OpenThread");
	*reinterpret_cast<FARPROC*>(0x37553078) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SuspendThread");
	*reinterpret_cast<FARPROC*>(0x3755307C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ResumeThread");
	*reinterpret_cast<FARPROC*>(0x37553080) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetThreadContext");
	*reinterpret_cast<FARPROC*>(0x37553084) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetThreadContext");
	*reinterpret_cast<FARPROC*>(0x37553088) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FlushInstructionCache");
	*reinterpret_cast<FARPROC*>(0x3755308C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "VirtualProtect");
	*reinterpret_cast<FARPROC*>(0x37553090) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleHandleW");
	*reinterpret_cast<FARPROC*>(0x37553094) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CloseHandle");
	*reinterpret_cast<FARPROC*>(0x37553098) = GetProcAddress(LoadLibraryA("kernel32.dll"), "Thread32First");
	*reinterpret_cast<FARPROC*>(0x3755309C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "Thread32Next");
	*reinterpret_cast<FARPROC*>(0x375530A0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCommandLineA");
	*reinterpret_cast<FARPROC*>(0x375530A4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "MultiByteToWideChar");
	*reinterpret_cast<FARPROC*>(0x375530A8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitializeCriticalSection");
	*reinterpret_cast<FARPROC*>(0x375530AC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "EnterCriticalSection");
	*reinterpret_cast<FARPROC*>(0x375530B0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LeaveCriticalSection");
	*reinterpret_cast<FARPROC*>(0x375530B4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "DeleteCriticalSection");
	*reinterpret_cast<FARPROC*>(0x375530B8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WaitForSingleObject");
	*reinterpret_cast<FARPROC*>(0x375530BC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateSemaphoreA");
	*reinterpret_cast<FARPROC*>(0x375530C0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitOnceInitialize");
	*reinterpret_cast<FARPROC*>(0x375530C4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ReleaseSRWLockExclusive");
	*reinterpret_cast<FARPROC*>(0x375530C8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "AcquireSRWLockExclusive");
	*reinterpret_cast<FARPROC*>(0x375530CC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateThread");
	*reinterpret_cast<FARPROC*>(0x375530D0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ResetEvent");
	*reinterpret_cast<FARPROC*>(0x375530D4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetEvent");
	*reinterpret_cast<FARPROC*>(0x375530D8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WriteFile");
	*reinterpret_cast<FARPROC*>(0x375530DC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateFileA");
	*reinterpret_cast<FARPROC*>(0x375530E0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WideCharToMultiByte");
	*reinterpret_cast<FARPROC*>(0x375530E4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetProcAddress");
	*reinterpret_cast<FARPROC*>(0x375530E8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleHandleA");
	*reinterpret_cast<FARPROC*>(0x375530EC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindNextFileA");
	*reinterpret_cast<FARPROC*>(0x375530F0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindFirstFileA");
	*reinterpret_cast<FARPROC*>(0x375530F4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindClose");
	*reinterpret_cast<FARPROC*>(0x375530F8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateDirectoryW");
	*reinterpret_cast<FARPROC*>(0x375530FC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WriteConsoleW");
	*reinterpret_cast<FARPROC*>(0x37553100) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetStdHandle");
	*reinterpret_cast<FARPROC*>(0x37553104) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreatePipe");
	*reinterpret_cast<FARPROC*>(0x37553108) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetExitCodeProcess");
	*reinterpret_cast<FARPROC*>(0x3755310C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "HeapSize");
	*reinterpret_cast<FARPROC*>(0x37553110) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateToolhelp32Snapshot");
	*reinterpret_cast<FARPROC*>(0x37553114) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateDirectoryA");
	*reinterpret_cast<FARPROC*>(0x37553118) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetProcessHeap");
	*reinterpret_cast<FARPROC*>(0x3755311C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FreeEnvironmentStringsW");
	*reinterpret_cast<FARPROC*>(0x37553120) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetEnvironmentStringsW");
	*reinterpret_cast<FARPROC*>(0x37553124) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCommandLineW");
	*reinterpret_cast<FARPROC*>(0x37553128) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetOEMCP");
	*reinterpret_cast<FARPROC*>(0x3755312C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetACP");
	*reinterpret_cast<FARPROC*>(0x37553130) = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsValidCodePage");
	*reinterpret_cast<FARPROC*>(0x37553134) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetTimeZoneInformation");
	*reinterpret_cast<FARPROC*>(0x37553138) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ReadConsoleW");
	*reinterpret_cast<FARPROC*>(0x3755313C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFileSizeEx");
	*reinterpret_cast<FARPROC*>(0x37553140) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetConsoleMode");
	*reinterpret_cast<FARPROC*>(0x37553144) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetConsoleOutputCP");
	*reinterpret_cast<FARPROC*>(0x37553148) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FlushFileBuffers");
	*reinterpret_cast<FARPROC*>(0x3755314C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "EnumSystemLocalesW");
	*reinterpret_cast<FARPROC*>(0x37553150) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetUserDefaultLCID");
	*reinterpret_cast<FARPROC*>(0x37553154) = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsValidLocale");
	*reinterpret_cast<FARPROC*>(0x37553158) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetLocaleInfoW");
	*reinterpret_cast<FARPROC*>(0x3755315C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LCMapStringW");
	*reinterpret_cast<FARPROC*>(0x37553160) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CompareStringW");
	*reinterpret_cast<FARPROC*>(0x37553164) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetTimeFormatW");
	*reinterpret_cast<FARPROC*>(0x37553168) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetDateFormatW");
	*reinterpret_cast<FARPROC*>(0x3755316C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFileType");
	*reinterpret_cast<FARPROC*>(0x37553170) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetStdHandle");
	*reinterpret_cast<FARPROC*>(0x37553174) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateProcessW");
	*reinterpret_cast<FARPROC*>(0x37553178) = GetProcAddress(LoadLibraryA("kernel32.dll"), "DuplicateHandle");
	*reinterpret_cast<FARPROC*>(0x3755317C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleFileNameW");
	*reinterpret_cast<FARPROC*>(0x37553180) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ExitProcess");
	*reinterpret_cast<FARPROC*>(0x37553184) = GetProcAddress(LoadLibraryA("kernel32.dll"), "DeleteFileW");
	*reinterpret_cast<FARPROC*>(0x37553188) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetEnvironmentVariableW");
	*reinterpret_cast<FARPROC*>(0x3755318C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetDriveTypeW");
	*reinterpret_cast<FARPROC*>(0x37553190) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleHandleExW");
	*reinterpret_cast<FARPROC*>(0x37553194) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FreeLibraryAndExitThread");
	*reinterpret_cast<FARPROC*>(0x37553198) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FormatMessageA");
	*reinterpret_cast<FARPROC*>(0x3755319C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LocalFree");
	*reinterpret_cast<FARPROC*>(0x375531A0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetLocaleInfoEx");
	*reinterpret_cast<FARPROC*>(0x375531A4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCurrentDirectoryW");
	*reinterpret_cast<FARPROC*>(0x375531A8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateFileW");
	*reinterpret_cast<FARPROC*>(0x375531AC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindFirstFileW");
	*reinterpret_cast<FARPROC*>(0x375531B0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindFirstFileExW");
	*reinterpret_cast<FARPROC*>(0x375531B4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FindNextFileW");
	*reinterpret_cast<FARPROC*>(0x375531B8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFileAttributesExW");
	*reinterpret_cast<FARPROC*>(0x375531BC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFullPathNameW");
	*reinterpret_cast<FARPROC*>(0x375531C0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetEndOfFile");
	*reinterpret_cast<FARPROC*>(0x375531C4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetFilePointerEx");
	*reinterpret_cast<FARPROC*>(0x375531C8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetTempPathW");
	*reinterpret_cast<FARPROC*>(0x375531CC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "AreFileApisANSI");
	*reinterpret_cast<FARPROC*>(0x375531D0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetLastError");
	*reinterpret_cast<FARPROC*>(0x375531D4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "MoveFileExW");
	*reinterpret_cast<FARPROC*>(0x375531D8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetFileInformationByHandleEx");
	*reinterpret_cast<FARPROC*>(0x375531DC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "QueryPerformanceCounter");
	*reinterpret_cast<FARPROC*>(0x375531E0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "QueryPerformanceFrequency");
	*reinterpret_cast<FARPROC*>(0x375531E4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WaitForSingleObjectEx");
	*reinterpret_cast<FARPROC*>(0x375531E8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetExitCodeThread");
	*reinterpret_cast<FARPROC*>(0x375531EC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitializeCriticalSectionEx");
	*reinterpret_cast<FARPROC*>(0x375531F0) = GetProcAddress(LoadLibraryA("kernel32.dll"), "EncodePointer");
	*reinterpret_cast<FARPROC*>(0x375531F4) = GetProcAddress(LoadLibraryA("kernel32.dll"), "DecodePointer");
	*reinterpret_cast<FARPROC*>(0x375531F8) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LCMapStringEx");
	*reinterpret_cast<FARPROC*>(0x375531FC) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitOnceInitialize");
	*reinterpret_cast<FARPROC*>(0x37553200) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WakeConditionVariable");
	*reinterpret_cast<FARPROC*>(0x37553204) = GetProcAddress(LoadLibraryA("kernel32.dll"), "WakeAllConditionVariable");
	*reinterpret_cast<FARPROC*>(0x37553208) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SleepConditionVariableCS");
	*reinterpret_cast<FARPROC*>(0x3755320C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SleepConditionVariableSRW");
	*reinterpret_cast<FARPROC*>(0x37553210) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetSystemTimeAsFileTime");
	*reinterpret_cast<FARPROC*>(0x37553214) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TryEnterCriticalSection");
	*reinterpret_cast<FARPROC*>(0x37553218) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetStringTypeW");
	*reinterpret_cast<FARPROC*>(0x3755321C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetCPInfo");
	*reinterpret_cast<FARPROC*>(0x37553220) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitializeSListHead");
	*reinterpret_cast<FARPROC*>(0x37553224) = GetProcAddress(LoadLibraryA("kernel32.dll"), "UnhandledExceptionFilter");
	*reinterpret_cast<FARPROC*>(0x37553228) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetUnhandledExceptionFilter");
	*reinterpret_cast<FARPROC*>(0x3755322C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TerminateProcess");
	*reinterpret_cast<FARPROC*>(0x37553230) = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsProcessorFeaturePresent");
	*reinterpret_cast<FARPROC*>(0x37553234) = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsDebuggerPresent");
	*reinterpret_cast<FARPROC*>(0x37553238) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetStartupInfoW");
	*reinterpret_cast<FARPROC*>(0x3755323C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "SetLastError");
	*reinterpret_cast<FARPROC*>(0x37553240) = GetProcAddress(LoadLibraryA("kernel32.dll"), "FreeLibrary");
	*reinterpret_cast<FARPROC*>(0x37553244) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleFileNameA");
	*reinterpret_cast<FARPROC*>(0x37553248) = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetModuleHandleExA");
	*reinterpret_cast<FARPROC*>(0x3755324C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LoadLibraryA");
	*reinterpret_cast<FARPROC*>(0x37553250) = GetProcAddress(LoadLibraryA("kernel32.dll"), "RtlUnwind");
	*reinterpret_cast<FARPROC*>(0x37553254) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InterlockedPushEntrySList");
	*reinterpret_cast<FARPROC*>(0x37553258) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InterlockedFlushSList");
	*reinterpret_cast<FARPROC*>(0x3755325C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "InitializeCriticalSectionAndSpinCount");
	*reinterpret_cast<FARPROC*>(0x37553260) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TlsAlloc");
	*reinterpret_cast<FARPROC*>(0x37553264) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TlsGetValue");
	*reinterpret_cast<FARPROC*>(0x37553268) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TlsSetValue");
	*reinterpret_cast<FARPROC*>(0x3755326C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "TlsFree");
	*reinterpret_cast<FARPROC*>(0x37553270) = GetProcAddress(LoadLibraryA("kernel32.dll"), "LoadLibraryExW");
	*reinterpret_cast<FARPROC*>(0x37553274) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ReadFile");
	*reinterpret_cast<FARPROC*>(0x37553278) = GetProcAddress(LoadLibraryA("kernel32.dll"), "ExitThread");
	*reinterpret_cast<FARPROC*>(0x3755327C) = GetProcAddress(LoadLibraryA("kernel32.dll"), "CreateEventW");
	*reinterpret_cast<FARPROC*>(0x37553284) = GetProcAddress(LoadLibraryA("shell32.dll"), "SHParseDisplayName");
	*reinterpret_cast<FARPROC*>(0x37553288) = GetProcAddress(LoadLibraryA("shell32.dll"), "SHOpenFolderAndSelectItems");
	*reinterpret_cast<FARPROC*>(0x3755328C) = GetProcAddress(LoadLibraryA("shell32.dll"), "SHGetFolderPathA");
	*reinterpret_cast<FARPROC*>(0x37553294) = GetProcAddress(LoadLibraryA("user32.dll"), "EmptyClipboard");
	*reinterpret_cast<FARPROC*>(0x37553298) = GetProcAddress(LoadLibraryA("user32.dll"), "GetKeyNameTextA");
	*reinterpret_cast<FARPROC*>(0x3755329C) = GetProcAddress(LoadLibraryA("user32.dll"), "MapVirtualKeyA");
	*reinterpret_cast<FARPROC*>(0x375532A0) = GetProcAddress(LoadLibraryA("user32.dll"), "SetCursor");
	*reinterpret_cast<FARPROC*>(0x375532A4) = GetProcAddress(LoadLibraryA("user32.dll"), "SetClipboardData");
	*reinterpret_cast<FARPROC*>(0x375532A8) = GetProcAddress(LoadLibraryA("user32.dll"), "GetAsyncKeyState");
	*reinterpret_cast<FARPROC*>(0x375532AC) = GetProcAddress(LoadLibraryA("user32.dll"), "wsprintfW");
	*reinterpret_cast<FARPROC*>(0x375532B0) = GetProcAddress(LoadLibraryA("user32.dll"), "GetFocus");
	*reinterpret_cast<FARPROC*>(0x375532B4) = GetProcAddress(LoadLibraryA("user32.dll"), "CallWindowProcA");
	*reinterpret_cast<FARPROC*>(0x375532B8) = GetProcAddress(LoadLibraryA("user32.dll"), "SetWindowLongA");
	*reinterpret_cast<FARPROC*>(0x375532BC) = GetProcAddress(LoadLibraryA("user32.dll"), "LoadCursorA");
	*reinterpret_cast<FARPROC*>(0x375532C0) = GetProcAddress(LoadLibraryA("user32.dll"), "IsClipboardFormatAvailable");
	*reinterpret_cast<FARPROC*>(0x375532C4) = GetProcAddress(LoadLibraryA("user32.dll"), "GetKeyState");
	*reinterpret_cast<FARPROC*>(0x375532C8) = GetProcAddress(LoadLibraryA("user32.dll"), "OpenClipboard");
	*reinterpret_cast<FARPROC*>(0x375532CC) = GetProcAddress(LoadLibraryA("user32.dll"), "CloseClipboard");
	*reinterpret_cast<FARPROC*>(0x375532D0) = GetProcAddress(LoadLibraryA("user32.dll"), "GetClipboardData");
	*reinterpret_cast<FARPROC*>(0x375532D8) = GetProcAddress(LoadLibraryA("winmm.dll"), "PlaySoundA");
	*reinterpret_cast<FARPROC*>(0x375532E0) = GetProcAddress(LoadLibraryA("wsock32.dll"), "WSAStartup");
	*reinterpret_cast<FARPROC*>(0x375532E4) = GetProcAddress(LoadLibraryA("wsock32.dll"), "__WSAFDIsSet");
	*reinterpret_cast<FARPROC*>(0x375532E8) = GetProcAddress(LoadLibraryA("wsock32.dll"), "closesocket");
	*reinterpret_cast<FARPROC*>(0x375532EC) = GetProcAddress(LoadLibraryA("ws2_32.dll"), "recv");
	*reinterpret_cast<FARPROC*>(0x375532F0) = GetProcAddress(LoadLibraryA("wsock32.dll"), "select");
	*reinterpret_cast<FARPROC*>(0x375532F4) = GetProcAddress(LoadLibraryA("wsock32.dll"), "send");
	*reinterpret_cast<FARPROC*>(0x375532F8) = GetProcAddress(LoadLibraryA("wsock32.dll"), "WSAGetLastError");
	*reinterpret_cast<FARPROC*>(0x375532FC) = GetProcAddress(LoadLibraryA("wsock32.dll"), "connect");
	*reinterpret_cast<FARPROC*>(0x37553300) = GetProcAddress(LoadLibraryA("wsock32.dll"), "ioctlsocket");
	*reinterpret_cast<FARPROC*>(0x37553304) = GetProcAddress(LoadLibraryA("ws2_32.dll"), "setsockopt");
	*reinterpret_cast<FARPROC*>(0x37553308) = GetProcAddress(LoadLibraryA("wsock32.dll"), "socket");
	*reinterpret_cast<FARPROC*>(0x3755330C) = GetProcAddress(LoadLibraryA("ws2_32.dll"), "FreeAddrInfoW");
	*reinterpret_cast<FARPROC*>(0x37553310) = GetProcAddress(LoadLibraryA("ws2_32.dll"), "getaddrinfo");
}

SOCKET socket_used_in_cheat = 0;

decltype(&send) oSend;

int PASCAL FAR hooked_send(
	_In_ SOCKET s,
	_In_reads_bytes_(len) const char FAR* buf,
	_In_ int len,
	_In_ int flags)
{
	if (s == socket_used_in_cheat)
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
	if (s == socket_used_in_cheat)
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
	if (_ReturnAddress() >= reinterpret_cast<void*>(0x36FA0000) && _ReturnAddress() < reinterpret_cast<void*>(0x36FA0000 + sizeof(hack_bin)))
	{
		socket_used_in_cheat = s;
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
	return 8328;
}

using find_pattern = int(__cdecl*)(void* dll, std::string& sig, int offset);
find_pattern ofind_pattern = 0;

int find_pattern_func(void* Module, const char* szPattern)
{
	// Pattern to bytes
	int PatternBytes[256];
	int PatternBytesSize = 0;
	for (char* Current = (const_cast<char*>(szPattern)); Current < (const_cast<char*>(szPattern) + strlen(szPattern)); Current++) {
		if (*Current == '?') {
			++Current;
			if (*Current == '?')
				++Current;
			PatternBytes[PatternBytesSize] = -1;
			PatternBytesSize++;
		}
		else {
			PatternBytes[PatternBytesSize] = strtoul(Current, &Current, 16);
			PatternBytesSize++;
		}
	}

	BYTE* ScanAddress = (BYTE*)Module;
	auto dosHeader = (PIMAGE_DOS_HEADER)ScanAddress;
	auto ntHeaders = (PIMAGE_NT_HEADERS)(ScanAddress + dosHeader->e_lfanew);
	int ScanSize = ntHeaders->OptionalHeader.SizeOfImage - PatternBytesSize;

	// Scan
	for (int i = 0; i < ScanSize; i++)
	{
		bool Found = true;
		for (int j = 0; j < PatternBytesSize; ++j)
		{
			if (ScanAddress[i + j] != PatternBytes[j] && PatternBytes[j] != -1)
			{
				Found = false;
				break;
			}
		}
		if (Found)
			return reinterpret_cast<int>(&ScanAddress[i]);
	}

	return 0;
}

int __cdecl hooked_find_pattern(void* dll, std::string & sig, int offset)
{
	//auto original = ofind_pattern(dll, sig, offset);
	int pattern = find_pattern_func(dll, sig.data());
	//printf("[+] find_pattern called -> %p -> %s -> %p\n", dll, sig.data(), pattern);
	if (!pattern)
	{
		printf("[+] find_pattern invalid...\n");
		system("pause");
	}
	return pattern;
}

struct module_info_t
{
	uint32_t start = 0;
	uint32_t end = 0;
	std::string name = "";
};

std::vector<module_info_t> g_modules_dumped = { };

std::vector<module_info_t> g_modules = { };

std::vector<module_info_t> g_sigs_dumped = { };

//stage //result
std::unordered_map<int, int> g_sig_addresses = {};

void init()
{
	g_modules_dumped.push_back({ 0x00400000,0x00414000,"XInput1_3" });
	g_modules_dumped.push_back({ 0x00570000,0x00672000,"csgo" });
	g_modules_dumped.push_back({ 0x1f9f0000,0x24ad3000,"client" });
	g_modules_dumped.push_back({ 0x50230000,0x50352000,"serverbrowser" });
	g_modules_dumped.push_back({ 0x50360000,0x503ee000,"XAudio2_7" });
	g_modules_dumped.push_back({ 0x503f0000,0x50f44000,"server" });
	g_modules_dumped.push_back({ 0x51450000,0x517a6000,"d3dcompiler_47_32" });
	g_modules_dumped.push_back({ 0x517b0000,0x51f7c000,"NvCamera32" });
	g_modules_dumped.push_back({ 0x51f80000,0x5217f000,"D3DX9_43" });
	g_modules_dumped.push_back({ 0x52180000,0x5398d000,"phonon" });
	g_modules_dumped.push_back({ 0x53990000,0x54231000,"engine" });
	g_modules_dumped.push_back({ 0x542d0000,0x54300000,"vaudio_celt" });
	g_modules_dumped.push_back({ 0x54300000,0x54383000,"mss32" });
	g_modules_dumped.push_back({ 0x54390000,0x54461000,"matchmaking" });
	g_modules_dumped.push_back({ 0x54470000,0x547e2000,"scaleformui" });
	g_modules_dumped.push_back({ 0x547f0000,0x54938000,"vguimatsurface" });
	g_modules_dumped.push_back({ 0x55130000,0x55255000,"stdshader_dx9" });
	g_modules_dumped.push_back({ 0x55260000,0x556bc000,"studiorender" });
	g_modules_dumped.push_back({ 0x556c0000,0x55cf7000,"nvapi" });
	g_modules_dumped.push_back({ 0x55df0000,0x55e43000,"stdshader_dbg" });
	g_modules_dumped.push_back({ 0x618e0000,0x61b39000,"AcGenral" });
	g_modules_dumped.push_back({ 0x61c40000,0x61d0a000,"shaderapidx9" });
	g_modules_dumped.push_back({ 0x62090000,0x620a6000,"mssmp3" });
	g_modules_dumped.push_back({ 0x62530000,0x6256b000,"localize" });
	g_modules_dumped.push_back({ 0x625c0000,0x62633000,"WindowManagementAPI" });
	g_modules_dumped.push_back({ 0x62640000,0x62733000,"Windows_UI" });
	g_modules_dumped.push_back({ 0x62740000,0x62759000,"vaudio_miles" });
	g_modules_dumped.push_back({ 0x62760000,0x627db000,"vgui2" });
	g_modules_dumped.push_back({ 0x627e0000,0x62833000,"soundsystem" });
	g_modules_dumped.push_back({ 0x62840000,0x62913000,"vscript" });
	g_modules_dumped.push_back({ 0x62920000,0x62998000,"datacache" });
	g_modules_dumped.push_back({ 0x629a0000,0x62ad3000,"vphysics" });
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
	g_modules_dumped.push_back({ 0x64400000,0x6446c000,"MpOAV" });
	g_modules_dumped.push_back({ 0x64470000,0x64488000,"amsi" });
	g_modules_dumped.push_back({ 0x64490000,0x64559000,"fastprox" });
	g_modules_dumped.push_back({ 0x64560000,0x64570000,"wbemsvc" });
	g_modules_dumped.push_back({ 0x64570000,0x6457d000,"wbemprox" });
	g_modules_dumped.push_back({ 0x64600000,0x64670000,"wbemcomn" });
	g_modules_dumped.push_back({ 0x64a30000,0x64a66000,"valve_avi" });
	g_modules_dumped.push_back({ 0x64b40000,0x64b66000,"dinput" });
	g_modules_dumped.push_back({ 0x64b70000,0x64baf000,"soundemittersystem" });
	g_modules_dumped.push_back({ 0x65210000,0x65232000,"msvfw32" });
	g_modules_dumped.push_back({ 0x65240000,0x6526c000,"DXCore" });
	g_modules_dumped.push_back({ 0x65270000,0x6528a000,"scenefilecache" });
	g_modules_dumped.push_back({ 0x657a0000,0x6592f000,"twinapi_appcore" });
	g_modules_dumped.push_back({ 0x65930000,0x65b10000,"d3d11" });
	g_modules_dumped.push_back({ 0x66fd0000,0x67058000,"vstdlib_s" });
	g_modules_dumped.push_back({ 0x67940000,0x679d9000,"tier0_s" });
	g_modules_dumped.push_back({ 0x68850000,0x69ce7000,"nvd3dum" });
	g_modules_dumped.push_back({ 0x69cf0000,0x69dd5000,"nvldumd" });
	g_modules_dumped.push_back({ 0x69e70000,0x69f7c000,"materialsystem" });
	g_modules_dumped.push_back({ 0x69f80000,0x6a3d6000,"wininet" });
	g_modules_dumped.push_back({ 0x6a3e0000,0x6a487000,"crashhandler" });
	g_modules_dumped.push_back({ 0x6a490000,0x6a498000,"wsock32" });
	g_modules_dumped.push_back({ 0x706e0000,0x70799000,"textinputframework" });
	g_modules_dumped.push_back({ 0x707e0000,0x70806000,"dwmapi" });
	g_modules_dumped.push_back({ 0x70810000,0x7084d000,"inputsystem" });
	g_modules_dumped.push_back({ 0x70ad0000,0x70c5f000,"d3d9" });
	g_modules_dumped.push_back({ 0x70e90000,0x70e9f000,"resourcepolicyclient" });
	g_modules_dumped.push_back({ 0x70ea0000,0x70ebb000,"avifil32" });
	g_modules_dumped.push_back({ 0x70ec0000,0x71150000,"steamnetworkingsockets" });
	g_modules_dumped.push_back({ 0x71150000,0x711c6000,"filesystem_stdio" });
	g_modules_dumped.push_back({ 0x711d0000,0x71319000,"GameOverlayRenderer" });
	g_modules_dumped.push_back({ 0x71320000,0x71363000,"vstdlib" });
	g_modules_dumped.push_back({ 0x71370000,0x71914000,"tier0" });
	g_modules_dumped.push_back({ 0x719b0000,0x71b21000,"WindowsCodecs" });
	g_modules_dumped.push_back({ 0x71d40000,0x71d64000,"devobj" });
	g_modules_dumped.push_back({ 0x71d70000,0x71e70000,"drvstore" });
	g_modules_dumped.push_back({ 0x71e70000,0x720ee000,"CoreUIComponents" });
	g_modules_dumped.push_back({ 0x720f0000,0x7218b000,"CoreMessaging" });
	g_modules_dumped.push_back({ 0x72190000,0x7226b000,"WinTypes" });
	g_modules_dumped.push_back({ 0x72270000,0x7235d000,"inputhost" });
	g_modules_dumped.push_back({ 0x72360000,0x72397000,"dinput8" });
	g_modules_dumped.push_back({ 0x72400000,0x72406000,"mssds3d" });
	g_modules_dumped.push_back({ 0x72410000,0x72448000,"steam_api" });
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
	g_modules_dumped.push_back({ 0x72fd0000,0x7353f000,"MessageBus" });
	g_modules_dumped.push_back({ 0x73a20000,0x73ae2000,"propsys" });
	g_modules_dumped.push_back({ 0x73cb0000,0x73cd1000,"sspicli" });
	g_modules_dumped.push_back({ 0x74260000,0x74285000,"userenv" });
	g_modules_dumped.push_back({ 0x74290000,0x7429a000,"secur32" });
	g_modules_dumped.push_back({ 0x742a0000,0x742d2000,"IPHLPAPI" });
	g_modules_dumped.push_back({ 0x742e0000,0x742f8000,"profapi" });
	g_modules_dumped.push_back({ 0x74300000,0x74373000,"winspool" });
	g_modules_dumped.push_back({ 0x74380000,0x7439e000,"gpapi" });
	g_modules_dumped.push_back({ 0x743a0000,0x743c8000,"winmm" });
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
	g_modules_dumped.push_back({ 0x773b0000,0x773fe000,"wintrust" });
	g_modules_dumped.push_back({ 0x77400000,0x774f0000,"kernel32" });
	g_modules_dumped.push_back({ 0x774f0000,0x77513000,"gdi32" });
	g_modules_dumped.push_back({ 0x77520000,0x77565000,"shlwapi" });
	g_modules_dumped.push_back({ 0x77570000,0x775f7000,"SHCore" });
	g_modules_dumped.push_back({ 0x77600000,0x77663000,"ws2_32" });
	g_modules_dumped.push_back({ 0x77670000,0x7780c000,"user32" });
	g_modules_dumped.push_back({ 0x77810000,0x778f0000,"gdi32full" });
	g_modules_dumped.push_back({ 0x778f0000,0x778fa000,"wow64cpu" });
	g_modules_dumped.push_back({ 0x77900000,0x77aa4000,"ntdll_77900000" });
	g_modules_dumped.push_back({ 0x78990000,0x7ab9a000,"nvwgf2um" });


	g_sig_addresses.insert({ 0xf818a000, 0x50370d90 });
	g_sig_addresses.insert({ 0x78cce6d5, 0x1fd887c8 });
	g_sig_addresses.insert({ 0x63aa2ad9, 0x1fb7cdd0 });
	g_sig_addresses.insert({ 0xd78f23e8, 0x1fb7cc4f });
	g_sig_addresses.insert({ 0xe6eaabdb, 0x1fd946c6 });
	g_sig_addresses.insert({ 0x398214b7, 0x1fd53f1d });
	g_sig_addresses.insert({ 0x13d4aced, 0x1fb7cbe5 });
	g_sig_addresses.insert({ 0xc62aa8b3, 0x1fb7c367 });
	g_sig_addresses.insert({ 0x321907d2, 0x1fb7cf91 });
	g_sig_addresses.insert({ 0x8cc9ff64, 0x1fb795d0 });
	g_sig_addresses.insert({ 0xf3dac366, 0x1fb7c5f1 });
	g_sig_addresses.insert({ 0x6939f9ab, 0x1fcfdce5 });
	g_sig_addresses.insert({ 0xa8d3b1b6, 0x5120e592 });
	g_sig_addresses.insert({ 0x38bb117e, 0x5120f879 });
	g_sig_addresses.insert({ 0x3ddb7621, 0x1fbafaae });
	g_sig_addresses.insert({ 0x5586ce17, 0x1fd4cc66 });
	g_sig_addresses.insert({ 0x297334f6, 0x1fd4cc52 });
	g_sig_addresses.insert({ 0xb7a8a31c, 0x1fd53eea });
	g_sig_addresses.insert({ 0xcb0e7fef, 0x1fef460c });
	g_sig_addresses.insert({ 0x630ba5f7, 0x1fef4621 });
	g_sig_addresses.insert({ 0x8add58a5, 0x1fd98429 });
	g_sig_addresses.insert({ 0x7d1aae8a, 0x1fd53e96 });
	g_sig_addresses.insert({ 0xfae77068, 0x1fc5212e });
	g_sig_addresses.insert({ 0xd957044c, 0x1fb9218c });
	g_sig_addresses.insert({ 0x6142d525, 0x1fe09d05 });
	g_sig_addresses.insert({ 0x1019e968, 0x1fccc02e });
	g_sig_addresses.insert({ 0x311eba0b, 0x1fe09ab8 });
	g_sig_addresses.insert({ 0x9ffa7202, 0x1fe09b6a });
	g_sig_addresses.insert({ 0x138a731c, 0x510aa060 });
	g_sig_addresses.insert({ 0x3e384190, 0x1fbc4762 });
	g_sig_addresses.insert({ 0x4bb73e38, 0x1ff4a9f0 });
	g_sig_addresses.insert({ 0x1d72700c, 0x1ffbf1e0 });
	g_sig_addresses.insert({ 0x741c7f81, 0x1fb6a9e0 });
	g_sig_addresses.insert({ 0x8d571754, 0x1fb795d6 });
	g_sig_addresses.insert({ 0xfc48a4be, 0x1fb6b296 });
	g_sig_addresses.insert({ 0xddcd38fa, 0x1fb888f6 });
	g_sig_addresses.insert({ 0x64f9f1c3, 0x1fb8888c });
	g_sig_addresses.insert({ 0x953c420c, 0x1ffc9580 });
	g_sig_addresses.insert({ 0xcc702117, 0x1ffca3b0 });
	g_sig_addresses.insert({ 0xec372476, 0x1ffcba10 });
	g_sig_addresses.insert({ 0xbfbcf44e, 0x1ffc44e0 });
	g_sig_addresses.insert({ 0x762f699b, 0x1ffc5640 });
	g_sig_addresses.insert({ 0xb59e105e, 0x1ffc6160 });
	g_sig_addresses.insert({ 0xd112472a, 0x1ffc5b00 });
	g_sig_addresses.insert({ 0x20277296, 0x51165c20 });
	g_sig_addresses.insert({ 0xe46b563d, 0x1fb5c2f0 });
	g_sig_addresses.insert({ 0x73dfc8e3, 0x1fd66b02 });
	g_sig_addresses.insert({ 0xa20084df, 0x1fd62590 });
	g_sig_addresses.insert({ 0x1d72700c, 0x1ffbf1e0 });
	g_sig_addresses.insert({ 0xb0df5d2b, 0x1fd87210 });
	g_sig_addresses.insert({ 0x907cf135, 0x1fd74df0 });
	g_sig_addresses.insert({ 0x8add58a5, 0x1fd98429 });
	g_sig_addresses.insert({ 0xd957044c, 0x1fb9218c });
	g_sig_addresses.insert({ 0x3e384190, 0x1fbc4762 });
	g_sig_addresses.insert({ 0x6ab01334, 0x1fd9411d });
	g_sig_addresses.insert({ 0xf52f3daf, 0x200bba80 });
	g_sig_addresses.insert({ 0xb52fc3ae, 0x200b9870 });
	g_sig_addresses.insert({ 0xb2522e60, 0x1fc27cf0 });
	g_sig_addresses.insert({ 0xb9188818, 0x1fd48f44 });
	g_sig_addresses.insert({ 0x4bb73e38, 0x1ff4a9f0 });
	g_sig_addresses.insert({ 0xe23ab8c6, 0x1fcc5994 });
	g_sig_addresses.insert({ 0x2bfe6e6a, 0x1fcc5960 });
	g_sig_addresses.insert({ 0x6142d525, 0x1fe09d05 });
	g_sig_addresses.insert({ 0x1019e968, 0x1fccc02e });
	g_sig_addresses.insert({ 0x311eba0b, 0x1fe09ab8 });
	g_sig_addresses.insert({ 0x9ffa7202, 0x1fe09b6a });
	g_sig_addresses.insert({ 0x15c3bdc4, 0x510b1f98 });
	g_sig_addresses.insert({ 0x3ecb2b71, 0x510ad4a4 });
	g_sig_addresses.insert({ 0xf870ddb4, 0x1fc54c28 });
	g_sig_addresses.insert({ 0xaf26a26c, 0x1fc00b8b });
	g_sig_addresses.insert({ 0x4911cf54, 0x1fb4b2ed });
	g_sig_addresses.insert({ 0xf743cc72, 0x1fcc5822 });
	g_sig_addresses.insert({ 0xe335ec62, 0x1fb82cc0 });
	g_sig_addresses.insert({ 0xaf09d530, 0x1fc5de66 });
	g_sig_addresses.insert({ 0xdc30b6b8, 0x1fc873bf });
	g_sig_addresses.insert({ 0x1e63778c, 0x1fd06f7e });
	g_sig_addresses.insert({ 0x3a5c86c0, 0x1fd42230 });
	g_sig_addresses.insert({ 0xb313bdd1, 0x1fc65b4a });
	g_sig_addresses.insert({ 0xc5391d89, 0x51174fbf });
	g_sig_addresses.insert({ 0x96060043, 0x24ddf147 });
	g_sig_addresses.insert({ 0x39f9e956, 0x24d76a57 });
	g_sig_addresses.insert({ 0x53028691, 0x24fef8ec });
	g_sig_addresses.insert({ 0x3e7e1623, 0x24eb8d94 });
	g_sig_addresses.insert({ 0x115bb8b, 0x1fc137c1 });
	g_sig_addresses.insert({ 0x78f7821b, 0x1fc0efef });
	g_sig_addresses.insert({ 0xa892eacf, 0x1fb92218 });
	g_sig_addresses.insert({ 0xb0df5d2b, 0x1fd87210 });
	g_sig_addresses.insert({ 0x8675e72a, 0x5023c920 });
	g_sig_addresses.insert({ 0xf836ab50, 0x1fb91f90 });
	g_sig_addresses.insert({ 0x56fe5978, 0x1fd4e529 });
	g_sig_addresses.insert({ 0x15218c62, 0x1fc57870 });
	g_sig_addresses.insert({ 0x73baa13f, 0x1fb91e00 });
	g_sig_addresses.insert({ 0x8a9e46f1, 0x5120f876 });
	g_sig_addresses.insert({ 0xb487ac6f, 0x5120e58f });
	g_sig_addresses.insert({ 0x9c2111a7, 0x5120e770 });
	g_sig_addresses.insert({ 0x17603a3, 0x512103d0 });
	g_sig_addresses.insert({ 0x53b94e91, 0x1fb92d80 });
	g_sig_addresses.insert({ 0x50a6b538, 0x1fb92f40 });
	g_sig_addresses.insert({ 0x5bfe5118, 0x1fca3c90 });
	g_sig_addresses.insert({ 0xe5193f4c, 0x51101a40 });
	g_sig_addresses.insert({ 0x38593d23, 0x1fd93730 });
	g_sig_addresses.insert({ 0xb8a03746, 0x1fd93840 });
	g_sig_addresses.insert({ 0xb79c175a, 0x1fd93cc0 });
	g_sig_addresses.insert({ 0xc9707da1, 0x51067060 });
	g_sig_addresses.insert({ 0xb78dd9f4, 0x1fb82040 });
	g_sig_addresses.insert({ 0x2d81357e, 0x1fb5a580 });
	g_sig_addresses.insert({ 0xdb0c438a, 0x1fb61020 });
	g_sig_addresses.insert({ 0x9a797d1d, 0x1fb5ede0 });
	g_sig_addresses.insert({ 0x757b85ad, 0x1fcb9ad0 });
	g_sig_addresses.insert({ 0x4bde48a2, 0x5120caf0 });
	g_sig_addresses.insert({ 0x8a0c5015, 0x1fc67880 });
	g_sig_addresses.insert({ 0xb2522e60, 0x1fc27cf0 });
	g_sig_addresses.insert({ 0xd34fe914, 0x200c4110 });
	g_sig_addresses.insert({ 0x1b1e1674, 0x1fcf3540 });
	g_sig_addresses.insert({ 0xeb5eae36, 0x5107e550 });
	g_sig_addresses.insert({ 0x5342b4b9, 0x1fce9440 });
	g_sig_addresses.insert({ 0xf70e7841, 0x1fb7ad20 });
	g_sig_addresses.insert({ 0xbb70a21, 0x1fb7c2eb });
	g_sig_addresses.insert({ 0x3a5c86c0, 0x1fd42230 });
	g_sig_addresses.insert({ 0xdfdf2d44, 0x1fcc678e });
	g_sig_addresses.insert({ 0xe46b563d, 0x1fb5c2f0 });
	g_sig_addresses.insert({ 0x5aa72a66, 0x1fb5f5b6 });
	g_sig_addresses.insert({ 0x115bb8b, 0x1fc137c1 });
	g_sig_addresses.insert({ 0x71b6730e, 0x1fd1dfd3 });
	g_sig_addresses.insert({ 0x670a12b6, 0x1fd6d201 });
	g_sig_addresses.insert({ 0x97227c40, 0x1ff37cec });
	g_sig_addresses.insert({ 0x723e15e4, 0x1ff36fc1 });
	g_sig_addresses.insert({ 0x7ebd80c5, 0x1fb5fc20 });
	g_sig_addresses.insert({ 0x1b89c3bc, 0x1fb44820 });
	g_sig_addresses.insert({ 0x6612c4d6, 0x510ad460 });
	g_sig_addresses.insert({ 0xa876ae7b, 0x1fbb3140 });
	g_sig_addresses.insert({ 0xa41c71e3, 0x1fc5e1ea });
	g_sig_addresses.insert({ 0xc5793d88, 0x510c2800 });
	g_sig_addresses.insert({ 0x196f4bcc, 0x1fb7a950 });
	g_sig_addresses.insert({ 0xee8a8ee2, 0x1fb795f0 });
	g_sig_addresses.insert({ 0x60c4477d, 0x1fd94790 });
	g_sig_addresses.insert({ 0x7a1307b, 0x51246ca7 });
	g_sig_addresses.insert({ 0xbce6e7c4, 0x1fd534c0 });
	g_sig_addresses.insert({ 0x512570e8, 0x1fe09480 });
	g_sig_addresses.insert({ 0x8cb22e69, 0x1fd94005 });
	g_sig_addresses.insert({ 0xcf1ad538, 0x1fd4e470 });
	g_sig_addresses.insert({ 0xdf37b812, 0x1fd70d40 });
	g_sig_addresses.insert({ 0x3251114e, 0x1fbb7300 });
	g_sig_addresses.insert({ 0x4c344c58, 0x51247d04 });
	g_sig_addresses.insert({ 0xe41fc2f4, 0x1fd44c50 });

	g_sigs_dumped.push_back({ 0x00910000,0x00a12000,"csgo" });
	g_sigs_dumped.push_back({ 0x0f930000,0x0f944000,"XInput1_3" });
	g_sigs_dumped.push_back({ 0x1f9e0000,0x24ac3000,"client" });
	g_sigs_dumped.push_back({ 0x24bd0000,0x25724000,"server" });
	g_sigs_dumped.push_back({ 0x50010000,0x5020f000,"D3DX9_43" });
	g_sigs_dumped.push_back({ 0x50210000,0x502da000,"shaderapidx9" });
	g_sigs_dumped.push_back({ 0x502e0000,0x5035b000,"vgui2" });
	g_sigs_dumped.push_back({ 0x50360000,0x504a8000,"vguimatsurface" });
	g_sigs_dumped.push_back({ 0x504b0000,0x504d2000,"msvfw32" });
	g_sigs_dumped.push_back({ 0x504e0000,0x50516000,"valve_avi" });
	g_sigs_dumped.push_back({ 0x50520000,0x50573000,"soundsystem" });
	g_sigs_dumped.push_back({ 0x50580000,0x50653000,"vscript" });
	g_sigs_dumped.push_back({ 0x50660000,0x5069f000,"soundemittersystem" });
	g_sigs_dumped.push_back({ 0x506a0000,0x50afc000,"studiorender" });
	g_sigs_dumped.push_back({ 0x50b00000,0x50c0c000,"materialsystem" });
	g_sigs_dumped.push_back({ 0x50c10000,0x50d43000,"vphysics" });
	g_sigs_dumped.push_back({ 0x50d50000,0x50fe0000,"steamnetworkingsockets" });
	g_sigs_dumped.push_back({ 0x50fe0000,0x51881000,"engine" });
	g_sigs_dumped.push_back({ 0x51890000,0x519d9000,"GameOverlayRenderer" });
	g_sigs_dumped.push_back({ 0x51a80000,0x51af8000,"datacache" });
	g_sigs_dumped.push_back({ 0x51b00000,0x51b76000,"filesystem_stdio" });
	g_sigs_dumped.push_back({ 0x51b80000,0x51bc3000,"vstdlib" });
	g_sigs_dumped.push_back({ 0x51bd0000,0x52174000,"tier0" });
	g_sigs_dumped.push_back({ 0x521b0000,0x52281000,"matchmaking" });
	g_sigs_dumped.push_back({ 0x52530000,0x52579000,"launcher" });
	g_sigs_dumped.push_back({ 0x52580000,0x5258f000,"resourcepolicyclient" });
	g_sigs_dumped.push_back({ 0x52670000,0x526ad000,"inputsystem" });
	g_sigs_dumped.push_back({ 0x52790000,0x527ab000,"avifil32" });
	g_sigs_dumped.push_back({ 0x527f0000,0x52843000,"stdshader_dbg" });
	g_sigs_dumped.push_back({ 0x53b60000,0x53b98000,"steam_api" });
	g_sigs_dumped.push_back({ 0x53bb0000,0x53bca000,"scenefilecache" });
	g_sigs_dumped.push_back({ 0x53bd0000,0x53bf6000,"dinput" });
	g_sigs_dumped.push_back({ 0x54110000,0x54747000,"nvapi" });
	g_sigs_dumped.push_back({ 0x56c00000,0x56c09000,"hi" });
	g_sigs_dumped.push_back({ 0x56c10000,0x56d32000,"serverbrowser" });
	g_sigs_dumped.push_back({ 0x56d40000,0x56d70000,"vaudio_celt" });
	g_sigs_dumped.push_back({ 0x56d70000,0x56dfe000,"XAudio2_7" });
	g_sigs_dumped.push_back({ 0x56e00000,0x56e06000,"mssds3d" });
	g_sigs_dumped.push_back({ 0x56e10000,0x56e26000,"mssmp3" });
	g_sigs_dumped.push_back({ 0x56e30000,0x56eb3000,"mss32" });
	g_sigs_dumped.push_back({ 0x56ec0000,0x56ed9000,"vaudio_miles" });
	g_sigs_dumped.push_back({ 0x57b10000,0x57c46000,"AudioSes" });
	g_sigs_dumped.push_back({ 0x57c50000,0x57c8a000,"wdmaud" });
	g_sigs_dumped.push_back({ 0x58150000,0x58158000,"midimap" });
	g_sigs_dumped.push_back({ 0x58160000,0x5816a000,"msacm32_58160000" });
	g_sigs_dumped.push_back({ 0x58170000,0x58177000,"ksuser" });
	g_sigs_dumped.push_back({ 0x581e0000,0x59426000,"steamclient" });
	g_sigs_dumped.push_back({ 0x5a100000,0x5a1c9000,"fastprox" });
	g_sigs_dumped.push_back({ 0x5b790000,0x5b818000,"vstdlib_s" });
	g_sigs_dumped.push_back({ 0x5c100000,0x5c199000,"tier0_s" });
	g_sigs_dumped.push_back({ 0x5d020000,0x5d08c000,"MpOAV" });
	g_sigs_dumped.push_back({ 0x5d090000,0x5d0a8000,"amsi" });
	g_sigs_dumped.push_back({ 0x5d0b0000,0x5d0c0000,"wbemsvc" });
	g_sigs_dumped.push_back({ 0x5d0c0000,0x5d130000,"wbemcomn" });
	g_sigs_dumped.push_back({ 0x5d130000,0x5d13d000,"wbemprox" });
	g_sigs_dumped.push_back({ 0x5dc90000,0x5dd03000,"WindowManagementAPI" });
	g_sigs_dumped.push_back({ 0x5dd10000,0x5de03000,"Windows_UI" });
	g_sigs_dumped.push_back({ 0x5dec0000,0x5df2b000,"MMDevAPI" });
	g_sigs_dumped.push_back({ 0x67ea0000,0x67ea8000,"avrt" });
	g_sigs_dumped.push_back({ 0x67eb0000,0x67f2f000,"dsound" });
	g_sigs_dumped.push_back({ 0x67f30000,0x67f4d000,"winmmbase" });
	g_sigs_dumped.push_back({ 0x67f50000,0x67f69000,"msacm32" });
	g_sigs_dumped.push_back({ 0x67f70000,0x67f85000,"samcli" });
	g_sigs_dumped.push_back({ 0x67f90000,0x681e9000,"AcGenral" });
	g_sigs_dumped.push_back({ 0x681f0000,0x682a9000,"textinputframework" });
	g_sigs_dumped.push_back({ 0x682b0000,0x682dc000,"DXCore" });
	g_sigs_dumped.push_back({ 0x682e0000,0x68502000,"nvspcap" });
	g_sigs_dumped.push_back({ 0x68510000,0x6869f000,"twinapi_appcore" });
	g_sigs_dumped.push_back({ 0x686a0000,0x68880000,"d3d11" });
	g_sigs_dumped.push_back({ 0x68a30000,0x69ec7000,"nvd3dum" });
	g_sigs_dumped.push_back({ 0x69ed0000,0x69fb5000,"nvldumd" });
	g_sigs_dumped.push_back({ 0x69fc0000,0x6a14f000,"d3d9" });
	g_sigs_dumped.push_back({ 0x6a150000,0x6a176000,"dwmapi" });
	g_sigs_dumped.push_back({ 0x6a260000,0x6a3d1000,"WindowsCodecs" });
	g_sigs_dumped.push_back({ 0x6a620000,0x6a6ad000,"comctl32" });
	g_sigs_dumped.push_back({ 0x70b00000,0x70f56000,"wininet" });
	g_sigs_dumped.push_back({ 0x71230000,0x7123a000,"hid" });
	g_sigs_dumped.push_back({ 0x71240000,0x71247000,"XINPUT9_1_0" });
	g_sigs_dumped.push_back({ 0x71300000,0x71324000,"devobj" });
	g_sigs_dumped.push_back({ 0x71330000,0x71430000,"drvstore" });
	g_sigs_dumped.push_back({ 0x71600000,0x716a7000,"crashhandler" });
	g_sigs_dumped.push_back({ 0x716b0000,0x716b8000,"wsock32" });
	g_sigs_dumped.push_back({ 0x718d0000,0x71929000,"FWPUCLNT" });
	g_sigs_dumped.push_back({ 0x71930000,0x71938000,"rasadhlp" });
	g_sigs_dumped.push_back({ 0x71940000,0x7194e000,"winrnr" });
	g_sigs_dumped.push_back({ 0x71950000,0x71966000,"nlaapi" });
	g_sigs_dumped.push_back({ 0x71970000,0x71980000,"wshbth" });
	g_sigs_dumped.push_back({ 0x71980000,0x71996000,"pnrpnsp" });
	g_sigs_dumped.push_back({ 0x719a0000,0x719b1000,"NapiNSP" });
	g_sigs_dumped.push_back({ 0x719c0000,0x71a50000,"dnsapi" });
	g_sigs_dumped.push_back({ 0x71a70000,0x71a86000,"dhcpcsvc" });
	g_sigs_dumped.push_back({ 0x71a90000,0x71d0e000,"CoreUIComponents" });
	g_sigs_dumped.push_back({ 0x71d10000,0x71deb000,"WinTypes" });
	g_sigs_dumped.push_back({ 0x71df0000,0x71e8b000,"CoreMessaging" });
	g_sigs_dumped.push_back({ 0x71e90000,0x71f7d000,"inputhost" });
	g_sigs_dumped.push_back({ 0x71f80000,0x71fb7000,"dinput8" });
	g_sigs_dumped.push_back({ 0x72520000,0x725e2000,"dxgi" });
	g_sigs_dumped.push_back({ 0x725f0000,0x72b5f000,"MessageBus" });
	g_sigs_dumped.push_back({ 0x72b60000,0x72bcd000,"msvcp140" });
	g_sigs_dumped.push_back({ 0x72f80000,0x73042000,"propsys" });
	g_sigs_dumped.push_back({ 0x73210000,0x73225000,"VCRUNTIME140" });
	g_sigs_dumped.push_back({ 0x73290000,0x732b1000,"sspicli" });
	g_sigs_dumped.push_back({ 0x732c0000,0x732ca000,"secur32" });
	g_sigs_dumped.push_back({ 0x73670000,0x73678000,"version" });
	g_sigs_dumped.push_back({ 0x73840000,0x73858000,"profapi" });
	g_sigs_dumped.push_back({ 0x73860000,0x7387e000,"gpapi" });
	g_sigs_dumped.push_back({ 0x73880000,0x738a6000,"cryptnet" });
	g_sigs_dumped.push_back({ 0x738b0000,0x738be000,"msasn1" });
	g_sigs_dumped.push_back({ 0x738c0000,0x738ca000,"cryptbase" });
	g_sigs_dumped.push_back({ 0x738d0000,0x738ff000,"rsaenh" });
	g_sigs_dumped.push_back({ 0x73900000,0x73913000,"cryptsp" });
	g_sigs_dumped.push_back({ 0x73920000,0x73949000,"ntmarta" });
	g_sigs_dumped.push_back({ 0x739d0000,0x73a22000,"mswsock" });
	g_sigs_dumped.push_back({ 0x73a30000,0x73a3d000,"umpdc" });
	g_sigs_dumped.push_back({ 0x73a40000,0x73a84000,"powrprof" });
	g_sigs_dumped.push_back({ 0x73a90000,0x73ab8000,"winmm" });
	g_sigs_dumped.push_back({ 0x73ac0000,0x73ae5000,"userenv" });
	g_sigs_dumped.push_back({ 0x73af0000,0x73b22000,"IPHLPAPI" });
	g_sigs_dumped.push_back({ 0x73cc0000,0x73d33000,"winspool" });
	g_sigs_dumped.push_back({ 0x73d40000,0x73d67000,"wldp" });
	g_sigs_dumped.push_back({ 0x73d70000,0x73d89000,"mpr" });
	g_sigs_dumped.push_back({ 0x74020000,0x7462a000,"windows_storage" });
	g_sigs_dumped.push_back({ 0x74630000,0x746d0000,"apphelp" });
	g_sigs_dumped.push_back({ 0x746d0000,0x746df000,"kernel_appcore" });
	g_sigs_dumped.push_back({ 0x746e0000,0x7490d000,"iertutil" });
	g_sigs_dumped.push_back({ 0x74910000,0x7491b000,"netutils" });
	g_sigs_dumped.push_back({ 0x74920000,0x7493d000,"srvcli" });
	g_sigs_dumped.push_back({ 0x74940000,0x74ae9000,"urlmon" });
	g_sigs_dumped.push_back({ 0x74af0000,0x74b64000,"uxtheme" });
	g_sigs_dumped.push_back({ 0x74d80000,0x74f9c000,"KERNELBASE" });
	g_sigs_dumped.push_back({ 0x750b0000,0x751d0000,"ucrtbase" });
	g_sigs_dumped.push_back({ 0x751d0000,0x7520b000,"cfgmgr32" });
	g_sigs_dumped.push_back({ 0x75210000,0x753ac000,"user32" });
	g_sigs_dumped.push_back({ 0x753b0000,0x75413000,"ws2_32" });
	g_sigs_dumped.push_back({ 0x75420000,0x75510000,"kernel32" });
	g_sigs_dumped.push_back({ 0x75510000,0x7560a000,"crypt32" });
	g_sigs_dumped.push_back({ 0x75610000,0x75890000,"combase" });
	g_sigs_dumped.push_back({ 0x75890000,0x758b6000,"imm32" });
	g_sigs_dumped.push_back({ 0x758c0000,0x7591f000,"bcryptPrimitives" });
	g_sigs_dumped.push_back({ 0x75920000,0x759b6000,"oleaut32" });
	g_sigs_dumped.push_back({ 0x759c0000,0x75a7f000,"msvcrt" });
	g_sigs_dumped.push_back({ 0x75ae0000,0x75b67000,"SHCore" });
	g_sigs_dumped.push_back({ 0x75b70000,0x75c2e000,"rpcrt4" });
	g_sigs_dumped.push_back({ 0x75c40000,0x75cbb000,"msvcp_win" });
	g_sigs_dumped.push_back({ 0x75cc0000,0x75cd9000,"imagehlp" });
	g_sigs_dumped.push_back({ 0x75e50000,0x75ecb000,"advapi32" });
	g_sigs_dumped.push_back({ 0x75ed0000,0x75ee8000,"win32u" });
	g_sigs_dumped.push_back({ 0x75ef0000,0x75f3e000,"wintrust" });
	g_sigs_dumped.push_back({ 0x75f40000,0x75fb6000,"sechost" });
	g_sigs_dumped.push_back({ 0x75fc0000,0x75fc7000,"nsi" });
	g_sigs_dumped.push_back({ 0x75fd0000,0x760a4000,"msctf" });
	g_sigs_dumped.push_back({ 0x760b0000,0x760b6000,"psapi" });
	g_sigs_dumped.push_back({ 0x760c0000,0x761a0000,"gdi32full" });
	g_sigs_dumped.push_back({ 0x761a0000,0x761c3000,"gdi32" });
	g_sigs_dumped.push_back({ 0x761d0000,0x76253000,"clbcatq" });
	g_sigs_dumped.push_back({ 0x76260000,0x76343000,"ole32" });
	g_sigs_dumped.push_back({ 0x76350000,0x76784000,"setupapi" });
	g_sigs_dumped.push_back({ 0x76790000,0x767d5000,"shlwapi" });
	g_sigs_dumped.push_back({ 0x768d0000,0x76e85000,"shell32" });
	g_sigs_dumped.push_back({ 0x76e90000,0x76ea9000,"bcrypt" });
	g_sigs_dumped.push_back({ 0x76eb0000,0x76eba000,"wow64cpu" });
	g_sigs_dumped.push_back({ 0x76ec0000,0x77064000,"ntdll_76ec0000" });
	g_sigs_dumped.push_back({ 0x77340000,0x77b0c000,"NvCamera32" });
	g_sigs_dumped.push_back({ 0x77b10000,0x77c35000,"stdshader_dx9" });
	g_sigs_dumped.push_back({ 0x77c40000,0x77c7b000,"localize" });
	g_sigs_dumped.push_back({ 0x77c80000,0x77ff2000,"scaleformui" });
	g_sigs_dumped.push_back({ 0x787b0000,0x7a9ba000,"nvwgf2um" });
	g_sigs_dumped.push_back({ 0x7a9c0000,0x7c1cd000,"phonon" });
	g_sigs_dumped.push_back({ 0x7c240000,0x7c596000,"d3dcompiler_47_32" });
	g_sigs_dumped.push_back({ 0x586d0000,0x58753000,"wow64win" });
	g_sigs_dumped.push_back({ 0x58e20000,0x58e79000,"wow64" });
}

int __stdcall fix_sig_address(int address)
{
	if (!address)
	{
		std::cout << "unknown address" << std::endl;
		return 0;
	}

	for (int i = 0; i < g_sigs_dumped.size(); i++)
	{
		if (address >= g_sigs_dumped[i].start && address < g_sigs_dumped[i].end)
		{
			int local_addr = reinterpret_cast<int>(LoadLibraryA(g_sigs_dumped[i].name.data()));
			if (!local_addr)
			{
				std::cout << std::format("FAILED TO FIND {} !!!", g_sigs_dumped[i].name) << std::endl;
				system("pause");
			}
			int rebased_pointer = address - g_sigs_dumped[i].start + local_addr;
			//std::cout << std::format("updating pointer (sig): {}.dll -> {:x}->{:x}", g_sigs_dumped[i].name, address, rebased_pointer) << std::endl;
			return rebased_pointer;
		}
	}

	std::cout << std::format("FAILED TO FIND {:x} !!!", address) << std::endl;
	system("pause");

	return 0;
}

int __stdcall fix_interface_address(int address)
{
	for (int i = 0; i < g_modules_dumped.size(); i++)
	{
		if (address >= g_modules_dumped[i].start && address < g_modules_dumped[i].end)
		{
			int local_addr = reinterpret_cast<int>(LoadLibraryA(g_modules_dumped[i].name.data()));
			if (!local_addr)
			{
				std::cout << std::format("FAILED TO FIND {} !!!", g_modules_dumped[i].name) << std::endl;
				system("pause");
			}
			int rebased_pointer = address - g_modules_dumped[i].start + local_addr;
			//std::cout << std::format("updating pointer (interface): {}.dll -> {:x}->{:x}", g_modules_dumped[i].name, address, rebased_pointer) << std::endl;
			return rebased_pointer;
		}
	}

	std::cout << std::format("FAILED TO FIND {:x} !!!", address) << std::endl;
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
		pop ebp // pop
		mov[ebp - 0x40], eax // put fixed address
		POPAD // get all original registers
		push g_interface_jmp_back // jmp back
		ret // ret
	}
}

bool g_should_print = false;

using get_server_address = int(__cdecl*)(int hash);
get_server_address oget_server_address = 0;

int __cdecl hooked_get_server_address(int hash)
{
	static int j = 0;
	j++;
	int fixed_address = fix_sig_address(g_sig_addresses.at(hash));

	if (j == 123)
	{
		g_should_print = true;
	}

	return fixed_address;
}

void* g_fix_username = 0;

int i = 0;

char fix_username()
{
	static const char* name = "PinkKing   ";
	char name_text = name[i];
	i++;
	if (i >= strlen(name))
	{
		i = 0;
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

int i2 = 0;

char fix_username2()
{
	static const char* name = "PinkKing   ";
	char name_text = name[i2];
	i2++;
	if (i2 >= strlen(name))
	{
		i2 = 0;
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
	printf("[+] allocating mem...\n");

	void* hack_address = VirtualAlloc(reinterpret_cast<void*>(0x36FA0000), sizeof(hack_bin), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!hack_address)
	{
		printf("[-] failed to allocate memory (restart game and instantly inject)\n");
		Sleep(3000);
		TerminateProcess(reinterpret_cast<HANDLE>(-1), 0);
	}

	/*
	void* stub_1 = VirtualAlloc(reinterpret_cast<void*>(0x42B50000), 0x00d7c000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!stub_1)
	{
		printf("[-] failed to allocate memory (restart game and instantly inject)\n");
		Sleep(3000);
		TerminateProcess(reinterpret_cast<HANDLE>(-1), 0);
	}

	void* stub_2 = VirtualAlloc(reinterpret_cast<void*>(0x42440000), 0x00010000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!stub_2)
	{
		printf("[-] failed to allocate memory (restart game and instantly inject)\n");
		Sleep(3000);
		TerminateProcess(reinterpret_cast<HANDLE>(-1), 0);
	}

	void* stub_3 = VirtualAlloc(reinterpret_cast<void*>(0x424C0000), 0x00010000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!stub_3)
	{
		printf("[-] failed to allocate memory (restart game and instantly inject)\n");
		Sleep(3000);
		TerminateProcess(reinterpret_cast<HANDLE>(-1), 0);
	}

	void* stub_4 = VirtualAlloc(reinterpret_cast<void*>(0x425C0000), 0x00010000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!stub_4)
	{
		printf("[-] failed to allocate memory (restart game and instantly inject)\n");
		Sleep(3000);
		TerminateProcess(reinterpret_cast<HANDLE>(-1), 0);
	}
	*/

	printf("[+] allocated mem!\n");

	printf("[+] init...\n");
	init();
	memcpy(hack_address, hack_bin, sizeof(hack_bin));
	/*
	memcpy(stub_1, bin_stub_1, sizeof(bin_stub_1));
	memcpy(stub_2, bin_stub_2, sizeof(bin_stub_2));
	memcpy(stub_3, bin_stub_3, sizeof(bin_stub_3));
	memcpy(stub_4, bin_stub_4, sizeof(bin_stub_4));
	*/
	printf("[+] inited!\n");

	printf("[+] waiting for serverbrowser.dll ...\n");
	while (!GetModuleHandleA("serverbrowser.dll")) Sleep(100);
	printf("[+] found serverbrowser.dll !\n");

	HANDLE hModSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());

	MODULEENTRY32 me;
	me.dwSize = sizeof(me);
	if (Module32First(hModSnap, &me))
	{
		g_modules.push_back({ reinterpret_cast<uint32_t>(me.modBaseAddr), me.modBaseSize, me.szModule });
		while (Module32Next(hModSnap, &me))
		{
			g_modules.push_back({ reinterpret_cast<uint32_t>(me.modBaseAddr), me.modBaseSize, me.szModule });
		}
	}

	printf("[+] patching...\n");
	// nop out "store result" since we do it anyway
	memset(reinterpret_cast<void*>(0x3743D012), 0x90, 3);

	// username
	memset(reinterpret_cast<void*>(0x3721A480), 0x90, 8);
	memset(reinterpret_cast<void*>(0x372AA3B4), 0x90, 8);

	// stop process from exiting
	std::array<uint8_t, 6> patch1 = { 0xE9, 0x7A, 0x02, 0x00, 0x00, 0x90 };
	std::array<uint8_t, 6> patch2 = { 0xE9, 0x7A, 0x02, 0x00, 0x00, 0x90 };
	std::array<uint8_t, 6> patch3 = { 0xE9, 0xAF, 0x02, 0x00, 0x00, 0x90 };
	std::array<uint8_t, 6> patch4 = { 0xE9, 0x7A, 0x02, 0x00, 0x00, 0x90 };

	memcpy(reinterpret_cast<void*>(0x373D5933), patch1.data(), patch1.size());
	memcpy(reinterpret_cast<void*>(0x373D5C20), patch2.data(), patch2.size());
	memcpy(reinterpret_cast<void*>(0x373D6DCB), patch3.data(), patch3.size());
	memcpy(reinterpret_cast<void*>(0x373D7AC5), patch4.data(), patch4.size());

	// fix slow injection
	*reinterpret_cast<BYTE*>(0x373D58D6) = 0xEB;
	*reinterpret_cast<BYTE*>(0x373D5BC3) = 0xEB;

	std::array<uint8_t, 6> patch5 = { 0xE9, 0x8C, 0x00, 0x00, 0x00, 0x90 };

	memcpy(reinterpret_cast<void*>(0x373D6D33), patch5.data(), patch5.size());

	*reinterpret_cast<BYTE*>(0x373D7A68) = 0xEB;

	// we init YES SIR
	*reinterpret_cast<bool*>(0x37219817) = 0;
	*reinterpret_cast<bool*>(0x373E8D52) = 0;
	*reinterpret_cast<bool*>(0x373E8D6B) = 0;

	printf("[+] patched!\n");

	printf("[+] creating hooks...\n");
	if (MH_Initialize() != MH_OK)
	{
		printf("[-] failed to initialize minhook\n");
		return;
	}

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

	if (MH_CreateHook(reinterpret_cast<void*>(0x37422060), hooked_find_pattern, reinterpret_cast<void**>(&ofind_pattern)) != MH_OK)
	{
		printf("[-] failed to create hook at find_pattern\n");
		return;
	}

	if (MH_CreateHook(reinterpret_cast<void*>(0x3743D012), rebase_interface_pointers, reinterpret_cast<void**>(&g_interface_jmp_back)) != MH_OK)
	{
		printf("[-] failed to create hook at rebase_interface\n");
		return;
	}

	if (MH_CreateHook(reinterpret_cast<void*>(0x3723B2B0), hooked_get_server_address, reinterpret_cast<void**>(&oget_server_address)) != MH_OK)
	{
		printf("[-] failed to create hook at get_server_address\n");
		return;
	}


	if (MH_CreateHook(reinterpret_cast<void*>(0x3721A480), hooked_username, reinterpret_cast<void**>(&g_fix_username)) != MH_OK)
	{
		printf("[-] failed to create hook at username\n");
		return;
	}

	if (MH_CreateHook(reinterpret_cast<void*>(0x372AA3B4), hooked_username2, reinterpret_cast<void**>(&g_fix_username2)) != MH_OK)
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

	uint32_t oep = 0x37447EDF;
	printf("[+] calling dllmain...\n");

	//printf("[+] calling dllmain... (%p->%p) (%p) (%p)\n", hack_address, oep, stub_1, stub_2);

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
	printf("[+] finished!\n");
	printf("[+] owned by PinkKing#8199 & NiceL#0001 ( https://discord.gg/GHKuYjZrdM )\n");
}

bool __stdcall DllMain(HANDLE hinstDLL, uint32_t fdwReason, void* lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		AllocConsole();
		SetConsoleTitleA("pandora.gg crack");
		freopen("CONOUT$", "w", stdout);
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), 0, 0, 0);
	}
	return true;
}