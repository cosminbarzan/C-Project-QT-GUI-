#pragma once
#include <string>
#include "domeniu.h"
#include <vector>
using namespace std;

class ValidateException {
private:
	string msg;
public:
	ValidateException(string m) :msg{ m } {

	}

	string getMessage() const;
};


class OfertaValidator {
public:
	void valideaza(const Oferta& o);
};