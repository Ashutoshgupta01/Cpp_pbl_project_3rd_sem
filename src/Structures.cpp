#ifndef STRUCTURES_CPP
#define STRUCTURES_CPP

#include <string>
using namespace std;

const int ROWS = 15;
const int COLS = 15;
const int TICKET_PRICE = 200;

struct Movie {
    int id;
    string name;
    string genre;
    string time;
};

struct FoodItem {
    int id;
    string name;
    int price;
};

#endif