#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>  // Для обработки исключений

bool isSimpleNumber(int number);

int main(int argc, char* argv[]) {
    // checking Enter
    int number;
    while (true) {
        try {
            number = std::stoi(argv[1]); // String to number
            break; // Если преобразование прошло успешно, выходим из цикла
        } catch (const std::invalid_argument&) {
            std::cout << "Error! Invalid input. Repeat enter a number: ";
        } catch (const std::out_of_range&) {
            std::cout << "The number is out of range. Repeat enter a number: ";
        }
    }

    std::cout << "Is the number prime? " << isSimpleNumber(number) << std::endl;
}

bool isSimpleNumber(int number) {
    if (number < 2) return false;
    for (int i = 2; i < number; i++) {
        if ((number % i) == 0) {
            return false;
        }
    }
    return true;
}
