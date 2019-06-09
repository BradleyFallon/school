package com.company;

abstract public class Booth {

    // This is the company name that is operating the booth
    protected String company;
    // If a booth is entered, it gets a registration id number
    protected int regId;

    public Booth() {
        this.company = null;
        this.regId = 0;
    }

    public Booth(String company) {
        this.regId = 0;
        this.company = company;
    }

    public void display() {
        System.out.println(company);
    }

    public String getCompany() {
        return company;
    }

    public void setCompany(String company) {
        this.company = company;
    }

    public int getRegId() {
        return regId;
    }

    public void setRegId(int regId) {
        this.regId = regId;
    }

}


