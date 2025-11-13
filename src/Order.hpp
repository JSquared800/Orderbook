#pragma once
#include <ctime>
#include <iostream>

class Order {
    private:
        int userId;
        int orderId;
        int amount;
        double price;
        bool side; // True: Bid, False: Ask
        time_t timestamp;
    public:
        Order(int userId_, int orderId_, int amount_, double price_, bool side_, time_t timestamp_): userId(userId_), orderId(orderId_), amount(amount_), price(price_), side(side_), timestamp(timestamp_) {};
        int getUserId();
        int getOrderId();
        int getAmount();
        double getPrice();
        bool getSide();
        void removeAmount(int amt);
        void setAmount(int amt);
        time_t getTimestamp();
        
        inline friend std::ostream& operator<<(std::ostream& os, const Order& order) {
            os << "Order #" << order.orderId << ", User: " << order.userId << ", Amount: " << order.amount << ", Timestamp: " << order.timestamp;
    return os;
        }
};