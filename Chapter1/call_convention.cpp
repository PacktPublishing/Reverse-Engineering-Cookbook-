
#include <stdio.h> 

 int __stdcall std_add_numbers(int a, int b, int c, int d, int e) { 
    return a + b + c + d + e; 
} 

int test_std() {
    return std_add_numbers(1, 2, 3, 4, 5);
}

 int __cdecl cdecl_add_numbers(int a, int b, int c, int d, int e) { 
    return a + b + c + d + e; 
} 

int test_cdecl() {
    return cdecl_add_numbers(1, 2, 3, 4, 5);
}

int __fastcall fastcall_add_numbers(int a, int b, int c, int d, int e) { 
    return a + b + c + d + e; 
} 

int test_fastcall() {
    return fastcall_add_numbers(1, 2, 3, 4, 5);
}

class MyClass {
public:
    int __thiscall std_memberFunc(int a) {
        return a + 5;
    }

    int __cdecl cdecl_memberFunc(int a) {
        return a + 5;
    }
};

int main() { 
    int result; 
    // Call the function with five integers 
    result = test_std(); 
    result = test_cdecl(); 
    result = test_fastcall(); 
    MyClass mycls;
    result = mycls.std_memberFunc(1);
    result = mycls.cdecl_memberFunc(1);
    printf("The result is: %d\n", result); 
    return 0; 
} 

 