#ifndef USCAPITALS_QUIZGAME_H
#define USCAPITALS_QUIZGAME_H

#include <chrono>
#include <algorithm>
#include <map>
#include <string>
#include "StringTools.h"
#include <deque>
#include <iostream>
#include "QuestionMap.h"

/**
 * QuizGame takes a QuestionMap and quizzes the users on the information.
 * It keeps track of correct and incorrect questions in a separate double-ended
 * queue. This may eventually be extended to allow the user to view a list of
 * questions they got correct and/or incorrect.
 * Statistics about the current quiz are displayed each time a question is asked.
 * If the user wants to quit at anytime, they can type in the QUIT_STR constant
 * and a QuitException will be thrown to signal the user's desire to quit the
 * quiz.
 */
class QuizGame {
public:
    class QuitException : public std::exception {
    public:
        QuitException() = default;
    };
private:
    QuestionMap questions;
    const std::string QUIT_STR = "quit";
    std::deque<std::string> questionsToAsk;
    std::deque<std::string> answeredCorrectlyList;
    std::deque<std::string> notAnsweredCorrectlyList;
    std::chrono::high_resolution_clock::time_point quizStartTime;
public:
    explicit QuizGame(QuestionMap questions);
private:
    void prepareQuestions();
    void displayStartMsg();
    void start();
    void askQuestion();
    void answeredCorrectly(const std::string &question);
    void notAnsweredCorrectly(const std::string &question);
    void showStatistics();
    void showCurrentPlayTime();
    void show(const std::string &msg) const;
    std::string guess();
    bool getYesNo();
    void quit();
};

#endif //USCAPITALS_QUIZGAME_H
