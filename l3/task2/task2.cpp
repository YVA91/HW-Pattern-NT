#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Observable {
private:
    std::vector<Observer*> observers;

   void clean() {
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [](Observer* obs) { return obs == nullptr; }),
            observers.end());
    }

public:

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            *it = nullptr;
            clean();
        }
    }

    void warning(const std::string& message) const {
        for (auto obs : observers) {
            if (obs) obs->onWarning(message);
        }
    }

    void error(const std::string& message) const {
        for (auto obs : observers) {
            if (obs) obs->onError(message);
        }
    }

    void fatalError(const std::string& message) const {
        for (auto obs : observers) {
            if (obs) obs->onFatalError(message);
        }
    }
};

class WarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << message << std::endl;
    }
};


class ErrorObserver : public Observer {
private:
    std::string filePath;

public:
    explicit ErrorObserver(const std::string& path) : filePath(path) {}

    void onError(const std::string& message) override {
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << message << std::endl;
        }
    }
};

class FatalErrorObserver : public Observer {
private:
    WarningObserver consoleObserver;
    ErrorObserver fileObserver;  

public:
    explicit FatalErrorObserver(const std::string& filePath)
        : fileObserver(filePath) {
    } 

    void onFatalError(const std::string& message) override {
        consoleObserver.onWarning(message);  
        fileObserver.onError(message);   
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Observable log;

    WarningObserver consoleObserver;
    ErrorObserver fileObserver("G:\\РС\\C++\\Project\\log2.txt");
    FatalErrorObserver fatalObserver("G:\\РС\\C++\\Project\\log3.txt");

    log.addObserver(&consoleObserver);
    log.addObserver(&fileObserver);
    log.addObserver(&fatalObserver);

    log.warning("Предупреждение");
    log.error("Ошибка");
    log.fatalError("Фатальная ошибка");

    log.removeObserver(&fileObserver);

    log.warning("Повторное предупреждение!");
    log.error("Повторная ошибка!");

    return 0;
}