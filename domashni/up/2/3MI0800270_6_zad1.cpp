#include <iostream>
#include <cstring>
#pragma warning(disable:4996)

using namespace std;

const int MAX_STR_LEN = 80;
const int LETTERS = 52;

bool isUpper(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}

bool isLower(char ch) {
    return (ch >= 'a' && ch <= 'z');
}

char checkBackpack(char* str) {
    int len = strlen(str);
    int firstLen = len / 2;
    char* firstComp = str;
    char* secondComp = str + firstLen;

    bool hist[LETTERS] = { 0 };

    for (int i = 0;i < firstLen;i++) {
        if (isLower(*firstComp)) {
            hist[*firstComp - 'a'] = 1;
        }
        else if (isUpper(*firstComp)) {
            hist[*firstComp - 'A' + 26] = 1;
        }
        firstComp++;
    }
    for (int i = 0;i < firstLen;i++) {
        if (isLower(*secondComp)) {
            if (hist[*secondComp - 'a']) {
                return *secondComp;
            }
        }
        else if (isUpper(*secondComp)) {
            if (hist[*secondComp - 'A' + 26]) {
                return *secondComp;
            }
        }
        secondComp++;
    }
    return '\0';
}

char* getRepeatingChars(char** backpacks, int n) {
    char* result = new char[n];
    for (int i = 0;i < n;i++) {
        result[i] = checkBackpack(backpacks[i]);
    }
    return result;
}
int* getRepeatingCharsPriority(char* repeatingCharacters, int n) {
    int* result = new int[n];
    for (int i = 0;i < n;i++) {
        if (isLower(repeatingCharacters[i])) {
            result[i] = repeatingCharacters[i] - 'a' + 1;
        }
        else if (isUpper(repeatingCharacters[i])) {
            result[i] = repeatingCharacters[i] - 'A' + 26 + 1;
        }
    }
    return result;
}
int getPrioritySum(char** backpacks, int n) {
    char* repeatingChars = getRepeatingChars(backpacks, n);
    int* problemsPriority = getRepeatingCharsPriority(repeatingChars, n);

    int prioritySum = 0;

    for (int i = 0;i < n;i++) {
        prioritySum += problemsPriority[i];
    }

    delete[] problemsPriority;
    delete[] repeatingChars;
    return prioritySum;
}

bool* createHistogram(char* backpack) {
    bool* hist = new bool[LETTERS];
    for (int i = 0;i < LETTERS;i++) {
        hist[i] = 0;
    }
    for (int i = 0;i < LETTERS;i++) {
        if (isLower(*backpack)) {
            hist[*backpack - 'a'] = 1;
        }
        else if (isUpper(*backpack)) {
            hist[*backpack - 'A' + 26] = 1;
        }
        backpack++;
    }
    return hist;
}

char getIdentificator(char**& backpacks) {
    bool* hist1 = createHistogram(*backpacks);
    backpacks++;
    bool* hist2 = createHistogram(*backpacks);
    backpacks++;
    bool* hist3 = createHistogram(*backpacks);
    backpacks++;

    for (int i = 0;i < LETTERS;i++) {
        if (hist1[i] && hist2[i] && hist3[i]) {
            if (i < 26) {
                return 'a' + i;
            }
            else {
                return i - 26 + 'A';
            }
        }
    }
    delete[] hist1;
    delete[] hist2;
    delete[] hist3;
    return '\0';

}

char* getIdentificators(char** backpacks, int n) {
    int numberOfTeams = n / 3;
    char* result = new char[numberOfTeams];

    for (int i = 0;i < numberOfTeams;i++) {
        result[i] = getIdentificator(backpacks);
    }
    return result;
}

int main() {
    int n;
    cin >> n;

    char** backpacks = new char* [n];

    for (int i = 0;i < n;i++) {
        backpacks[i] = new char[MAX_STR_LEN];
        cin >> backpacks[i];
        if (strlen(backpacks[i]) % 2) {
            cout << "Spisuka e greshen" << endl;
            return -1;
        }
    }

    char* repeatingChars = getRepeatingChars(backpacks, n);

    for (int i = 0;i < n;i++) {
        cout << repeatingChars[i] << endl;
    }

    delete[] repeatingChars;

    cout << getPrioritySum(backpacks, n) << endl;

    char* identificators = getIdentificators(backpacks, n);

    for (int i = 0;i < n / 3;i++) {
        cout << identificators[i] << endl;
    }

    delete[]identificators;

    for (int i = 0;i < n;i++) {
        delete[] backpacks[i];
    }
    delete[] backpacks;
}