#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t bit = ((*reg >> 0) ^ (*reg >> 2) ^ (*reg >> 3) ^ (*reg >> 5)) & 1;
    *reg = (*reg >> 1) | (bit << 15);
}

