#include "src/allocator.h"

#include <stdio.h>

#define TWO_MEGABYTES (2097152)

int main(void) {
  stack_frame context;
  stack_frame_initialize(&context, TWO_MEGABYTES);

  const uintptr_t t1 = stack_frame_allocate(&context, 4096);
  const uintptr_t t2 = stack_frame_allocate(&context, 4096);
  const uintptr_t t3 = stack_frame_allocate(&context, 4096);

  printf("t1: 0x%p\n", (void *)t1);
  printf("t2: 0x%p\n", (void *)t2);
  printf("t3: 0x%p\n", (void *)t3);

  stack_frame_deinitialize(&context);

  return 0;
}
