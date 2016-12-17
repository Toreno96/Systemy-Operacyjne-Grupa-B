#pragma once
#include <iostream>
enum class Register { A, B, C, D };

class Registers
{
private:
	int A, B, C, D;

	int& getRegister(Register reg);

public:
	
	Registers();
	Registers(int A, int B, int C, int D);
	

	void moveToRegister(Register target, Register from);
	void moveToRegister(Register target, int value);

	void addToRegister(Register target, Register from);
	void addToRegister(Register target, int value);

	void subFromRegister(Register target, Register from);
	void subFromRegister(Register target, int from);

	void multiplyRegister(Register target, Register from);
	void multiplyRegister(Register target, int from);

	friend std::ostream& operator << (std::ostream& o, Registers a);

	bool jumpCounterIsEmpty() const;

};