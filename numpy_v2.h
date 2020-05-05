#include <iostream>
#include <vector>

using namespace std;

class numpy
{
public:
    vector<float> array1d;
    vector<vector<float>> array2d;

    numpy(vector<float> a);
    numpy(vector<vector<float>> a);
    numpy operator+(numpy const &);

    float dot(vector<float>, vector<float>);
    vector<float> dot(vector<vector<float>>, vector<float>);
    vector<vector<float>> dot(vector<vector<float>> a, vector<vector<float>> b);

    vector<vector<float>> transpose(vector<vector<float>>);

    void display(vector<float>);
    void display(vector<vector<float>>);
};

numpy::numpy(vector<float> a)
{
    array1d = a;
}

numpy::numpy(vector<vector<float>> a)
{
    array2d = a;
}

float numpy::dot(vector<float> a, vector<float> b)
{
    float result = 0;
    if (a.size() == b.size())
    {
        for (int i = 0; i < a.size(); i++)
            result += a[i] * b[i];
    }
    return result;
}

vector<float> numpy::dot(vector<vector<float>> a, vector<float> b)
{
    vector<float> result;
    if (a[0].size() == b.size())
    {
        for (auto v : a)
        {
            result.push_back(dot(v, b));
        }
    }
    return result;
}

vector<vector<float>> numpy::dot(vector<vector<float>> a, vector<vector<float>> b)
{
    vector<vector<float>> result;
    if (a[0].size() == b.size())
    {
        result = vector<vector<float>>(a.size(), vector<float>(b[0].size(), 0));
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < b[0].size(); j++)
                for (int k = 0; k < b.size(); k++)
                    result[i][j] += a[i][k] * b[k][j];
    }
    return result;
}

vector<vector<float>> numpy::transpose(vector<vector<float>> a)
{
    vector<vector<float>> new_a = vector<vector<float>>(a[0].size(), vector<float>(a.size(), 0));
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            new_a[j][i] = a[i][j];
        }
    }
    return new_a;
}

void numpy::display(vector<float> a)
{
    cout << "\t[";
    for (auto v : a)
        cout << fixed << v << "\t";
    cout << "]" << endl;
}

void numpy::display(vector<vector<float>> a)
{
    cout << "[" << endl;
    for (auto v : a)
    {
        display(v);
    }
    cout << "]" << endl;
}

numpy numpy ::operator+(numpy const &a)
{
    // check for both 1d array case
    if (array1d.size() != 0 && a.array1d.size() != 0)
    {
        // check for valid additon parameters
        if (array1d.size() == a.array1d.size())
        {
            vector<float> result = vector<float>(a.array1d.size(), 0);
            for (int i = 0; i < result.size(); i++)
                result[i] = array1d[i] + a.array1d[i];
            return numpy(result);
        }
    }

    // check for one 1d and one 2d case
    else if (array2d.size() != 0 && a.array1d.size() != 0)
    {
        // check for valid parameters
        if (array2d[0].size() == a.array1d.size())
        {
            vector<vector<float>> result = vector<vector<float>>(array2d.size(), vector<float>(array2d[0].size(), 0));
            for (int i = 0; i < result.size(); i++)
                for (int j = 0; j < result[0].size(); j++)
                    result[i][j] = array2d[i][j] + a.array1d[j];
            return numpy(result);
        }
    }
}
