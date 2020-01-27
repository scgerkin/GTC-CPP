/**
 * Contains methods for demonstrating the QuizGame class.
 */
#ifndef USCAPITALS_QUIZCREATION_H
#define USCAPITALS_QUIZCREATION_H

#include "QuestionMap.h"

void initAndGo();
void determineQuizType();
void displayMenu();
int getMenuEntry();
void stateCapitalQuiz();
void countryCapitalQuiz();
void debugQuiz();
void invalidSelection();
void startQuiz(const QuestionMap &questions);
bool getYesNo();

#endif //USCAPITALS_QUIZCREATION_H
