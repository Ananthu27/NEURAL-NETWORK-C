#include <math.h>
namespace activation::functions
{
    inline int step(float value)
    {
        return (value > 0 ? 1 : 0);
    }

    inline float sigmoid(float value)
    {
        return (1 / (1 + exp(-value)));
    }

    inline float rlu(float value)
    {
        return (value > 0 ? value : 0);
    }
} // namespace activation::functions
