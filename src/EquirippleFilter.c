#include "EquirippleFilter.h"

Equiripple *newEquiripple(double coefficients[], int filter_size)
{
    Equiripple *equiripple = (Equiripple *)calloc(1, sizeof(Equiripple));

    equiripple->filter_size = filter_size;

    equiripple->coefficients = (double *)calloc(coefficients, sizeof(double));

    equiripple->filter_buffer = (double *)calloc(filter_size, sizeof(double));

    for (int i = 0; i < filter_size; i++)
    {
        equiripple->coefficients[i] = coefficients[i];
    }

    equiripple->filter = filter;

    return equiripple;
}

void filter(Equiripple *equiripple, double sample)
{
    equiripple->filter_buffer[equiripple->k0] = sample;

    equiripple->output = 0;

    for (int k = 0; k < equiripple->filter_size; k++)
    {
        equiripple->output += equiripple->filter_buffer[equiripple->k0] * equiripple->coefficients[k];
        equiripple->k0--;
        if (equiripple->k0 < 0)
        {
            equiripple->k0 += equiripple->filter_size;
        }
    }

    equiripple->k0 = ++equiripple->k0 >= equiripple->filter_size ? 0 : equiripple->k0++;
}