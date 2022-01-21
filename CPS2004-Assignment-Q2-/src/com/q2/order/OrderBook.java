package com.q2.order;

import java.util.LinkedList;
import java.util.ArrayList;

public class OrderBook {
    public ArrayList<Order> orders; // Order History
    public LinkedList<Order> order_queue; // Order Queue (i.e. current orders yet to be settled)

    public OrderBook() {
        orders = new ArrayList<>();
        order_queue = new LinkedList<>();
    }
}
