package com.q2;

import com.q2.platform.Platform;
import com.q2.order.Crypto;
import com.q2.order.Order;
import com.q2.user.Admin;
import com.q2.user.User;

public class Main {
    public static void main(String[] args) {
        Platform platform = Platform.getInstance();

        Admin admin1 = new Admin("Admin", 20);
        User user1 = new User("Daryl", 18, 2000);
        platform.registerUser(user1);
        admin1.processRegistrations();

        Crypto btc = new Crypto("btc", 20, 200);

        Order order1 = new Order(user1, btc, 20, Order.OrderType.BUY, Order.OrderSubType.MARKET);
        platform.addOrder(order1);

        Order order2 = new Order(user1, btc, 20, Order.OrderType.BUY, Order.OrderSubType.MARKET);
        platform.addOrder(order2);

        Order order3 = new Order(user1, btc, 20, Order.OrderType.SELL, Order.OrderSubType.LIMIT, 1.2);
        platform.addOrder(order3);

        Order order4 = new Order(user1, btc, 10, Order.OrderType.SELL, Order.OrderSubType.MARKET);
        platform.addOrder(order4);

        //Future goals: Implement further Abstraction and Modularity.
        for (Order orders : platform.order_book.order_queue) {
            System.out.println("Order ID: " + orders.order_id + "\nMade by com.q2.user: " + orders.user + "\nOrder Type: " + orders.orderType + "\nOrder Sub-type: " + orders.orderSubType);
            platform.processOrder(orders);
        }
        //I believe that this function should be run as a background process (i.e. concurrency using threads & Runnable).
    }
}