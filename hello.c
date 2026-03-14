#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>
#include <rtems/confdefs.h>
#include <rtems/malloc.h>
#include <rtems/libcsupport.h>
#include <rtems/score/heapinfo.h>
#include <rtems/score/heapimpl.h>



static void print_info(Heap_Information_block *info)
{
    printf("Heap Information\n");
    printf("  Free blocks      : %zu\n", info->Free.number);
    printf("  Free largest     : %zu bytes\n", info->Free.largest);
    printf("  Free total       : %zu bytes\n", info->Free.total);
    printf("  Used blocks      : %zu\n", info->Used.number);
    printf("  Used largest     : %zu bytes\n", info->Used.largest);
    printf("  Used total       : %zu bytes\n", info->Used.total);

    printf("Heap Statistics\n");
    printf("  Lifetime alloc   : %llu bytes\n",
           info->Stats.lifetime_allocated);
    printf("  Lifetime freed   : %llu bytes\n",
           info->Stats.lifetime_freed);
    printf("  Current free     : %zu bytes\n",
           info->Stats.free_size);
    printf("  Free blocks stat : %u\n",
           info->Stats.free_blocks);
    printf("  Used blocks stat : %u\n",
           info->Stats.used_blocks);
}


#ifdef HEAP_PROTECTION
static void print_delayed()
{
    printf("delayed_free_block_count = %d\n", RTEMS_Malloc_Heap->Protection.delayed_free_block_count);
}
#endif


rtems_task Init(rtems_task_argument ignored)
{
#ifdef HEAP_PROTECTION
    printf("HEAP_PROTECTION is ENABLED\n");
#else
    printf("HEAP_PROTECTION is NOT ENABLED\n");
#endif

    void *ptrs[100];
    Heap_Information_block before;
    Heap_Information_block after;

    for (int i = 0; i < 50; i++) {
        ptrs[i] = malloc(1024);
    }

    for (int i = 0; i < 50; i++) {
        free(ptrs[i]);
    }

#ifdef HEAP_PROTECTION
    print_delayed();
#endif

    malloc_info(&before);
    printf("Stats after first malloc_info\n");
    print_info(&before);

#ifdef HEAP_PROTECTION
    print_delayed();
#endif

    malloc_info(&after);
    printf("Stats after second malloc info\n");
    print_info(&after);

#ifdef HEAP_PROTECTION
    print_delayed();
#endif
    exit(0);
}

