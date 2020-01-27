#include "QuizGame.h"
#include <utility>
#include <regex>
#include <random>
#include <algorithm>

/**
 * The constructor initializes the QuestionMap we are working with and starts
 * the quiz.
 * @param questions The questions we are to use for the game.
 */
QuizGame::QuizGame(QuestionMap questions) : questions(std::move(questions)) {
    prepareQuestions();
    displayStartMsg();
}

/**
 * Gets our list of questions and shuffles them using a Mersenne twister
 * algorithm.
 */
void QuizGame::prepareQuestions() {
    questionsToAsk = questions.getListOfQuestionParts();
    std::random_device rd;
    std::mt19937 seed(rd());
    std::shuffle(questionsToAsk.begin(),questionsToAsk.end(), seed);
}

/**
 * Displays the starting message information for the quiz.
 */
void QuizGame::displayStartMsg() {
    show("Welcome to the " + questions.getQuestionTypeName() + " quiz.");
    show("This quiz will test your knowledge of " + questions.getAnswerTypeName() + "s.");
    show("You can exit the quiz at any time by typing \""+QUIT_STR+"\".");
    show("Are you ready...?");
    if (getYesNo()) {
        start();
    }
}

/**
 * Notes the beginning time of the quiz and asks questions until there are no
 * more questions to ask.
 */
void QuizGame::start() {
    quizStartTime = std::chrono::high_resolution_clock::now();
    while (!questionsToAsk.empty()) {
        askQuestion();
        showStatistics();
    }
}

/**
 * Asks the next question in the queue and moves it to the appropriate correct
 * or incorrect queue after answered.
 */
void QuizGame::askQuestion() {
    std::string question = questionsToAsk.front();
    questionsToAsk.pop_front();
    show("What is the " + questions.getAnswerTypeName() + " of " + question + "?");
    std::string answer = guess();

    if (questions.checkGuess(question, answer)) {
        answeredCorrectly(question);
    }
    else {
        notAnsweredCorrectly(question);
    }
}

/**
 * Handles correctly answered questions.
 * @param question The question the user answered correctly.
 */
void QuizGame::answeredCorrectly(const std::string &question) {
    answeredCorrectlyList.emplace_back(question);
    show("That is correct!\n");
}

/**
 * Handles incorrectly answered questions.
 * @param question The question the user answered incorrectly.
 */
void QuizGame::notAnsweredCorrectly(const std::string &question) {
    notAnsweredCorrectlyList.emplace_back(question);
    show("Sorry, that was not correct.");
    show("The correct answer was: " + questions.getAnswer(question) + ".\n");
}

/**
 * Shows the current game statistics including time played and number of questions
 * answered correctly/incorrectly.
 */
void QuizGame::showStatistics() {
    int totalCorrect = answeredCorrectlyList.size();
    int totalNotCorrect = notAnsweredCorrectlyList.size();
    int totalQuestionsAsked = totalCorrect + totalNotCorrect;

    showCurrentPlayTime();

    std::string msg =
            "Of " + std::to_string(totalQuestionsAsked) +
            " questions asked, you have answered:\nCorrect: " +
            std::to_string(totalCorrect) + "\nIncorrect: "
            + std::to_string(totalNotCorrect);
    show(msg);
}

/**
 * Displays the current time played. The time played may be off by at most 1
 * second any time this function is called but this is not cumulative as the
 * amount of time played is recalculated every time this function is called.
 */
void QuizGame::showCurrentPlayTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now - quizStartTime;
    // could be off by ~1 second due to truncation but that is insignificant
    int seconds = floor(duration.count() * .000000001);
    int minutes = 0;

    if (seconds >= 60) {
        minutes = seconds / 60;
        seconds %= 60;
    }
    std::string msg = "Current play time: " +
            std::to_string(minutes) + " minutes and " +
            std::to_string(seconds) + " seconds.";
    show(msg);
}

/**
 * Shows a given string to the user.
 * @param msg
 */
void QuizGame::show(const std::string &msg) const {
    std::cout << msg << std::endl;
}

/**
 * Gets a guess from the user.
 * @return The user input.
 */
std::string QuizGame::guess() {
    std::string userInput;
    std::cout << "Enter your guess:\n>> ";
    std::getline(std::cin, userInput);
    std::cout << "\n";
    userInput = toLower(trim(userInput));
    if (userInput == QUIT_STR) {
        quit();
    }
    return userInput;
}

/**
 * Gets yes or not input from the user.
 * @return True if yes.
 */
bool QuizGame::getYesNo() {
    std::regex pattern("Y|N", std::regex_constants::icase);
    std::cout << "Enter 'Y' or 'N':\n>> ";
    std::string userInput;
    std::getline(std::cin, userInput);
    std::cout << "\n";
    userInput = toLower(trim(userInput));

    if (userInput == QUIT_STR) {
        quit();
    }

    if (std::regex_match(userInput, pattern)) {
        return userInput == "y";
    }
    else {
        std::cout << "Sorry, That entry was not recognized.\n";
        return getYesNo();
    }
}

/**
 * Throws an exception to signal the user wishes to quit the quiz.
 */
void QuizGame::quit() {
    showStatistics();
    throw QuitException();
}
