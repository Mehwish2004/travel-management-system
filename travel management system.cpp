#include<iostream>
#include<fstream>                //read or write in file
#include<string>
#include<windows.h>               //for sleep()
#include<sstream>           
#include <cstdlib>              //for exit function used in main()

using namespace std;

template <typename T> 
std::string to_string(T value) 
{
    std::ostringstream os;           //<sstream> headerfile is used for this
    os << value;
    return os.str();
}

class ManagerMenu
{
	protected:
    string userName; // Hide admin name
    
    public:
    	ManagerMenu()
    	{
    		system("color 0B"); 
        	cout << "\n\n\n\n\n\t  Enter Your Name to Continue as an Admin: ";
            getline(cin,userName);
            system("CLS");
		}
		~ManagerMenu()
		{
		}
};
class Customer
{
	private:
	   string name;
	   static int id;
	   string address, gender;
	   long long int cell_no;
	   int age;
	   char all[999];
	   
	public:
		Customer()
		{
		}
		void getdetails()
		{
			ofstream out("old-customers.txt", ios::app);
			cout << "\nEnter Customer's ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin,name);
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Mobile Number: ";
            cin >> cell_no;
            cin.ignore();
            cout << "Address: ";
            getline(cin,address);
            cout << "Gender: ";
            getline(cin,gender);
		
	        string record = "Customer ID: " + to_string(id) + ", Name: " + name + ", Age: " + to_string(age) + ", Mobile Number: " + to_string(cell_no) + ", Address: " + address + ", Gender: " + gender;

            out << record << endl;
            out.close();
            cout << "\nSaved \nNOTE: We save your details record for future purposes.\n" << endl;
	}
	void showDetails() // Function to show old customer records
    {
    ifstream in("old-customers.txt");
    if (!in)
    {
        cout << "File Error!" << endl;
        return ;
    }
    string line;
    while (getline(in, line))
    {
        size_t idPos = line.find("Customer ID: ");
        if (idPos != string::npos)
        {
            // Extract the customer ID from the file
            string idStr = line.substr(idPos + 13);           // Length of "Customer ID: " is 13
            this-> id = stoi(idStr);
            cout << "Customer ID: " << id << endl;
        }
        else
        {
            // Display the remaining fields
            cout << line << endl;
        }
    }
            in.close();
        }
	void removeRecord(int id)
          {
          	ifstream inFile("old-customers.txt");
            ofstream tempFile("temp.txt");
            bool recordFound = false;
    while (!inFile.eof())
    {
        string line;
        getline(inFile, line);
        if (line.find("Customer ID: " + to_string(id)) != string::npos)
        {
            recordFound = true;
            // Skip the customer record
            for (int i = 0; i < 6; i++)
            {
                getline(inFile, line);
            }
        }
        else
        {
            tempFile << line << endl;
        }
    }
            inFile.close();
            tempFile.close();
            // Remove the original file and rename the temporary file
           if (recordFound)
          {
             remove("old-customers.txt");
             rename("temp.txt", "old-customers.txt");
             cout << "Customer record removed successfully!" << endl;
          }
           else
          {

             cout << "Customer record not found!" << endl;
          }
      }
};

int Customer::id=0 ;

class Transport
{
	private:
		int id;
	public:
		string Jeep_id="LES 129",Bus_id="PSE 860",Hiace_id="KGS 395",Corrola_id="AKF 839",Suzuki_id="PYZ 432";
		string type;
		string JeepCapacity="4 people",BusCapacity="50 people",HiaceCapacity="14 people",CorrolaCapacity="5 people",SuzukiCapacity="10 people";
		double fare;
		int kilometers;
		int no_of_customers;		                    
		static float totalCost;
        friend class Billing;
		Transport()
		{
			totalCost = 0.0;
	    }
	    
	    void getdetails()
		{
			cout<<"Enter Customer id: ";
			cin>>id;
			cin.ignore();
			cout<<"Currently we have 5 Travelling Cars"<<endl;
			cout<<"1. Potohar Jeep(4000cc) "<<Jeep_id<<" capacity of people: "<<JeepCapacity<<endl;
			cout<<"2. Hino Kazay Bus "<<Bus_id<<" capacity of people: "<<BusCapacity<<endl;
			cout<<"3. Toyota Hiace"<<Hiace_id<<" capacity of people: "<<HiaceCapacity<<endl;
			cout<<"4. Corrola "<<Corrola_id<<" capacity of people: "<<CorrolaCapacity<<endl;
			cout<<"5. Suzuki "<<Suzuki_id<<" capacity of people: "<<SuzukiCapacity<<endl;
			cout<<"Enter the car type that you want: ";
			cin>>type;
			cout<<"Enter the total number of customers: ";
			cin>>no_of_customers;
			cout<<"Enter Kilometers you have to travel: ";
			cin>>kilometers;
			double fare = calculateFare(no_of_customers, kilometers);
            cout << "Fare for " << no_of_customers << " customers and " << kilometers << " kilometers: " << fare << endl;
            totalCost += fare;
        }
        double calculateFare(int numCustomers, double kilometers)
       {
       	  double fare = 0.0;
       	if (type == "jeep"|| type=="1")
        {
            fare = numCustomers * (kilometers * 26.277 );            // Current Petrol price/mileage of transport
        }
        if (type == "Bus"|| type=="2")
        {
            fare = numCustomers * (kilometers * 52.554);  
        }
        if (type == "Hiace"||type=="3")
        {
            fare = numCustomers * (kilometers * 26.277);  
        }
        if (type == "Corrola"||type=="4")
        {
            fare = numCustomers * (kilometers * 23.253);  
        }
        if (type == "Suzuki"||type=="5")
        {
            fare = numCustomers * (kilometers * 16.423);  
        }
        return fare;
    } 	  
};

float Transport::totalCost = 0.0;

class Booking:public Transport                    //using hotelcost from base class
{
	private:
		string Destination;   
		int id;                               //Aggregation
		
	public:
		int choice, days, packageChoice;
        float packageCost;
        float hotelCost; 
        friend class Billing;
        
	void bookHotel()
    {
		cout<<"Enter Customer id: ";
		cin>>id;
		cin.ignore();
        cout << "\nWhich hotel you would like to book?\n" << endl;
        cout << "1. Hotel Royal  - Rs.5000/day" << endl;
        cout << "2. Hotel Green Palace  - Rs.4000/day" << endl;
        cout << "3. Hotel Radisson  - Rs.3000/day" << endl;
        cout << "4. Lemon Tree  - Rs.2000/day" << endl;
        cout << "5. Hotel Fort Continental  - Rs.1700/day" << endl;
        cout << "\nEnter another key to go back or," << endl;
        cout << "\nTo book a hotel room.." << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
    switch (choice)
    {
        case 1:
            cout << "You have chosen Hotel Royal." << endl;
            cout << "Enter number of days to stay: ";
            cin >> days;
            packageCost = days * 5000;
            cout << "Your stay at Hotel Royal will cost " << packageCost << " rupees." << endl;
            hotelCost = packageCost;
            break;
            
        case 2:
            cout << "You have chosen Hotel Green Palace." << endl;
            cout << "Enter number of days to stay: ";
            cin >> days;
            packageCost = days * 4000;
            cout << "Your stay at Hotel Green Palace will cost " << packageCost << " rupees." << endl;
            hotelCost = packageCost;
            break;
            
        case 3:
            cout << "You have chosen Hotel Radisson." << endl;
            cout << "Enter number of days to stay: ";
            cin >> days;
            packageCost = days * 3000;
            cout << "Your stay at Hotel Radisson will cost " << packageCost << " rupees." << endl;
            hotelCost = packageCost;
            break;
            
        case 4:
            cout << "You have chosen Hotel Lemon Tree." << endl;
            cout << "Enter number of days to stay: ";
            cin >> days;
            packageCost = days * 2000;
            cout << "Your stay at Hotel Lemon Tree will cost " << packageCost << " rupees." << endl;
            hotelCost = packageCost;
            break;
            
        case 5:
            cout << "You have chosen Hotel Fort Continental." << endl;
            cout << "Enter number of days to stay: ";
            cin >> days;
            packageCost = days * 1700;
            cout << "Your stay at Hotel Fort Continental will cost " << packageCost << " rupees." << endl;
            hotelCost = packageCost;
            break;
            
        default:
            cout << "Invalid choice! Redirecting to main menu.." << endl;
            Sleep(3000);
        }
    }
    friend void CancelBooking();
};
void CancelBooking(Booking& booking)
{
	// Check if the booking is already canceled
    if (booking.choice == 0) 
	{
        cout << "Booking has already been cancelled." << endl;
        return;
    }

    // Reset the choice to cancel the booking
    booking.choice = 0;

    // Reset the package cost
    booking.packageCost = 0;

    // Reset the hotel cost
    booking.hotelCost = 0;

    // Reset any other relevant booking details

    cout << "Booking has been canceled!" << endl;
}

class Destination                            //Aggregation
{
	private:
	  string city;
	  int id;
	  
	public:
		Destination()
		{
		}
		void getdestinationInfo()
		{
			cout<<"Enter Customer id: ";
		    cin>>id;
		    cin.ignore();
			cout<<"Enter city name inside Pakistan from these(Karachi,Lahore,FaisalAbad,Islamabad,Peshawar,Abbottabad): ";
			cin>>city;
			if(city=="Karachi"||city=="karachi")
			{
				cout<<"You have chosed Karachi for the visit!"<< endl;
			}
			else if(city=="Lahore"||city=="lahore")
			{
				cout<<"You have chosed Lahore for the visit!"<< endl;
			}
			else if(city=="FaisalAbad"||city=="faisalAbad")
			{
				cout<<"You have chosed FaisalAbad for the visit!"<< endl;
			}
			else if(city=="Islamabad"||city=="islamabad")
			{
				cout<<"You have chosed Islamabad for the visit!"<< endl;
			}
			else if(city=="Peshawar"||city=="peshawar")
			{
				cout<<"You have chosed Peshawar for the visit!"<< endl;
			}
			else if(city=="Abbottabad"||city=="abbottabad")
			{
				cout<<"You have chosed Abbottabad for the visit!"<< endl;
			}
		}
};

class Billing
{
	private:
    float totalBill;
    
	public:
		Billing()
		{
			totalBill = 0.0;
		}
		inline void calculateTotalBill(float transportCost, float hotelCost)
    {
        totalBill = transportCost + hotelCost;
    }

    void displayTotalBill()
    {
        cout << "Total Bill is: " << totalBill << endl;
    }
};

int main()
{
	ManagerMenu M1;
	Customer cus;
	Transport trans;
	Booking book;
	Destination des;
	Billing bill;
	int choice;
    bool exitMenu = false;
    while (!exitMenu)
    {
        cout << "======================================== Menu ========================================" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Select Destination"<<endl;
        cout << "3. Select Transport" << endl;
        cout << "4. Hotel Booking" << endl;
        cout << "5. Remove Customer Record" << endl;
        cout << "6. Cancel Booking"<<endl;
        cout << "7. Exit" << endl;
        cout << "================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
    switch (choice)
    {
        case 1:
            cus.getdetails(); // Call the getdetails() function of the Customer class
            break;
            
        case 2:
        	des.getdestinationInfo();
        	break;
        	
        case 3:
            trans.getdetails(); // Call the getTransportInfo() function of the Transport class
            break;
            
        case 4:
        	book.bookHotel();
        	bill.calculateTotalBill(trans.totalCost,book.hotelCost);
            bill.displayTotalBill();
        	break;
        	
        case 5:
        	int cusId;
            cout << "Enter the Customer ID to remove the record: ";
            cin >> cusId;
            cus.removeRecord(cusId); // Call the removeRecord() function of the Customer class
            break;
        case 6:
        	CancelBooking(book);
        	break;
        case 7:
            exitMenu = true;
            break;
            
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
	
	}

 cout << endl;
    }
	return 0;
}