#include <stdio.h>

int main() {
    // (arg1 * arg2) - (arg1 + arg2) = result
    int arg1, arg2, result, check;
    // Get input
    printf("Enter two integers : ");
    scanf("%d%d", &arg1, &arg2);
    asm volatile (
        "movl %1, %%eax;    "  /* Set arg1 to A */
        "movl %2, %%ebx;    "  /* Set arg2 to B */
        "movl %%eax, %%ecx; "  /* Copy A to C */
        "movl %%eax, %%edx; "  /* Copy A to D */
        "imull %%ebx, %%ecx;"  /* C = B x C */
        "addl %%ebx, %%edx; "  /* D = B + D */
        "subl %%edx, %%ecx  "  /* C = C - D, return C */
            : "=c" (result) 
            : "g" (arg1), "g" (arg2)
    );

    check = (arg1*arg2)-(arg1+arg2);
    printf("(%d * %d) - (%d + %d) = %d\n", arg1, arg2, arg1, arg2, check);
    printf("C check result: %d\n", check);
    printf("Assembly result: %d\n", result);
    if (check == result) {
        printf("Success!\n");
    } else {
        printf("Failure!\n");
    }
    return 0;
}
