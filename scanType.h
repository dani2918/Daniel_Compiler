#ifndef SCANTYPE_H
#define SCANTYPE_H

struct TokenData
{
	int tokenClass;
	int lineno;
	char *tokenString;
	int numVal;
	char charVal;
	char *idVal;
	bool bvalue;
};



#endif