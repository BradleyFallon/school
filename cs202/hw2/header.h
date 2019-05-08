/*
================================================================================
Homework 2 for CS202
Bradley Fallon
bfallon@pdx.edu
5/8/2019

This is the one and only header that contains prototypes for all classes and
shared functions.
================================================================================
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Shipper;

Shipper * copy_shipper_rtti(Shipper * ref_shippy);
void display_shipper_rtti(Shipper * ref_shippy);

/*
The Shipper class is the root base class for all shipper classes. The shipper is not abstract,
so it is ok to create an instance of a shipper. A base shipper will just be 
a standard package that gets left at the door. There are two direcly derive classes,
they are the gift, which comes with return instructions, and the signed package,
which tracks wheteher the package has been signed for. Derived from signed shipper,
we have the installed shipper. This tracks if the delivery has been signed for
and also tracks if the product has been installed at the delivery location.
*/
class Shipper{
	public:
		Shipper();
		Shipper(const Shipper &);
		virtual ~Shipper();

		void clone(const Shipper &);
		int set_contact_to(const char text[]);
		int set_contact_from(const char text[]);
		int set_contents(const char text[]);

		virtual void display();

	private:
		char * contact_to;
		char * contact_from;
		char * contents;
};

struct ShipperNode{
	ShipperNode * next;
	Shipper * shippy;
};

class SignedShipper: public Shipper{
	public:
		SignedShipper();
		SignedShipper(const Shipper &);
		SignedShipper(const SignedShipper &);

		virtual void display();
		int sign();
	protected:
		bool is_signed;
};

class InstalledShipper: public SignedShipper{
	public:
		InstalledShipper();
		InstalledShipper(const Shipper &);
		InstalledShipper(const SignedShipper &);
		InstalledShipper(const InstalledShipper &);

		void display();
		int install();
	protected:
		bool is_installed;
};

class GiftShipper: public Shipper{
	public:
		GiftShipper();
		GiftShipper(const Shipper &);
		GiftShipper(const GiftShipper &);
		~GiftShipper();

		void display();
	protected:
		char * exchange_policy;
};

class Queue{
	public:
		Queue(void);
		~Queue(void);

		int enqueue(Shipper *); // Add new shippy to rear
		Shipper * peek(); // Copy the front item
		Shipper * dequeue(); // "Remove" the front item, and copy
		bool is_empty();
		void display_all();

	private:
		void display_all(ShipperNode *);
		void delete_all(ShipperNode *);
		ShipperNode * rear;                                                                                       
};
