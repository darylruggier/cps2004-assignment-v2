package user;

import platform.Platform;

import java.util.concurrent.atomic.AtomicInteger;

public class Admin extends User {
    Platform platform = Platform.getInstance();
    private static final AtomicInteger count = new AtomicInteger(0); //Used to set IDs (index 1)
    public final int admin_id;

    public Admin(String name, int age) {
        super(name, age);
        super.isAdmin = true;
        this.admin_id = count.incrementAndGet(); // Incrementing the ID and assigning it to the Admin
    }

    public void processRegistrations() { // Function used to approve the user, given they are age 18+
        for (User registration : platform.registrations) {
            registration.approved = registration.age >= 18;
        }
        platform.registrations.clear();
    }
}
