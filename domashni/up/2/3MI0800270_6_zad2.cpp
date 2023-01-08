#include <iostream>
#include <cstring>
using namespace std;
#pragma warning(disable:4996)


const int rows = 5, columns = 8;

void findBeginning(char matrix[rows][columns], int& x, int& y) {
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < columns;j++) {
            if (matrix[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
    }
}

bool isLowest(char ch) {
    return ch == 'a' || ch == 'S';
}
bool isHighest(char ch) {
    return ch == 'z' || ch == 'E';
}
bool isValidMove(char ch1, char ch2) {
    return ch2 == (ch1 + 1) || ch2 == (ch1 - 1) || ch1 == ch2 || (isHighest(ch1) && isHighest(ch2)) || (isLowest(ch1) && isLowest(ch2));
}

void pathfinderB(int x, int y, int& shortestPathLen, int currPathLen,
    char matrix[rows][columns], bool walked[rows][columns], char* shortestPath, char* currPath) {

    currPathLen++;
    *currPath = matrix[x][y];
    currPath++;
    walked[x][y] = 1;
    if (matrix[x][y] == 'E') {
        if (currPathLen < shortestPathLen) {
            shortestPathLen = currPathLen;
            strcpy(shortestPath, currPath - currPathLen);
        }
        walked[x][y] = 0;
        return;
    }

    if (x - 1 > -1) {
        if (!walked[x - 1][y] && isValidMove(matrix[x][y], matrix[x - 1][y])) {
            pathfinderB(x - 1, y, shortestPathLen, currPathLen, matrix, walked, shortestPath, currPath);
        }
    }
    if (x + 1 < rows) {
        if (!walked[x + 1][y] && isValidMove(matrix[x][y], matrix[x + 1][y])) {
            pathfinderB(x + 1, y, shortestPathLen, currPathLen, matrix, walked, shortestPath, currPath);
        }
    }
    if (y - 1 > -1) {
        if (!walked[x][y - 1] && isValidMove(matrix[x][y], matrix[x][y - 1])) {
            pathfinderB(x, y - 1, shortestPathLen, currPathLen, matrix, walked, shortestPath, currPath);
        }
    }
    if (y + 1 < columns) {
        if (!walked[x][y + 1] && isValidMove(matrix[x][y], matrix[x][y + 1])) {
            pathfinderB(x, y + 1, shortestPathLen, currPathLen, matrix, walked, shortestPath, currPath);
        }
    }
    currPath--;
    walked[x][y] = 0;
}
void path(int x, int y, int& shortestPath, int currPath, char matrix[rows][columns], bool walked[rows][columns]) {
    currPath++;

    walked[x][y] = 1;
    if (matrix[x][y] == 'E') {
        if (currPath < shortestPath) {
            shortestPath = currPath;
        }
        walked[x][y] = 0;
        return;
    }
    if (x - 1 > -1) {
        if (!walked[x - 1][y] && isValidMove(matrix[x][y], matrix[x - 1][y])) {
            path(x - 1, y, shortestPath, currPath, matrix, walked);
        }
    }
    if (x + 1 < rows) {
        if (!walked[x + 1][y] && isValidMove(matrix[x][y], matrix[x + 1][y])) {
            path(x + 1, y, shortestPath, currPath, matrix, walked);
        }
    }
    if (y - 1 > -1) {
        if (!walked[x][y - 1] && isValidMove(matrix[x][y], matrix[x][y - 1])) {
            path(x, y - 1, shortestPath, currPath, matrix, walked);
        }
    }
    if (y + 1 < columns) {
        if (!walked[x][y + 1] && isValidMove(matrix[x][y], matrix[x][y + 1])) {
            path(x, y + 1, shortestPath, currPath, matrix, walked);
        }
    }


    walked[x][y] = 0;

}

void editPath(char* path) {
    int size = strlen(path);
    for (int i = 0;i < size;i++) {
        if (*path == 'E') {
            path++;
            *path = '\0';
        }
        path++;
    }
}

void shortestPathFromA(char* shortestPath, int& shortestPathLen, char matrixB[rows][columns]) {
    int tempShortestPathLen = rows * columns + 1;
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < columns;j++) {
            if (matrixB[i][j] == 'a') {
                bool walked[rows][columns] = { 0 };
                char tempShortestPath[rows * columns + 1] = { '\0' };
                char tempCurrentPath[rows * columns + 1] = { '\0' };
                int currPathLen = 0;
                pathfinderB(i, j, tempShortestPathLen, currPathLen, matrixB, walked, tempShortestPath, tempCurrentPath);
                if (shortestPathLen > tempShortestPathLen) {
                    shortestPathLen = tempShortestPathLen;
                    strcpy(shortestPath, tempShortestPath);
                    editPath(shortestPath);
                }
            }
        }
    }
}


int main() {
    char matrix[rows][columns] = {
        {'S', 'a', 'b', 'q', 'p', 'o', 'n', 'm'},
        {'a', 'b', 'c', 'r', 'y', 'x', 'x', 'l'},
        {'a', 'c', 'c', 's', 'z', 'E', 'x', 'k'},
        {'a', 'c', 'c', 't', 'u', 'v', 'w', 'j'},
        {'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i'}
    };
    int x = -1, y = -1;

    findBeginning(matrix, x, y);

    if (x == -1 && y == -1) {
        cout << "No beginning" << endl;
        return -1;
    }

    int shortestPath = rows * columns + 1;
    bool walked[rows][columns] = { 0 };
    int currPath = 0;
    path(x, y, shortestPath, currPath, matrix, walked);

    if (shortestPath == rows * columns + 1) {
        cout << "no path" << endl;
    }
    else {
        cout << shortestPath << endl;
    }

    char matrixB[rows][columns] = {
        {'a', 'a', 'b', 'q', 'p', 'o', 'n', 'm'},
        {'a', 'b', 'c', 'r', 'y', 'x', 'x', 'l'},
        {'a', 'c', 'c', 's', 'z', 'E', 'x', 'k'},
        {'a', 'c', 'c', 't', 'u', 'v', 'w', 'j'},
        {'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i'}
    };

    char shortestPathB[rows * columns + 1] = { '\0' };
    int shortestPathLenB = rows * columns + 1;

    shortestPathFromA(shortestPathB, shortestPathLenB, matrixB);

    if (shortestPathLenB == rows * columns + 1) {
        cout << "no path" << endl;
        return -1;
    }
    else {
        cout << shortestPathLenB << endl;
        cout << shortestPathB << endl;
    }
}