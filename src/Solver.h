#include "Element.h"
#include <string>

using namespace std;

bool check(Element* cell, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9);
bool read(Element* cell, string name);
bool write(Element* cell, string name, bool done);
bool solve(Element* cell, int recLimit);
bool finished(Element* cell);
