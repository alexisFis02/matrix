#ifndef MATEXP_H
#define MATEXP_H

#include <string>
using namespace std;

class matExp
{
public:
    matExp(const string mensaje);
    const string getMensaje() const;
private:
    string mensaje;

};

inline matExp::matExp(const string mensaje):mensaje(mensaje){}

inline const string matExp::getMensaje()const {return this->mensaje;}


#endif // MATEXP_H
