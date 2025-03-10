#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <regex>
#include <fstream>
#include <graphics.h>
#include <conio.h> 
#include <windows.h>
#include <ctime>


using namespace std;
int length=16*80;
int breadth=9*80;

POINT cursorPos;
void drawButton(int x, int y, int width, int height, const char* text);
void drawTextBox(int x, int y, int width, int height);
void getInput(int x, int y, char* input);

void convert(POINT &cursorPos) {
    GetCursorPos(&cursorPos);
    ScreenToClient(GetForegroundWindow(), &cursorPos);
}

bool isInsideButton(int left, int top, int right, int bottom, int x, int y) {
    return x >= left && x <= right && y >= top && y <= bottom;
}

void textArea(int button_left, int button_top, int button_right, int button_bottom, int color_inside)
{ 
	 setcolor(color_inside);
                rectangle(button_left+5, button_top+5, button_right-5, button_bottom-5);
                floodfill(button_left + 10, button_top + 10, color_inside );
}
void captureAndDisplayChar(int left, int top, int right, int bottom, char &inputChar) {
    char ch;
    setbkcolor(15);
    settextstyle(10, HORIZ_DIR, 3);
    bool charCaptured = false; // Flag to check if the character is captured

    while (true) {
        if (kbhit()) {
            ch = getch();

            // Check for valid characters (alphanumeric)
            if (isalnum(ch)) {
                inputChar = ch;
                charCaptured = true;
            }

            if (ch == 13 && charCaptured) { // Enter key to break the loop if a valid character was captured
                break;
            } else if (ch == 8) { // Backspace key
                charCaptured = false;
                inputChar = '\0'; // Clear the character
            }

            // Clear the rectangle area
            setfillstyle(SOLID_FILL, WHITE);
            bar(left + 6, top + 6, right - 5, bottom - 5);

            // Redraw the character if a valid one is captured
            if (charCaptured) {
                setcolor(BLACK);
                outtextxy(left + 10, top + 20, &inputChar);
            }
        }
        delay(100);
    }
}


void captureAndDisplayInt(int left, int top, int right, int bottom, int &output) {
    char ch;
    std::string input = "";  // Initialize the input string
    setbkcolor(15);
    settextstyle(10, HORIZ_DIR, 3);

    while (true) {
        if (kbhit()) {
            ch = getch();
            if (ch == 13) {  // Enter key to break the loop
                if (!input.empty()) {
                    output = std::stoi(input);  // Convert string to int
                }
                break;
            } else if (ch == 8) {  // Backspace key
                if (!input.empty()) {
                    input.pop_back();
                }
            } else if (isdigit(ch) && input.size() < 18) {  // Only allow digits and limit to 18 characters
                input += ch;
            }

            // Clear the rectangle area
            setfillstyle(SOLID_FILL, WHITE);
            bar(left + 6, top + 6, right - 5, bottom - 5);

            // Redraw the text
            setcolor(BLACK);
            outtextxy(left + 10, top + 20, (char*)input.c_str());
        }
        delay(100);
    }
}

void captureAndDisplayText(int left, int top, int right, int bottom, string &input) {
    char ch;
    input = ""; // Initialize the input string
    setbkcolor(15);
    settextstyle(10, HORIZ_DIR, 3);
    while (true) {
        if (kbhit()) {
            ch = getch();
            if (ch == 13) { // Enter key to break the loop
                break;
            } else if (ch == 8) { // Backspace key
                if (!input.empty()) {
                    input.pop_back();
                }
            } else if (input.size() < 18) { // Limit to 18 characters
                input += ch;
            }

            // Clear the rectangle area
            setfillstyle(SOLID_FILL, WHITE);
            bar(left + 6, top + 6, right - 5, bottom - 5);

            // Redraw the text
            setcolor(BLACK);
            outtextxy(left + 10, top + 20, (char*)input.c_str());
        }
        delay(100);
    }
}

void captureAndDisplayPassword(int left, int top, int right, int bottom, string &input) {
    char ch;
    input = ""; // Initialize the input string
    setbkcolor(15);
    string display = "";
    settextstyle(10, HORIZ_DIR, 2);
    while (true) {
        if (kbhit()) {
            ch = getch();
            if (ch == 13) { // Enter key to break the loop
                if (input.size() <= 12) {
                    break;
                }
            } else if (ch == 8) { // Backspace key
                if (!input.empty()) {
                    input.pop_back();
                    display.pop_back();
                }
            } else if (input.size() < 12) { // Limit to 12 characters
                input += ch;
                display += '*';
            }

            // Clear the rectangle area
            setfillstyle(SOLID_FILL, WHITE);
            bar(left + 6, top + 6, right - 5, bottom - 15);

            // Redraw the text
            setcolor(BLACK);
            outtextxy(left + 10, top + 15, (char*)display.c_str());
        }
        delay(100);
    }
}
// Base class for vehicles
class Vehicle {
protected:
    int id;
    int seatCapacity;
    int availability;
    string vehicleType;
public:
    float pricePerHour;

    Vehicle(int id, int seatCapacity, float pricePerHour, string vehicleType)
        : id(id), seatCapacity(seatCapacity), pricePerHour(pricePerHour), vehicleType(vehicleType) {
        availability = 10;
    }
    
    //user wala display
 virtual void display_From(int x, int y) const {
        settextstyle(10, HORIZ_DIR, 3); 		
        char buffer[100];
        sprintf(buffer, "Vehicle ID: %d", id);
        outtextxy(x, y, buffer);

        sprintf(buffer, "Vehicle Type: %s", vehicleType.c_str());
        outtextxy(x, y + 20, buffer);

        sprintf(buffer, "Seat Capacity: %d", seatCapacity);
        outtextxy(x, y + 40, buffer);

        sprintf(buffer, "Availability: %d", availability);
        outtextxy(x, y + 60, buffer);

        sprintf(buffer, "Price per Hour: $%.2f", pricePerHour);
        outtextxy(x, y + 80, buffer);
    }
    // Mark display as a const member function
    virtual void display(int x, int y) const {
    	setcolor(WHITE);
    	setbkcolor(BLACK);
        char buffer[100];
        //int x = 465;
       // int y = 225;
        readimagefile("solo.jpg", 0, 0, 16*80, 9*80);
        sprintf(buffer, "%d", id);
        outtextxy(x, y, buffer);

        sprintf(buffer, "%s", vehicleType.c_str());
        outtextxy(x, y + 100, buffer);

        sprintf(buffer, "%d", seatCapacity);
        outtextxy(x, y + 200, buffer);

        sprintf(buffer, "%d", availability);
        outtextxy(x, y + 300, buffer);

        sprintf(buffer, "$%.2f", pricePerHour);
        outtextxy(x, y + 400, buffer);
    }

    int getId() const { return id; }

    int getAvailability() const { return availability; }

    void setAvailability(int availability) { this->availability = availability; }

    float getPricePerHour() const { return pricePerHour; }

    string getVehicleType() const { return vehicleType; }

    virtual ~Vehicle() {}

    virtual void saveToFile(ofstream& outFile) const {
        outFile << id << " " << seatCapacity << " " << pricePerHour << " " << vehicleType << " " << availability << endl;
    }

    virtual void loadFromFile(ifstream& inFile) {
        inFile >> id >> seatCapacity >> pricePerHour >> vehicleType >> availability;
    }
};


// Derived classes for specific vehicle types
class Car : public Vehicle {
public:
    Car(int id) : Vehicle(id, 4, 20.0, "Car") {}
    
      void display(int x, int y) const override {
        Vehicle::display(x, y);
    }

    void saveToFile(ofstream& outFile) const override {
        outFile << "Car ";
        Vehicle::saveToFile(outFile);
    }

    void loadFromFile(ifstream& inFile) override {
        Vehicle::loadFromFile(inFile);
    }
};

class Bus : public Vehicle {
public:
    Bus(int id) : Vehicle(id, 40, 50.0, "Bus") {}

	  void display(int x, int y) const override {
        Vehicle::display(x, y);
    }
    void saveToFile(ofstream& outFile) const override {
        outFile << "Bus ";
        Vehicle::saveToFile(outFile);
    }

    void loadFromFile(ifstream& inFile) override {
        Vehicle::loadFromFile(inFile);
    }
};

class Jeep : public Vehicle {
public:
    Jeep(int id) : Vehicle(id, 7, 30.0, "Jeep") {}
	
	  void display(int x, int y) const override {
        Vehicle::display(x, y);
    }
    void saveToFile(ofstream& outFile) const override {
        outFile << "Jeep ";
        Vehicle::saveToFile(outFile);
    }

    void loadFromFile(ifstream& inFile) override {
        Vehicle::loadFromFile(inFile);
    }
};

class Micro : public Vehicle {
public:
    Micro(int id) : Vehicle(id, 10, 25.0, "Micro") {}
	 
	   void display(int x, int y) const override {
        Vehicle::display(x, y);
    }
    void saveToFile(ofstream& outFile) const override {
        outFile << "Micro ";
        Vehicle::saveToFile(outFile);
    }

    void loadFromFile(ifstream& inFile) override {
        Vehicle::loadFromFile(inFile);
    }
};

class Bike : public Vehicle {
public:
    Bike(int id) : Vehicle(id, 2, 10.0, "Bike") {}
	  void display(int x, int y) const override {
        Vehicle::display(x, y);
    }
    void saveToFile(ofstream& outFile) const override {
        outFile << "Bike ";
        Vehicle::saveToFile(outFile);
    }

    void loadFromFile(ifstream& inFile) override {
        Vehicle::loadFromFile(inFile);
    }
};

// Class for managing bookings
class Booking {
public:
    int roomNumber;
    string name;
    string contactNumber;
    int vehicleId;
    int estimatedTime;
    string purpose;
    string vehicleType;

    Booking(int roomNumber, string name, string contactNumber, int vehicleId, int estimatedTime, string purpose, string vehicleType)
        : roomNumber(roomNumber), name(name), contactNumber(contactNumber), vehicleId(vehicleId), estimatedTime(estimatedTime), purpose(purpose), vehicleType(vehicleType) {}

    void display(int x, int y) const {
    	
        char buffer[100];
        sprintf(buffer, "Room Number   : %d", roomNumber);
        outtextxy(x, y, buffer);

        sprintf(buffer, "Name          : %s", name.c_str());
        outtextxy(x, y + 20, buffer);

        sprintf(buffer, "Contact Number: %s", contactNumber.c_str());
        outtextxy(x, y + 40, buffer);

        sprintf(buffer, "Vehicle ID    : %d", vehicleId);
        outtextxy(x, y + 60, buffer);

        sprintf(buffer, "Vehicle Type  : %s", vehicleType.c_str());
        outtextxy(x, y + 80, buffer);

        sprintf(buffer, "Time          : %d hours", estimatedTime);
        outtextxy(x, y + 100, buffer);

        sprintf(buffer, "Purpose       : %s", purpose.c_str());
        outtextxy(x, y + 120, buffer);
        
        outtextxy(x, y + 140, (char *)"-----------------------");
    }
	
	void displayForReceipt(int x, int y) const {
	//	readimagefile("receipt.jpg",0,0,16*80,9*80);
        char buffer[100];
        
        sprintf(buffer, "%d", roomNumber);
        outtextxy(x, y, buffer);

        sprintf(buffer, "%s", name.c_str());
        outtextxy(x, y + 50, buffer);

        sprintf(buffer, "%s", contactNumber.c_str());
        outtextxy(x, y + 100, buffer);

        sprintf(buffer, "%d", vehicleId);
        outtextxy(x, y + 150, buffer);

        sprintf(buffer, "%s", vehicleType.c_str());
        outtextxy(x, y + 200, buffer);

        sprintf(buffer, "%d Hours", estimatedTime);
        outtextxy(x, y + 250, buffer);

        sprintf(buffer, "%s", purpose.c_str());
        outtextxy(x, y + 300, buffer);
    }

    void saveToFile(ofstream& outFile) const {
        outFile << roomNumber << " " << name << " " << contactNumber << " " << vehicleId << " " << estimatedTime << " " << purpose << " " << vehicleType << endl;
    }

    void loadFromFile(ifstream& inFile) {
        inFile >> roomNumber;
        inFile.ignore();
        getline(inFile, name, ' ');
        getline(inFile, contactNumber, ' ');
        inFile >> vehicleId >> estimatedTime;
        inFile.ignore();
        getline(inFile, purpose, ' ');
        getline(inFile, vehicleType);
    }
};

// Class for system operations
class Sys {
private:
//	string username, password;
    vector<Vehicle*> vehicles;   //vetcor banako 
    vector<Booking> bookings;

    void saveVehiclesToFile() const {
        ofstream outFile("vehicles.txt");
        for (const Vehicle* v : vehicles) {
            v->saveToFile(outFile);
        }
        outFile.close();
    }

    void loadVehiclesFromFile() {
        ifstream inFile("vehicles.txt");
        string type;
        while (inFile >> type) {
            Vehicle* v = nullptr;
            if (type == "Car") v = new Car(0);
            else if (type == "Bus") v = new Bus(0);
            else if (type == "Jeep") v = new Jeep(0);
            else if (type == "Micro") v = new Micro(0);
            else if (type == "Bike") v = new Bike(0);

            if (v) {
                v->loadFromFile(inFile);
                vehicles.push_back(v);
            }
        }
        inFile.close();
    }

    void saveBookingsToFile() const {
        ofstream outFile("bookings.txt");
        for (const Booking& b : bookings) {
            b.saveToFile(outFile);
        }
        outFile.close();
    }

    void loadBookingsFromFile() {
    	//bookings.clear();
        ifstream inFile("bookings.txt");
        while (inFile.peek() != EOF) {
            Booking b(0, "", "", 0, 0, "", "");
            b.loadFromFile(inFile);
            bookings.push_back(b);
        }
        inFile.close();
    }
	
	/*void loadBookingsFromFileRestore() {
    	bookings.clear();
        ifstream inFile("bookings.txt");
        while (inFile.peek() != EOF) {
            Booking b(0, "", "", 0, 0, "", "");
            b.loadFromFile(inFile);
            bookings.push_back(b);
        }
        inFile.close();
    }*/


    void drawButton(int x, int y, int width, int height, const char* text) {
        rectangle(x, y, x + width, y + height);
        outtextxy(x + (width / 4), y + (height / 4), (char*)text);
    }

    void drawTextBox(int x, int y, int width, int height) {
        rectangle(x, y, x + width, y + height);
    }

    void getInput(int x, int y, char* input) {
    	setcolor(WHITE);
    	setbkcolor(BLACK);
        char ch;
        int i = 0;
        while (true) {
            ch = getch();
            if (ch == 13) { // Enter key
                input[i] = '\0';
                break;
            } else if (ch == 8 && i > 0) { // Backspace
                input[--i] = '\0';
                settextstyle(BOLD_FONT,0,3);
                outtextxy(x, y, (char *)"                "); // Clear the previous character
                outtextxy(x, y, input);
                settextstyle(BOLD_FONT,0,1);
            } else if (ch != 8) { // Ignore backspace if no characters to delete
                input[i++] = ch;
                input[i] = '\0';
                settextstyle(BOLD_FONT,0,3);
                outtextxy(x, y, input);
                settextstyle(BOLD_FONT,0,1);
            }
        }
    }
public:
    Sys() {
        loadVehiclesFromFile();
        loadBookingsFromFile();
        if (vehicles.empty()) {
            vehicles.push_back(new Car(1));
            vehicles.push_back(new Bus(2));
            vehicles.push_back(new Jeep(3));
            vehicles.push_back(new Micro(4));
            vehicles.push_back(new Bike(5));
            saveVehiclesToFile();
        }
    }

    ~Sys() {
        for (Vehicle* v : vehicles) {
            delete v;
        }
    }
    void displayVehicles() {
        cleardevice();
        outtextxy(200, 50, (char *)"AVAILABLE VEHICLES");
        int y = 100;
        for (const Vehicle* v : vehicles) {
            v->display_From(100, y);
            y += 100;
        }
        outtextxy(100, y + 50, (char *)"Press any key to return to menu...");
        getch();
    }

    void displayVehicleDetails(int vehicleId) {
        cleardevice();
        for (const Vehicle* v : vehicles) {
            if (v->getId() == vehicleId) {
               // outtextxy(200, 50, (char *)"VEHICLE DETAILS");
                v->display(465, 230);
              //  outtextxy(100, 300, (char *)"Press any key to return to menu...");
                getch();
                return;
            }
        }
        outtextxy(100, 350, (char *)"Vehicle not found.");
        outtextxy(100, 400, (char *)"Press any key to return to menu...");
        getch();
    }

    void updateVehicleDetails(int vehicleId, int newAvailability, float newPricePerHour) {
        cleardevice();
        for (Vehicle* v : vehicles) {
            if (v->getId() == vehicleId) {
                v->setAvailability(newAvailability);
                v->pricePerHour = newPricePerHour;
                outtextxy(100, 100, (char *)"Vehicle details updated successfully!");
                saveVehiclesToFile();
                return;
            }
        }
        outtextxy(100, 150, (char *)"Vehicle not found.");
    }
	
	bool validatePhoneNumber(const string& phoneNumber) {
        return regex_match(phoneNumber, regex("\\d{10}"));
    }

    bool validateName(const string& name) {
        return regex_match(name, regex("^[A-Za-z]+$"));
    }

    bool isRollNumberUnique(int roomNumber) {
        for (const Booking& b : bookings) {
            if (b.roomNumber == roomNumber) {
                return false;
            }
        }
        return true;
    }
    bool isValidVehicleId(const std::string& vehicleId) {
    std::regex vehicleIdPattern("^[1-5]$");  // Matches vehicle IDs 1 through 5
    return std::regex_match(vehicleId, vehicleIdPattern);
}
    bool bookVehicle(int roomNumber, const string& name, const string& contactNumber, int vehicleId, int estimatedTime, const string& purpose) {
        cleardevice();
        
        if (!validateName(name)) {
            readimagefile("same room.jpg", 0, 0, length, breadth);
            delay(2000);
            return false;
        }

        if (!isRollNumberUnique(roomNumber)) {
            readimagefile("same room.jpg", 0, 0, length, breadth);
            delay(2000);
            return false;
        }
        
        for (Vehicle* v : vehicles) {
            if (v->getId() == vehicleId) {
                if (v->getAvailability() > 0) {
                    float totalPrice = estimatedTime * v->getPricePerHour();
                    char buffer[100];
                    readimagefile("confirmation.jpg", 0, 0, length, breadth);
                    sprintf(buffer, "$%.1f ", totalPrice);
                    settextstyle(BOLD_FONT,0,8);
                    outtextxy(742, 246, buffer);
                    settextstyle(BOLD_FONT,0,1);  //Default font


                    char confirm = getch();
                    if (tolower(confirm) == 'y') {
                        bookings.emplace_back(roomNumber, name, contactNumber, vehicleId, estimatedTime, purpose, v->getVehicleType());
                        v->setAvailability(v->getAvailability() - 1);
                  
                        readimagefile("booking success.jpg", 0, 0, length, breadth);
						delay(1500);
						saveVehiclesToFile();
                        saveBookingsToFile();
                        return true;
                    } else {
            
                        readimagefile("booking cancel.jpg", 0, 0, length, breadth);
						delay(1500);
                        return false;
                    }
                } else {
                    outtextxy(100, 100, (char *)"Vehicle not available.");
                    getch();
                    return false;
                }
            }
        }
  
        readimagefile("invalid id.jpg", 0, 0, length, breadth);
	    getch();
        return false;
    }

    void displayBookings() {
        cleardevice();
        bookings.clear();
        loadBookingsFromFile();
        
        
      // / setbkcolor(15);
    	settextstyle(10, HORIZ_DIR, 2);
        outtextxy(200, 50, (char *)"CURRENT BOOKINGS");
        
        int y = 100;
        outtextxy(100, y , (char *)"                       <--");
        for (const Booking& b : bookings) {
            b.display(100, y);
            y += 140;
        outtextxy(100, y , (char *)"                       <--");
        }
        outtextxy(100, y , (char *)"                           ");
        outtextxy(100, y + 50, (char *)"Press any key to return to menu...");
        getch();
    }

    void deleteBooking(int bookingIndex) {
        cleardevice();
        if (bookingIndex >= 0 && bookingIndex < bookings.size()) {
            int vehicleId = bookings[bookingIndex].vehicleId;
            for (Vehicle* v : vehicles) {
                if (v->getId() == vehicleId) {
                    v->setAvailability(v->getAvailability() + 1);
                    break;
                }
            }
            bookings.erase(bookings.begin() + bookingIndex);
            outtextxy(100, 100, (char *)"Booking deleted successfully!");
            saveVehiclesToFile();
            saveBookingsToFile();
        } else {
            outtextxy(100, 100, (char *)"Invalid booking index.");
        }
        outtextxy(100, 150, (char *)"Press any key to return to menu...");
        getch();
    }

	void handleBookVehicle() {
        cleardevice();
        outtextxy(200, 50, (char *)"BOOK VEHICLE");
        drawTextBox(100, 100, 200, 30);
        drawTextBox(100, 150, 200, 30);
        drawTextBox(100, 200, 200, 30);
        drawTextBox(100, 250, 200, 30);
        drawTextBox(100, 300, 200, 30);
        drawTextBox(100, 350, 200, 30);

        char roomNumberStr[100];
        char name[100];
        char contactNumber[100];
        char vehicleIdStr[100];
        char estimatedTimeStr[100];
        char purpose[100];

        getInput(100, 100, roomNumberStr);
        getInput(100, 150, name);
        getInput(100, 200, contactNumber);
        getInput(100, 250, vehicleIdStr);
        getInput(100, 300, estimatedTimeStr);
        getInput(100, 350, purpose);

        int roomNumber = atoi(roomNumberStr);
        int vehicleId = atoi(vehicleIdStr);
        int estimatedTime = atoi(estimatedTimeStr);

        if (bookVehicle(roomNumber, name, contactNumber, vehicleId, estimatedTime, purpose)) {
            outtextxy(100, 400, (char *)"Booking successful!");
        } else {
            outtextxy(100, 400, (char *)"Booking failed. Vehicle may not be available.");
        }

        outtextxy(100, 450, (char *)"Press any key to return to menu...");
        getch();
    }

void editBooking(std::vector<Booking>& bookings, std::vector<Vehicle*>& vehicles) {
    cleardevice();
   // readimagefile("edit your booking.jpg", 0, 0, 16*80, 9*80);

    // Prompt the user to enter the room number
    string roomNumberInput;
    captureAndDisplayText(776, 316, 949, 393, roomNumberInput);
    int roomNumber = stoi(roomNumberInput);

    // Search for the booking
    bool bookingFound = false;
    for (Booking& booking : bookings) {
        if (booking.roomNumber == roomNumber) {
            bookingFound = true;
            cleardevice();
			readimagefile("edit your booking.jpg", 0, 0, 16*80, 9*80);
            // Prompt for new contact number
            string newContactNumber;
            //outtextxy(100, 200, (char *)"Enter new contact number:");
            captureAndDisplayText(463, 226, 715, 263, newContactNumber);
            

     
            string newVehicleId;
   
            captureAndDisplayText(463, 326, 715, 363, newVehicleId);

            string newDurationInput;

            captureAndDisplayText(463, 426, 715, 463, newDurationInput);
            
            
            //checkupdate(newContactNumber, stoi(newvehicleId), stoi(newDurationInput));
           booking.contactNumber = newContactNumber;
            booking.vehicleId = stoi(newVehicleId);
            booking.estimatedTime = stoi(newDurationInput);  // Convert string to int   
            saveVehiclesToFile();
            saveBookingsToFile();

            // Confirm the update
            readimagefile("updated.jpg", 0, 0, 16*80, 9*80);
           // outtextxy(100, 500, (char *)"Booking updated successfully!");
           userMenu();
            break;
        }
    }

    if (!bookingFound) {
        readimagefile("booking not found.jpg", 0, 0, 16*80, 9*80);
        outtextxy(100, 140, (char *)"No booking found for the entered room number.");
    }

    getch();  // Wait for user to press a key
}

   
    
    void getReceipt(char roomNumber) {
    //cleardevice(); // Clear the screen for new content
    float totalCost = 0;
    int yPosition = 240; // Starting y position for text
    bool bookingFound = false;
    for (const Booking& b : bookings) {
        if (b.roomNumber == roomNumber) {
            bookingFound = true;
            for (const Vehicle* v : vehicles) {
                if (v->getId() == b.vehicleId) {
                    totalCost = b.estimatedTime * v->getPricePerHour();
                    break;
                }
            }

            // Display booking details
            std::string roomText = std::to_string(b.roomNumber);
            outtextxy(253, yPosition, (char *)roomText.c_str());
            yPosition += 50;

            std::string vehicleText = std::to_string(b.vehicleId);
            outtextxy(253, yPosition, (char *)vehicleText.c_str());
            yPosition += 50;

            std::string estimatedTimeText =  std::to_string(b.estimatedTime);
            outtextxy(253, yPosition, (char *)estimatedTimeText.c_str());
            yPosition += 50;

            outtextxy(100, yPosition, (char *)"----------------------");
            
        }
    }

    if (!bookingFound) {
        outtextxy(100, yPosition, (char *)"No booking found for the specified room number.");
        yPosition += 20;
		userMenu();
		    }
	
    //outtextxy(100, yPosition, (char *)"Press any key to return to menu...");
    getch(); // Wait for user input
    userMenu();
}

void getTime() {
    // Get current time
    time_t now = time(0);

    // Convert to local time format
    tm *localTime = localtime(&now);

    // Format the date and time string
    char timeStr[100];
    sprintf(timeStr, "%04d-%02d-%02d %02d:%02d:%02d",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

    // Display the time string in the graphics window
    outtextxy(653, 169, timeStr);  // You can change the position as needed
}
	
    void userMenu() {
        
     cleardevice();
      while (true) {
        convert(cursorPos);
        cout << cursorPos.x << " " << cursorPos.y << endl;
        
		readimagefile("user page.jpg", 0, 0, length, breadth); 

    // Button coordinates
    int button1_left = 74, button1_top = 277, button1_right = 393, button1_bottom =382;
	int button2_left = 64, button2_top = 416, button2_right = 395, button2_bottom =516;
    int button3_left = 462, button3_top = 277, button3_right = 786, button3_bottom =382;
    int button4_left = 462, button4_top = 412, button4_right = 782, button4_bottom =516;
    int button5_left = 866, button5_top = 278, button5_right = 1174, button5_bottom =375;
    int button6_left = 850, button6_top = 422, button6_right = 1173, button6_bottom =525;
    int button7_left = 1166, button7_top = 609, button7_right = 1250, button7_bottom =683;// exit
    
    if (GetAsyncKeyState(VK_LBUTTON)) {
            if (isInsideButton(button1_left, button1_top, button1_right, button1_bottom, cursorPos.x, cursorPos.y)) {
            	//displayVehicles();
            	char vehicleId[10];
                    cleardevice();
                    readimagefile("id.jpg",0,0,16*80,9*80); 
           // captureAndDisplayInt(776, 316, 949, 393, roomNumber);
                   // outtextxy(100, 50, (char *)"Enter vehicle ID: ");
                    //drawTextBox(300, 50, 200, 20);
                    getInput(726, 340, vehicleId);
                    displayVehicleDetails(stoi(vehicleId));
                    userMenu();
            }
		//Book
			else if (isInsideButton(button2_left, button2_top, button2_right, button2_bottom, cursorPos.x, cursorPos.y)) {
			
                char roomNumber[10], vehicleId[10], estimatedTime[10];
                    char name[50], contactNumber[15], purpose[100];
                    
                    readimagefile("book now.jpg", 0, 0, length, breadth);
                    
                    outtextxy(735, 133, (char *)"<--");

                    getInput(460, 123, roomNumber);
                    
                    outtextxy(735, 233, (char *)"<--");

                    getInput(460, 222, name);
                    
                    outtextxy(735, 333, (char *)"<--");

                    getInput(460, 321, contactNumber);

                    while (!regex_match(contactNumber, regex("^[0-9]{10}$"))) {
                        outtextxy(460, 330, (char *)"Must be 10-digit");
                        delay(1000);
                        outtextxy(460, 320, (char *)"                ");
                        outtextxy(460, 330, (char *)"                ");
                        getInput(460, 321, contactNumber);
                    }
                    
                    outtextxy(735, 433, (char *)"<--");
			
                   getInput(460, 417, vehicleId);
                   
                   while (!regex_match(vehicleId, regex("^[1-5]"))) {
                        outtextxy(460, 430, (char *)"Must be 1-5");
                        delay(1000);
                        outtextxy(460, 420, (char *)"                ");
                        outtextxy(460, 430, (char *)"                ");
                        getInput(460, 417, vehicleId);
                    }
                    
                    outtextxy(735, 533, (char *)"<--");
                    getInput(460, 514, estimatedTime);
                    
                    outtextxy(735, 633, (char *)"<--");
                    getInput(460, 614, purpose);

                    bookVehicle(stoi(roomNumber), name, contactNumber, stoi(vehicleId), stoi(estimatedTime), purpose);
                   userMenu();  
                
            }
            // Check booking
             else if (isInsideButton(button3_left, button3_top, button3_right, button3_bottom, cursorPos.x, cursorPos.y)) {
            	 cleardevice();
                readimagefile("check your booking.jpg",0,0,16*80,9*80);
                //outtextxy(100, 100, (char *)"Enter Room Number for Receipt:");
                string roomNumberInput;
                captureAndDisplayText(793, 329, 932, 385, roomNumberInput);
                int roomNumber = stoi(roomNumberInput);
                
                readimagefile("your booking.jpg",0,0,16*80,9*80);

                bool bookingFound = false;
                int y = 240;
                for (const Booking& booking : bookings) {
                    if (booking.roomNumber == roomNumber) {
                        bookingFound = true;
                        booking.displayForReceipt(253, y);
                    }
                }

                if (!bookingFound) {
                	cleardevice();
                	readimagefile("check your booking ko not found.jpg",0,0,16*80,9*80);
                	std::string errorMessage = std::to_string(roomNumber);
        			outtextxy(793, 329, (char *)errorMessage.c_str());
        			
                    //outtextxy(100, 140, (char *)"No booking found for the entered room number.");
                }
                getch();
                userMenu();
            }
		//cancel
			else if (isInsideButton(button4_left, button4_top, button4_right, button4_bottom, cursorPos.x, cursorPos.y)) {
				cancleBooking();
				userMenu();
}
	
    else if (isInsideButton(button5_left, button5_top, button5_right, button5_bottom, cursorPos.x, cursorPos.y)) {
    cleardevice();
   int roomNumber;
            readimagefile("edit page, room number ask.jpg",0,0,16*80,9*80); 
            captureAndDisplayInt(776, 316, 949, 393, roomNumber);
    //readimagefile("edit booking page.jpg", 0, 0, 16*80, 9*80);

    bool bookingFound = false;

    for (Booking& b : bookings) {
        if (b.roomNumber == roomNumber) {
            bookingFound = true;
             readimagefile("edit your booking.jpg",0,0,16*80,9*80);

         /*   // Prompt for new name with validation
            string newName;
            do {
                outtextxy(100, 200, (char *)"Enter new name:");
                captureAndDisplayText(776, 316, 949, 393, newName);
                if (!validateName(newName)) {
                    outtextxy(100, 240, (char *)"Invalid name. It must contain only characters.");
                }
            } while (!validateName(newName));
            b.name = newName;
*/



                    
                    
            // Prompt for new contact number with validation
            string newContactNumber;
            do {
              //  outtextxy(100, 300, (char *)"Enter new contact number:");
              	outtextxy(735, 233, (char *)"<--");
                captureAndDisplayText(460, 210, 700, 254, newContactNumber);
                if (!validatePhoneNumber(newContactNumber)) {
                    outtextxy(460, 220, (char *)"Must be 10 digits.");
                    delay(1000);
                    outtextxy(460, 220, (char *)"                  ");
                    outtextxy(460, 218, (char *)"                  ");
                    outtextxy(460, 222, (char *)"                  ");
                }
            } while (!validatePhoneNumber(newContactNumber));
            b.contactNumber = newContactNumber;

            // Prompt for new vehicle ID with validation
            string newVehicleId;
            outtextxy(735, 333, (char *)"<--");
            do {
              //  outtextxy(100, 400, (char *)"Enter new vehicle ID (1-Car, 2-Bus, 3-Jeep, 4-Micro, 5-Bike):");
                captureAndDisplayText(460, 310, 700, 356, newVehicleId);
                if (!isValidVehicleId(newVehicleId)) {
                    outtextxy(460, 320, (char *)"Must be 1 - 5.");
                    delay(1000);
                    outtextxy(460, 320, (char *)"              ");
                    outtextxy(460, 318, (char *)"              ");
                    outtextxy(460, 322, (char *)"              ");
                }
            } while (!isValidVehicleId(newVehicleId));
            int vehicleIdInt = stoi(newVehicleId);  // Convert string to int

            // Restore previous vehicle's availability
            for (Vehicle* v : vehicles) {
                if (v->getId() == b.vehicleId) {
                    v->setAvailability(v->getAvailability() + 1);
                    break;
                }
            }
                        
            // Update booking details
            b.vehicleId = vehicleIdInt;
            if (vehicleIdInt == 5) {
                b.vehicleType = "Bike";
            } else {
                for (Vehicle* v : vehicles) {
                    if (v->getId() == vehicleIdInt) {
                        b.vehicleType = v->getVehicleType();
                        v->setAvailability(v->getAvailability() - 1);  // Decrease new vehicle's availability
                        break;
                    }
                }
            }

            // Prompt for new estimated time
          string newEstimatedTime;
          //  outtextxy(100, 500, (char *)"Enter new estimated time (hours):");
          outtextxy(735, 433, (char *)"<--");
            captureAndDisplayText(460, 410, 700, 456, newEstimatedTime);
            b.estimatedTime = stoi(newEstimatedTime);

            // Prompt for new purpose
           /* string newPurpose;
            outtextxy(100, 600, (char *)"Enter new purpose:");
            captureAndDisplayText(776, 316, 949, 393, newPurpose);
            b.purpose = newPurpose;*/

            saveBookingsToFile();  // Save updated bookings to file
            readimagefile("updated.jpg", 0, 0, 16*80, 9*80);            
          //  outtextxy(100, 700, (char *)"Booking updated successfully!");
            break;
        }
    }

    if (!bookingFound) {
        readimagefile("booking not found.jpg", 0, 0, 16*80, 9*80);
        outtextxy(100, 140, (char *)"No booking found for the entered room number.");
    }

    getch();  // Wait for user to press a key}


            }
		//Receipt
			 if (isInsideButton(button6_left, button6_top, button6_right, button6_bottom, cursorPos.x, cursorPos.y)) {
                cleardevice();
                readimagefile("get your receipt.jpg",0,0,16*80,9*80);
                //outtextxy(100, 100, (char *)"Enter Room Number for Receipt:");
                string roomNumberInput;
                captureAndDisplayText(793, 329, 932, 385, roomNumberInput);
                int roomNumber = stoi(roomNumberInput);

                bool bookingFound = false;
                readimagefile("receipt.jpg",0,0,16*80,9*80);
                getTime();
                int y = 240;
                for (const Booking& booking : bookings) {
                    if (booking.roomNumber == roomNumber) {
                        bookingFound = true;
                        booking.displayForReceipt(253, y);
						
                        // Calculate and display total cost
                        float totalCost = 0.0;
                        for (const Vehicle* vehicle : vehicles) {
                            if (vehicle->getId() == booking.vehicleId) {
                                totalCost = booking.estimatedTime * vehicle->getPricePerHour();
                                break;
                            }
                        }
                        char buffer[100];
                       // readimagefile("receipt.jpg",0,0,16*80,9*80);
                        sprintf(buffer, "$ %.2f", totalCost);
                        outtextxy(667, 649, buffer);
                        break;
                    }
                }

                if (!bookingFound) {
                	readimagefile("receipt ko not found.jpg",0,0,16*80,9*80);
                    //outtextxy(100, 140, (char *)"No booking found for the entered room number.");
                }
                getch();
                userMenu();
            }
            } 
        //home
			else if (isInsideButton(button7_left, button7_top, button7_right, button7_bottom, cursorPos.x, cursorPos.y)) {
               break;
            }    
        }
    } 
void cancleBooking() {
   // char roomNumberStr[10];  // Buffer to store the input as a string
    int roomNumber;  // Declare roomNumber in the correct scope
    bool found = false;  // Declare found in the correct scope

    readimagefile("cancellation page.jpg",0,0,16*80,9*80);
    captureAndDisplayInt(776, 316, 949, 393, roomNumber);


    // Search for the room number in the bookings
  /*  int button0_left = 1173, button0_top = 613, button0_right = 1252, button0_bottom = 685; // Exit
   if (GetAsyncKeyState(VK_LBUTTON)) {
   	 if (isInsideButton(button0_left, button0_top, button0_right, button0_bottom, cursorPos.x, cursorPos.y)) {
               exit (0); //userMenu();         
			      }    
        }*/
    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
        if (it->roomNumber == roomNumber) {
            found = true;  // Set found to true if the room number is found

            // Update vehicle availability
            for (Vehicle* v : vehicles) {
                if (v->getId() == it->vehicleId) {
                    v->setAvailability(v->getAvailability() + 1);
                    break;
                }
            }

            // Remove the booking
            bookings.erase(it);
            saveVehiclesToFile();
            saveBookingsToFile();
			readimagefile("cancellation success.jpg",0,0,16*80,9*80);
          //  outtextxy(100, 50, (char *)"Success: ");
            delay(2000);  // Exit the loop once the booking is found and removed    
			userMenu();       
        }
    }

    // If the room number was not found, display an error message
    if (!found) {
       std::string errorMessage = std::to_string(roomNumber);
        readimagefile("room not found.jpg",0,0,16*80,9*80);
        outtextxy(786, 336, (char *)errorMessage.c_str());
        delay(2000);
    }
    userMenu();
}
	void validatelLogin() {
    cleardevice();
    string username, password, storedUsername, storedPassword;

    // Read credentials from file
    ifstream credentialsFile("admin_credentials.txt");
    if (credentialsFile.is_open()) {
        credentialsFile >> storedUsername >> storedPassword;
        credentialsFile.close();
    } else {
        outtextxy(100, 100, (char *)"Error: Unable to open credentials file.");
        delay(2000);
        return;
    }

    readimagefile("login page.jpg", 0, 0, length, breadth);

    // Example coordinates for username and password fields
    int userLeft = 484, userTop = 289, userRight = 734, userBottom = 333;
    int passLeft = 484, passTop = 394, passRight = 734, passBottom = 425;

    // Capture username and password
    captureAndDisplayText(userLeft, userTop, userRight, userBottom, username);
    captureAndDisplayPassword(passLeft, passTop, passRight, passBottom, password);

    // Validate username and password
    if (username == storedUsername && password == storedPassword) {
        readimagefile("login success.jpg", 0, 0, length, breadth);
        delay(2000);
        return;       
    } else {
        readimagefile("invalid login.jpg", 0, 0, length, breadth);
        delay(2000);
        validatelLogin();
    }
}
void deleteAllBookings() {
    // If bookings are stored in a vector
    bookings.clear();

    // If bookings are stored in a file, open it in trunc mode
    std::ofstream file("bookings.txt", std::ofstream::out | std::ofstream::trunc);
    if (file.is_open()) {
    	readimagefile("deleted all.jpg",0,0,16*80,9*80);
        //cout << "All bookings have been deleted." << endl;
        file.close();
        delay(2000);
        adminMenu();
    } else {
        //cout << "Error: Unable to open bookings file." << endl;
        readimagefile("khulena.jpg",0,0,16*80,9*80);
        file.close();
        delay(2000);
        adminMenu();
    }
}

void moveToRecycleBin() {
    std::ifstream bookingFile("bookings.txt"); // Open the booking file
    std::ofstream recycleBinFile("recyclebin.txt", std::ios::app); // Open the recycle bin file for appending

    if (!bookingFile) {
        std::cerr << "Error opening bookings.txt.\n";
        return;
    }

    if (!recycleBinFile) {
        std::cerr << "Error opening recyclebin.txt.\n";
        return;
    }

    std::string line;
    while (getline(bookingFile, line)) { // Read each line from the booking file
        recycleBinFile << line << "\n"; // Write the line to the recycle bin file
    }
    bookings.clear();
    saveVehiclesToFile();
    saveBookingsToFile();
    

    bookingFile.close(); // Close the booking file
    recycleBinFile.close(); // Close the recycle bin file

    // Clear the contents of the original booking file
    std::ofstream clearFile("bookings.txt", std::ios::trunc); // Open the booking file in truncate mode to clear it
    if (!clearFile) {
        std::cerr << "Error clearing bookings.txt.\n";
        return;
    }
    clearFile.close();
    readimagefile("moved to bin.jpg",0,0,16*80,9*80);
    delay(2000);
   // std::cout << "All bookings moved to recyclebin.txt.\n";
    adminMenu();
}

void restoreBooking(int roomNumber) {
    std::ifstream recycleBinFile("recyclebin.txt"); // Open recycle bin file
    std::ofstream bookingFile("bookings.txt", ios::app); // Append to booking file
    std::ofstream tempFile("temp.txt"); // Temporary file for non-matching entries

    if (!recycleBinFile) {
        std::cerr << "Error opening recyclebin.txt.\n";
        return;
    }

    if (!bookingFile) {
        cerr << "Error opening bookings.txt.\n";
        return;
    }

    if (!tempFile) {
        std::cerr << "Error creating temporary file.\n";
        return;
    }

    string line;
    bool bookingFound = false;
    while (getline(recycleBinFile, line)) { // Read each line in recyclebin.txt
        int currentRoomNumber;
        istringstream iss(line);
        iss >> currentRoomNumber; // Extract room number

        if (currentRoomNumber == roomNumber) {
            bookingFile << line << "\n"; // Restore booking
            bookingFile.flush(); // Ensure booking is immediately saved
            bookingFound = true;
        } else {
            tempFile << line << "\n"; // Keep non-matching bookings in temp file
            tempFile.flush();
        }
    }  
    // Close file streams before file operations
    recycleBinFile.close();
    bookingFile.close();
    tempFile.close();

    if (bookingFound) {
        // Replace recyclebin.txt with temp.txt
        remove("recyclebin.txt");
        rename("temp.txt", "recyclebin.txt");

        // Display success image and room number
        std::string successMessage = std::to_string(roomNumber);
        readimagefile("restore success.jpg", 0, 0, 16 * 80, 9 * 80);
        outtextxy(786, 336, (char *)successMessage.c_str());

        // Ensure graphical changes are visible immediately
        delay(2000); // Pause to show the success message
        cleardevice(); // Clear the screen to prepare for the next UI screen

        adminMenu(); // Return to admin menu
    } else {
        // If no booking found, clean up temp file
        remove("temp.txt");

        // Display failure image and room number
        std::string errorMessage = std::to_string(roomNumber);
        readimagefile("restore not found.jpg", 0, 0, 16 * 80, 9 * 80);
        outtextxy(786, 336, (char *)errorMessage.c_str());

        // Ensure graphical changes are visible immediately
        delay(2000); // Pause to show the failure message
        cleardevice(); // Clear the screen

        adminMenu(); // Return to admin menu
    }
}

void adminMenu() {
    cleardevice();
    
    int button1_left = 74, button1_top = 277, button1_right = 393, button1_bottom =382;
	int button2_left = 64, button2_top = 416, button2_right = 395, button2_bottom =516;
    int button3_left = 462, button3_top = 277, button3_right = 786, button3_bottom =382;
    int button4_left = 462, button4_top = 412, button4_right = 782, button4_bottom =516;
    int button5_left = 866, button5_top = 278, button5_right = 1174, button5_bottom =375;
    int button6_left = 850, button6_top = 422, button6_right = 1173, button6_bottom =525;
    int button7_left = 1166, button7_top = 609, button7_right = 1250, button7_bottom =683;// exit
    readimagefile("admin page.jpg", 0, 0, length, breadth);
  while (true) {
    convert(cursorPos);
    //cout << cursorPos.x << " " << cursorPos.y << endl;
    
    if (GetAsyncKeyState(VK_LBUTTON)) {
            if (isInsideButton(button1_left, button1_top, button1_right, button1_bottom, cursorPos.x, cursorPos.y)) {
            	char vehicleId[10];
                    cleardevice();
                    readimagefile("id.jpg",0,0,16*80,9*80); 
           // captureAndDisplayInt(776, 316, 949, 393, roomNumber);
                   // outtextxy(100, 50, (char *)"Enter vehicle ID: ");
                    //drawTextBox(300, 50, 200, 20);
                    getInput(726, 340, vehicleId);
                    displayVehicleDetails(stoi(vehicleId));
                    adminMenu();
            }
		//recycle 
			else if (isInsideButton(button2_left, button2_top, button2_right, button2_bottom, cursorPos.x, cursorPos.y)) {
               
             moveToRecycleBin();
            break;
            } 
            // Display booking
             else if (isInsideButton(button3_left, button3_top, button3_right, button3_bottom, cursorPos.x, cursorPos.y)) {
             	cleardevice();
             	//loadBookingsFromFile();
             	//bookings.clear();
            	displayBookings();
            	adminMenu();
            }
		//Permanent 
			else if (isInsideButton(button4_left, button4_top, button4_right, button4_bottom, cursorPos.x, cursorPos.y)) {
				deleteAllBookings();
			}
	

            else if (isInsideButton(button5_left, button5_top, button5_right, button5_bottom, cursorPos.x, cursorPos.y)) {
            	char vehicleId[10], newAvailability[10], newPrice[10];
                    cleardevice();
                                        
                    readimagefile("update gadi through admin.jpg", 0, 0, length, breadth);

                  //  getInput(462, 228, vehicleId);
                   // string VehicleId;
            do {
              //  outtextxy(100, 400, (char *)"Enter new vehicle ID (1-Car, 2-Bus, 3-Jeep, 4-Micro, 5-Bike):");
              //  captureAndDisplayText(460, 210, 700, 256, VehicleId);
                getInput(462, 228, vehicleId);
                if (!isValidVehicleId(vehicleId)) {
                    outtextxy(462, 190, (char *)"Must be between 1 and 5.");
                }
            } while (!isValidVehicleId(vehicleId));
            int vehicleIdInt = stoi(vehicleId);

                    getInput(462, 327, newAvailability);

                    getInput(462, 423, newPrice);

                    updateVehicleDetails(stoi(vehicleId), stoi(newAvailability), stof(newPrice));
                    outtextxy(100, 200, (char *)"Press any key to return to menu...");
                    adminMenu();
            }
		//Restore
			else if (isInsideButton(button6_left, button6_top, button6_right, button6_bottom, cursorPos.x, cursorPos.y)) {
            int roomNumber;
            readimagefile("restore page.jpg",0,0,16*80,9*80); 
            captureAndDisplayInt(776, 316, 949, 393, roomNumber);
                restoreBooking(roomNumber);
                }
        //home
			else if (isInsideButton(button7_left, button7_top, button7_right, button7_bottom, cursorPos.x, cursorPos.y)) {
               break;
            }

}
    }
}
};   //system class close
// Function to draw the welcome screen
void drawWelcomeScreen() {
	readimagefile("welcome.jpg",0,0,16*80,9*80);
	delay(2000);
}

int main() {
    initwindow(16*80,9*80, (char *)"GOD BLESS YOU !!");

    drawWelcomeScreen();

    Sys system;
    cleardevice();
    int button1_left = 76, button1_top = 280, button1_right = 265, button1_bottom = 507;  //Admin
    int button2_left = 432, button2_top = 268, button2_right = 660, button2_bottom = 491;  // User
    int button0_left = 1161, button0_top = 27, button0_right = 1257, button0_bottom = 114; // Exit

                while (true) {
        convert(cursorPos);
        cout << cursorPos.x << " " << cursorPos.y << endl;
        
        
   // readimagefile("solo.jpg", 0, 0, 16*80, 9*80);
   //   readimagefile("get your receipt.jpg",0,0,16*80,9*80);
    // readimagefile("receipt.jpg",0,0,16*80,9*80);
   // readimagefile("book now.jpg", 0, 0, length, breadth);
   readimagefile("main.jpg",0,0,16*80,9*80);
     	 //readimagefile("update gadi through admin.jpg", 0, 0, length, breadth);
        //admin login
   if (GetAsyncKeyState(VK_LBUTTON)) {
            if (isInsideButton(button1_left, button1_top, button1_right, button1_bottom, cursorPos.x, cursorPos.y)) {
            	system.validatelLogin();
            	system.adminMenu();
            }
		//user login
			else if (isInsideButton(button2_left, button2_top, button2_right, button2_bottom, cursorPos.x, cursorPos.y)) {
                system.userMenu();
            } 
        //home
			else if (isInsideButton(button0_left, button0_top, button0_right, button0_bottom, cursorPos.x, cursorPos.y)) {
               exit (0);
            }    
        }
        delay(200);
 
    }
 }