## Завдання
Написати програму мовою Сі, яка описує цілі змінні, здійснює їх ініціалізацію та виводить результат обчислень. За допомогою вбудованого асемблерного коду виконати наступне:  
Знайти різницю між добутком двох чисел та їх сумою, тобто: _(a*b)-(a+b)_
## Виконання
```c
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
```
## Висновок
В ході даної роботи був розроблений код, який дозволяє ввести два цілих числа, які будуть записані у змінні `arg1` та `arg2`.  
Після цього виконуються арифметичні дії, що вказані в завданні.  
Один раз мовою *С*, результат буде записаний у змінну `check`, та виведеться у консоль.  
Другий раз мовою *Assembly*, результат буде записаний до змінної `result`, та виведеться у консоль.  
Якщо `result`  збігається з `check` программа вважається виконаною вірно та виводить у консоль *Success!*.
