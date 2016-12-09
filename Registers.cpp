#include "Registers.h"

Registers::Registers()
	:Registers(0,0,0,0)
{}

Registers::Registers(int A, int B, int C, int D)
	:A(A),B(B),C(C),D(D)
{
}

int & Registers::getRegister(Register reg)
{
	switch(reg)
	{
	case Register::A:
	{
		return A;
		break;
	}
	case Register::B:
	{
		return B;
		break;
	}
	case Register::C:
	{
		return C;
		break;
	}
	case Register::D:
	{
		return D;
		break;
	}
	}
}

void Registers::moveToRegister(Register target, Register from)
{
	getRegister(target) = getRegister(from);
}

void Registers::moveToRegister(Register target, int value)
{
	getRegister(target) = value;
}

void Registers::addToRegister(Register target, Register from)
{
	getRegister(target) = getRegister(target) + getRegister(from);
}

void Registers::addToRegister(Register target, int value)
{
	getRegister(target) = getRegister(target) + value;
}

void Registers::subFromRegister(Register target, Register from)
{
	getRegister(target) = getRegister(target) - getRegister(from);
}

void Registers::subFromRegister(Register target, int from)
{
	getRegister(target) = getRegister(target) - from;
}

void Registers::multiplyRegister(Register target, Register from)
{
	getRegister(target) = getRegister(target) * getRegister(from);
}

void Registers::multiplyRegister(Register target, int from)
{
	getRegister(target) = getRegister(target) * from;
}

std::ostream & operator<<(std::ostream & o, Registers a)
{
	o << "Rejestry: " << std::endl << "A: " << a.A << std::endl << "B: " << a.B << std::endl << "C: " << a.C << std::endl << "D: " << a.D << std::endl;
	return o;
}
