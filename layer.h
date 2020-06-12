#include "numpy.h"
#include <ctime>
#include "afuncs.h"

using namespace std;

class layer
{
public:
    numpy inputs, weights, outputs, biases, weight_change;
    layer *llink, *rlink;

    layer() {}
    layer(int, int, layer *, layer *);
    ~layer() {}

    void forward(vector<vector<float>>);
    void linkleft(layer *);
    void linkright(layer *);
    void update_weights();
    void backpropagate(vector<vector<float>> target);
    numpy wwcim();
    void backpropagate();
};

layer ::layer(int n_inputs, int n_neurons, layer *left_link = NULL, layer *right_link = NULL)
{
    biases = numpy(vector<float>(n_neurons, 0));
    weights = numpy(vector<vector<float>>(n_neurons, vector<float>(n_inputs, 0)));

    srand((int)time(0));

    for (int i = 0; i < weights.x; i++)
        for (int j = 0; j < weights.y; j++)
            weights.array[i][j] = rand() * 0.000000001 - 1;

    if (left_link != NULL)
        linkleft(left_link);
    else
        llink = NULL;

    if (right_link != NULL)
        linkright(right_link);
    else
        rlink = right_link;
}

void layer ::forward(vector<vector<float>> p_inputs)
{
    inputs = numpy(p_inputs);
    if (inputs.y == weights.y)
    {
        outputs = (inputs * weights.transpose());
    }

    for (int i = 0; i < outputs.x; i++)
        for (int j = 0; j < outputs.y; j++)
            outputs.array[i][j] = sigmoid(outputs.array[i][j]);

    if (rlink != NULL)
        rlink->forward(outputs.array);
}

void layer::linkleft(layer *left_link)
{
    try
    {
        if (left_link != NULL && left_link->weights.x == weights.y)
            llink = left_link;

        else
            return;
    }
    catch (exception e)
    {
        return;
    }
}

void layer::linkright(layer *right_link)
{
    try
    {
        if (right_link != NULL && right_link->weights.y == weights.x)
            rlink = right_link;

        else
            return;
    }
    catch (exception e)
    {
        return;
    }
}

void layer::update_weights()
{
    if (weight_change.x > 0 && weight_change.y > 0)
    {
        weights = weights - weight_change;
        if (llink != NULL)
            llink->update_weights();
    }
}

void layer::backpropagate(vector<vector<float>> target)
{
    if (rlink == NULL)
    {
        if (target.size() == outputs.x && target[0].size() == outputs.y)
        {
            numpy one = numpy(vector<vector<float>>(1, vector<float>(outputs.y, 1)));
            weight_change = numpy(vector<vector<float>>(weights.x, vector<float>(weights.y, 0)));

            numpy i;
            numpy o;
            numpy wc;
            numpy t;
            numpy temp;

            for (int j = 0; j < outputs.x; j++)
            {
                o = numpy(outputs.array[j]);
                i = numpy(inputs.array[j]);
                t = numpy(target[j]);

                wc = (o - t);
                temp = o.get_identity();
                wc = wc * temp;
                temp = one - o;
                temp = temp.get_identity();
                wc = wc * temp;
                wc = wc.transpose();
                wc = wc * i;
                weight_change = wc + weight_change;
            }

            for (int j = 0; j < weight_change.x; j++)
                for (int k = 0; k < weight_change.y; k++)
                    weight_change.array[j][k] = (weight_change.array[j][k] / outputs.x);

            // weights = weights - weight_change;
            if (llink != NULL)
                llink->backpropagate();
            update_weights();
        }

        else
            return;
    }
    else
    {
        rlink->backpropagate(target);
    }
}

numpy layer::wwcim()
{
    numpy matrix;
    matrix = (weights.transpose() * weight_change).get_identity();

    if (rlink == NULL)
        return matrix;

    else
        return (matrix + rlink->wwcim());
}

void layer::backpropagate()
{
    {
        numpy one = numpy(vector<vector<float>>(1, vector<float>(outputs.y, 1)));
        weight_change = numpy(vector<vector<float>>(weights.x, vector<float>(weights.y, 0)));

        numpy h;
        numpy temp;
        numpy i;
        for (int j = 0; j < outputs.x; j++)
        {
            i = numpy(inputs.array[j]);
            h = i * weights.transpose();
            numpy temp = one - h;
            temp = temp.transpose() * i;
            temp = rlink->wwcim() * temp;
            weight_change = weight_change + temp;
        }
        for (int j = 0; j < weight_change.x; j++)
            for (int k = 0; k < weight_change.y; k++)
                weight_change.array[j][k] = (weight_change.array[j][k] / outputs.x);
    }
    if (llink != NULL)
        llink->backpropagate();
    else
        return;
}
