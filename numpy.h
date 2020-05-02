#include <iostream>
#include <vector>

using namespace std;

class numpy
{
public:
    vector<float> add(vector<float>, vector<float>);
    float dot(vector<float>, vector<float>);
    vector<float> dot(vector<vector<float>>, vector<float>);
    void display(vector<float>);
    void display(vector<vector<float>>);
};

vector<float> numpy::add(vector<float> a, vector<float> b)
{
    vector<float> result;
    if (a.size() == b.size())
    {
        for (int i = 0; i < a.size(); i++)
            result.push_back(a[i] + b[i]);
    }
    return result;
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

void numpy::display(vector<float> a)
{
    cout << "\t[";
    for (auto v : a)
        cout << fixed << v << "\t";
    cout << "\b\b\b\b\b\b\b\b]" << endl;
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