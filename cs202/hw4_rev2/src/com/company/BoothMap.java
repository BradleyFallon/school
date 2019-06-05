package com.company;

public class BoothMap extends AisleCLL {

    public BoothMap() {
        super();
    }

    public void display() {
        if (rear == null) return;
        display(rear.getNext());
        rear.getAisle().display();
    }

    public void display(AisleNodeCLL current) {
        if (current == rear) return;
        current.getAisle().display();
        display(current.getNext());
    }

    public boolean placeBooth(Booth booth) {
        if (booth instanceof FoodBooth) {
            // Clustered. Unless more than 5 in a cluster, than can go to next cluster or alone.
            return placeFoodBooth((FoodBooth) booth);
        } else if (booth instanceof PhotoBooth) {
            // Spaced as much as possible. No clusters if possible.
            return placePhotoBooth((PhotoBooth) booth);
        } else if (booth instanceof StageBooth) {
            // Spaced as much as possible. At least 5 other type booths in between.
            return placeStageBooth((StageBooth) booth);
        } else if (booth instanceof RetailBooth) {
            // No special rules, these can go anywhere.
            return placeRetailBooth((RetailBooth) booth);
        } else {
            // This is not a supported booth type
            return false;
        }
    }


    public boolean placeFoodBooth(FoodBooth booth) {
        // cluster
        // not at entrance

        // Recursively check each aisle and get the number of food booths
        // if food booth count is greater than max, and aisle is not full,
        //     then set this as max
        // On the way back up stack, add to best aisle
        System.out.println("in the food booth placer");
        int[] maxInt = new int[1];
        maxInt[0] = 0;
        return placeFoodBooth(booth, rear.getNext(), maxInt);
    }


    protected boolean placeFoodBooth(FoodBooth booth, AisleNodeCLL current, int[] maxInt) {
        int count;
        Aisle aisle;

        if (current == rear) return false;

        // Check how many food booths are in this aisle, and compare with up stack
        aisle = current.getAisle();
        if (aisle.isFull()) {
            count = 0;
        } else {
            count = aisle.countType(booth);
            if (count > maxInt[0]) {
                maxInt[0] = count;
            }
        }

        // Go down the stack to search for a better cluster
        if (placeFoodBooth(booth, current.getNext(), maxInt)) {
            // Already found a spot deeper in stack
            return true;
        }

        // If this is the non-full aisle with most food, place here to cluster food
        if (count == maxInt[0] && !aisle.isFull()) {
            aisle.addBooth(booth);
            return true;
        }

        return false;
    }


    public boolean placePhotoBooth(PhotoBooth booth) {
        // Place in first non-full aisle without a photo booth
        return placePhotoBooth(booth, rear.getNext());
    }


    protected boolean placePhotoBooth(PhotoBooth booth, AisleNodeCLL current) {
        Aisle aisle;

        if (current == rear) return false;

        // Check how many food booths are in this aisle, and compare with up stack
        aisle = current.getAisle();
        if (aisle.isFull() || (aisle.countType(booth) > 0)) {
            return placePhotoBooth(booth, current.getNext());
        } else {
            aisle.addBooth(booth);
            return true;
        }
    }


    public boolean placeStageBooth(StageBooth booth) {
        // Place in first non-full aisle without a photo booth
        return placeStageBooth(booth, rear.getNext());
    }


    protected boolean placeStageBooth(StageBooth booth, AisleNodeCLL current) {
        Aisle aisle;

        if (current == rear) return false;

        // Check how many food booths are in this aisle, and compare with up stack
        aisle = current.getAisle();
        if (aisle.isFull() || aisle.countType(booth) > 0) {
            return placeStageBooth(booth, current.getNext());
        } else {
            aisle.addBooth(booth);
            return true;
        }
    }

    public boolean placeRetailBooth(RetailBooth booth) {
        // filler
        // Place in first non-full aisle without a photo booth
        return placeRetailBooth(booth, rear.getNext());
    }


    protected boolean placeRetailBooth(RetailBooth booth, AisleNodeCLL current) {
        Aisle aisle;

        if (current == rear) return false;

        // Check how many food booths are in this aisle, and compare with up stack
        aisle = current.getAisle();
        if (aisle.isFull()) {
            return placeRetailBooth(booth, current.getNext());
        } else {
            aisle.addBooth(booth);
            return true;
        }
    }
}
