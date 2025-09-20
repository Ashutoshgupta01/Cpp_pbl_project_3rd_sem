# Cpp_pbl_project_3rd_sem

This is a simple command-line interface (CLI) application developed in C++ that simulates a movie theatre booking system. It allows users to go through the process of selecting a movie, booking seats, and ordering from a food menu before generating a final bill.

## Features

*   **List Movies**: Displays a list of available movies with their genre and showtimes.
*   **Select Movie**: Allows the user to choose a movie to watch.
*   **Seat Management**:
    *   Displays a 15x15 seating grid, showing available ('O') and booked ('X') seats.
    *   Allows booking of one or more seats by specifying row and column numbers.
*   **Food & Beverage Ordering**:
    *   Presents a menu of available food and beverage items.
    *   Allows users to add items to their order.
*   **Bill Generation**: Generates a final ticket that includes details of the selected movie, booked seats, food ordered, and the total amount due.

## Getting Started

### Prerequisites

You will need a C++ compiler installed on your system (e.g., g++, Clang).

### Compilation and Execution

1.  Clone the repository:
    ```sh
    git clone https://github.com/Ashutoshgupta01/Cpp_pbl_project_3rd_sem.git
    cd Cpp_pbl_project_3rd_sem
    ```

2.  Compile the source files using your C++ compiler. For example, with `g++`:
    ```sh
    g++ main.cpp -o theatre_booking
    ```

3.  Run the executable:
    ```sh
    ./theatre_booking
    ```

4.  Follow the on-screen prompts to book your movie ticket.

## Code Structure

*   `main.cpp`: This file contains the main logic of the application. It includes the `Theatre` class which manages movies, seats, menus, and the entire booking process from start to finish. The `main()` function orchestrates the user interaction flow.
*   `Structures.cpp`: Defines the data structures `Movie` and `FoodItem`, which are used throughout the application to model the entities. It also defines constants for the seating layout and ticket price.
*   `LICENSE`: The project is licensed under the GNU General Public License v3.0.