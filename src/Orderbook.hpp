#pragma once
#include <Order.hpp>
#include <map>
#include <vector>

class Orderbook {
    private:
        int current_order_id = 0;
        std::map<double, std::vector<Order>> bid_map;
        std::map<double, std::vector<Order>> ask_map;
        std::vector<Order, Order> history;
        void walkBidBook(Order order);
        void walkAskBook(Order order);
    public:
        int getCurrentId();

        void addBuyOrder(double price, int amount);
        void cancelBuyOrder(double price, int amount);
        void addSellOrder(double price, int amount);
        void cancelSellOrder(double price, int amount);

        void marketBuyOrder(int amount);
        void marketSellOrder(int amount);

        void printOrderBook();
};