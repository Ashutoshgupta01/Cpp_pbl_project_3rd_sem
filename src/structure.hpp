#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <string>
using namespace std;

struct Movie {
    int id{};
    string name;
    string genre;
    string time;
};

struct FoodItem {
    int id{};
    string name;
    int price{};
};

struct Seat {
    int row;
    int col;
};

#endif