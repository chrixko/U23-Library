#include "Utils.h"

uint32_t randomInRange(uint32_t min, uint32_t max) {
    return min + GetRandomInteger() % max;
}
