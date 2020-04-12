#include <stdio.h>

int main() {
    // (arg1 * arg2) - (arg1 + arg2) = result
    int arg1, arg2, result;
    printf("Enter two integers : ");
    scanf("%d%d", &arg1, &arg2);
    asm volatile (
            "movl %1, %%eax;"
            "movl %2, %%ebx;"
            "movl %%eax, %%ecx;"
            "movl %%eax, %%edx;"
            "imull %%ebx, %%ecx;"
            "addl %%ebx, %%edx;"
            "subl %%edx, %%ecx" : "=c" (result) : "g" (arg1), "g" (arg2));

    printf("Assembly result: %d\n", result);
    
    return 0;
}
