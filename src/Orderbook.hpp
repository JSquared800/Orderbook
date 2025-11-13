#pragma once
#include "Order.hpp"
#include <map>
#include <vector>
#include <limits>
#include <list>
#include <unordered_map>

class Orderbook {
    private:
        int current_order_id = 0;
        std::map<double, std::list<std::shared_ptr<Order>>> bid_map;
        std::map<double, std::list<std::shared_ptr<Order>>> ask_map;
        // user_id: {order_id: Order}
        std::unordered_map<int, std::unordered_map<int, std::list<std::shared_ptr<Order>>::iterator>> order_history;

        static constexpr double TICK = 0.1;
        double best_bid = std::numeric_limits<double>::max();
        double best_ask = 0;
        void walkBidBook(double price, Order& order);
        void walkAskBook(double price, Order& order);
        // getVolumeAtPrice
        // getPriceLevels
    public:
        int getCurrentId();

        void addBuyOrder(int user_id, double price, int amount);
        void addSellOrder(int user_id, double price, int amount);
        void cancelOrder(int user_id, int order_id);

        void marketBuyOrder(int user_id, int amount);
        void marketSellOrder(int user_id, int amount);

        void printOrderBook();

        inline friend std::ostream& operator<<(std::ostream& os, const Orderbook& orderbook) {
            os << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= BID MAP -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
            for(auto &vo : orderbook.bid_map) {
                if(vo.second.size() == 0){
                    continue;
                }
                os << "Price: " << vo.first << std::endl;
                for(auto &o : vo.second) {
                    os << *o << std::endl;
                }
            }
            os << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ASK MAP -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
            for(auto &vo : orderbook.ask_map) {
                if(vo.second.size() == 0){
                    continue;
                }
                os << "Price: " << vo.first << std::endl;
                for(auto &o : vo.second) {
                    os << *o << std::endl;
                }
            }
            os << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+";
            return os;
        }
};