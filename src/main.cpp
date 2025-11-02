#include <iostream>
#include <vector>
#include <iomanip>
#include "structures.cpp"

using namespace std;

class Theatre {
private:
    vector<Movie> movies;
    vector<FoodItem> menu;
    char seats[ROWS][COLS];
    Movie selectedMovie;
    vector<string> bookedSeats;
    vector<FoodItem> orderedFood;
    int totalAmount = 0;

public:
    Theatre() {
        // Initialize movie list
        movies.push_back({1, "Avengers: Endgame", "Action/Sci-Fi", "10:00 AM"});
        movies.push_back({2, "Inception", "Sci-Fi/Thriller", "1:30 PM"});
        movies.push_back({3, "The Lion King", "Animation/Drama", "5:00 PM"});
        movies.push_back({4, "Interstellar", "Adventure/Sci-Fi", "8:00 PM"});
        movies.push_back({5, "Joker", "Psychological/Drama", "10:30 PM"});
        movies.push_back({6, "Avatar: The Way of Water", "Adventure/Fantasy", "12:00 PM"});

        // Initialize food menu
        menu.push_back({1, "Popcorn", 100});
        menu.push_back({2, "Cold Drink", 80});
        menu.push_back({3, "Nachos", 120});
        menu.push_back({4, "Burger", 150});
        menu.push_back({5, "Pizza Slice", 200});
        menu.push_back({6, "French Fries", 90});
        menu.push_back({7, "Ice Cream", 60});
        menu.push_back({8, "Coffee", 70});
        menu.push_back({9, "Sandwich", 110});
        menu.push_back({10, "Chocolate Bar", 50});

        // Initialize all seats as available
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                seats[i][j] = 'O';
    }

    void showMovies() {
        cout << "\n========== AVAILABLE MOVIES ==========\n";
        for (auto &m : movies) {
            cout << setw(2) << m.id << ". " << m.name 
                 << " (" << m.genre << ") - " << m.time << endl;
        }
    }

    void selectMovie() {
        int choice;
        cout << "\nEnter movie ID to select: ";
        cin >> choice;

        for (auto &m : movies) {
            if (m.id == choice) {
                selectedMovie = m;
                cout << "\nYou selected: " << m.name 
                     << " (" << m.genre << ") at " << m.time << endl;
                return;
            }
        }
        cout << "Invalid choice! Try again.\n";
        selectMovie();
    }

    void displaySeats() {
        cout << "\n========== SEAT LAYOUT (O = Available, X = Booked) ==========\n\n   ";
        for (int j = 0; j < COLS; j++)
            cout << setw(2) << j + 1 << " ";
        cout << endl;

        for (int i = 0; i < ROWS; i++) {
            cout << setw(2) << i + 1 << " ";
            for (int j = 0; j < COLS; j++) {
                cout << " " << seats[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bookSeat() {
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

            if (seats[row-1][col-1] == 'X') {
                cout << "Seat already booked! Choose another.\n";
                k--;
            } else {
                seats[row-1][col-1] = 'X';
                bookedSeats.push_back("Row " + to_string(row) + " Col " + to_string(col));
                totalAmount += TICKET_PRICE;
                cout << "Seat booked successfully!\n";
            }
        }
    }

    void showMenu() {
        cout << "\n===== Food & Beverages Menu =====\n";
        for (auto &f : menu) {
            cout << f.id << ". " << f.name << " - Rs. " << f.price << endl;
        }
    }

    void orderFood() {
        char choice;
        cout << "\nDo you want to order food? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            int foodId, qty;
            do {
                showMenu();
                cout << "Enter food ID to order (0 to finish): ";
                cin >> foodId;

                if (foodId == 0) break;

                cout << "Enter quantity: ";
                cin >> qty;

                bool found = false;
                for (auto &f : menu) {
                    if (f.id == foodId) {
                        for (int i = 0; i < qty; i++)
                            orderedFood.push_back(f);
                        totalAmount += f.price * qty;
                        cout << f.name << " x" << qty << " added to order.\n";
                        found = true;
                        break;
                    }
                }

                if (!found) cout << "Invalid food ID!\n";

            } while (true);
        }
    }

    void generateBill() {
        cout << "\n=================== TICKET ===================\n";
        cout << "Movie: " << selectedMovie.name 
             << " (" << selectedMovie.genre << ")\n";
        cout << "Show Time: " << selectedMovie.time << "\n";
        cout << "Seats: ";
        for (auto &s : bookedSeats) cout << s << "  ";
        cout << "\nTicket Price: Rs. " << bookedSeats.size() * TICKET_PRICE << endl;

        if (!orderedFood.empty()) {
            cout << "\nFood Ordered:\n";
            for (auto &f : orderedFood) {
                cout << "- " << f.name << " Rs. " << f.price << endl;
            }
        }

        cout << "\n----------------------------------------------\n";
        cout << "TOTAL AMOUNT: Rs. " << totalAmount << endl;
        cout << "==============================================\n";
    }
};

int main() {
    Theatre t;
    t.showMovies();
    t.selectMovie();
    t.displaySeats();
    t.bookSeat();
    t.orderFood();
    t.generateBill();
    return 0;
}
