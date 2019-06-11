package com.company;

/*
================================================================================
Homework 5 for CS202
Bradley Fallon
bfallon@pdx.edu
6/10/2019

This is the node of a 23tree. Most of the behavior for the 23Tree is from here.
I built the recursive functions into the nodes, since in Java the nodes are a
class and not a struct.
================================================================================
*/

public class BoothNode23 {

    // These arrays can be temporarily overpopulated.
    // The tree class must do split when nodes are full
    protected Booth[] data;
    protected BoothNode23[] children;

    public BoothNode23() {
        data = new Booth[3];
        children = new BoothNode23[4];
    }

    public BoothNode23(Booth booth) {
        data = new Booth[3];
        data[0] = booth;
        children = new BoothNode23[4];
    }

    public BoothNode23(Booth booth, BoothNode23 left, BoothNode23 right) {
        data = new Booth[3];
        data[0] = booth;
        children = new BoothNode23[4];
        children[0] = left;
        children[1] = right;
    }


    public boolean isLeaf() {
        return children[0] == null;
    }
    public boolean isFull() {
        return data[2] != null;
    }

    public void display() {
        display(0);
    }

    protected void display(int level) {
        int i = 0;

        while (i < 2) {
            if (children[i] != null) {
                children[i].display(level + 1);
            }
            if (data[i] != null) {
                System.out.print("At level " + level + ": ");
                data[i].display();
            };
            ++i;
        }
        if (children[i] != null) {
            children[i].display(level + 1);
        }
    }

    public final Booth lookup(String keyword) {
        int i = 0;
        int comp;

        while (i < 2) {
            if (data[i] != null) {
                comp = keyword.compareTo(data[i].getCompany());
                if (comp == 0){
                    return data[i];
                }
                else if (comp < 0) {
                    if (children[i] != null) {
                        return children[i].lookup(keyword);
                    }
                }
            } else {
                if (children[i] != null) {
                    return children[i].lookup(keyword);
                }
            }
            ++i;
        }
        if (children[i] != null) {
            return children[i].lookup(keyword);
        }
        return null;
    }

    public boolean add(Booth booth) {
        if (isLeaf()){
            System.out.println("adding to leaf");
            return addHere(booth);
        } else {
            System.out.println("going deeper");
            return addBelow(booth);
        }
    }

    protected boolean addHere(Booth booth) {
        int i = 0;
        int comp;

        while (i < 3) {
            if (data[i] == null) {
                // If we have reached free index, place val here
                data[i] = booth;
                return true;
            }
            comp = booth.getCompany().compareTo(data[i].getCompany());
            if (comp == 0) return false;
            else if (comp < 0) {
                // If new val belongs here, place val here and shift all following down
                while (i < 3) {
                    Booth temp = data[i];
                    data[i] = booth;
                    booth = temp;
                    ++i;
                }
                return true;
            }
            ++i;
        }
        return false; // This should be unreachable
    }

    protected boolean addBelow(Booth booth) {
        int i = 0;
        int comp;
        boolean wasAdded;

        while (i < 3) {
            if (data[i] == null) {
                comp = -1;
            } else {
                comp = booth.getCompany().compareTo(data[i].getCompany());
            }
            if (comp == 0) return false;
            else if (comp < 0) {
                if (children[i] == null){
                    children[i] = new BoothNode23(booth);
                    wasAdded = true;
                }
                else {
                    wasAdded = children[i].add(booth);
                }
                // Check if the child is now too big, if so, split it
                if (children[i].isFull()) {
                    // do split of child
                    splitChild(i);
                }
                return wasAdded;
            }
            ++i;
        }
        return false;
    }

    protected void splitChild(int i) {
        BoothNode23 toSplit = children[i];
        BoothNode23 newLeft;
        BoothNode23 newRight;

        // Middle val comes up to parent
        System.out.println("Pushing up " + toSplit.data[1].getCompany());
        addHere(toSplit.data[1]);

        if (toSplit.isLeaf()) {
            System.out.println("newLeft " + toSplit.data[0].getCompany());
            newLeft = new BoothNode23(toSplit.data[0]);
            System.out.println("newRight " + toSplit.data[2].getCompany());
            newRight = new BoothNode23(toSplit.data[2]);
        } else {
            newLeft = new BoothNode23(
                    toSplit.data[0],
                    toSplit.children[0],
                    toSplit.children[1]);
            newRight = new BoothNode23(
                    toSplit.data[2],
                    toSplit.children[2],
                    toSplit.children[3]);
        }

        children[i] = newLeft;
        ++i;

        // If new val belongs here, place val here and shift all following down
        BoothNode23 temp;
        while (i < 4) {
            temp = children[i];
            children[i] = newRight;
            newRight = temp;
            ++i;
        }
    }

    public BoothNode23 split() {
        System.out.println("Splitting!");
        BoothNode23 newLeft;
        BoothNode23 newRight;

        // Middle val comes up to parent
        addHere(this.data[1]);

        if (this.isLeaf()) {
            newLeft = new BoothNode23(data[0]);
            newRight = new BoothNode23(data[2]);
        } else {
            newLeft = new BoothNode23(
                    data[0],
                    this.children[0],
                    this.children[1]);
            newRight = new BoothNode23(
                    data[2],
                    this.children[2],
                    this.children[3]);
        }
        return new BoothNode23(this.data[1], newLeft, newRight);
    }


}