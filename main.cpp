#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

void sort_goats(list<Goat> &trip);
void find_goat(list<Goat> &trip);
void count_goats(list<Goat> &trip);
void remove_old_goats(list<Goat> &trip);
void reverse_goats(list<Goat> &trip);
void display_oldest_goat(list<Goat> &trip);
void display_youngest_goat(list<Goat> &trip);
void unique_goats(list<Goat> &trip);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Sorting goats.\n";
                sort_goats(trip);
                break;
            case 5:
                cout <<"Finding a goat by name.\n";
                find_goat(trip);
                break;
            case 6:
                cout << "Counting goats by color.\n";
                count_goats(trip);
                break;
            case 7:
                cout << "Removing old goats.\n";
                remove_old_goats(trip);
                break;
            case 8:
                cout << "Reversing goat list.\n";
                reverse_goats(trip);
                break;
            case 9:
                cout << "Displaying the oldest goat.\n";
                display_oldest_goat(trip);
                break;
            case 10:
                cout << "Displaying the youngest goat.\n";
                display_youngest_goat(trip);
                break;
            case 11:
                cout << "Removing duplicate goats.\n";
                unique_goats(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats\n";
    cout << "[5] Find goat\n";
    cout << "[6] Count goats by color\n";
    cout << "[7] Remove old goats\n";
    cout << "[8] Reverse goat list\n";
    cout << "[9] Display oldest goat\n";
    cout << "[10] Display youngest goat\n";
    cout << "[11] Remove duplicate goats\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void sort_goats(list<Goat> &trip) {
    trip.sort();
    cout << "Goats sorted by name.\n";
}

void find_goat(list<Goat> &trip) {
    string name;
    cout << "Enter name to search: ";
    cin >> name;

    auto it = find_if(trip.begin(), trip.end(), [name](const Goat &g) { return g.get_name() == name; });
    if (it != trip.end()) {
        cout << "Goat found: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
    } else {
        cout << "Goat not found.\n";
    }
}

void count_goats(list<Goat> &trip) {
    string color;
    cout << "Enter color to count: ";
    cin >> color;
    int count = count_if(trip.begin(), trip.end(), [color](const Goat &g) { return g.get_color() == color; });
    cout << "Number of goats with color " << color << ": " << count << "\n";
}

void remove_old_goats(list<Goat> &trip) {
    trip.remove_if([](const Goat &g) { return g.get_age() > 10; });
    cout << "Old goats removed.\n";
}

void reverse_goats(list<Goat> &trip) {
    trip.reverse();
    cout << "Goat list reversed.\n";
}

void display_oldest_goat(list<Goat> &trip) {
    auto it = max_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b) { return a.get_age() < b.get_age(); });
    if (it != trip.end()) {
        cout << "Oldest goat: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
    }
}

void display_youngest_goat(list<Goat> &trip) {
    auto it = min_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b) { return a.get_age() < b.get_age(); });
    if (it != trip.end()) {
        cout << "Youngest goat: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
    }
}

void unique_goats(list<Goat> &trip) {
    trip.sort();
    trip.unique([](const Goat &a, const Goat &b) { return a.get_name() == b.get_name() && a.get_age() == b.get_age() && a.get_color() == b.get_color(); });
    cout << "Duplicate goats removed.\n";
}
