#ifndef SERVER_SEARCHABLEMATRIX_H
#define SERVER_SEARCHABLEMATRIX_H

#include <vector>
#include "Searchable.h"
#include "Point.h"

class SearchableMatrix : public virtual Searchable<Point> {
private:
    const Point *start;
    const Point *dest;
    vector<vector<int>> matrix;
    map<Point, State<Point> *> *my_map;
public:
    map<Point, State<Point> *> *matrixToStates(const vector<vector<int>> &matrix);

    SearchableMatrix(const Point &start, const Point &dest, const vector<vector<int>> &matrix);

    ~SearchableMatrix() {
        delete my_map;
    }
};


#endif //SERVER_SEARCHABLEMATRIX_H
