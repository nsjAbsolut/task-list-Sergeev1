#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <sstream>   // Для безопасного парсинга ввода
#include <windows.h> // Для настройки кодировки

// Класс для управления списком задач
class TaskManager {
private:
    std::vector<std::string> taskList; // Хранилище задач

    // Приватный метод для очистки буфера ввода
    void clearInputStream() {
        std::cin.ignore(10000, '\n');
    }

    // Приватный метод для безопасного получения целого числа
    int getSafeIntInput() {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        int value;
        if (ss >> value) {
            return value;
        }
        return -1; // Возвращаем -1, если введено не число
    }

public:
    // Метод для отображения интерфейса
    void renderInterface() {
        std::cout << "\n---------------------------------\n";
        std::cout << "       МЕНЕДЖЕР ЗАДАЧ\n";
        std::cout << "---------------------------------\n";
        std::cout << " [1] Добавить новую задачу\n";
        std::cout << " [2] Просмотреть все задачи\n";
        std::cout << " [3] Удалить задачу по номеру\n";
        std::cout << " [4] Завершить работу\n";
        std::cout << "---------------------------------\n";
        std::cout << " Ваш выбор: ";
    }

    // Метод добавления задачи
    void createTask() {
        std::cout << "Введите описание задачи: ";
        std::string newTask;
        std::getline(std::cin, newTask);

        if (newTask.empty()) {
            std::cout << "[!] Ошибка: описание не может быть пустым.\n";
        }
        else {
            taskList.push_back(newTask);
            std::cout << "[+] Задача успешно сохранена.\n";
        }
    }

    // Метод вывода всех задач
    void printAllTasks() {
        if (taskList.empty()) {
            std::cout << "[-] Список задач пуст.\n";
            return;
        }

        std::cout << "\n--- Текущие задачи ---\n";
        for (size_t i = 0; i < taskList.size(); ++i) {
            std::cout << " " << i + 1 << ". " << taskList[i] << "\n";
        }
        std::cout << "----------------------\n";
    }

    // Метод удаления задачи
    void removeTask() {
        printAllTasks();
        if (taskList.empty()) return;

        std::cout << "Укажите номер задачи для удаления: ";
        int index = getSafeIntInput();

        if (index < 1 || index > static_cast<int>(taskList.size())) {
            std::cout << "[!] Ошибка: задачи с таким номером не существует.\n";
            return;
        }

        // Используем итераторы для удаления (другой стиль программирования)
        auto it = taskList.begin() + (index - 1);
        std::string deletedTask = *it;
        taskList.erase(it);

        std::cout << "[-] Задача \"" << deletedTask << "\" удалена.\n";
    }

    // Главный цикл программы
    void run() {
        while (true) {
            renderInterface();
            int choice = getSafeIntInput();

            switch (choice) {
            case 1:
                createTask();
                break;
            case 2:
                printAllTasks();
                break;
            case 3:
                removeTask();
                break;
            case 4:
                std::cout << "Завершение работы программы...\n";
                return;
            default:
                std::cout << "[!] Ошибка: выберите пункт от 1 до 4.\n";
            }
        }
    }
};

int main() {
    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TaskManager app; // Создаем объект класса
    app.run();       // Запускаем главный цикл

    return 0;
}