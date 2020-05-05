#include "layer.h"

using namespace std;

int main()
{
    // numpy np;

    vector<vector<float>> inputs = {
        {1, 2, 3, 2.5},
        {2.0, 5, -1, 2},
        {-1.5, 2.7, 3.3, -0.8}};

    layer l1(4, 4);
    l1.forward(inputs);

    layer l2(4, 8);
    l2.forward(l1.outputs);

    layer out(8, 4);
    out.forward(l2.outputs);

    out.output();

    return 0;
}