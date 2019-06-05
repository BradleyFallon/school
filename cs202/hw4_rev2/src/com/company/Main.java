package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        BoothManager manager = new BoothManager();

        manager.addBooth(1, "First Booth");
        manager.addBooth(2, "Second Booth");
        manager.addBooth(3, "Third Booth");
        manager.addBooth(4, "Fourth Booth");

        manager.addBooth(1, "Yummy Junk");
        manager.addBooth(2, "Glam Grams");
        manager.addBooth(3, "Talent Nation");
        manager.addBooth(4, "Shoes R U");

        manager.addBooth(1, "Taco Boys");
        manager.addBooth(2, "Snappy");
        manager.addBooth(3, "Jacked Jugglers");
        manager.addBooth(4, "Garden Supply");

        manager.displayMap();




        Scanner scan = new Scanner(System.in);
        boolean running = true;
        int opt;
        String companyName;
        int typeCode;
        while (running) {
            System.out.println("Enter a number to run an option");
            System.out.println("1: add a new booth");
            System.out.println("2: display");
            System.out.println("3: quit");
            opt = scan.nextInt();
            switch (opt)
            {
                case 1:
                    manager.displayTypes();
                    System.out.println("What type of booth do you want to add?...");
                    typeCode = scan.nextInt(); scan.nextLine();
                    System.out.println("Enter a name for the booths company...");
                    companyName = scan.nextLine();
                    if (manager.addBooth(typeCode, companyName)) {
                        System.out.println("Booth added successfully!");
                    } else {
                        System.out.println("Booth rejected!");
                    }
                    break;
                case 2:
                    manager.displayMap();
                    break;
                case 3:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        System.out.println("Done with test main.");
    }
}
