package com.company;

public class BoothManager {
    protected CLL aisles;
    protected Tree23 lookup;

    public BoothManager() {
        Booth[] aisle1;
        Booth[] aisle2;
        Booth[] aisle3;

        aisles = new CLL();
    }

    protected Booth[] extendAisle(Booth[] aisle) {
        return aisle;
    }

    public void display_map() {
        System.out.println("This is the map");
        aisles.display();
    }

    public void addBooth(int typeCode, String company){
        Booth newBooth;

        if (typeCode == 1) {
            // Clustered. Unless more than 5 in a cluster, than can go to next cluster or alone.
            newBooth = new FoodBooth();
        } else if (typeCode == 2) {
            // Spaced as much as possible. No clusters if possible.
            newBooth = new PhotoBooth();
        } else if (typeCode == 3) {
            // Spaced as much as possible. At least 5 other type booths in between.
            newBooth = new StageBooth();
        } else if (typeCode == 4) {
            // No special rules, these can go anywhere.
            newBooth = new RetailBooth();
        } else {
            // This is not a supported booth type
            return;
        }
        newBooth.setCompany(company);
        placeBooth(newBooth);
        return;
    }

    public void placeBooth(Booth booth) {
        if (booth instanceof FoodBooth) {
            // Clustered. Unless more than 5 in a cluster, than can go to next cluster or alone.
            placeFoodBooth((FoodBooth) booth);
        } else if (booth instanceof PhotoBooth) {
            // Spaced as much as possible. No clusters if possible.
            placePhotoBooth((PhotoBooth) booth);
        } else if (booth instanceof StageBooth) {
            // Spaced as much as possible. At least 5 other type booths in between.
            placeStageBooth((StageBooth) booth);
        } else if (booth instanceof RetailBooth) {
            // No special rules, these can go anywhere.
            placeRetailBooth((RetailBooth) booth);
        } else {
            // This is not a supported booth type
            return;
        }
        return;
    }

    /*
        starts initialized with three aisles.
        when an aisle is added, it is initialized with array of null booths
     */

    protected void placeFoodBooth(FoodBooth booth) {
        // cluster
        // not at entrance
        aisles.isEmpty();
    }

    protected void addBoothLookup(Booth booth) {

    }

    public final Booth lookupBooth (String keyword) {
        return new Booth();
    }

    protected void placePhotoBooth(PhotoBooth booth) {
        // no cluster
        aisles.isEmpty();
    }

    protected void placeStageBooth(StageBooth booth) {
        // not at entrance
        //
        aisles.isEmpty();
    }

    protected void placeRetailBooth(RetailBooth booth) {
        // filler
        aisles.isEmpty();
    }

    public void check() {}
    // Checks if all rules for vendor locations are satisfied
    // generates a report of failed rules

    public void removeBooth(int index) {}
    // remove a booth which is at the given index

    public void display() {}
    // Display info about all booths, their status, and their index

    public void display (int index) {}
    // display info and status of a booth at the given index
}


/*
addBooth(type, name)
    if a booth is added this way, it gets automatically assigned a location

addBooth(type, name, aisleNo, boothNo)
    adds a booth to a specific location, returns error string if rejected

when a booth is added without a specified location, put it in the first spot
(first free array index first available aisle) that is compliant with rules.

How should I report errors or success?
    String with message and empty string for no error?
    An error object?
    Boolean, and display error message

Automatically add booth to correct location, or just reject if location is bad?


 */





