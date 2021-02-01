import java.util.*;
public class ComputerBuilder
{
    public static void main(String[] args) {
        System.out.println("Welcome to Jaime's Computer Store");
        System.out.println("Quality Parts at the Best Prices");
        System.out.println("=================================");
        new ComputerBuilder().use();
    }
    private Catalogue catalogue;
    private Build currentBuild;
    
    /**
     * Constructor for objects of class ComputerBuilder
     */
    public ComputerBuilder()
    {
        // initialise instance variables
        catalogue = new Catalogue();
        currentBuild = new Build();
    }
    
    public void use() {
        int choice;
        while ((choice = readChoice()) != '3') {
            switch (choice) {
            case '1': openCatalogue(); break;
            case '2': openBuild(); break;
            default: help(); break;
            }
        }
    }
    
    public void openCatalogue() {
        catalogue.catalogueMenu();
    }
    
    public void openBuild() {
        currentBuild.buildMenu();
    }
    
    private char readChoice() {
        System.out.println("1. Catalogue Menu");
        System.out.println("2. Build Menu");
        System.out.println("3. Exit");        
        System.out.print("Select option: ");
        return In.nextChar();
    }
    
    private void help() {
        System.out.println("1 = interact with the catalogue");                                      
        System.out.println("2 = build your computer!");  
        System.out.println("? = this help message");  
    }
}
