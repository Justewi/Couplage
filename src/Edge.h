/*
 * Edge.h
 * Classe réutilisée du cours d'ADS en SI3
 * Alexandre BAR, Cyprien LEVY
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include <iostream>

class Edge {
private:
    int x;
    int y;

public:

    Edge(int _x = 0, int _y = 0) : x(_x), y(_y) {
    }

    int origin() const;
    int destination() const;

    bool equals(Edge& e);

    bool operator==(const Edge& right) const;
    bool operator!=(const Edge& right) const;

    struct Hash {

        size_t operator()(const Edge &edge) const {
            return edge.origin();
        }
    };

    virtual ~Edge();

    friend std::ostream& operator<<(std::ostream& os, const Edge& obj) {
        os << "(" << obj.origin() << "," << obj.destination() << ")";
        return os;
    }

};

#endif /* SRC_EDGE_H_ */
