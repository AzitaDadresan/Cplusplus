//============================================================================
// Name        : VectorSorting.cpp
// Author      : Azita Dadresan
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

// Display the bid information to the console (std::out)

void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

// Prompt user for bid information using console (std::in)

Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

// Load a CSV file containing bids into a container

vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title

// Partition the vector of bids into two parts, low and high

int partition(vector<Bid>& bids, int begin, int end) {

   int l = begin;
   int h = end;


   int pivot = (begin + (end - begin) / 2);
   bool finished = false;

   // this while loops continually increments the low point as long as it's below the pivot
   // then continually decrements the high point as long as it's above the pivot
   while(!finished) {

       while(bids[l].title.compare(bids[pivot].title) < 0) {
           ++l;
       }

       while(bids[pivot].title.compare(bids[h].title) < 0) {
           --h;
       }

       if (l >= h) {
           finished = true;
       // if variable l is not greater than or equal to h the two bids are swapped
       } else {
           swap(bids[l] , bids[h]);


           //bring end points closer to one another

           ++l;
           --h;
       }
   }
   return h;
}


// Perform a quick sort on bid title

void quickSort(vector<Bid>& bids, int begin, int end) {
   unsigned int middle = 0;

   // make sure the algorithm stops running if there are 1 or 0 bids left to sort

   if (begin >= end) {
       return;
   }

   // this code partitions the bids into lower and higher sections

   middle = partition(bids, begin, end);

   // function is called recursively to sort the individual partitions

   // first call sorts the initial element to the midpoint

   quickSort(bids, begin, middle);

   // second call sorts the middle + 1th element to the endpoint
   quickSort(bids, middle + 1, end);

}

// FIXME (1a): Implement the selection sort logic over bid.title

// Perform a selection sort on bid title

void selectionSort(vector<Bid>& bids) {
   // this creates an index to the smallest minimum bid found
   unsigned int smallest;
   unsigned int largest = bids.size();

   // place designates the position at which bids are sorted/unsorted
   for (unsigned place = 0; place < largest; ++place) {
       smallest = place;

       for (unsigned j = place + 1; j < largest; ++j) {
           if (bids[j].title.compare(bids[smallest].title) < 0) {
               smallest = j;
           }
       }

       if (smallest != place)
           swap(bids[place], bids[smallest]);
   }

}

// Simple C function to convert a string to a double after stripping out unwanted char

double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
* The one and only main() method
*/
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << " 1. Load Bids" << endl;
        cout << " 2. Display All Bids" << endl;
        cout << " 3. Selection Sort All Bids" << endl;
        cout << " 4. Quick Sort All Bids" << endl;
        cout << " 9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (unsigned int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        // FIXME (1b): Invoke the selection sort and report timing results
        case 3:
           ticks = clock();

           // call selectionSort method to sort the loaded bids
           selectionSort(bids);

           cout << bids.size() << " bids read" << endl;

           // Calculate elapsed time and display result
           ticks = clock() - ticks; // current clock ticks minus starting clock ticks
           cout << "time: " << ticks << " clock ticks" << endl;
           cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

           break;

        // FIXME (2b): Invoke the quick sort and report timing resultscase 3:

        case 4:
           ticks = clock();

           // call quickSort method to sort the loaded bids
           quickSort(bids, 0, bids.size() - 1);

           cout << bids.size() << " bids read" << endl;

           // Calculate elapsed time and display result
           ticks = clock() - ticks; // current clock ticks minus starting clock ticks
           cout << "time: " << ticks << " clock ticks" << endl;
           cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

           break;

    }

    }
    cout << "Good bye." << endl;

    return 0;
}