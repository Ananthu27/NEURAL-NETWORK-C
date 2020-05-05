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
    ~numpy() {}
    numpy operator+(numpy const &);
    numpy operator-(numpy const &);
    numpy operator*(numpy const &);
    void transpose(vector<vector<float>>);
    void display();
};

numpy::numpy(vector<float> a)
{
    array1d = a;
}

numpy::numpy(vector<vector<float>> a)
{
    array2d = a;
}

void numpy ::display()
{
    if (array1d.size() != 0)
    {
        cout << "[";
        for (auto value : array1d)
            cout << "\t" << (fixed) << value;
        cout << "]" << endl;
    }
    else
    {
        cout << "[" << endl;
        for (auto v : array2d)
        {
            cout << "[";
            for (auto value : v)
                cout << "\t" << (fixed) << value;
            cout << "]" << endl;
        }
    }
}

void numpy::transpose(vector<vector<float>> a)
{
    if (array2d.size() != 0)
    {
        vector<vector<float>> transpose = vector<vector<float>>(array2d[0].size(), vector<float>(array2d.size(), 0));
        for (int i = 0; i < transpose[0].size(); i++)
            for (int j = 0; j < transpose.size(); j++)
                transpose[j][i] = array2d[i][j];
        array2d.clear();
        array2d = transpose;
    }
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

    // check for 2d array caes;
    else if (array2d.size() != 0 && a.array2d.size() != 0)
    {
        // chenk for valid inputs
        if (array2d.size() == a.array2d.size() && array2d[0].size() == a.array2d[0].size())
        {
            vector<vector<float>> result = vector<vector<float>>(array2d.size(), vector<float>(array2d[0].size(), 0));
            for (int i = 0; i < result.size(); i++)
                for (int j = 0; j < result[0].size(); j++)
                    result[i][j] = array2d[i][j] + a.array2d[i][j];
            return numpy(result);
        }
    }
}

numpy numpy ::operator-(numpy const &a)
{
    // check for both 1d array case
    if (array1d.size() != 0 && a.array1d.size() != 0)
    {
        // check for valid additon parameters
        if (array1d.size() == a.array1d.size())
        {
            vector<float> result = vector<float>(a.array1d.size(), 0);
            for (int i = 0; i < result.size(); i++)
                result[i] = array1d[i] - a.array1d[i];
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
                    result[i][j] = array2d[i][j] - a.array1d[j];
            return numpy(result);
        }
    }

    // check for 2d array caes;
    else if (array2d.size() != 0 && a.array2d.size() != 0)
    {
        // chenk for valid inputs
        if (array2d.size() == a.array2d.size() && array2d[0].size() == a.array2d[0].size())
        {
            vector<vector<float>> result = vector<vector<float>>(array2d.size(), vector<float>(array2d[0].size(), 0));
            for (int i = 0; i < result.size(); i++)
                for (int j = 0; j < result[0].size(); j++)
                    result[i][j] = array2d[i][j] - a.array2d[i][j];
            return numpy(result);
        }
    }
}

numpy numpy::operator*(numpy const &a)
{
    // check for valid addition
    if (array2d.size() != 0 && a.array2d.size() != 0)
    {
        // check for valid input dimetions
        if (array2d[0].size() == a.array2d.size())
        {
            vector<vector<float>> result = vector<vector<float>>(array2d.size(), vector<float>(a.array2d[0].size(), 0));

            for (int i = 0; i < result.size(); i++)
                for (int j = 0; j < result[0].size(); j++)
                    for (int k = 0; k < array2d[0].size(); k++)
                        result[i][j] += array2d[i][k] * a.array2d[k][j];
            return numpy(result);
        }
    }
}