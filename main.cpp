#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PARCELS = 100;

class Stock {
    
    public:
        string myStock[MAX_PARCELS];
        int amount = 0, i = 0;
        fstream myFile;
    
    public: void showParcel() {
        cout << "[ Parcel in stock ]" << endl << endl;
        for (i=0; i<amount; i++) {
            cout << myStock[i] << endl;
        }
        cout << endl;
    }
    
    public: Stock(); // #1st Scope resolution operator

}; // #1st class

Stock :: Stock() {
    myFile.open("Stock.txt", ios::in);
        if (myFile.is_open()) {
            while (getline(myFile, myStock[i])) {
                amount += 1;
                i += 1;
            }
            myFile.close();
        }
} // constructor for read file

class Parcel : public Stock { // #1st inheritance
    
    public: 
        string track;

    public:
        
        bool checkTrackingNumber(string track); // #2nd Scope resolution operator
        
        void addParcel() { 
            
            char con = 'y';
            int n;
            
            cout << "[ Add parcel ]" << endl << endl;
            
            while ((con == 'y') or (con == 'Y')) 
            {
                cout << "How many parcel do you want to add into the system : "; cin >> n;
                cout << endl;
                
                myFile.open("Stock.txt", ios::app); // open file for append
                
                for (i=0; i<n; i++) 
                {
                    cout << "#" << i+1 << " : "; 
                    cin >> track;
                    
                    if (checkTrackingNumber(track)) {
                        cout << endl;
                        cout << "[ There is already a parcel with this tracking number in the system ]" << endl << endl;
                        i -= 1;
                    }
                    else {
                        myStock[amount] = track; // add new parcel to array
                        myFile << track << endl; // append file
                        amount += 1;
                    }
                }
                cout  << endl;
                showParcel();
                cout << "Will you continue addition (y/n) : "; cin >> con;
                cout << endl;
            }
            myFile.close();
        }
        
        void searchParcel() {
            
            char con = 'y';
            
            cout << "[ Search parcel ]" << endl << endl;
            
            while ((con == 'y') or (con == 'Y')) 
            {
                cout << "Enter a track number : "; cin >> track;
                cout << endl;
                
                if (checkTrackingNumber(track)) {
                    cout << "[ Parcel found ]" << endl << endl;
                    cout << "Will you take it out (y/n) : "; cin >> con;
                    cout << endl;
                    if ((con == 'y') or (con == 'Y')) takeParcel(track);
                }
                else {
                    cout << "[ Parcel not found ]" << endl << endl;
                }
                cout << "Will you continue searching (y/n) : "; cin >> con;
                cout << endl;
            }    
        } 
        
        void takeParcel(string track) {
            
            myFile.open("Stock.txt", ios::out); // open file for write
                
                for (i=0; i<amount; i++) 
                {
                    if (myStock[i] == track) { // rewrite array
                        for (int j=i; j<(amount-1); j++) {
                            myStock[j] = myStock[j+1];
                        }
                        i -= 1;
                        amount -= 1;
                        cout << "[ The parcel was taken off! ]" << endl;
                    }
                    else {
                        myFile << myStock[i] << endl; // rewrite file
                    }
                }
            myFile.close(); 
            cout << endl;
            showParcel();
        } // #1st overloading
        
        void takeParcel() {
            
            char con = 'y';
            
            cout << "[ Take parcel ]" << endl << endl;
            
            while ((con == 'y') or (con == 'Y'))
            {
                cout << "Enter a track number : "; cin >> track;
                cout << endl;
                
                if (checkTrackingNumber(track)) {
                    takeParcel(track);
                }
                else {
                    cout << "[ Pacel not found ]" << endl << endl;
                }
                cout << "Will you continue taking off (y/n) : "; cin >> con;
                cout << endl;
            }
        } // #2nd overloading
}; // #2nd class

bool Parcel :: checkTrackingNumber(string track) { 
    for (int i=0; i<amount; i++) {
        if (track == myStock[i]) {
            return true;
        }
    }
    return false;
} 

void farewell() {
    cout << "[ Program is closed, Thank you :) ]";
}

int main()
{
    Stock readObj;
    Parcel obj;
    
    int choice;
    
    cout << "Press 1 to show parcels" << endl;
    cout << "Press 2 to search for a specific parcel" << endl;
    cout << "Press 3 to add a new parcel into the system" << endl;
    cout << "Press 4 to take a parcel off" << endl; 
    cout << "Press 0 to close the program" << endl << endl;

    while (true) {
        
        cout << "Please select an option : "; cin >> choice;
        cout << endl;
        
        if (choice == 1) obj.showParcel();
        else if (choice == 2) obj.searchParcel();
        else if (choice == 3) obj.addParcel();
        else if (choice == 4) obj.takeParcel();
        else if (choice == 0) {
            farewell();
            break;
        }
        else cout << "[ The number that you entered is invalid ]" << endl << endl;
    }
    
    return 0;
}
