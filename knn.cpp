#include "numpy.h"
#include <math.h>
#include <bits/stdc++.h>
#include <chrono>

using namespace std::chrono;

class knn : public numpy
{
public:
    numpy distances;
    vector<float> point;

    // modify ...
    knn(){};
    knn(vector<vector<float>> dataframe)
    {
        array = dataframe;
        x = dataframe.size();
        y = dataframe[0].size();
    };
    ~knn() {}

    void get_distances(numpy);
    numpy nearest(numpy, int);
    int predict(numpy, int, int);
    float score(int, int);
};

void knn ::get_distances(numpy point)
{
    // cout << "start:distance" << endl;
    // if the input dimentions are not none then
    distances.array.clear();
    this->point.clear();
    if (point.x > 0 && point.y > 0 && x > 0 && y)
    {
        if ((y - 1) == point.y)
        {
            point.transpose();
            distances = numpy(vector<vector<float>>(x, vector<float>(point.y, 0)));
            for (int i = 0; i < x; i++)
                for (int j = 0; j < point.y; j++)
                {
                    for (int k = 0; k < (y - 1); k++)
                        distances.array[i][j] += pow(array[i][k] - point.array[k][j], 2);
                    distances.array[i][j] = sqrt(distances.array[i][j]);
                }

            vector<vector<float>> indexV;
            for (int i = 0; i < distances.x; i++)
                indexV.push_back(vector<float>(1, i));

            vector<vector<float>> classV;
            for (int i = 0; i < distances.x; i++)
                classV.push_back(vector<float>(1, array[i][y - 1]));

            distances = numpy(indexV) | distances | numpy(classV);

            // cout << "end:distance" << endl;
            // if this doesnt sort it right then do some other sort , with exception handleing

            // cout << "start:sort" << endl;
            distances.quicksort(0, distances.array.size() - 1, 1);
            distances.bubblesort(1);
            // cout << "end:sort" << endl;

            this->point = point.array[0];
        }
    }
}

numpy knn ::nearest(numpy point, int k = 3)
{
    // cout << "start:nearest" << endl;

    numpy result;

    // if distances are not calculated then
    if (this->point != point.array[0])
        get_distances(point);

    if (distances.x == x)
    {
        if (k > distances.array.size())
            k = distances.array.size();

        result = numpy(vector<vector<float>>(distances.array.begin() + (distances.x - k), distances.array.end()));

        // now return the nearest
    }

    // cout << "end:nearest" << endl;
    return result;
}

int knn ::predict(numpy point, int k, int no_of_classes)
{
    // cout << "start:predict" << endl;
    int index = -1;

    vector<int> count = vector<int>(no_of_classes + 1, 0);

    numpy result;

    result = nearest(point, k);

    if (result.x == k || result.x == x)
    {
        for (int i = 0; i < result.x; i++)
            count[result.array[i][result.y - 1]]++;

        int max = -1;
        for (int i = 0; i < count.size(); i++)
        {
            if (count[i] > max)
            {
                max = count[i];
                index = i;
            }
        }
    }

    // cout << "end:predict" << endl;

    return index;
}

float knn::score(int k, int no_of_classes)
{
    float score_percentage = -1;
    if (x > 0 && y > 0)
    {
        vector<float> pointV;
        vector<int> result;
        numpy point;
        int c = no_of_classes;
        int cls = 0;
        for (int i = 0; i < x; i++)
        {
            pointV.clear();
            pointV = array[i];
            point = numpy(vector<float>(pointV.begin(), pointV.end() - 1));

            cls = predict(point, k, c);

            if (cls == pointV[pointV.size() - 1])
                result.push_back(1);
            else
                result.push_back(0);
        }

        int sum = 0;
        for (auto value : result)
            sum += value;

        score_percentage = (float)((float)sum / (float)result.size()) * 100;
    }
    return score_percentage;
}

int main()
{
    // knn implementation

    knn clf;
    char filename[] = "/ANNA/PROGRAMS/DATASETS/bcc.csv";
    clf.read_csv(filename);

    if (clf.array.size() > 0)
    {
        // next task : calculate time for different sorting algorithm
        // next task : fix quick sort in numpy
        auto start = high_resolution_clock::now();
        cout << clf.score(3, 2) << endl;
        auto stop = high_resolution_clock::now();
        auto duration = (stop - start);
        cout << "Time taken by function: " << duration.count() << endl;
    }

    return 0;
}
