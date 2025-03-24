#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>  // Для обработки исключений
#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/counter.h>
#include <prometheus/histogram.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace prometheus;

bool isSimpleNumber(int number);

int main(int argc, char* argv[]) {
    // Проверка на количество аргументов
    if (argc < 2) {
        std::cerr << "Error! Please provide a number as an argument." << std::endl;
        return 1;
    }

    // Создание Exposer для Prometheus
    Exposer exposer{"0.0.0.0:8080"}; // Ожидаем, что Prometheus будет подключаться по порту 8080
    auto registry = std::make_shared<Registry>();

    // Создание метрик
    auto& request_counter_family = BuildCounter()
        .Name("prime_number_requests_total")
        .Help("Total number of requests to check if a number is prime")
        .Register(*registry);
    auto& request_counter = request_counter_family.Add({});

    std::vector<double> bucket_boundaries = {0.1, 0.2, 0.5, 1.0, 2.0, 5.0}; // Для гистограммы
    auto& request_time_family = BuildHistogram()
        .Name("prime_number_request_duration_seconds")
        .Help("Histogram of request durations to check if a number is prime")
        .Register(*registry);
    auto& request_time = request_time_family.Add({}, bucket_boundaries);

    exposer.RegisterCollectable(registry);  // Регистрируем collectable для Prometheus

    // Главный цикл программы
    int number;
    while (true) {
        try {
            number = std::stoi(argv[1]); // Преобразуем строку в число
            break; // Выход из цикла после успешной конвертации
        } catch (const std::invalid_argument&) {
            std::cout << "Error! Invalid input. Repeat enter a number: ";
        } catch (const std::out_of_range&) {
            std::cout << "The number is out of range. Repeat enter a number: ";
        }
    }

    // Замер времени выполнения функции isSimpleNumber
    auto start = chrono::high_resolution_clock::now();
    bool result = isSimpleNumber(number);
    auto end = chrono::high_resolution_clock::now();

    // Вычисляем продолжительность запроса
    double duration = chrono::duration<double>(end - start).count();
    request_time.Observe(duration);  // Записываем длительность в гистограмму
    request_counter.Increment();     // Увеличиваем счетчик запросов

    // Выводим результат
    if (result) {
        std::cout << "Yes, the number " << number << " is prime." << std::endl;
    } else {
        std::cout << "No, the number " << number << " is not prime." << std::endl;
    }

    std::cout << "Request duration: " << duration << " seconds." << std::endl;

    // Пауза перед следующим запросом (можно изменить по необходимости)
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    return 0;
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
