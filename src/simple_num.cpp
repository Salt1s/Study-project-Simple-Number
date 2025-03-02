#include <iostream>
#include <limits>

bool isSimpleNumber(int number);

int main() {
    int number;
    std::cout << "Enter a number:  ";

    // checking Enter
    while (true) {
        std::string input;
        std::cin >> input;
        
        bool isInteger = true;

        if (input[0] == '-' && input.size()>1) {
            for (size_t i =1; i < input.size(); i++) {
                //checking every char in string 0-9 and first minus
                if (!isdigit(input[i])) { 
                    isInteger = false;
                    break;
                }
            }
        }
        else {
        for (char c : input) {
            //checking every char in string 0-9 and first minus
            if (!isdigit(c)) { 
                isInteger = false;
                break;
            }
        }
        }
        
        if (!isInteger) {
            std::cout << "Error! Repeat enter a number: ";
            continue;
        }
        
        try {
            number = std::stoi(input); //String to number
            break;
        } catch (const std::out_of_range&) {
            std::cout << "The number out of range. Repeat enter a number: ";
        }
    }
    std::cout << isSimpleNumber(number) << std::endl;
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
