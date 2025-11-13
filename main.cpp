#include "src/Orderbook.hpp"
#include <iostream>

// class Foo {
//     private:
//         int priv_num;
//     public:
//         Foo(int num) {
//             priv_num = num;
//         };
//         int getNum(){
//             return priv_num;
//         }
// };


int main() {
    Orderbook orderbook = Orderbook();
    orderbook.addBuyOrder(1,7.0,1);
    orderbook.addBuyOrder(1,7.1,1);
    orderbook.addBuyOrder(1,7.2,1);
    orderbook.addBuyOrder(1,7.3,1);
    orderbook.addSellOrder(2,7.6,1);
    orderbook.addSellOrder(2,7.3,1);
    std::cout << orderbook << std::endl;
}