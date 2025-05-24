// Copyright 2025 Cameron Gagne and Ryan Greaney

#include <climits>
#include "EDistance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

/*
    Checking to see if the min function works properly
*/
BOOST_AUTO_TEST_CASE(check_min_works) {
    BOOST_REQUIRE_EQUAL(EDistance::min3(1, 1, 1), 1);
    BOOST_REQUIRE_EQUAL(EDistance::min3(1, 2, 3), 1);
    BOOST_REQUIRE_EQUAL(EDistance::min3(3, 1, 2), 1);
    BOOST_REQUIRE_EQUAL(EDistance::min3(3, 2, 1), 1);

    BOOST_REQUIRE_EQUAL(EDistance::min3(-1, 2, 3), -1);
    BOOST_REQUIRE_EQUAL(EDistance::min3(3, -1, 2), -1);
    BOOST_REQUIRE_EQUAL(EDistance::min3(3, 2, -1), -1);

    BOOST_REQUIRE_EQUAL(EDistance::min3(INT_MAX, INT_MIN, 0), INT_MIN);
}

/*
    Checking to see if the min function works correctly
*/
BOOST_AUTO_TEST_CASE(check_penalty_works) {
    BOOST_REQUIRE_EQUAL(EDistance::penalty('A', 'A'), 0);
    BOOST_REQUIRE_EQUAL(EDistance::penalty('A', 'T'), 1);
    BOOST_REQUIRE_EQUAL(EDistance::penalty('A', '-'), 1);
}

/*
    checking to see how the program works given two strings from example10.txt
*/
BOOST_AUTO_TEST_CASE(Example10Test) {
    std::string str1 = "AACAGTTACC";
    std::string str2 = "TAAGGTCA";

    EDistance eDis(str1, str2);
    BOOST_REQUIRE_EQUAL(eDis.optDistance(), 7);
}

/*
    Test the alignment function with examples10.txt
*/
BOOST_AUTO_TEST_CASE(test_alignment_w_ex10) {
    std::string str1 = "AACAGTTACC";
    std::string str2 = "TAAGGTCA";

    EDistance eDis(str1, str2);
    eDis.optDistance();
    std::string align = eDis.alignment();

    std::istringstream iss(align);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(iss, line)) {
        lines.push_back(line);
    }
    BOOST_REQUIRE_EQUAL(lines.size(), 10);
    BOOST_REQUIRE(lines[0].find("A T 1") != std::string::npos);
}

/*
    Testing valid DNA strings and it should not throw anything
    with a vaid constructor
*/
BOOST_AUTO_TEST_CASE(Valid_Characters_DNA) {
    std::string str1 = "TACAGTTACC";
    std::string str2 = "TAAGGTCA";

    BOOST_REQUIRE_NO_THROW(EDistance ed(str1, str2));
}

/*
    Test that the tail end of the alignment gets printed
*/
BOOST_AUTO_TEST_CASE(test_cut_ends_x) {
    std::string str1 = "atattat";
    std::string str2 = "atattatag";

    EDistance eDis(str1, str2);
    eDis.optDistance();
    std::string align = eDis.alignment();

    std::istringstream iss(align);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(iss, line)) {
        lines.push_back(line);
    }

    BOOST_REQUIRE_EQUAL(lines.size(), 9);
    BOOST_REQUIRE(lines[8].find("- g 2") != std::string::npos);
}

/*
    Test that the tail end of the alignment gets printed
*/
BOOST_AUTO_TEST_CASE(test_cut_ends_y) {
    std::string str1 = "atattataa";
    std::string str2 = "atattat";

    EDistance eDis(str1, str2);
    eDis.optDistance();
    std::string align = eDis.alignment();

    std::istringstream iss(align);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(iss, line)) {
        lines.push_back(line);
    }

    BOOST_REQUIRE_EQUAL(lines.size(), 9);
    BOOST_REQUIRE(lines[8].find("a - 2") != std::string::npos);
}
