#ifndef __instancia_H_INCLUDED_
#define __instancia_H_INCLUDED_

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "../vector/vectorNum.h"

using namespace std;

struct imagen{
    int label;
    vectorNum *vect;
};
vector<imagen> procesarEntrada(string archivo,bool entrenamiento);

#endif
