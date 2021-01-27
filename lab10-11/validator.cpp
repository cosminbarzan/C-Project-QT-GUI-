#include "validator.h"

string ValidateException::getMessage() const
{
	return msg;
}

void OfertaValidator::valideaza(const Oferta& o)
{
	string mess;
	if (o.getDenumire().size() == 0) mess += "Denumire vida!";
	if (o.getDestinatie().size() == 0) mess += "Destinatie vida!";
	if (o.getTip().size() == 0) mess += "Tip vid!";
	if (o.getPret() < 0) mess += "Pret negativ!";
	if (mess.size() > 0) {
		throw ValidateException(mess);
	}
}
