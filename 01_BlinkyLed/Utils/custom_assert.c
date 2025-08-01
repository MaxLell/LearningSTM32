#include "custom_assert.h"
#include <stdio.h>

void assert_failed(const char *condition, const char *file, int line)
{
    printf("\n\n");
    printf("#########################\n");
    printf("#      ASSERT FAILED    #\n");
    printf("#########################\n");
    printf("----> Condition: (%s)\n", condition);
    printf("----> File: %s:%d\n", file, line);

    asm volatile("BKPT #0"); // Trigger a breakpoint
    
    for(;;)
    {
        // Infinite loop to halt execution
    }
}
