#ifndef SLICE_H
#define SLICE_H

struct slice;

void slice_init(struct slice*, int sz);
void slice_append(strucd slice*, void*);
void slice_release(struct slice*);

#endif
