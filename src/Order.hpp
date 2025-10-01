#pragma once
#include <ctime>

struct Order {
    int id;
    int amount;
    time_t timestamp;
};