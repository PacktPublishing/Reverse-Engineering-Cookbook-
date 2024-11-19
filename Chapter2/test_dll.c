#include <windows.h> 
  
__declspec(dllexport) void Test() 
{ 
    MessageBox(NULL, "Hello", "Test", MB_OK); 
} 
  
BOOL WINAPI DllMain( 
    HINSTANCE hinstDLL, 
    DWORD fdwReason, 
    LPVOID lpvReserved ) 
{ 
    return TRUE; 
} 
  