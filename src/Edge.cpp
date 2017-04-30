/*
 * Edge.cpp
 * Classe réutilisée du cours d'ADS en SI3
 * Alexandre BAR, Cyprien LEVY
 */

#include "Edge.h"

int Edge::origin() const{
    return x;
}

int Edge::destination() const{
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
