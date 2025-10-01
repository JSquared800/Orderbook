#pragma once
#include <ctime>

struct Order {
    int userId;
    int orderId;
    int amount;
    time_t timestamp;
};