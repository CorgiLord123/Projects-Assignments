import java.text.*;
import java.util.*;
/**
 * Write a description of class Build here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Build
{
    // instance variables - replace the example below with your own
    private List<Part> parts;
    /**
     * Constructor for objects of class Build
     */
    public Build()
    {
        // initialise instance variables
        parts = new ArrayList<Part>();
    }
    
    public void buildMenu() {
        char choice;
        System.out.println("Let's build a 1337 box!");
        while ((choice = readChoice()) != 'x') {
            switch (choice) {
            case 'n': newBuild(); break;
            case 'a': addBuild(); break;
            case 'r': removeBuild(); break;
            case 'v': showBuild(); break;
            case 'c': checkBuild(); break;
            default: help(); break;
            }
        }
    }
    
    public void newBuild() {
        parts.removeAll(parts);
    }
    
    public void addBuild() {
        Catalogue catalogue = new Catalogue();
        List<Part> catalogueParts = catalogue.getCatalogue();
        System.out.print("Enter catalogue number of the part: ");
        String choice = In.nextLine();
        String[] components = choice.split(",\\s*");
        int[] multiParts = new int[components.length];
        for (int i = 0; i < components.length; i++) {
            multiParts[i] = Integer.parseInt(components[i]);
        }
        for (int c : multiParts) {
            if ((c <= catalogueParts.size())) {
                parts.add(catalogueParts.get(c-1));
            }
            else {        
                System.out.println("There is no part by that number.");
            }
        }
    }
    
    public void removeBuild() {
        System.out.print("Enter number of part to remove: ");
        int choice = In.nextInt();
        if (choice > 0 && choice <= parts.size()) {
            parts.remove(choice - 1);
        }
        else {
            System.out.println("The build has no part with that number.");
        }
    }
    
    public void showBuild() {
        double totalCost = 0;
        int i = 1; 
        for (Part p : parts) {
            System.out.println(i + ". " + p);
            i++;
        }
        for (Part part : parts) {
            totalCost += part.getPrice();
        }
        System.out.println("Total price: $" + formatted(totalCost));
    }
    
    public void checkBuild() {
        int i = 0;
        int missingParts = 0;
        String[] checkList = {"motherboard", "memory", "storage", "cpu", "case"};
        String[] checkMsg = {"a motherboard",  "RAM", "storage", "a CPU", "a case"};
        for (String type : checkList) {
            int temp = 0;
            for (Part part : parts) {
                if (part.getType() == type) {
                    temp = 1;
                }
            }
            if (temp == 0) {
                System.out.println("the build is missing " + checkMsg[i] + ".");
                missingParts++;
            }
            i++;
        }
        if (missingParts == 0) System.out.println("The build is functional.");
    }
    
    
    private char readChoice() {   
        System.out.print("Enter choice (n/a/r/v/c/x): ");
        return In.nextChar();
    }
    
    private String formatted(double price) {
        return new DecimalFormat("#####0.00").format(price);
    }
    
    private void help() {
        System.out.println("n = start a new build (clears old build)");                                      
        System.out.println("a = add a part from the catalogue to the build");  
        System.out.println("r = remove a part from the build");  
        System.out.println("v = show the current state of the build"); 
        System.out.println("c = check if the build is a functional computer"); 
        System.out.println("? = this help message");  
    }
}
