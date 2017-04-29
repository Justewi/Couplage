/*
 * Edge.h
 *
 * This class is the traduction in C++ of the Java Edge classe studied in ADS2 course (Polytech SI3)
 *
 *  Created on: 5 mars 2017
 *      Authors: Alexis Metge, Liavona Zheltanosava, Gaspard lacroix
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include <iostream>

class Edge {
private:
    unsigned int x;
    unsigned int y;

public:

    Edge(int _x = 0, int _y = 0) : x(_x), y(_y) {
    }

    unsigned int origin() const;
    unsigned int destination() const;

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
