package com.company;

/*
This class is an array of booths, which has added functionality for checking the array's content.
 */
public class Aisle {
    static int LEN_LONG = 8;
    static int LEN_SHORT = 4;

    protected Booth[] array;
    protected int id;
    protected int length;

    public Aisle() {
        this.array = new Booth[LEN_SHORT];
        this.length = LEN_SHORT;
        this.id = 0;
    }

    public Aisle(Booth[] array) {
        this.array = array;
        // ToDo this should be the size of the input
        this.length = LEN_SHORT;
        this.id = 0;
    }


    public void display() {
        System.out.println("=========== Aisle #" + id + ": ");
        for (int i=0; i<this.length; ++i) {
            System.out.print("\tBooth #" + (i+1) + ": ");
            array[i].display();
        }
    }



    public boolean isFull(){
        return false;
    }

    /*
    If array is short length, copy to new array of longer length.
    If already long, return false.
     */
    public boolean extendAisle () {
        return true;
    }

    /*
    Count the number of booths matching the input booth's type are in the array
     */
    public int countType(Booth other) {
        return 0;
    }

    /*
    Add the booth to the first free slot, and return the index used.
     */
    public int addBooth(Booth other) {
        return 0;
    }

    /*
    Given an index, remove the booth at that index from the array.
    Return reference to the booth that was removed.
     */
    public Booth popBooth(int index) {
        return array[0];
    }


}
