/*
 * Edge.cpp
 *
 *  Created on: 5 mars 2017
 *      Authors: Alexis Metge, Liavona Zheltanosava, Gaspard lacroix
 */

#include "Edge.h"

unsigned int Edge::origin() const{
    return x;
}

unsigned int Edge::destination() const{
    return y;
}

bool Edge::equals(Edge& e){
    return x == e.x && y == e.y;
}

Edge::~Edge(){
}

bool Edge::operator==(const Edge& right) const{
    return x == right.x && y == right.y;
}

bool Edge::operator!=(const Edge& right) const{
    return !operator==(right);
}