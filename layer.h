#include "numpy.h"
#include <ctime>
#include "afuncs.h"

using namespace std;

class layer
{
public:
    numpy inputs, weights, outputs, biases, deltaw;

    layer() {}
    layer(int, int);
    ~layer() {}

    void forward(vector<vector<float>>);
    void forward(numpy);
    void backpropagate(numpy);
    void output();
    float cal_error(numpy);
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
    for (int i = 0; i < outputs.x; i++)
        for (int j = 0; j < outputs.y; j++)
            outputs.array[i][j] = sigmoid(outputs.array[i][j]);
}

void layer ::forward(numpy p_inputs)
{
    inputs = numpy(p_inputs.array);
    if (inputs.y == weights.x)
    {
        outputs = (inputs * weights) + biases;
    }
    for (int i = 0; i < outputs.x; i++)
        for (int j = 0; j < outputs.y; j++)
            outputs.array[i][j] = sigmoid(outputs.array[i][j]);
}

void layer::output()
{
    outputs.display(outputs.array);
}

float layer::cal_error(numpy target)
{
    float error = 0;

    if (outputs.x == target.x && outputs.y == target.y)
    {
        numpy temp(vector<vector<float>>(outputs.x, vector<float>(outputs.y, 0)));
        for (int i = 0; i < outputs.x; i++)
            for (int j = 0; j < outputs.y; j++)
                temp.array[i][j] = 0.5 * pow((target.array[i][j] - outputs.array[i][j]), 2);
        for (auto v : temp.array)
            for (auto value : v)
                error += value;
    }

    return error;
}