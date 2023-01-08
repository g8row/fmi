#include <iostream>
using namespace std;

int getLitFloors(int* buildings, int n) {
    int litFloors = 0;
    int coveredFloors = buildings[0];

    for (int i = 1;i < n;i++) {
        if (coveredFloors <= buildings[i]) {
            litFloors += buildings[i] - coveredFloors;
            coveredFloors = buildings[i];
        }
        else {
            coveredFloors--;
        }
    }
    return litFloors;
}

int tallestBuilding(int* buildings, int n) {
    int result = 0;
    for (int i = 0;i < n;i++) {
        if (result < *buildings) {
            result = *buildings;
        }
        buildings++;
    }
    return result;
}

void printScheme(char** scheme, int n, int tallest) {
    for (int i = tallest - 1;i >= 0;i--) {
        for (int j = 0;j < n;j++) {
            cout << scheme[j][i];
        }
        cout << endl;
    }
}

char** createScheme(int* buildings, int n, int tallest) {
    int litFloors = 0;
    int coveredFloors = buildings[0];

    char** scheme = new char* [n];

    for (int i = 0; i < n; i++)
    {
        scheme[i] = new char[tallest];
    }


    for (int i = 0;i < n;i++) {
        int pos = 0;
        if (coveredFloors <= buildings[i]) {
            litFloors = buildings[i] - coveredFloors;
            coveredFloors = buildings[i];
        }
        else {
            litFloors = 0;
            coveredFloors--;
        }
        for (int j = 0;j < buildings[i] - litFloors;j++) {
            scheme[i][pos] = '#';
            pos++;
        }
        for (int j = 0;j < coveredFloors - buildings[i];j++) {
            scheme[i][pos] = '-';
            pos++;
        }
        for (int j = 0;j < litFloors;j++) {
            scheme[i][pos] = '*';
            pos++;
        }
        while (pos < tallest) {
            scheme[i][pos] = '\\';
            pos++;
        }
    }
    return scheme;
}

int main() {
    int n;
    cin >> n;
    int* buildings = new int[n];

    for (int i = 0;i < n;i++) {
        cin >> buildings[i];
    }

    int litFloors = getLitFloors(buildings, n);

    cout << litFloors << endl;

    int tallest = tallestBuilding(buildings, n) + 1;

    char** scheme = createScheme(buildings, n, tallest);

    printScheme(scheme, n, tallest);

    for (int i = 0; i < tallest; i++)
    {
        delete[] scheme[i];
    }

    delete[] scheme;

    delete[] buildings;
}