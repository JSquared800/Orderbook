#include "Orderbook.hpp"
#include <iostream>
#include <chrono>
#include <iterator>
#include <stdexcept>

void Orderbook::walkBidBook(double price, Order& order) {
    int curAmt = order.getAmount();
    std::cout << curAmt << std::endl;
    while(!bid_map.empty() && (--bid_map.end())->first >= price && curAmt > 0) {
        auto top_it = --bid_map.end();
        auto& order_list = top_it->second;
        while (!order_list.empty() && curAmt > 0) {
            auto list_it = order_list.front();
            int clearAmt = std::min(list_it->getAmount(), curAmt);
            list_it->removeAmount(clearAmt);
            curAmt -= clearAmt;
            if(list_it->getAmount() == 0) {
                order_list.pop_front();
            }
        }
        if (order_list.empty()) {
            bid_map.erase(top_it);
        }
    }
    std::cout << curAmt << std::endl;
    if (curAmt > 0) {
        order.setAmount(curAmt);
    } else {
        ask_map[price].pop_back();
    }
}


void Orderbook::walkAskBook(double price, Order& order) {
    int curAmt = order.getAmount();
    while(!ask_map.empty() && ask_map.begin()->first <= price && curAmt > 0) {
        auto top_it = ask_map.begin();
        auto& order_list = top_it->second;
        while (!order_list.empty() && curAmt > 0) {
            auto list_it = order_list.front();
            int clearAmt = std::min(list_it->getAmount(), curAmt);
            list_it->removeAmount(clearAmt);
            curAmt -= clearAmt;
            if(list_it->getAmount() == 0) {
                order_list.pop_front();
            }
        }
        if (order_list.empty()) {
            ask_map.erase(top_it);
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
    auto buyOrderPtr = std::make_shared<Order>(user_id,
        current_order_id++,
        amount,
        price,
        true,
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())
    );
    
    Order* buyOrder = buyOrderPtr.get();
    bid_map[price].push_back(buyOrderPtr);
    order_history[user_id][current_order_id - 1] = --bid_map[price].end();
    if(!ask_map.empty() && price >= ask_map.begin()->first){
        walkAskBook(price, *buyOrder);
    }
}

void Orderbook::addSellOrder(int user_id, double price, int amount){
    auto sellOrderPtr = std::make_shared<Order>(user_id,
        current_order_id++,
        amount,
        price,
        false,
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())
    );
    Order* sellOrder = sellOrderPtr.get();
    ask_map[price].push_back(sellOrderPtr);
    order_history[user_id][current_order_id - 1] = --ask_map[price].end();
    if(!bid_map.empty() && price <= bid_map.rbegin()->first){
        std::cout << "walking bid book" << std::endl;
        walkBidBook(price, *sellOrder);
    }
}

void Orderbook::cancelOrder(int user_id, int order_id) {
    if(order_history.find(user_id) == order_history.end()){
        throw std::runtime_error("Invalid user_id to cancel buy order");
    }
    if(order_history[user_id].find(order_id) == order_history[user_id].end()){
        throw std::runtime_error(std::format("User {} doesn't contain the order with orderId {}", user_id, order_id));
    }
    auto order_it = order_history[user_id][order_id];
    double price = (**order_it).getPrice();
    std::map<double, std::list<std::shared_ptr<Order>>>& side = (**order_it).getSide() ? bid_map : ask_map;
    side[price].erase(order_it);
    order_history[user_id].erase(order_id);
}
