#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include "logger.h"
using namespace std;

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), [](unsigned char c) {
        return std::isspace(c);
    }));
}

void rtrim(std::string &s) {
    s.erase(std::find_if_not(s.rbegin(), s.rend(), [](unsigned char c) {
        return std::isspace(c);
    }).base(), s.end());
}

void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

int main (int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Only 1 argument of directory path is allowed" << endl;
        cout << "Usage: " << endl;
        cout << "\t./app \"./\" " << endl;
        cout << "\t./app \"/home/user/Desktop\" " << endl;

        exit(1);
    }

    string DIR_PATH = argv[1];

    trim(DIR_PATH);
    if (DIR_PATH == "") {
        cout << "Invalid Directory path, try again." << endl;

        exit(1);
    }

    Logger logger("./log.txt");

    int fd = inotify_init();
    if (fd == -1) {
        cout << "Error initializing inotify" << endl;
        exit(1);
    }

    int watch_descriptor = inotify_add_watch(fd, DIR_PATH.c_str(), 
            IN_CREATE | IN_MODIFY | IN_DELETE | IN_CLOSE_WRITE | IN_MOVED_FROM | IN_MOVED_TO
        );
    if (watch_descriptor == -1) {
        cout << "Error adding watch, enter a valid directory!" << endl;

        exit(1);
    }

    
    cout << "WATCHING DIRECTOR FOR CHANGES : " << DIR_PATH << endl;
    
    char buffer[4096];
    while (true) {
        int length = read(fd, buffer, sizeof(buffer));
        if (length <= 0) continue;

        int i = 0;
        while (i < length) {
            inotify_event *event = (inotify_event*) &buffer[i];

            std::string name = (event->len > 0) ? event->name : "[dir]";

            if (name == "log.txt") {
                i += sizeof(inotify_event) + event->len;
                continue;
            }

            if (event->mask & IN_CREATE)
                logger.log("CREATE : " + name, INFO);

            if (event->mask & IN_MODIFY)
                logger.log("MODIFY : " + name, INFO);

            if (event->mask & IN_DELETE)
                logger.log("DELETE : " + name, WARN);

            if (event->mask & IN_CLOSE_WRITE)
                logger.log("CLOSE_WRITE : " + name, INFO);

            if (event->mask & IN_MOVED_FROM)
                logger.log("MOVED_FROM : " + name, INFO);

            if (event->mask & IN_MOVED_TO)
                logger.log("MOVED_TO : " + name, INFO);

            i += sizeof(inotify_event) + event->len;
        }

    }
}