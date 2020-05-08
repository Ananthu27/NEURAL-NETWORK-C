#include "numpy.h"

class knn : public numpy
{
public:
    numpy get_distances(numpy, numpy);
};

numpy knn ::get_distances(numpy df, numpy point)
{
    numpy distances;

    if (true)
        ;

    return distances;
}

int main()
{
    vector<float> test = {2, 4, 6, 7, 8};
    numpy t(test);
    cout << t.x << "," << t.y << endl;
    t.display();
    t.transpose();

    return 0;
}