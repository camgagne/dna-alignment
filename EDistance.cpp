// Copyright 2025 Cameron Gagne and Ryan Greaney

#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "EDistance.hpp"

EDistance::EDistance(const std::string& s1, const std::string& s2)
    : string1(s1), string2(s2) {
    matrixHeight = string1.size() + 1;
    matrixWidth = string2.size() + 1;
    matrix.resize(matrixHeight, std::vector<int>(matrixWidth, 0));

    int M = matrixHeight - 1;
    int N = matrixWidth - 1;

    // Initialize bottom row
    for (int i = 0; i < M; ++i)
        matrix[i][N] = 2 * (M - i);

    // Initialize right column
    for (int j = 0; j < N; ++j)
        matrix[M][j] = 2 * (N - j);

    matrix[M][N] = 0;  // Corner cell
}

int EDistance::penalty(char a, char b) {
    return a == b ? 0 : 1;
}

int EDistance::min3(int a, int b, int c) {
    return (a < b) ? ((a < c) ? a : c)
                   : ((b < c) ? b : c);
}

int EDistance::optDistance() {
    for (int i = matrixHeight - 2; i >= 0; --i) {
        for (int j = matrixWidth - 2; j >= 0; --j) {
            int cost = penalty(string1[i], string2[j]);
            matrix[i][j] = min3(
                matrix[i + 1][j + 1] + cost,  // Diagonal
                matrix[i + 1][j] + 2,  // Up
                matrix[i][j + 1] + 2);  // Right
        }
    }

    return matrix[0][0];
}

std::string EDistance::alignment() {
    int i = 0, j = 0;
    std::ostringstream alignmentStr;

    while ((i != matrixHeight - 1) && (j != matrixWidth - 1)) {
        char cost = penalty(string1[i], string2[j]);
        if (matrix[i][j] == matrix[i + 1][j + 1] + cost) {  // Diagonal
            alignmentStr << string1[i] << ' ';
            alignmentStr << string2[j] << ' ';
            alignmentStr << (cost == 1 ? '1' : '0');
            i++;
            j++;
        } else if (matrix[i][j] == matrix[i + 1][j] + 2) {  // Down
            alignmentStr << string1[i] << ' ';
            alignmentStr << "- 2";
            i++;
        } else if (matrix[i][j] == matrix[i][j + 1] + 2) {  // Right
            alignmentStr << "- " << string2[j] << " 2";
            j++;
        }
        alignmentStr << '\n';
    }

    // Handle remaining chars if strings are unequal
    while (i < matrixHeight - 1) {
        alignmentStr << string1[i] << " - 2\n";
        i++;
    }
    while (j < matrixWidth - 1) {
        alignmentStr << "- " << string2[j] << " 2\n";
        j++;
    }

    return alignmentStr.str();
}

