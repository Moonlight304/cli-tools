#include <string>
#include <fstream>

enum LogEvent {
    INFO,
    WARN,
    ERROR
};

class Logger {
    public:
    explicit Logger(const std::string &path);

    void log(const std::string &content, LogEvent logEvent);

    private:
    std::ofstream file;
    LogEvent logEvent;
};