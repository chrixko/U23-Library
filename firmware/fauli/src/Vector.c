
#include "Vector.h"

// public
void Vector_init(Vector* this) {
    this->elements = NULL;
    this->usedElements = 0;
    this->allocatedElements = 0;
}

void Vector_addElement(Vector* this, ElementType element) {
    if (this->allocatedElements <= this->usedElements) {
        _Vector_recreateWithoutSizeCheck(this, this->allocatedElements + CacheIncreaseRate);
    }
    _Vector_addElementWithoutSizeCheck(this, element);
}

void Vector_shrinkCache(Vector* this, bool maximumShrink) {
    if (this->allocatedElements - CacheIncreaseRate > this->usedElements) {
        _Vector_recreateWithoutSizeCheck(this, this->usedElements+CacheIncreaseRate);
    } else if (maximumShrink && this->allocatedElements > this->usedElements) {
        _Vector_recreateWithoutSizeCheck(this, this->usedElements);
    }
}

ElementType Vector_get(Vector* this, unsigned int i) {
    if (i < this->usedElements) {
        return this->elements[i];
    }
    return NULL;
}

void Vector_set(Vector* this, unsigned int i, ElementType element) {
    if (i < this->usedElements) {
        this->elements[i] = element;
    }
}

// private
void _Vector_addElementWithoutSizeCheck(Vector* this, ElementType element) {
    this->elements[this->usedElements] = element;
    this->usedElements++;
}

/// newallocatedElements must be higher than this->usedElements to succeed
void _Vector_recreateWithoutSizeCheck(Vector* this, unsigned int newallocatedElements) {
    ElementType* copy = malloc(newallocatedElements * sizeof(ElementType));
    for (unsigned int i=0; i < this->usedElements; ++i) {
        copy[i] = this->elements[i];
    }
    free(this->elements);
    this->elements = copy;
    this->allocatedElements = newallocatedElements;
}
