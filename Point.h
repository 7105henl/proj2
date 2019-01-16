#ifndef SERVER_POINT_H
#define SERVER_POINT_H


class Point {
public:
    int x;
    int y;

    Point() {}

    Point(int first, int second) {
        x = first;
        y = second;
    }

    Point calcNext(Point next) {
        return {x + next.x, y + next.y};
    }


    friend bool operator<(const Point &l, const Point &r) {
        if (l.x == r.x) {
            return l.y < r.y;
        }
        return l.x < r.x;

    }

    friend bool operator==(const Point &l, const Point &r) {
        return l.x == r.x && l.y == r.y;
    }
};


#endif //SERVER_POINT_H
