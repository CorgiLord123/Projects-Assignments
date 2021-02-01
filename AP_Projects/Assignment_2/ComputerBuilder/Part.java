import java.text.*;
public class Part
{
    
    private String name;
    private String type;
    private double price;

    /**
     * Constructor for objects of class Part
     */
    public Part(String newName, String newType, double newPrice)
    {
        name = newName;
        type = newType;
        price = newPrice;
    }
    
    public boolean isType(String ftype) {
        return type.contains(ftype);
    }
    
    public boolean minPrice(double min) {
        return price >= min;
    }
    
    public boolean maxPrice(double max) {
        return price <= max;
    }
    
    public double getPrice() {
        return price;
    }
    
    public String getType() {
        return type;
    }
    
    @Override
    public String toString() {
        return type.toUpperCase() + ": " + name + " @ $" + formatted(price);
    }
    
    public int index() {
        return index();
    }
    
    private String formatted(double price) {
        return new DecimalFormat("#####0.00").format(price);
    }
}
