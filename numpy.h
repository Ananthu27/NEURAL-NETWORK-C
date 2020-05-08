#include <iostream>
#include <vector>

using namespace std;

class numpy
{
public:
    // vector<float> array1d;
    vector<vector<float>> array;
    int x, y;

    numpy() {}
    numpy(vector<float> a);
    numpy(vector<vector<float>> a);
    ~numpy() {}

    numpy operator+(numpy const &);
    numpy operator-(numpy const &);
    numpy operator*(numpy const &);

    void transpose();
    void display();
};

numpy::numpy(vector<float> a)
{
    array.push_back(a);
    x = 1;
    y = a.size();
}

numpy::numpy(vector<vector<float>> a)
{
    array = a;
    x = a.size();
    y = a[0].size();
}

void numpy ::display()
{
    if (x > 0 && y > 0)
    {
        cout << "[" << endl;
        for (auto v : array)
        {
            cout << "\t[";
            for (auto value : v)
                cout << "\t" << (fixed) << (showpos) << value;
            cout << "\t]" << endl;
        }
        cout << "]" << endl;
    }
}

void numpy::transpose()
{
    if (x > 0 && y > 0)
    {
        vector<vector<float>> transpose = vector<vector<float>>(y, vector<float>(x, 0));
        for (int i = 0; i < y; i++)
            for (int j = 0; j < x; j++)
                transpose[i][j] = array[j][i];
        array.clear();
        array = transpose;
    }
}

numpy numpy ::operator+(numpy const &a)
{
    numpy result;
    if (x > 0 && y > 0 && a.x > 0 && a.y > 0)
    {
        if (y == a.y)
        {
            if (x == a.x)
            {
                result = numpy(vector<vector<float>>(x, vector<float>(y, 0)));
                for (int i = 0; i < x; i++)
                    for (int j = 0; j < y; j++)
                        result.array[i][j] = array[i][j] + a.array[i][j];
            }
            else if (a.x == 1)
            {
                result = numpy(vector<vector<float>>(x, vector<float>(y, 0)));
                for (int i = 0; i < x; i++)
                    for (int j = 0; j < y; j++)
                        result.array[i][j] = array[i][j] + a.array[0][j];
            }
        }
    }
    return result;
}

numpy numpy ::operator-(numpy const &a)
{
    numpy result;
    if (x > 0 && y > 0 && a.x > 0 && a.y > 0)
    {
        if (y == a.y)
        {
            if (x == a.x)
            {
                result = numpy(vector<vector<float>>(x, vector<float>(y, 0)));
                for (int i = 0; i < x; i++)
                    for (int j = 0; j < y; j++)
                        result.array[i][j] = array[i][j] - a.array[i][j];
            }
            else if (a.x == 1)
            {
                result = numpy(vector<vector<float>>(x, vector<float>(y, 0)));
                for (int i = 0; i < x; i++)
                    for (int j = 0; j < y; j++)
                        result.array[i][j] = array[i][j] - a.array[0][j];
            }
        }
    }
    return result;
}

numpy numpy::operator*(numpy const &a)
{
    numpy result;
    // check for valid addition
    if (x > 0 && y > 0 && a.x > 0 && a.y > 0)
    {
        // check for valid input dimetions
        if (y == a.x)
        {
            result = numpy(vector<vector<float>>(x, vector<float>(a.y, 0)));

            for (int i = 0; i < x; i++)
                for (int j = 0; j < a.y; j++)
                    for (int k = 0; k < y; k++)
                        result.array[i][j] += array[i][k] * a.array[k][j];
        }
    }
    return result;
}