#include "QuestionMap.h"

#include <utility>
#include "StringTools.h"

/**
 * Main constructor using a file to construct a set of questions and information
 * about the questions. See convertFile documentation for information on how a
 * the file should be structured.
 * @param inputFile The file from which we are to retrieve information.
 */
QuestionMap::QuestionMap(std::ifstream &inputFile) {
    convertFile(inputFile);
}

/**
 * Additional constructor allowing the creation of a question set from a map
 * created by means other than reading a file.
 * @param map The map of question to answer key/val pairs.
 * @param questionTypeName The field name for the questions (ie "State").
 * @param answerTypeName The field name for the answers (ie "Capital").
 */
QuestionMap::QuestionMap(std::map<std::string, std::string> map,
                         std::string questionTypeName,
                         std::string answerTypeName)
    : questionAnswerMap(std::move(map)),
    questionTypeName(std::move(questionTypeName)),
    answerTypeName(std::move(answerTypeName))
{}

/**Getter for question type name*/
const std::string &QuestionMap::getQuestionTypeName() const {
    return questionTypeName;
}

/**Getter for answer type name*/
const std::string &QuestionMap::getAnswerTypeName() const {
    return answerTypeName;
}

/**
 * Gets a double-ended queue of question pieces only.
 * @return A double-ended queue consisting of the map keys.
 */
std::deque<std::string> QuestionMap::getListOfQuestionParts() {
    std::deque<std::string> questions;

    for (const auto &entry : questionAnswerMap) {
        questions.emplace_back(entry.first);
    }

    return questions;
}

/**
 * Checks a given question against a guess within the map to verify the correct
 * answer. Allows for leading/trailing whitespace and different case entry.
 * @param questionPart The question we want to check.
 * @param guess The guess we want to check.
 * @return True if the guess is equal to the val in the map given the question.
 */
bool QuestionMap::checkGuess(const std::string &questionPart, const std::string &guess) {
    return toLower(questionAnswerMap.at(questionPart)) == toLower(trim(guess));
}

/**
 * Gets a value from the map containing the question information given a question.
 * @param question The question we want the answer for.
 * @return The answer to the question.
 */
std::string QuestionMap::getAnswer(const std::string &question) const {
    return questionAnswerMap.at(question);
}

/**
 * Converts a CSV file into a QuestionMap object.
 * Each key/val must be on a separate line and separated by only a comma.
 * The first line of the file should be the question field type name and answer
 * field type name.
 * @param file The file we wish to convert to a QuestionMap.
 */
void QuestionMap::convertFile(std::ifstream &file) {
    std::string line;
    std::getline(file, line);

    // get the question/answer type names
    std::pair<std::string, std::string> linePair = parseLineIntoPair(trim(line));
    questionTypeName = linePair.first;
    answerTypeName = linePair.second;

    // read each line into the map
    while (file) {
        std::getline(file, line);
        linePair = parseLineIntoPair(trim(line));
        questionAnswerMap.emplace(linePair.first, linePair.second);
    }

    // close the file when we're done
    file.close();
}

/**
 * Parses an individual line of a file into a pair of entries.
 * @param line The line we wish to parse into two values.
 * @return A pair containing the two pieces of the line.
 */
std::pair<std::string, std::string> QuestionMap::parseLineIntoPair(const std::string &line) {
    const char delimiter = ',';
    size_t loc = line.find(delimiter);
    std::pair<std::string, std::string> pair;
    pair.first = line.substr(0, loc);
    pair.second = line.substr(loc+1, line.size());
    return pair;
}