#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char password[] = "123456";

void win() {
    system("/bin/sh"); // 或其他功能
}

int main(int argc, char *argv[]) {
    char buffer[128];
    //_set_printf_count_output(1);
    printf("%p %s\n", &password, password);
    while(1) {
        printf("Enter input: ");
        fflush(stdout);
        //memset(&buffer, 0,sizeof(buffer));
        read(0, buffer, sizeof(buffer)); 
        printf("%s\n",buffer);
        fflush(stdout);
        printf(buffer);
        fflush(stdout);
        printf("\n");
        fflush(stdout);
    }
    return 0;
}
