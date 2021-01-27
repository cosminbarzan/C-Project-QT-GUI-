#include "domeniu.h"

bool Oferta::operator==(const Oferta& ot) const
{
	return denumire == ot.denumire;
}

bool cmpDenumire(const Oferta& o1, const Oferta& o2)
{
	return o1.getDenumire() < o2.getDenumire();
}

bool cmpDestinatie(const Oferta& o1, const Oferta& o2)
{
	return o1.getDestinatie() < o2.getDestinatie();
}

const Oferta& Oferta::operator=(const Oferta& ot)
{
	denumire = ot.denumire;
	destinatie = ot.destinatie;
	tip = ot.tip;
	pret = ot.pret;
	return *this;
}
