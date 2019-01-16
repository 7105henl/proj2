

#include "MyTestClientHandler.h"


void MyTestClientHandler::handleClient(std::string problem) {

    string reverseString;
    string parsedProblem = Utils::parser(problem);
    if (this->cacheManager->isSavedInCache(parsedProblem)) {
        this->cacheManager->getFromCache(parsedProblem);
    } else {

        reverseString = this->solver->solve(&problem);
        this->cacheManager->saveSLNForProblem(parsedProblem, reverseString);
    }
}