package com.company;

public class BoothManager {
    protected BoothMap layout;
//    protected Tree23 lookup;

    public BoothManager() {
        Aisle aisle1 = new Aisle();
        Aisle aisle2 = new Aisle();
        Aisle aisle3 = new Aisle();

        layout = new BoothMap();
        layout.insert(aisle1);
        layout.insert(aisle2);
        layout.insert(aisle3);
    }


    public void display_map() {
        System.out.println("This is the map");
        layout.display();
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
        layout.placeBooth(newBooth);
        return;
    }



    /*
        starts initialized with three aisles.
        when an aisle is added, it is initialized with array of null booths
     */


    public void check() {}
    // Checks if all rules for vendor locations are satisfied
    // generates a report of failed rules

    public void removeBooth(int index) {}
    // remove a booth which is at the given index

    public void display() {}
    // Display info about all booths, their status, and their index

    public void display (int index) {}
    // display info and status of a booth at the given index

    /*
    public final Booth lookupBooth (String keyword) {
        return new Booth();
    }
    protected void addBoothLookup(Booth booth) {

    }
     */
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