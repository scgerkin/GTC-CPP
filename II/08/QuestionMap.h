#ifndef USCAPITALS_QUESTIONMAP_H
#define USCAPITALS_QUESTIONMAP_H

#include <string>
#include <map>
#include <deque>
#include <fstream>

/**
 * Creates a map of key/value pairs with the Key being a question field to ask
 * and the Value being the correct answer for the question.
 * It can be constructed from a properly formatted file or from a map object.
 */
class QuestionMap {
private:
    std::map<std::string, std::string> questionAnswerMap;
    std::string questionTypeName;
    std::string answerTypeName;
public:
    QuestionMap(std::ifstream &inputFile);
    explicit QuestionMap(std::map<std::string, std::string> map,
                         std::string questionTypeName,
                         std::string answerTypeName);
    const std::string &getQuestionTypeName() const;
    const std::string &getAnswerTypeName() const;
    std::deque<std::string> getListOfQuestionParts();
    bool checkGuess(const std::string &questionPart, const std::string &guess);
    std::string getAnswer(const std::string &question) const;
private:
    void convertFile(std::ifstream &file);
    std::pair<std::string, std::string> parseLineIntoPair(const std::string &line);
};

#endif //USCAPITALS_QUESTIONMAP_H
