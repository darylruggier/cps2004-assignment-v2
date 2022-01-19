package order;

public class Crypto {
    public int supply;
    public double price;
    public String symbol;

    public Crypto(String symbol, double price, int supply) { // Constructor. Will be used to create various coins if needed.
        this.symbol = symbol;
        this.price = price;
        this.supply = supply;
    }
}
