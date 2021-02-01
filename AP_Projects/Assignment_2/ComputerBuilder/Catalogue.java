import java.util.*;
/**
 * Write a description of class Catalogue here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Catalogue
{
    // instance variables - replace the example below with your own
    private List<Part> parts;

    /**
     * Constructor for objects of class Catalogue
     */
    public Catalogue()
    {
        // initialise instance variables
        parts = new ArrayList<Part>();
        parts.add(new Part("evo 860", "storage", 155.00));
        parts.add(new Part("daskeyboard", "keyboard", 239.00));
        parts.add(new Part("i5", "cpu", 365.00));
        parts.add(new Part("Corsair 16G", "memory", 299.00));
        parts.add(new Part("ASUS ROG", "motherboard", 159.00));
        parts.add(new Part("sheetmetal box", "case", 39.00));
        parts.add(new Part("Ryzen 7", "cpu", 299.00));
    }
    
    public List<Part> getCatalogue() {
        return parts;
    }
    
    public void catalogueMenu() {
        char choice;
        System.out.println("Welcome to the parts catalogue.");
        while ((choice = readChoice()) != 'x') {
            switch (choice) {
            case 'a': add(); break;
            case 'r': remove(); break;
            case 's': show(); break;
            case 'f': filter(); break;
            default: help(); break;
            }
        }
    }
    
    public void add() {
        parts.add(new Part(readName(), readType(), readPrice()));
    }
    
    public void remove() {
        System.out.print("Enter catalogue number of part to remove: ");
        int choice = In.nextInt();
        if (choice > 0 && choice <= parts.size()) {
            parts.remove(choice - 1);
        }
        else {
            System.out.println("The catalogue has no part with that number.");
        }
    }
    
    public void show() {
        int i = 1;
        for (Part p : parts) {
            System.out.println(i + ". " + p);
            i++;
        }
    }
    
    public void filter() {
        System.out.print("Enter type of part to view ('all' for no filtering): ");
        String ofType = In.nextLine();
        System.out.print("Enter minimum price ('-1' for no filtering): ");
        double minPrice = In.nextDouble();
        if (minPrice == -1) {
            ArrayList<Part> filteredList = filteredList(parts, ofType, minPrice);
            for (Part part : filteredList) {
                System.out.println(parts.indexOf(part)+1 +". " + part);
            }
        }
        else {
            System.out.print("Enter maximum price: ");
            double maxPrice = In.nextDouble();
            if (minPrice > maxPrice) System.out.println("Minimum price shouldn't be greater than maximum price.");
            ArrayList<Part> filteredListV2 = filteredListV2(parts, ofType, minPrice, maxPrice);
            for (Part part : filteredListV2) {
                System.out.println(parts.indexOf(part)+1 +". " + part);
            }            
        }
    }
    
    private boolean noFilter(String option) {
        return "all".contains(option);
    }
    
    private ArrayList<Part> filteredList(List<Part> parts, String type, double min) {
        ArrayList<Part> matches = new ArrayList<Part>();
        for (Part part : parts) {
            if (noFilter(type) && part.minPrice(min)) {
                matches.add(part);
            }
            else if (part.isType(type) && part.minPrice(min)){
                matches.add(part);
            }
        }
        return matches;
    }
    
    private ArrayList<Part> filteredListV2(List<Part> parts, String type, double min, double max) {
        ArrayList<Part> matches = new ArrayList<Part>();
        for (Part part : parts) {
            if (noFilter(type) && part.minPrice(min) && part.maxPrice(max)) {
                matches.add(part);
            }
            else if (part.isType(type) && part.minPrice(min) && part.maxPrice(max)){
                matches.add(part);
            }
        }
        return matches;
    }
    private char readChoice() {   
        System.out.print("Enter choice (a/r/s/f/x): ");
        return In.nextChar();
    }
    
    private String readName() {
        System.out.print("Enter part name: ");
        return In.nextLine();
    }

    private String readType() {
        System.out.print("Enter part type: ");
        return In.nextLine();
    }
    
    private double readPrice() {
        System.out.print("Enter part price: ");
        return In.nextDouble();
    }

    
    private void help() {
        System.out.println("a = add a new part to the catalogue");                                      
        System.out.println("r = remove a part from the catalogue");  
        System.out.println("s = show the catalogue");  
        System.out.println("f = show a filtered view of the catalogue");     
        System.out.println("? = this help message");  
    }
}
