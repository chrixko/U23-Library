#ifndef C_VECTOR_H 
#define C_VECTOR_H 

#define CacheIncreaseRate 8
#define ElementType void*

#include "stdbool.h"
#include "malloc.h"

#ifndef NULL
    #define NULL 0
#endif


typedef struct {
    ElementType* elements;
    unsigned int usedElements;
    unsigned int allocatedElements;
} Vector;

// public
void Vector_init(Vector* this);
void Vector_addElement(Vector* this, ElementType element);
void Vector_shrinkCache(Vector* this, bool maximumShrink);
ElementType Vector_get(Vector* this, unsigned int i);
void Vector_set(Vector* this, unsigned int i, ElementType element);
// private
void _Vector_addElementWithoutSizeCheck(Vector* this, ElementType element);
void _Vector_recreateWithoutSizeCheck(Vector* this, unsigned int newallocatedElements);
#endif
