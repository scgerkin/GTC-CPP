#include <iostream>
#include <regex>
#include "StringTools.h"
#include "QuizCreation.h"
#include "QuestionMap.h"
#include "QuizGame.h"

#define DEBUGGING 0 // for allowing a quick quiz with few values for testing

/**
 * Main entry point for demonstrating the QuizGame class.
 * Asks the user to select a quiz type.
 */
void initAndGo() {
   determineQuizType();
}

/**
 * Gets the type of quiz the user wants to attempt and starts that quiz.
 */
void determineQuizType() {
    displayMenu();
    int selection = getMenuEntry();

    switch (selection) {
        case 1:
            stateCapitalQuiz();
            break;
        case 2:
            countryCapitalQuiz();
            break;
        case 3:
            return;
#if DEBUGGING
        case 0:
            debugQuiz();
            break;
#endif DEBUGGING
        default:
            break;
    }
}

/**
 * Displays a menu of options to the user.
 */
void displayMenu() {
    std::cout << "What quiz would you like to play?\n"
              << "1. State Capitals\n"
              << "2. Country Capitals\n"
              << "3. Exit\n"
              << "Enter your choice:\n>> ";
}

/**
 * Gets a menu selection from the user as an integer value.
 * @return The selection as an integer.
 */
int getMenuEntry() {
    std::string input;
    std::getline(std::cin, input);
    input = toLower(trim(input));

    int selection;

    std::regex p("(^[0-9]+[0-9]*$)");
    if (std::regex_match(input, p)) {
        selection = std::stoi(input);
    }
#if DEBUGGING
    if (selection >= 0 && selection < 4) {
        return selection;
    }
#endif
    if (selection > 0 && selection < 4) {
        return selection;
    }
    // if we get here, selection is invalid
    invalidSelection();
    std::cout << "\n";
    displayMenu();
    return getMenuEntry();
}

/**
 * Initializes a QuizGame with state capital quiz questions and starts it.
 */
void stateCapitalQuiz() {
    std::ifstream inputFile;
    inputFile.open("../state_capitals.csv");
    QuestionMap questionSet(inputFile);
    startQuiz(questionSet);
}

/**
 * Initializes a QuizGame with country capital quiz questions and starts it.
 */
void countryCapitalQuiz() {
    std::ifstream inputFile;
    inputFile.open("../country_capitals.csv");
    QuestionMap questionSet(inputFile);
    startQuiz(questionSet);
}

/**
 * For testing a quick quiz.
 */
void debugQuiz() {
    std::map<std::string, std::string> map;
    map.emplace("One", "One");
    map.emplace("Two", "Two");
    map.emplace("Three", "Three");
    QuestionMap questionSet(map, "Question", "Answer");
    startQuiz(questionSet);
}

/**
 * Displays information if a selection is invalid.
 */
void invalidSelection() {
    std::cout << "Sorry, that was not a recognized selection.\n";
    std::cout << "\n";
}

/**
 * Starts a quiz with the given questions.
 * @param questions The questions we want to start a quiz with.
 */
void startQuiz(const QuestionMap &questions) {
    try {
        QuizGame quizGame(questions);
    }
    catch (const std::exception &ex) {
        exit(0);
    }

    std::cout << "Would you like to play another quiz?\n";
    if (getYesNo()) {
        determineQuizType();
    }
}

/**
 * Gets a yes or no entry input from the user.
 * @return True if yes.
 */
bool getYesNo() {
    std::regex pattern("Y|N", std::regex_constants::icase);
    std::cout << "Enter 'Y' or 'N':\n>> ";
    std::string userInput;
    std::getline(std::cin, userInput);
    std::cout << "\n";
    userInput = toLower(trim(userInput));

    if (std::regex_match(userInput, pattern)) {
        return userInput == "y";
    }
    else {
        std::cout << "Sorry, That entry was not recognized.\n";
        return getYesNo();
    }
}