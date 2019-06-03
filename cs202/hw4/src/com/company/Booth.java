package com.company;

public class Booth {

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
        System.out.println("Booth for " + company);
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




/*
    BoothManager class

    addBooth( booth )
        // checks the type of booth
        // inserts into special location accordingly
        // If rule is broken, insert anyway at default spot (allow user to decide how to fix)

    check()
        // Checks if all rules for vendor locations are satisfied
        // generates a report of failed rules

    removeBooth( index)
        // remove a booth which is at the given index

    display()
        // Display info about all booths, their status, and their index

    display (index )
        // display info and status of a booth at the given index
 */




//
///* Class CircularSinglyLinkedList */
//public class CircularSinglyLinkedList
//{
//    public static void main(String[] args)
//    {
//        Scanner scan = new Scanner(System.in);
//        /* Creating object of linkedList */
//        linkedList list = new linkedList();
//        System.out.println("Circular Singly Linked List Test\n");
//        char ch;
//        /*  Perform list operations  */
//        do
//        {
//            System.out.println("\nCircular Singly Linked List Operations\n");
//            System.out.println("1. insert at begining");
//            System.out.println("2. insert at end");
//            System.out.println("3. insert at position");
//            System.out.println("4. delete at position");
//            System.out.println("5. check empty");
//            System.out.println("6. get size");
//            int choice = scan.nextInt();
//            switch (choice)
//            {
//                case 1 :
//                    System.out.println("Enter integer element to insert");
//                    list.insertAtStart( scan.nextInt() );
//                    break;
//                case 2 :
//                    System.out.println("Enter integer element to insert");
//                    list.insertAtEnd( scan.nextInt() );
//                    break;
//                case 3 :
//                    System.out.println("Enter integer element to insert");
//                    int num = scan.nextInt() ;
//                    System.out.println("Enter position");
//                    int pos = scan.nextInt() ;
//                    if (pos <= 1 || pos > list.getSize() )
//                        System.out.println("Invalid position\n");
//                    else
//                        list.insertAtPos(num, pos);
//                    break;
//                case 4 :
//                    System.out.println("Enter position");
//                    int p = scan.nextInt() ;
//                    if (p < 1 || p > list.getSize() )
//                        System.out.println("Invalid position\n");
//                    else
//                        list.deleteAtPos(p);
//                    break;
//                case 5 :
//                    System.out.println("Empty status = "+ list.isEmpty());
//                    break;
//                case 6 :
//                    System.out.println("Size = "+ list.getSize() +" \n");
//                    break;
//                default :
//                    System.out.println("Wrong Entry \n ");
//                    break;
//            }
//            /*  Display List  */
//            list.display();
//            System.out.println("\nDo you want to continue (Type y or n) \n");
//            ch = scan.next().charAt(0);
//        } while (ch == 'Y'|| ch == 'y');
//    }
//}
//*/