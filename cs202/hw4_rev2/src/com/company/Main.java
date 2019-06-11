package com.company;

/*
================================================================================
Homework 5 for CS202
Bradley Fallon
bfallon@pdx.edu
6/10/2019

This is the test client.
================================================================================
*/

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        boolean running = true;
        int opt;

        System.out.println(
                "Welcome to my test client." + "\n"
                + "In the HW5 edition of this app, we get to test a 23 tree." + "\n"
                + "The booth manager will be loaded with some booths." + "\n"
                + "When a booth is added, it is added to the CLL as a marker of location." + "\n"
                + "The booth is also added to a 23tree, used to check for duplicates." + "\n"
                + "If a booth to be added has one of the same company name in the 23tree," + "\n"
                + "it will be rejected. This utilizes adding and retrieving from a 23tree." + "\n\n"
                + "Press enter to continue."
        );
        scan.nextLine();

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


        Booth fetched;



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
