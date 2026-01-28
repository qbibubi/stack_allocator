#include "allocator.h"

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

