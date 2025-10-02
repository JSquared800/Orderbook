#pragma once
#include "Order.hpp"
#include <map>
#include <vector>

class Orderbook {
    private:
        int current_order_id = 0;
        std::map<double, std::vector<Order>> bid_map;
        std::map<double, std::vector<Order>> ask_map;
        std::vector<Order> history;
        void walkBidBook(double price, Order& order);
        void walkAskBook(double price, Order& order);
    public:
        int getCurrentId();

        void addBuyOrder(int user_id, double price, int amount);
        void cancelBuyOrder(int user_id, double price, int amount);
        void addSellOrder(int user_id, double price, int amount);
        void cancelSellOrder(int user_id, double price, int amount);

        void marketBuyOrder(int user_id, int amount);
        void marketSellOrder(int user_id, int amount);

        void printOrderBook();

        inline friend std::ostream& operator<<(std::ostream& os, const Orderbook& orderbook) {
            os << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= BID MAP -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
            for(auto vo : orderbook.bid_map) {
                if(vo.second.size() == 0){
                    continue;
                }
                os << "Price: " << vo.first << std::endl;
                for(auto o : vo.second) {
                    os << o << std::endl;
                }
            }
            os << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ASK MAP -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
            for(auto vo : orderbook.ask_map) {
                if(vo.second.size() == 0){
                    continue;
                }
                os << "Price: " << vo.first << std::endl;
                for(auto o : vo.second) {
                    os << o << std::endl;
                }
            }
            os << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+";
            return os;
        }
};