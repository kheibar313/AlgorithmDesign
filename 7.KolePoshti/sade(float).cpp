#include <iostream>
#include <vector>
#include <algorithm>

bool func(std::vector<double> a, std::vector<double> b) { return a[3] > b[3]; }

int main()
{
    using namespace std;
    double vKole;
    int nAshia;
    vector<vector<double>> out;
    vector<vector<double>> ashia;

    cout << "Enter KOLE Volume: ";
    cin >> vKole;

    cout << "Enter size of array ashia: ";
    cin >> nAshia;
    for (int i = 0; i < nAshia; i++)
    {
        int m = 0, v = 1;
        cout << "Enter Mass, Volume: ";
        cin >> m >> v;
        ashia.push_back({i+1, m, v, static_cast<double>((m * 1.0) / (v * 1.0))});
    }

    sort(ashia.begin(), ashia.end(), *func);
    // sort(ashia.begin(), ashia.end(), bool (*) (std::vector<double> a, std::vector<double> b) { return a[2] > b[2]; });

    for (int i=0; i<nAshia; i++)
    {
        if(ashia[i][2] < vKole)
        {
            vKole -= ashia[i][2];
            out.push_back(ashia[i]);
            continue;
        }
        out.push_back({ashia[i][0], static_cast<double>(ashia[i][1]*(vKole/ashia[i][2])), vKole, ashia[i][3]});
        break;
    }

    cout << "\n\nOUT: \n";
    for(int i=0; i<out.size(); i++)
    {
        cout << "Type: " << out[i][0] << ", Volume: " << out[i][2] << endl;
    }
}