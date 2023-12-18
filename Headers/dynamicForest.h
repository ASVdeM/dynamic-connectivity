#ifndef __DYNAMICFOREST_H__
#define __DYNAMICFOREST_H__
#include "node.h"

Node *makeDynamicForest (int n);
void addEdge (Node *dynamicForest, int i, int j);
void deleteEdge (Node *dynamicForest, int i, int j);
bool connected (Node *dynamicForest, int i, int j);
unsigned int size (Node *dynamicForest, int i);

#endif /* __DYNAMICFOREST_H__ */

