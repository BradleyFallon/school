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

    public Aisle(int id) {
        this.array = new Booth[LEN_SHORT];
        this.length = LEN_SHORT;
        this.id = id;
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
            if (array[i] != null) {
                array[i].display();
            } else {
                System.out.println("--Vacant--");
            }
        }
        System.out.println();
    }



    public boolean isFull(){
        for (int i=0; i<this.length; ++i) {
            if (array[i] == null) {
                return false;
            }
        }
        return true;
    }

    /*
    If array is short length, copy to new array of longer length.
    If already long, return false.
     */
    public boolean extendAisle () {
        if (this.length == LEN_LONG) return false;

        Booth[] extended_array = new Booth[LEN_LONG];
        for (int i=0; i<this.length; ++i) {
            if (array[i] != null) {
                extended_array[i] = array[i];
            }
        }
        array = extended_array;
        return true;
    }

    /*
    Count the number of booths matching the input booth's type are in the array
     */
    public int countType(Booth other) {
        int count = 0;
        for (int i=0; i<this.length; ++i) {
            if ((array[i] != null) && (array[i].getClass() == other.getClass())) {
                ++count;
            }
        }
        return count;
    }

    /*
    Add the booth to the first free slot, and return the index used.
     */
    public int addBooth(Booth other) {
        for (int i=0; i<this.length; ++i) {
            if (array[i] == null) {
                array[i] = other;
                return i;
            }
        }
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
