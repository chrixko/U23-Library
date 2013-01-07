
#include "c-vector.h"

int main(void) {
    Vector vector;
    Vector_init(&vector);
    
    for (int i=0; i < 9000; ++i) {
        int* element = malloc(1*sizeof(int));
        *element = i;
        Vector_addElement(&vector, element);
    }
    
    printf("filled vector with %d Elements\n", vector.usedElements);
    printf("element #1337 is %d\n", *(int*)Vector_get(&vector, 1337));
    for (int i=0; i < vector.usedElements; ++i) {
        int* element = Vector_get(&vector, i);
        free(element);
        Vector_set(&vector, i, NULL);
    }
    printf("freed elements & vector");
}
