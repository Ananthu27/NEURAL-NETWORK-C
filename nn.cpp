#include "layer.h"
// #include "knn.h"
#include "afuncs.h"

using namespace std;

int main()
{
    // // tutorial implementation ...
    // vector<vector<float>> input = {
    //     {-1, -1, -1},
    //     {-1, -1, 1},
    //     {-1, 1, -1},
    //     {-1, 1, 1},
    //     {1, -1, -1},
    //     {1, -1, 1},
    //     {1, 1, -1},
    //     {1, 1, 1},
    // };

    // // biases[no of neurons]
    // // weights[no of neurons][n inputs]
    // // layer(n inputs, no of neurons)

    // vector<vector<float>> target = {
    //     {-1},
    //     {1},
    //     {-1},
    //     {1},
    //     {-1},
    //     {1},
    //     {-1},
    //     {1},

    // };
    // layer l1(3, 1);

    // for (int i = 0; i < 100; i++)
    // {
    //     l1.backpropagate(target);
    //     l1.forward(input);
    //     l1.outputs.display();
    // }

    numpy v(vector<vector<float>>(3, vector<float>(3, 3)));
    numpy e(vector<vector<float>>(3, vector<float>(3, 4)));
    numpy c(vector<float>(3, 5));
    numpy t = v ^ c;
    numpy o = v - e;
    v.display();
    e.display();
    t.display();
    o.display();
}