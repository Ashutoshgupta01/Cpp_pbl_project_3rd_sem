#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "constants.hpp"
#include "structure.hpp"

using namespace std;

class Theatre {
private:
    vector<Movie> movies;
    vector<FoodItem> menu;
    char seats[ROWS][COLS];

    Movie selectedMovie{};
    vector<Seat> bookedSeats;
    vector<FoodItem> orderedFood;

    int totalAmount = 0;

public:
    Theatre()
    {
        movies.push_back({1, "Avengers: Endgame", "Action/Sci-Fi", "10:00 AM"});
        movies.push_back({2, "Inception", "Sci-Fi/Thriller", "1:30 PM"});
        movies.push_back({3, "The Lion King", "Animation/Drama", "5:00 PM"});

        menu.push_back({1, "Popcorn", 100});
        menu.push_back({2, "Cold Drink", 80});
        menu.push_back({3, "Nachos", 120});
        menu.push_back({4, "Burger", 150});
        menu.push_back({5, "Pizza Slice", 160});

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                seats[i][j] = 'O';
            }
        }
    }

    void showMovies() {
        cout << "\n===== Available Movies =====\n";
        for (const auto &m : movies) {
            cout << m.id << ". " << m.name << " (" << m.genre << ") - " << m.time << "\n";
        }
    }

    void selectMovie()
    {
        int choice;

        while (true) {
            cout << "\nEnter movie ID to select: ";
            cin >> choice;

            for (const auto &m : movies) {
                if (m.id == choice) {
                    selectedMovie = m;
                    cout << "\nYou selected: " << m.name << " (" << m.genre << ") at " << m.time << "\n";
                    return;
                }
            }
            cout << "Invalid choice! Try again.\n";
        }
    }

    void displaySeats()
    {
        cout << "\n===== Seat Layout (O = Available, X = Booked) =====\n\n   ";
        for (int j = 0; j < COLS; j++) {
            cout << setw(2) << j + 1 << " ";
        }
        cout << "\n";

        for (int i = 0; i < ROWS; i++) {
            cout << setw(2) << i + 1 << " ";
            for (int j = 0; j < COLS; j++) {
                cout << " " << seats[i][j] << " ";
            }
            cout << "\n";
        }
    }

    void bookSeat()
    {
        int row, col, numSeats;

        cout << "\nHow many seats do you want to book? ";
        cin >> numSeats;

        for (int k = 0; k < numSeats; k++) {
            cout << "Enter seat row (1-" << ROWS << "): ";
            cin >> row;

            cout << "Enter seat column (1-" << COLS << "): ";
            cin >> col;

            if (row < 1 || row > ROWS || col < 1 || col > COLS) {
                cout << "Invalid seat! Try again.\n";
                k--;
                continue;
            }

            if (seats[row - 1][col - 1] == 'X') {
                cout << "Seat already booked! Choose another.\n";
                k--;
                continue;
            }

            seats[row - 1][col - 1] = 'X';
            bookedSeats.push_back({row, col});
            totalAmount += TICKET_PRICE;

            cout << "Seat booked successfully!\n";
        }
    }

    void showMenu() {
        cout << "\n===== Food & Beverages Menu =====\n";
        for (const auto &f : menu) {
            cout << f.id << ". " << f.name << " - Rs. " << f.price << "\n";
        }
    }

    void orderFood()
    {
        char choice;
        cout << "\nDo you want to order food? (y/n): ";
        cin >> choice;

        if (choice != 'y' && choice != 'Y')
            return;

        int foodId, qty;

        while (true) {
            showMenu();
            cout << "Enter food ID to order (0 to finish): ";
            cin >> foodId;

            if (foodId == 0)
                break;

            cout << "Enter quantity: ";
            cin >> qty;

            bool found = false;

            for (const auto &f : menu) {
                if (f.id == foodId) {
                    for (int i = 0; i < qty; i++) {
                        orderedFood.push_back(f);
                    }

                    totalAmount += f.price * qty;
                    cout << f.name << " x" << qty << " added.\n";
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Invalid food ID!\n";
        }
    }
    void exportToJSON() 
    {
        ofstream file("bookings.json");
        if (!file.is_open()) {
            cout << "\nError: Unable to create bookings.json file!\n";
            return;
        }

        file << "{\n";
        file << "  \"movie\": \"" << selectedMovie.name << "\",\n";
        file << "  \"time\": \"" << selectedMovie.time << "\",\n";

        file << "  \"seats\": [\n";
        for (size_t i = 0; i < bookedSeats.size(); i++) {
            file << "    { \"row\": " << bookedSeats[i].row << ", \"col\": " << bookedSeats[i].col << " }";
            if (i != bookedSeats.size() - 1) file << ",";
            file << "\n";
        }
        file << "  ],\n";

        file << "  \"food\": [\n";
        for (size_t i = 0; i < orderedFood.size(); i++) {
            file << "    { \"name\": \"" << orderedFood[i].name 
                 << "\", \"price\": " << orderedFood[i].price << " }";
            if (i != orderedFood.size() - 1) file << ",";
            file << "\n";
        }
        file << "  ],\n";

        file << "  \"total\": " << totalAmount << "\n";
        file << "}\n";

        file.close();
        cout << "\nBookings exported to bookings.json successfully!\n";
    }

    void generateBill()
    {
        cout << "\n===== TICKET =====\n";

        cout << "Movie: " << selectedMovie.name << " (" << selectedMovie.genre << ")\n";

        cout << "Time: " << selectedMovie.time << "\n";

        cout << "Seats: ";
        for (const auto &s : bookedSeats) {
            cout << "(Row " << s.row << ", Col " << s.col << ") ";
        }
        cout << "\n";

        cout << "Ticket Price: Rs. " << bookedSeats.size() * TICKET_PRICE << "\n";

        if (!orderedFood.empty()) {
            cout << "\nFood Ordered:\n";
            for (const auto &f : orderedFood) {
                cout << "- " << f.name << " Rs. " << f.price << "\n";
            }
        }

        cout << "\nTOTAL: Rs. " << totalAmount << "\n";
        cout << "===================\n";
    }
};

int main()
{
    Theatre t;
    t.showMovies();
    t.selectMovie();
    t.displaySeats();
    t.bookSeat();
    t.orderFood();
    t.generateBill();
    t.exportToJSON();

    return 0;
}