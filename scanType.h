#ifndef SCANTYPEH
#define SCANTYPEH

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