#include "numpy.h"
#include <ctime>

using namespace std;

class layer
{
public:
    vector<vector<float>> inputs, weights, outputs;
    vector<float> biases;
    layer(int, int, int);
    vector<vector<float>> forward(vector<vector<float>>);
};

layer ::layer(int n_inputs, int n_neurons, int b = 0)
{
    biases = vector<float>(n_neurons, b);
    weights = vector<vector<float>>(n_inputs, vector<float>(n_neurons, 0));

    srand((int)time(0));

    for (int i = 0; i < weights.size(); i++)
        for (int j = 0; j < weights[0].size(); j++)
            weights[i][j] = rand() * 0.000000001 - 1;
}

vector<vector<float>> layer ::forward(vector<vector<float>> inputs)
{
    numpy np;
    if (inputs[0].size() == weights.size())
    {
        this->inputs = inputs;
        outputs = np.add(np.dot(inputs, weights), biases);
    }
    return outputs;
}
