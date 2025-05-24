// Copyright 2025 Cameron Gagne and Ryan Greaney

#pragma once

#include <string>
#include <vector>

class EDistance {
 public:
    EDistance(const std::string& s1, const std::string& s2);

    static int penalty(char a, char b);
    static int min3(int a, int b, int c);

    int optDistance();
    std::string alignment();
 private:
    std::string string1;
    std::string string2;
    int matrixHeight;
    int matrixWidth;
    std::vector<std::vector<int>> matrix;
};
