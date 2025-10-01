#include "Order.hpp"

class Order {
  int getUserId() {
    return userId;
  }
  int getOrderId() {
    return orderId;
  }
  int getAmount() {
    return amount;
  }
  void setAmount(int amt) {
    amount = amt;
  }
  time_t getTimestamp() {
    return timestamp;
  }
};

