#pragma once
#include <ctime>

class Order {
    private:
        int userId;
        int orderId;
        int amount;
        time_t timestamp;
    public:
        int getUserId();
        int getOrderId();
        int getAmount();
        void setAmount(int amt);
        time_t getTimestamp();
};