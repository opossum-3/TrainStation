#include "FirstClassWagon.h"
#include "SecondClassWagon.h"
#include "SleepWagon.h"

int main()
{
	FirstClassWagon w(100, 10, true, 0.5);
	w.print();
	
	SecondClassWagon w2(100, 10, 10);
	w2.print();

	SleepWagon w3(100, 10, 5);
	w3.print();
}