package com.company;

public class StageBooth extends Booth {
    public StageBooth() { super(); }

    public StageBooth(String company) {
        super(company);
    }

    public void display() {
        System.out.print("Live Performances by ");
        super.display();
    }
}
