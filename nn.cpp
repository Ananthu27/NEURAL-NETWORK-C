#include "layer.h"
// #include "knn.h"
#include "afuncs.h"

using namespace std;

int main()
{
    // tutorial implementation ...
    vector<vector<float>> inputs = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1},
    };

    vector<vector<float>> targetv = {
        {0},
        {1},
        {0},
        {1},
        {0},
        {1},
        {0},
        {1},
    };
    numpy target(targetv);

    vector<vector<float>> onev = {
        {1},
        {1},
        {1},
        {1},
        {1},
        {1},
        {1},
        {1},
    };
    numpy one(onev);

    layer l1(3, 4);
    l1.forward(inputs);

    layer l2(4, 1);
    l2.forward(l1.outputs);

    // l2.output();
    std::cout << l2.cal_error(target) << std::endl;

    return 0;
}