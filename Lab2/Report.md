## Завдання
Написати програму на мові Сі, яка описує та ініціює одновимірний масив з 10 цілих значень і виводить результат його обробки. За допомогою вбудованого асемблерного коду виконати наступне: Знайти середнє арифметичне елементів масиву та знайти максимальне значення 
## Виконання
```c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

float average_c(int *arr) {
/***********************************
* Get average value of array using C
***********************************/
    float sum = 0.0;
    for (int i = 0; i<10; ++i)
        sum += arr[i];
    return sum/10;
};

int max_c(int *arr) {
/***********************************
* Get maximum value of array using C
***********************************/
    int value = 0;
    for (int i=0; i < 10; ++i) {
        if (value < arr[i])
            value = arr[i];
    }
    return value;
}

float average_a(int *arr) {
/******************************************
* Get average value of array using Assembly
******************************************/
    int sum, rem;
    float f_rem, result;
    asm volatile (
            "    xorl %%eax,%%eax;          "  /* Set A to 0 */
            "    xorl %%edx,%%edx;          "  /* Set D to 0 */
            "repl: jecxz done;              "  /* Start cycle */
            "    decl %%ecx;                "  /* C -= 1 */
            "    addl (%%ebx,%%ecx,4),%%eax;"  /* Add B[C] to A */
            "    jmp repl;                  "  /* Jump to cycle start */
            "done:                          "  /* Break loop */
            "movl $10, %%ecx;               "  /* Set C to 10 */
            "idivl %%ecx;"                     /* Return A // C and A % C */ 
                : "=a"(sum), "=d"(rem)
                :"b"(arr),"c"(10)
    );
    f_rem = (float)rem/10;
    result = (float)sum + f_rem;
    return result;
}

int max_a(int *arr) {
/******************************************
* Get maximum value of array using Assembly
******************************************/
    int result;
    asm volatile (
            "    xorl %%eax,%%eax;               "  /* Set A to 0 */
            "rep2: jecxz done2;                  "  /* Start cycle */
            "    decl %%ecx;                     "  /* C -= 1 */
            "    cmpl (%%ebx,%%ecx,4),%%eax;     "  /* If B[C] > A... */
            "    jl check;                       "  /* ... jump to "check" block */
            "    jmp rep2;                       "  /* Jump to rep2 cycle */
            "    check: jecxz stop;              "  /* Check block */
            "        movl (%%ebx,%%ecx,4), %%eax;"  /* Change A to B[C] */
            "        jmp rep2;                   "  /* Jump to rep2 cycle */
            "    stop:                           "  /* Stop "check" */
            "done2:"                                /* Stop cycle, return A */
                :"=a"(result)
                :"b"(arr),"c"(10)
    );
    return result;
}

int main() {
    // Get average and max of array[10]
    srand(time(NULL));
    int tpl[10], c, mx_a, mx_c;
    float avrg_a, avrg_c;
    
    // Generate random array
    printf("Tuple is: [");
    for(c=0; c<10; ++c) {
        tpl[c] = rand() % 501;
        printf("%d", tpl[c]);
        if (c<9) {
            printf(", ");
        } else {
            printf("]\n");
        }
    }
    
    avrg_c = average_c(tpl);
    mx_c = max_c(tpl);
    avrg_a = average_a(tpl);
    mx_a = max_a(tpl);

    printf("Assembler Average: %.1f\n", avrg_a);
    printf("Assembler Max: %d\n", mx_a);
    printf("C Average: %.1f\n", avrg_c);
    printf("C Max: %d\n", mx_c);

    if ((avrg_a == avrg_c) && (mx_a == mx_c)) {
        printf("Success!\n");
    } else {
        printf("Failure!\n");
    }
    return 0;
}
```
## Висновок
В ході даної роботи був створений код, що генерує масив з 10 випадкових цілих чисел та записує їх у змінну `tpl`, та виводить його у консоль.  
Після цього у змінну `avrg_c` записується результат функції `average_c`. У цю функцію передається масив, а повертається середнє значення всіх його елементів. Обчислення виконуються мовою *С*.  
У змінну `mx_c` записується результат функції `max_c`. У цю функцію передається масив, а повертається його найбільший елемент. Обчислення виконуються мовою *С*.  
У змінну `avrg_a` та `mx_a` записуються значення функцій `average_a` та `max_a` відповідно. Функції аналогічні попереднім, але обчислення виконуються мовою *Assembly*.  
Значення останніх 4 змінних виводиться у консоль.  
Після цього якщо `avrg_c` дорівнює `avrg_a`, а `mx_c` дорівнює `mx_a` у консоль виводиться *Success!*.  
