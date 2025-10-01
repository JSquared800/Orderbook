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
time_t Order::getTimestamp() {
    return timestamp;
}

