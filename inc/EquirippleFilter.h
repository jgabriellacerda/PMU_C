#ifndef EQUIRIPPLE_H
#define EQUIRIPPLE_H

#include <stdlib.h>

struct Equiripple
{
    double *coefficients;

    int filter_size;

    double *filter_buffer;

    // Points to the position in the buffer the stores the most recent sample
    int k0;

    double output;

    void (*filter)(Equiripple *equiripple, double sample);
};

typedef struct Equiripple Equiripple;

Equiripple *newEquiripple(double coefficients[], int filter_size);

static void filter(Equiripple *equiripple, double sample);

#endif