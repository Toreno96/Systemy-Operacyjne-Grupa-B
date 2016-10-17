#pragma once

struct Register
{
private:
	char H0, H1, L0, L1; // Od najstarszego bajta

public:
	Register()
		:H0(0), H1(0), L0(0), L1(0)
	{}

	char* H()
	{
		char H[2] = { H0,H1 };
		return H;
	}

	char* L()
	{
		char L[2] = { L0,L1 };
		return L;
	}

	char* X()
	{
		char X[4] = { H0,H1,L0,L1 };
		return X;
	}

	void setH(char* newH)
	{
		H0 = newH[0];
		H1 = newH[1];
	}

	void setL(char* newL)
	{
		L0 = newL[0];
		L1 = newL[1];
	}
};


class Registers
{
	

};