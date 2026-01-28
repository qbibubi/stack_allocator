#pragma once
#include <stdint.h>
#include <stdlib.h>

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

