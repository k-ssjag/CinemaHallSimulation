/*
|==================================================
|                                                 |
|   Program    : CS 1428 H Program 05             |
|   Author     : Kushal Timsina ( xrd19 )         |
|   Class      : CS 1428 H01                      |
|   Instructor : Dr. Zilliang Zong                | 
|   Date       : October 17, 2024                 |
|                                                 |
|=================================================|==================================
|                                                                                   |
|   Input :                                                                         |
|                                                                                   |
|   5 Alphabets ( either in capitals or small )                                     |
|   in order to navigate through the main menu.                                     |
|       S - Sell a ticket                                                           |
|       C - Display the seating chart                                               |
|       D - Display sales summary -  Day  Listing                                   |
|       F - Display sales summary - Floor Listing                                   |
|       Q - Quit the program                                                        |
|                                                                                   |
|   Seat selection input chart  ( a four character alphanumeric code )   [ AFNN ]   |
|       (T)hursday , (F)riday  , (S)aturday      -> Show    day  selection [ A  ]   |
|       (F)loor    , (B)alcony , (U)pper Balcony -> Seating area selection [ F  ]   |
|       Any number from 01 - 20, if not taken    -> Seat  number selection [ NN ]   |
|                                                                                   |
|====================================================================================
|                                                                                   |
|   Description :                                                                   |
|                                                                                   |
|       This program will simulate  a small scale cinema hall which will allow      |
|       the operator  to select a day to watch  a show with  a seating section      |
|       selection out of 3 section and one of 20 seats in each section.             |
|                                                                                   |
|       This will also allow the user to calculate and view the sales stats of      |
|       the hall ( sales per day and  sales per seating section ) and will run      |
|       until the operator manually quits the program.                              |
|                                                                                   |
|=================================================|==================================
|                                                 |
|   Output :                                      |
|                                                 |
|   S :                                           |
|       Displays the  seat chart and allows       |
|       the operator to enter the AFNN code       |
|                                                 |
|   C :                                           |
|       Only  displays the seating chart with     |
|       available seats indicated by an ' - '     |
|       booked    seats indicated by an ' * '     |
|                                                 |
|   D :                                           |
|       Displays  total sale in  terms of Day.    |
|                                                 |
|   F :                                           |
|       Displays total sales in terms of Floor.   |
|                                                 |
|   Q :                                           |
|       Quit the program.                         |
|                                                 |
|==================================================
*/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

using namespace std;

const int days    = 03;
const int section = 03;
const int seats   = 20;

const int  f_p    = 10;
const int  b_p    = 20;
const int ub_p    = 30;


char chart[days][section][seats];

void get_menu_choice();                   // prints the menu
void sell_seat();                         // Handles ticket sales
void cashier(int day, int sec, int seat); // Main ticket selling procedure
void print_chart();                       // Displays the seating chart
void print_day_list();                    // Displays sales summary by day
void print_section_list();                // Displays sales summary by section
void initialize_chart();                  // Initializes seating chart

int main()
{
    initialize_chart();                   // Initialize the seating chart to available

    char choice;

    do 
    {
        get_menu_choice();
        cin >> choice;

        // Convert lowercase letters to uppercase
        choice = toupper(choice);

        switch (choice)
        {
            case 'S':
            {
                sell_seat();
                break;
            }

            case 'C':
            {
                print_chart();
                break;
            }

            case 'D':
            {
                print_day_list();
                break;
            }

            case 'F':
            {
                print_section_list();
                break;
            }

            case 'Q':
            {
                cout << "Bye" << endl;
                break;
            }

            default:
            {
                cout << "'" << choice << "' is not a valid choice. Try Again." << endl;
                break;
            }
        }
    } 
    while (choice != 'Q');

    return 0;
}

void get_menu_choice()
{
    cout << " "                                         << endl
         << " "                                         << endl
         << "        *** Main Menu ***     "            << endl
         << " "                                         << endl
         << "S - Sell a ticket"                         << endl
         << "C - Display seating chart"                 << endl
         << "D - Display sales summary - Day Listing"   << endl
         << "F - Display sales summary - Floor Listing" << endl
         << "Q - Quit"                                  << endl
         << " "                                         << endl
         << "Your choice : ";                            
}

void initialize_chart()
{
    for (int d = 0 ; d < days ; d++)
    {
        for (int s = 0 ; s < section ; s++)
        {
            for (int seat = 0 ; seat < seats ; seat++)
            {
                chart[d][s][seat] = '-'; // Mark all seats as available
            }
        }
    }
}

void sell_seat()
{
    string code;

    while (true)
    {
        cout << endl
             << "Enter seat request by "                                                 << endl
             << "Day         :  (T)hursday , (F)riday  , (S)aturday     , followed by"   << endl
             << "Section     :  (F)loor    , (B)alcony , (U)pper Balcony, followed by"   << endl
             << "seat number :  1 - 20"                                                  << endl
             << "                     "                                                  << endl
             << "Enter seat request : ";
        cin  >> code;

        // Validate input length and content
        if ((code.length() != 3 && code.length() != 4) ||   // checks if the code is 3 or 4 characters 
            !isalpha(code[0]) ||                            // checks if the first  character is alphabet
            !isalpha(code[1]) ||                            // checks if the second character is alphabet
            !isdigit(code[2]) ||                            // checks if the third  character is a number
            (code.length() == 4 && !isdigit(code[3])))      // checks if the fourth character is a number for 4 character code
        {
            cout << "Invalid code. Please use the format as specified." << endl;
            continue; // Restart the loop for new input
        }

        // Convert first two characters to uppercase
        code[0] = toupper(code[0]);
        code[1] = toupper(code[1]);

        int day, sec, seat;

        // Decode day
        switch (code[0])
        {
            case 'T':
            {
                day = 0; 
                break;
            }

            case 'F':
            {
                day = 1; 
                break;
            }

            case 'S':
            {
                day = 2; 
                break;
            }

            default:
            {
                cout << "Your day code is invalid. Please try again." << endl;
                continue; // Restart the loop
            }
        }

        // Decode section
        switch (code[1])
        {
            case 'F':
            {
                sec = 0; 
                break;
            }

            case 'B':
            {
                sec = 1; 
                break;
            }

            case 'U':
            {
                sec = 2; 
                break;
            }

            default:
            {
                cout << "Your section code is invalid. Please try again." << endl;
                continue; // Restart the loop
            }
        }

        // Decode seat number
        if (code.length() == 3)
        {
            seat = code[2] - '0' - 1; // Single-digit seat
        }

        else
        {
            seat = (code[2] - '0') * 10 + (code[3] - '0') - 1; // Two-digit seat
        }

        if (seat < 0 || seat >= seats)
        {
            cout << "Invalid seat number. Please try again." << endl;
            continue; // Restart the loop
        }

        // Reserve seat if available
        if (chart[day][sec][seat] == '-')
        {
            cashier(day, sec, seat);

            cout << "Congratulations ! You got the seat." << endl;
            return; // Exit to the main menu after booking
        }

        else
        {
            cout << "That seat was taken. Please select another." << endl;
        }
    }
}

void cashier(int day, int sec, int seat)
{
    chart[day][sec][seat] = '*'; // Mark seat as booked
}

void print_chart()
{
    cout << "Seating Chart ( '-' = available, '*' = booked ) : " << endl;

    // Loop through days
    for (int d = 0 ; d < days ; d++)
    {
        if (d == 0)
        {
            cout << "                " << endl
                 << "                " << endl
                 << "Thursday        " << endl;
        }

        else if (d == 1)
        {
            cout << "                " << endl
                 << "                " << endl
                 << "Friday          " << endl;
            
        }
        
        else if (d == 2)
        {
            cout << "                " << endl
                 << "                " << endl
                 << "Saturday        " << endl;
        }

        // Loop through sections
        for (int s = 0 ; s < section ; s++)
        {
            if (s == 0)
            {
                cout << "                          " << endl;
                cout << "          Floor         : "        ;
            }

            else if (s == 1)
            {
                cout << "                          " << endl;
                cout << "          Balcony       : "        ;
            }

            else if (s == 2)
            {
                cout << "                          " << endl;
                cout << "          Upper Balcony : "        ;
            }

            // Loop through seats
            for (int seat = 0 ; seat < seats ; seat++)
            {
                cout << chart[d][s][seat] << " " ;
            }

            cout << endl;
        }
    }
}

void print_day_list()
{
    int grandTotalTickets = 0;
    int grandTotalSales   = 0;

    cout << "                           " << endl
         << "Sales Summary by Day :     " << endl 
         << "                           " << endl;

    for (int d = 0 ; d < days ; d++)
    {
        int count = 0;                    // Reset ticket count for the day
        int total = 0;                    // Reset total sales for the day
        int sectionCounts[section] = {0}; // To track counts per section, reset every day

        // Print day name
        if (d == 0) 
        {
            cout << "Thursday : ";
        }

        else if (d == 1) 
        {
            cout << "Friday   : ";
        }

        else if (d == 2) 
        {
            cout << "Saturday : ";
        }

        for (int s = 0 ; s < section ; s++)
        {
            for (int seat = 0 ; seat < seats ; seat++)
            {
                if (chart[d][s][seat] == '*')
                {
                    count++;                       // Count sold tickets
                    sectionCounts[s]++;            // Increment count for the section

                    if (s == 0) 
                    {
                        total += f_p;              // Add to total sales for Floor
                    }

                    else if (s == 1) 
                    {
                        total += b_p;              // Add to total sales for Balcony
                    }

                    else if (s == 2) 
                    {
                        total += ub_p;             // Add to total sales for Upper Balcony
                    }
                }
            }
        }

        grandTotalTickets += count;             // Accumulate total tickets sold
        grandTotalSales += total;               // Accumulate total sales

        cout << "                            " << endl
             << "           Total Tickets sold : " << setw(3) << count << setw(5) << " $" << total << endl
             << "                            " << endl;

        cout << "           Floor tickets sold : " << setw(3) << sectionCounts[0] << setw(5) << " $" << (sectionCounts[0] * f_p ) << endl
             << "         Balcony tickets sold : " << setw(3) << sectionCounts[1] << setw(5) << " $" << (sectionCounts[1] * b_p ) << endl    
             << "   Upper Balcony tickets sold : " << setw(3) << sectionCounts[2] << setw(5) << " $" << (sectionCounts[2] * ub_p) << endl 
             << "                                " << endl;
    }

    cout << "                                    " << endl
         << "Total ticket sales for all shows:   " << setw(3) << grandTotalTickets << setw(5) << " $" << grandTotalSales << endl;
}

void print_section_list()
{
    int grandTotalTickets = 0;
    int grandTotalSales   = 0;

    cout << "                           " << endl
         << "Sales Summary by Section : " << endl 
         << "                           " << endl;

    for (int s = 0 ; s < section ; s++)
    {
        int sectionTotalTickets = 0;  // Reset ticket count for the section
        int sectionTotalSales   = 0;  // Reset total sales for the section

        // Print section name
        if (s == 0) 
        {
            cout << "Floor           " << endl;
        }

        else if (s == 1) 
        {
            cout << "Balcony         " << endl;
        }

        else if (s == 2) 
        {
            cout << "Upper Balcony   " << endl;
        }

        for (int d = 0 ; d < days ; d++)
        {
            int count = 0;  // Reset count for the day
            int price = 0;

            for (int seat = 0 ; seat < seats ; seat++)
            {
                if (chart[d][s][seat] == '*')
                {
                    count++;  // Count sold tickets
                }
            }

            // Assign the price based on section
            if (s == 0)
            {
                price = f_p;
                sectionTotalSales += (count * f_p);
            }

            else if (s == 1)
            {
                price = b_p;
                sectionTotalSales += (count * b_p);
            }

            else if (s == 2)
            {
                price = ub_p;
                sectionTotalSales += (count * ub_p);
            }

            sectionTotalTickets += count;  // Accumulate tickets sold for the section

            // Print tickets sold for each day
            if (d == 0)
            {
                cout << "               Thursday Tickets sold : " << setw(3) << count << setw(5) << " $" << (count * price) << endl;
            }

            else if (d == 1)
            {
                cout << "                 Friday Tickets sold : " << setw(3) << count << setw(5) << " $" << (count * price) << endl;
            }

            else if (d == 2)
            {
                cout << "               Saturday Tickets sold : " << setw(3) << count << setw(5) << " $" << (count * price) << endl;
            }
        }

        grandTotalTickets += sectionTotalTickets;  // Accumulate total tickets
        grandTotalSales   += sectionTotalSales;    // Accumulate total sales

        cout << "                                " << endl
             << "  Total tickets sold in this section : " << setw(3) << sectionTotalTickets << setw(5) << " $" << sectionTotalSales << endl
             << "                                " << endl;
    }

    cout << "                                    " << endl
         << "Grand Total ticket sales for all sections : " << setw(3) << grandTotalTickets << setw(5)  << " $" << grandTotalSales << endl;
}