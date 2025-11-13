#include "Order.hpp"

int Order::getUserId() {
    return userId;
}
int Order::getOrderId() {
    return orderId;
}
int Order::getAmount() {
    return amount;
}
void Order::setAmount(int amt) {
    amount = amt;
}
double Order::getPrice() {
    return price;
}
bool Order::getSide() {
    return side;
}
time_t Order::getTimestamp() {
    return timestamp;
}



