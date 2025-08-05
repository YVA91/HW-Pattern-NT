#include <iostream>
#include <fstream>
#include <string>
#include <clocale> 

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
    ConsoleLogCommand() {
        setlocale(LC_ALL, "Russian"); 
    }
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class FileLogCommand : public LogCommand {
private:
    std::string fileLog;
public:
    explicit FileLogCommand(const std::string& file_log) : fileLog (file_log) {}

    void print(const std::string& message) override {
        std::ofstream file(fileLog, std::ios::app);
        if (file.is_open()) {
            file << message << std::endl;
        }
        else {
            std::cerr << "Failed to open file: " << fileLog << std::endl;
        }
    }
};

void oid_print(LogCommand& log, const std::string& message) {
    log.print(message);
}

int main() {
  
    ConsoleLogCommand console_log;
    oid_print(console_log, "Запишем это в консоль");
    FileLogCommand file_log("G:\\РС\\C++\\Project\\log.txt");
    oid_print(file_log, "Запишем это в файл");
    return 0;
}