#include <iostream>
#include <vector>
#include "numpy.h"

using namespace std;

int main()
{
    numpy np;

    vector<vector<float>> inputs = {
        {1, 2, 3, 2.5},
        {2.0, 5, -1, 2},
        {-1.5, 2.7, 3.3, -0.8}};

    vector<vector<float>> weights = {
        {0.2, 0.8, -0.5, 1.0},
        {0.5, -0.91, 0.26, -0.5},
        {-0.26, -0.27, 0.17, 0.87}};

    vector<float> biases = {2, 3, 0.5};

    vector<vector<float>> layer_outputs = np.add(np.dot(inputs, np.transpose(weights)), biases);

    np.display(layer_outputs);

    return 0;
}