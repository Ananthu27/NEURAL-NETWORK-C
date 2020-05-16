#include <math.h>

#define step(value) value > 0 ? 1 : 0
#define sigmoid(value) 1 / (1 + exp(-value))
#define rlu(value) value > 0 ? value : 0
