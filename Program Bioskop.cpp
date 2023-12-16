#include <iostream>
#include <vector>
#include <unordered_set>

class CinemaQueue {
private:
    std::vector<std::pair<std::string, std::string>> customerSeats;

public:
    void enqueue(const std::string& customer, const std::string& seat) {
        customerSeats.push_back(std::make_pair(customer, seat));
    }

    std::string dequeue() {
        if (!customerSeats.empty()) {
            std::string customer = customerSeats.back().first;
            customerSeats.pop_back();
            return customer;
        }
        return "";
    }

    bool empty() const {
        return customerSeats.empty();
    }

    void printCustomerSeats() const {
        if (customerSeats.empty()) {
            std::cout << "No customer orders." << std::endl;
        } else {
            std::cout << "Customer Orders:" << std::endl;
            for (const auto& order : customerSeats) {
                std::cout << "Customer: " << order.first << ", Seat: " << order.second << std::endl;
            }
        }
    }

    size_t size() const {
        return customerSeats.size();
    }

    void editOrder(size_t index, const std::string& newSeat) {
        if (index < customerSeats.size()) {
            customerSeats[index].second = newSeat;
        }
    }

    void deleteOrder(size_t index) {
        if (index < customerSeats.size()) {
            customerSeats.erase(customerSeats.begin() + index);
        }
    }
};

class SeatsOption {
private:
    std::unordered_set<std::string> bookedSeats;

public:
    std::string bookSeat() {
        std::string seat;

        std::cout << "Enter seat choice (e.g., A1): ";
        std::cin >> seat;

        if (bookedSeats.find(seat) != bookedSeats.end()) {
            std::cout << "Seat " << seat << " is already booked. Please choose another seat." << std::endl;
            return "";
        }

        bookedSeats.insert(seat);
        return seat;
    }

    bool isSeatAvailable(const std::string& seat) {
        return bookedSeats.find(seat) == bookedSeats.end();
    }
};

void addCustomer(CinemaQueue& queue, SeatsOption& seatsOption) {
    std::string customerName;
    std::cout << "Enter customer name: ";
    std::cin >> customerName;

    std::string seat = seatsOption.bookSeat();
    if (seat.empty()) {
        std::cout << "No available seats. Customer " << customerName << " cannot be added." << std::endl;
        return;
    }

    queue.enqueue(customerName, seat);
    std::cout << "Customer " << customerName << " added to the queue with seat " << seat << "." << std::endl;
}

void orderSeat(CinemaQueue& queue, SeatsOption& seatsOption) {
    if (queue.empty()) {
        std::cout << "No customers in the queue." << std::endl;
        return;
    }

    std::string customer = queue.dequeue();
    std::cout << "Customer: " << customer << std::endl;

    std::string seat = seatsOption.bookSeat();
    if (seat.empty()) {
        queue.enqueue(customer, "");
        return;
    }

    std::cout << "Seat " << seat << " booked for " << customer << std::endl;
    queue.enqueue(customer, seat);
}

void printCustomerOrders(const CinemaQueue& queue) {
    queue.printCustomerSeats();
}

void editCustomerOrder(CinemaQueue& queue) {
    size_t index;
    std::string newSeat;

    std::cout << "Enter the index of the customer order to edit: ";
    std::cin >> index;

    if (index < queue.size()) {
        std::cout << "Enter the new seat choice: ";
        std::cin >> newSeat;

        queue.editOrder(index, newSeat);
        std::cout << "Order updated successfully." << std::endl;
    } else {
        std::cout << "Invalid index." << std::endl;
    }
}

void deleteCustomerOrder(CinemaQueue& queue) {
    size_t index;
    std::cout << "Enter the index of the customer order to delete: ";
    std::cin >> index;

    if (index < queue.size()) {
        queue.deleteOrder(index);
        std::cout << "Order deleted successfully." << std::endl;
    } else {
        std::cout << "Invalid index." << std::endl;
    }
}

void runCinemaProgram() {
    CinemaQueue queue;
    SeatsOption seatsOption;

    int choice;
    while (true) {
        std::cout << "1. Add Customer and Order Seat" << std::endl;
        std::cout << "2. Print Customer Orders" << std::endl;
        std::cout << "3. Edit Customer Order" << std::endl;
        std::cout << "4. Delete Customer Order" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addCustomer(queue, seatsOption);
                break;
            case 2:
                printCustomerOrders(queue);
                break;
            case 3:
                editCustomerOrder(queue);
                break;
            case 4:
                deleteCustomerOrder(queue);
                break;
            case 5:
                std::cout << "Exiting program." << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

int main() {
    runCinemaProgram();
    return 0;
}
