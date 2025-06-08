#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <filesystem>

#include <windows.h>

std::vector<std::pair<int, std::string>> getTags();
std::pair<int, std::string> getTagById(const std::vector<std::pair<int, std::string>>& tags, int searchId);
int getHistory();

void askForTag();
void askForDuration(std::string& tag);

void customTag();
void existingTag(std::string& value);

void confirmPrompt(std::string& tag, int& minutes);
void printSeparator();

void runTimer(std::string& tag, int& minutes);
void endTimer();

int main() {
    SetConsoleOutputCP(CP_UTF8);

    askForTag();

    return 0;
}

std::vector<std::pair<int, std::string>> getTags() {
    std::ifstream file("data/tags.csv");
    std::vector<std::pair<int, std::string>> tags;

    if (!file.is_open()) {
        std::cerr << "Unable to load file tags.csv" << std::endl;
    }

    std::string line;

    // pula o header do .csv
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string idStr, tag;

        if (std::getline(iss, idStr, ',') && std::getline(iss, tag)) {
            int id = std::stoi(idStr);
            tags.emplace_back(id, tag);
        }
    }

    return tags;
}

std::pair<int, std::string> getTagById(const std::vector<std::pair<int, std::string>>& tags, int searchId) {
    for (const auto& [id, tag] : tags) {
        if (id == searchId) {
            return {id, tag};
        }
    }
    return {-1, ""};
}

int getHistory() {
    // TODO: adicionar leitura do arquivo history.csv
    return 0;
}

void printSeparator() {
    std::cout << "\n**********************************************\n\n";
}

void askForTag() {
    int number{};

    std::vector<std::pair<int, std::string>> tags = getTags();

    printSeparator();

    std::cout << "From the list of tags bellow...\n\n";

    std::cout << "[" << 0 << "] " << "I'd like a custom one..." << std::endl;

    for (const auto& [id, tag] : tags) {
        std::cout << "[" << id << "] " << tag << std::endl;
    }

    do {
        std::cout << "\n>> Select a tag by its number: ";
        std::cin >> number;
    } while (number < 0 || number > tags.size());

    std::pair<int, std::string> selectedTag = getTagById(tags, number);

    number == 0 ? customTag() : existingTag(selectedTag.second);
}

void askForDuration(std::string& tag) {
    int minutes{};

    do {
        std::cout << "\n>> How many minutes do you want to focus on: ";
        std::cin >> minutes;
    } while (minutes <= 0);

    confirmPrompt(tag, minutes);
}

void confirmPrompt(std::string& tag, int& minutes) {
    char prompt{};

    do {
        std::cout << "Do you want to focus on <" << tag << "> for " << minutes << " min? [y/n]: ";
        std::cin >> prompt;
    } while (prompt != 'y' && prompt != 'n');

    if (prompt == 'y') {
        runTimer(tag, minutes);
    } else {
        askForTag();
    }
}

void customTag() {
    std::string newTag{};

    printSeparator();

    std::cout << "You're creating a new tag." << std::endl;

    // FIXME: print duplicado
    do {
        std::cout << "\n>> Type the name: ";
        std::getline(std::cin, newTag);
    } while (newTag.empty());

    std::cout << "\nTag <" << newTag << "> created successfully!" << std::endl;

    askForDuration(newTag);
}

void existingTag(std::string& value) {
    std::cout << value << std::endl;
}

void runTimer(std::string& tag, int& minutes) {
    endTimer();
}

void endTimer() {
    // alarm sound starts ringing
}