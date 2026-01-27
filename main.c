#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TWO_MEGABYTES (2097152)

typedef struct stack_allocator_context {
  uintptr_t cursor;
  uintptr_t start;
  size_t size;
} stack_frame;

void stack_frame_initialize(stack_frame *context, size_t size);
void stack_frame_clear(stack_frame *context);
void stack_frame_deinitialize(stack_frame *context);

uintptr_t stack_frame_allocate(stack_frame *context, size_t size);
void stack_frame_deallocate(stack_frame *context, size_t size);

int main() {
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

void stack_frame_initialize(stack_frame *context, size_t size) {
  const uintptr_t buffer = (uint64_t)(malloc(size));

  context->start = buffer;
  context->cursor = buffer;
  context->size = size;
}

void stack_frame_clear(stack_frame *context) {
  context->cursor = context->start;
}

void stack_frame_deinitialize(stack_frame *context) {
  free((void *)context->start);
}

uintptr_t stack_frame_allocate(stack_frame *context, size_t size) {
  if (context == NULL || size == 0UL) {
    return 0UL;
  }

  const uintptr_t end = context->start + context->size;
  const uintptr_t current = context->cursor;
  const uintptr_t next = current + size;

  if (next > end) {
    return 0UL;
  }

  context->cursor += size;

  return current;
}

void stack_frame_deallocate(stack_frame *context, size_t size) {
  if (context == NULL || size == 0UL) {
    return;
  }

  const uintptr_t current = context->cursor;
  const uintptr_t previous = current - size;

  if (previous < context->start) {
    return;
  }

  context->cursor -= size;
}
