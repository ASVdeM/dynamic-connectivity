#ifndef __SPLAY_H__
#define __SPLAY_H__
#include "node.h"
void createSplay (Node x);
void joinSplay (Node v, Node w);
void reflectSplay (Node v);
void splitSplay (Node x);
Node maxSplay(Node x);

#endif /* __SPLAY_H__ */

