#include <iostream>
#include <vector>
#include <stack>

class CinemaQueue {
private:
    std::vector<std::string> queue;

public:
    void enqueue(const std::string& customer) {
        queue.push_back(customer);
    }

    std::string dequeue() {
        std::string customer = queue.front();
        queue.erase(queue.begin());
        return customer;
    }

    bool empty() const {
        return queue.empty();
    }
};


class SeatsOption {
private:
    std::stack<int> availableSeats;
    int cols;
public:
    SeatsOption(int rows, int cols) {
        // Inisialisasi availableSeats dari E5 hingga A1
        for (int i = rows * cols; i >= 1; --i) {
            availableSeats.push(i);
        }
    }

    std::string bookSeat() {
        if (availableSeats.empty()) {
            return "No seats available.";
        }

        int seatCode = availableSeats.top();
        availableSeats.pop();

        int row = (seatCode - 1) / 5 + 'A';
        int column = (seatCode - 1) % 5 + '1';

        return std::string(1, row) + std::string(1, column);
    }
};



int main() {
    CinemaQueue queue;
    SeatsOption seatsOption(5, 5);

    std::string input;
    while (std::cin >> input) {
        queue.enqueue(input);
        std::cout << input << " - " << seatsOption.bookSeat() << std::endl;
    }

    return 0;
}
