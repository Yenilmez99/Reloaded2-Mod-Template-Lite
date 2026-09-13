#include <windows.h>


DWORD WINAPI MainCore(LPVOID lpParam) {
    HMODULE myHModule = reinterpret_cast<HMODULE>(lpParam);

    // Your DLL Mod starts here
    while (!(GetAsyncKeyState(VK_F1)&0x1)) {
        Sleep(16); // 60fps
    }

    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH:
    {
        HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainCore, hModule, 0, nullptr);
        if (hThread != nullptr) CloseHandle(hThread);
        break;
    }
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}