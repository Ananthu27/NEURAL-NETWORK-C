#include <iostream>
#include <vector>
#include <fstream>
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
    // veritcal join
    numpy operator|(numpy);
    // horizontal join
    numpy operator||(numpy);

    void transpose();
    void swap(int, int);

    // quicksort
    int partition(int, int, int);
    void quicksort(int, int, int);

    // numpy io
    void read_csv(char *);
    void head(int);
    void tail(int);
    void display(vector<vector<float>>);
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

void numpy ::head(int n = 5)
{
    display(vector<vector<float>>(array.begin(), array.begin() + n));
}

void numpy ::tail(int n = 5)
{
    display(vector<vector<float>>(array.begin() + (array.size() - n), array.end()));
}

void numpy ::display(vector<vector<float>> arr)
{
    cout << showpos << fixed;
    if (x > 0 && y > 0)
    {
        cout << "[" << endl;
        for (auto v : arr)
        {
            cout << "\t[";
            for (auto value : v)
                cout << "\t" << value;
            cout << "\t]" << endl;
        }
        cout << "]" << endl;
    }
    cout << noshowpos;
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
        x = array.size();
        y = array[0].size();
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

numpy numpy::operator|(numpy a)
{
    numpy result;
    if (x > 0 && y > 0 && a.x > 0 && a.y > 0)
    {
        result = numpy(vector<vector<float>>(max(x, a.x), vector<float>(y + a.y, 0)));
        // threadable
        for (int i = 0; i < x; i++)
            for (int j = 0; j < y; j++)
                result.array[i][j] = array[i][j];
        // threadable
        for (int i = 0; i < a.x; i++)
            for (int j = 0; j < a.y; j++)
                result.array[i][j + y] = a.array[i][j];
    }
    return result;
}

numpy numpy::operator||(numpy a)
{
    numpy result;
    if (x > 0 && y > 0 && a.x > 0 && a.y > 0)
    {
        result = numpy(vector<vector<float>>(x + a.x, vector<float>(max(y, a.y), 0)));
        // threadable
        for (int i = 0; i < x; i++)
            for (int j = 0; j < y; j++)
                result.array[i][j] = array[i][j];
        // threadable
        for (int i = 0; i < a.x; i++)
            for (int j = 0; j < a.y; j++)
                result.array[i + x][j] = a.array[i][j];
    }
    return result;
}

void numpy ::swap(int i, int j)
{
    if (i >= 0 && j >= 0 && i < x && j < x)
    {
        vector<float> temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int numpy ::partition(int low, int high, int c = 0)
{
    float pivot = array[low][c];
    int i = low;
    int j = high + 1;

    while (i < j)
    {
        do
        {
            i++;
        } while (pivot <= array[i][c]);
        do
        {
            j--;
        } while (pivot > array[j][c]);

        if (i < j)
            swap(i, j);
    }
    swap(low, j);
    return j;
}

void numpy ::quicksort(int low, int high, int c = 0)
{
    int p;
    if (low < high)
    {
        p = partition(low, high, c);
        quicksort(low, (p - 1), c);
        quicksort((p + 1), high, c);
    }
}

//io

void numpy ::read_csv(char *filename)
{
    fstream file(filename, ios::app);
    file << " ";
    file.close();
    file = fstream(filename, ios::in);

    if (file.is_open())
    {
        array.clear();
        string line;
        vector<float> lineV;
        int start = 0, end = 0;

        while (getline(file, line))
        {
            start = 0;
            end = start;
            lineV.clear();

            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] == ',' || i == line.size() - 1)
                {
                    end = i;
                    string temp(line.begin() + start, line.begin() + end);
                    start = end = i + 1;
                    try
                    {
                        lineV.push_back(stof(temp));
                    }
                    catch (exception e)
                    {
                        // cout << " error caught , couldnt convert and push :" << temp << endl;
                    }
                }
            }
            if (lineV.size() > 0)
            {
                array.push_back(lineV);
                lineV.clear();
            }
        }
    }
    else
    {
        cout << "error opening file check filename in numpy.read_csv() call" << endl;
    }
    file.close();
}
