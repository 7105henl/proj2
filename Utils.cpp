
#include "Utils.h"

vector<string> Utils::splitToVectorByDelimiter(string str, char delimiter) {
    string temp;
    vector<string> result;
    for (string::iterator i = str.begin(); i != str.end(); ++i) {
        if (*i != delimiter) {
            temp += *i;
        } else {
            result.push_back(temp);
            temp = "";
        }
    }
    result.push_back(temp);
    return result;
}

string Utils::parser(string str) {
    string temp;
    for (string::iterator i = str.begin(); i != str.end(); ++i) {
        if (*i == '\n' || *i == '\r' || *i == '\0') {
            continue;
        }
        temp += *i;
    }
    return temp;
}

Point Utils::getPointFromString(string str) {
    string first = delimiterAndIndex(str, ',', 1);
    string second = delimiterAndIndex(str, ',', 2);
    Point p1(std::stoi(first), std::stoi(second));
    return p1;
}

vector<string> Utils::split(const string &s, char delimiter) {
    vector<string> word;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        word.push_back(token);
    }
    return word;
}

vector<vector<int>> Utils::vecStrToMat(vector<string> strings) {
    vector<vector<int>> matrix;
    vector<int> array;

    for (int i = 0; i < strings.size(); ++i) {
        vector<string> afterSplit = split(strings[i], ',');
        for (int j = 0; j < afterSplit.size(); ++j) {
            int num = stoi(afterSplit[j]);
            array.push_back(num);
        }
        matrix.push_back(array);
        array.clear();
    }

    return matrix;
}

string Utils::delimiterAndIndex(string str, char delimiter, int index) {
    int counter = 0;
    string basic_string;
    for (string::iterator i = str.begin(); i != str.end(); ++i) {
        if (*i != delimiter) {
            basic_string += *i;
        } else if (counter == index - 1) {
            return basic_string;
        } else if (*i == ' ') {
            continue;
        } else {
            counter++;
            basic_string = "";
        }
    }
    return basic_string;
}