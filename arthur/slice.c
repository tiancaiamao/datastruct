#include <string.h>
#include <stdlib.h>

struct slice {
  void *ptr;
  int elem_size;
  int pos;
  int cap;
};

void
slice_init(struct slice* s, int sz) {
  s->pos = 0;
  s->cap = 16;
  s->elem_size = sz;
  s->ptr = malloc(s->cap * sz);
}

void
slice_append(struct slice* s, void* v) {
  if (s->pos >= s->cap) {
    s->cap = s->cap * 2;
    s->ptr = realloc(s->ptr, s->cap * s->elem_size);
  }

  memcpy(s->ptr+s->pos*s->elem_size, v, s->elem_size);
  s->pos++;
}

void
slice_release(struct slice* s) {
  free(s->ptr);
}
