#include "utils.h"

double randRange(double low, double high)
{

    // Convert to int, as QRandomGenerator does not support double

    int L = (int)(low * 1000000);

    int H = (int)(high * 1000000);

    int r = QRandomGenerator::global()->bounded(L, H);

    return r / 1000000.0;
}