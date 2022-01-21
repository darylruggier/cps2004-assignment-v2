package com.q2.user;

import com.q2.order.Order;
import com.q2.platform.Platform;
import java.util.concurrent.atomic.AtomicInteger;

public class User {
    private static final AtomicInteger count = new AtomicInteger(0); // Used to set IDs (index 1)
    public final int user_id;
    public String name;
    public int age;
    public double fiat_balance;
    public double crypto_balance = 0;
    public boolean approved = false;
    public boolean isAdmin = false;

    public User(String name, int age, double balance) {
        this.name = name;
        this.age = age;
        this.fiat_balance = balance;
        this.user_id = count.incrementAndGet(); // Incrementing the ID and assigning it to the User
    }

    public User(String name, int age) {
        this.name = name;
        this.age = age;
        this.user_id = count.incrementAndGet(); // Incrementing the ID and assigning it to the User
    }

    Platform platform = Platform.getInstance();
    public void placeOrder(Order order) { // used mainly for testing.
        if (!approved) {
            System.out.println("User is not an approved trader.");
        }
        platform.processOrder(order);
    }
}