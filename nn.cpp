#include "layer.h"

using namespace std;

int main()
{
    // numpy np;

    vector<vector<float>> inputs = {
        {1, 2, 3, 2.5},
        {2.0, 5, -1, 2},
        {-1.5, 2.7, 3.3, -0.8}};

    layer l1(4, 12);
    l1.forward(inputs);

    layer l2(12, 12);
    l2.forward(l1.outputs.array2d);

    layer out(12, 2);
    out.forward(l2.outputs.array2d);

    out.output();

    return 0;
}