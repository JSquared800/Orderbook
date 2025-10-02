#include "Orderbook.hpp"
#include <iostream>
#include <chrono>

void Orderbook::walkBidBook(double price, Order& order) {
    // Currently only support single asset positions
    int curAmt = order.getAmount();
    while(!bid_map.empty() && bid_map.begin()->first >= price && curAmt > 0) {
        auto top = bid_map.begin();
        if(top->second.size() >= curAmt) {
            top->second.erase(top->second.begin(),top->second.begin()+curAmt); // future optimization includes doubly linked list
            curAmt = 0;
        } else {
            curAmt-=top->second.size();
            bid_map.erase(top->first);
        }
    }
    if(curAmt > 0) {
        order.setAmount(curAmt);
    } else {
        ask_map[price].erase(ask_map[price].end());
    }
}


void Orderbook::walkAskBook(double price, Order& order) {
    int curAmt = order.getAmount();
    while(!ask_map.empty() && ask_map.begin()->first <= price && curAmt > 0) {
        auto top = ask_map.begin();
        if(top->second.size() >= curAmt) {
            top->second.erase(top->second.begin(),top->second.begin()+curAmt);
            curAmt = 0;
        } else {
            curAmt-=top->second.size();
            ask_map.erase(top->first);
        }
    }
    if(curAmt > 0) {
        order.setAmount(curAmt);
    } else {
        bid_map[price].pop_back();
    }
}



int Orderbook::getCurrentId() {
    return current_order_id;
}
void Orderbook::addBuyOrder(int user_id, double price, int amount){
    Order buyOrder = Order(user_id, current_order_id++, amount, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    bid_map[price].push_back(buyOrder);
    if(!ask_map.empty() && price <= ask_map.begin()->first){
        walkAskBook(price, buyOrder);
    }
    // std::cout << buyOrder << std::endl;
}
void Orderbook::addSellOrder(int user_id, double price, int amount){
    Order sellOrder = Order(user_id, current_order_id++, amount, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    ask_map[price].push_back(sellOrder);
    if(!bid_map.empty() && price <= bid_map.rbegin()->first){
        walkBidBook(price, sellOrder);
    }
    // std::cout << sellOrder << std::endl;
}

