#include "numpy.h"
#include <ctime>

using namespace std;

class layer
{
public:
    numpy inputs, weights, outputs, biases;

    layer() {}
    layer(int, int);
    ~layer() {}

    void forward(vector<vector<float>>);
    void forward(numpy);
    void output();
};

layer ::layer(int n_inputs, int n_neurons)
{
    biases = numpy(vector<float>(n_neurons, 0));
    weights = numpy(vector<vector<float>>(n_inputs, vector<float>(n_neurons, 0)));

    srand((int)time(0));

    for (int i = 0; i < weights.x; i++)
        for (int j = 0; j < weights.y; j++)
            weights.array[i][j] = rand() * 0.000000001 - 1;
}

void layer ::forward(vector<vector<float>> p_inputs)
{
    inputs = numpy(p_inputs);
    if (inputs.y == weights.x)
    {
        outputs = (inputs * weights) + biases;
    }
}

void layer ::forward(numpy p_inputs)
{
    inputs = numpy(p_inputs.array);
    if (inputs.y == weights.x)
    {
        outputs = (inputs * weights) + biases;
    }
}

void layer::output()
{
    outputs.display(outputs.array);
}