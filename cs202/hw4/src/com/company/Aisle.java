package com.company;

public class Aisle extends AisleNode {
    protected int id;

    public Aisle() {
        super();
        id = 0;
    }

    public Aisle(int id) {
        this.id = 0;
    }

    public void display() {
        System.out.println("=========== Aisle #" + id + ": ");
        for (int i=0; i<this.length; ++i) {
            System.out.print("\tBooth #" + (i+1) + ": ");
            array[i].display();
        }
    }


    // stage booth
    // only one stage required per aisle. It should be at end only
    // Stages cannot be in adjacent aisles
    public boolean hasStage() {
        return true;
    }

    // Food Booth
    // Foodbooths should be clustered. We want a way to check how many fod vendors in an aisle.
    public int countFood() {
        return 1;
    }

    // Photobooth
    // These should be scattered as much as possible
    // Will be useful to have a check if aisle contains photobooth
    public boolean hasPhoto() {
        return true;
    }


}
