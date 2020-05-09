#include "numpy.h"
#include <math.h>
#include <bits/stdc++.h>

class knn : public numpy
{
public:
    numpy distances;
    vector<float> point;
    // modify ...
    knn(vector<vector<float>> dataframe)
    {
        array = dataframe;
        x = dataframe.size();
        y = dataframe[0].size();
    };
    void get_distances(numpy);
    numpy nearest(numpy, int);
};

void knn ::get_distances(numpy point)
{
    // if the input dimentions are not none then
    if (point.x > 0 && point.y > 0 && x > 0 && y)
    {
        if (y == point.y)
        {
            point.transpose();
            distances = numpy(vector<vector<float>>(x, vector<float>(point.y, 0)));
            for (int i = 0; i < x; i++)
                for (int j = 0; j < point.y; j++)
                {
                    for (int k = 0; k < y; k++)
                        distances.array[i][j] += pow(array[i][k] - point.array[k][j], 2);
                    distances.array[i][j] = sqrt(distances.array[i][j]);
                }
        }
    }

    vector<vector<float>> indexV;
    for (int i = 0; i < distances.x; i++)
        indexV.push_back(vector<float>(1, i));

    distances = numpy(indexV) | distances;
    this->point = point.array[0];
}

numpy knn ::nearest(numpy point, int k = 3)
{
    numpy result;

    // if distances are not calculated then
    if (this->point != point.array[0])
        get_distances(point);

    if (k > distances.array.size())
        k = distances.array.size();

    // if this doesnt sort it right then do some other sort , with exception handleing
    distances.quicksort(0, distances.array.size() - 1, 1);
    result = numpy(vector<vector<float>>(distances.array.begin() + (distances.x - k), distances.array.end()));

    // now return the nearest
    return result;
}

int main()
{
    vector<vector<float>> df = {
        {1.8, 3},
        {4, 5},
        {6, 3},
        {2, 1},
        {6, 3},
        {7, 5},
        {9, 3},
        {-5, 1},
        {-5, -8},
    };
    knn clf(df);

    vector<float> vp = {1, 1};
    numpy point(vp);

    numpy result = clf.nearest(point, 3);
    result.display();
    return 0;
}