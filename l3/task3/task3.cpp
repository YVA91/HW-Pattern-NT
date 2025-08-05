#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <memory>


enum class Type {
    WARNING,
    ERROR,
    FATAL_ERROR,
    UNKNOWN
};


class LogMessage {
public:
    LogMessage(Type type, const std::string& message)
        : typeErr(type), messageErr(message) {
    }

    Type type() const { return typeErr; }
    const std::string& message() const { return messageErr; }

private:
    Type typeErr;
    std::string messageErr;
};


class Handler {
public:
    virtual ~Handler() = default;
    void setNext(std::shared_ptr<Handler> next) { nextErr = next; }
    virtual void handle(const LogMessage& msg) = 0;

protected:
    void passToNext(const LogMessage& msg) {
        if (nextErr) {
            nextErr->handle(msg);
        }
    }

private:
    std::shared_ptr<Handler> nextErr;
};

class FatalErrorHandler : public Handler {
public:
    void handle(const LogMessage& msg) override {
        if (msg.type() == Type::FATAL_ERROR) {
            throw std::runtime_error("Фатальная ошибка: " + msg.message());
        }
        passToNext(msg);
    }
};

class ErrorHandler : public Handler {
public:
    explicit ErrorHandler(const std::string& filePath)
        : filePath_(filePath) {
    }

    void handle(const LogMessage& msg) override {
        if (msg.type() == Type::ERROR) {
            std::ofstream file(filePath_, std::ios::app);
            if (file) {
                file << "Ошибка" << msg.message() << std::endl;
            }
            else {
                throw std::runtime_error("Не удалось откыть файл: " + filePath_);
            }
            return;
        }
        passToNext(msg);
    }

private:
    std::string filePath_;
};


class WarningHandler : public Handler {
public:
    void handle(const LogMessage& msg) override {
        if (msg.type() == Type::WARNING) {
            std::cout << "Предупреждение: " << msg.message() << std::endl;
            return;
        }
        passToNext(msg);
    }
};


class UnknownMessageHandler : public Handler {
public:
    void handle(const LogMessage& msg) override {
        if (msg.type() == Type::UNKNOWN) {
            throw std::runtime_error("Неизвестное сообщение: " + msg.message());
        }
        passToNext(msg);
    }
};


std::shared_ptr<Handler> createChain(const std::string& errorLogPath) {
    auto fatalHandler = std::make_shared<FatalErrorHandler>();
    auto errorHandler = std::make_shared<ErrorHandler>(errorLogPath);
    auto warningHandler = std::make_shared<WarningHandler>();
    auto unknownHandler = std::make_shared<UnknownMessageHandler>();

    fatalHandler->setNext(errorHandler);
    errorHandler->setNext(warningHandler);
    warningHandler->setNext(unknownHandler);

    return fatalHandler;
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        auto handlerChain = createChain("G:\\РС\\C++\\Project\\Pattern\log.txt");


        handlerChain->handle(LogMessage(Type::WARNING, "Предупреждение"));
        handlerChain->handle(LogMessage(Type::ERROR, "Ошибка"));
        handlerChain->handle(LogMessage(Type::UNKNOWN, "Неизвестное сообщение"));
        handlerChain->handle(LogMessage(Type::FATAL_ERROR, "Фатальная ошибка"));
    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    return 0;
}
