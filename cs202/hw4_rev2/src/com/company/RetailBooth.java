package com.company;

public class RetailBooth extends Booth {
    public RetailBooth() { super(); }

    public RetailBooth(String company) {
        super(company);
    }

    public void display() {
        System.out.print("Products from ");
        super.display();
    }
}
