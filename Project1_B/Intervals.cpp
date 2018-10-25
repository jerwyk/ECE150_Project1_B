#include <iostream>
#include <string>
#include <cmath>

//all function declarations
#pragma region Declarations
int main();
int interval_calculator();
struct interval;

//for all the function below just see the project description
void enter(interval &inter, double a, double b);
void negate(interval &inter);
void invert(interval &inter);
//assign obj to inter
//used for ms and mr
void assign(interval &inter, interval &obj);
//plus obj to inter
//used for m+ and m-
void m_plus(interval &inter, interval &obj);
void m_minus(interval &inter, interval &obj);

//about the add functions
//So the scalar operations can be preformed using the following functions
//when c == d an scalar operation is equivelent to an interval operation
//these functions are designed for interval operations
void value_add(interval &inter, double c, double d);
void value_minus(interval &inter, double c, double d);
void value_multiply(interval &inter, double c, double d);
void value_divide(interval &inter, double c, double d);
void scalar_divide_by(interval &inter, double c);

void intersect(interval &inter, double c, double d);
void integers(interval inter);
void cartesian_integers(interval &inter, double c, double d);
//end of declarations-------
#pragma endregion


//structures---------------------------------

//an interval from a to b
struct interval
{
	//struct members
	double A;
	double B;
	bool Empty;

	//default constructor
	interval() : A(0), B(0), Empty(true) {}

	//another constructor
	interval(double a, double b)
	{
		A = a;
		B = b;
	}

	//assign the interval i to this interval
	void equal(interval i)
	{
		A = i.A;
		B = i.B;
		Empty = i.Empty;
	}
	
	//assigning individual intervals
	//may cause a > b
	void equal(double a, double b)
	{
		A = a;
		B = b;
	}

	//basically uninitialize the interval
	void clear()
	{
		A = 0;
		B = 0;
		Empty = true;
	}

	//print the interval
	void print()
	{
		//print -- if uninitialized
		if (Empty)
		{
			std::cout << "--" << std::endl;
		}
		else
		{
			std::cout << "[" << A << ", " << B << "]" << std::endl;
		}
	}
};
//----------

//tha main func(which does nothing)
int main(){//does everything in interval cal function
	interval_calculator();
	return 0;
}

//the main body of the program
int interval_calculator()
{

	//for the local variables
	std::string command = "";

	interval immediate = interval();
	interval memory = interval();
	//-----------------------

	//the infinite loop
	while (true)
	{

		std::cout << "input :> ";
		std::cin >> command;
		
		//execution of the command
		//all functions are passed by reference for the intervals
#pragma region Commands

		if (command == "exit")
		{
			std::cout << "Bye bye: Terminating interval calculator program." << std::endl;
			return 0;
		}
		else if (command == "enter")
		{
			//get input for parameter
			double a = 0, b = 0;
			std::cin >> a >> b;
			enter(immediate, a, b);
			//will just print -- if uninitialized
			immediate.print();
		}
		else if (command == "negate")
		{
			negate(immediate);
			immediate.print();
		}
		else if (command == "invert")
		{
			invert(immediate);
			immediate.print();
		}
		else if (command == "ms")
		{
			//assign immediate to memory
			assign(memory, immediate);	
			immediate.print();
		}
		else if (command == "mr")
		{
			//assign memory to immdiate
			assign(immediate, memory);
			immediate.print();
		}
		else if (command == "mc")
		{
			//uninitialize the memory stored interval
			memory.clear();
			immediate.print();
		}
		else if (command == "m+")
		{
			m_plus(memory, immediate);
			immediate.print();
		}
		else if (command == "m-")
		{
			m_minus(memory, immediate);
			immediate.print();
		}
		//the scalar operations
		else if (command == "scalar_add")
		{
			//get input for parameter
			double c = 0;
			std::cin >> c;
			//scalar is an interval with a = b
			value_add(immediate, c, c);
			immediate.print();
		}
		else if (command == "scalar_subtract")
		{
			//get input for parameter
			double c = 0;
			std::cin >> c;
			value_minus(immediate, c, c);
			immediate.print();
		}
		else if (command == "scalar_multiply")
		{
			//get input for parameter
			double c = 0;
			std::cin >> c;
			value_multiply(immediate, c, c);
			immediate.print();
		}
		else if (command == "scalar_divide")
		{
			//get input for parameter
			double c = 0;
			std::cin >> c;
			value_divide(immediate, c, c);
			immediate.print();
		}
		else if (command == "scalar_divided_by")
		{
			//get input for parameter
			double c = 0;
			std::cin >> c;
			//there is no interval operation for divided by
			//so I hae a seperate scalar function
			scalar_divide_by(immediate, c);
			immediate.print();
		}
		//the interval operations
		else if (command == "interval_add")
		{
			//get input for parameter
			double c = 0, d = 0;
			std::cin >> c >> d;
			value_add(immediate, c, d);
			immediate.print();
		}
		else if (command == "interval_subtract")
		{
			//get input for parameter
			double c = 0, d = 0;
			std::cin >> c >> d;
			value_minus(immediate, c, d);
			immediate.print();
		}
		else if (command == "interval_multiply")
		{
			//get input for parameter
			double c = 0, d = 0;
			std::cin >> c >> d;
			value_multiply(immediate, c, d);
			immediate.print();
		}
		else if (command == "interval_divide")
		{
			//get input for parameter
			double c = 0, d = 0;
			std::cin >> c >> d;
			value_divide(immediate, c, d);
			immediate.print();
		}
		else if (command == "intersect")
		{
			//get input for parameter
			double c = 0, d = 0;
			std::cin >> c >> d;
			intersect(immediate, c, d);
			immediate.print();
		}
		else if (command == "integers")
		{
			integers(immediate);
			immediate.print();
		}
		else if (command == "cartesian_integers")
		{
			//get input for parameter
			double c = 0, d = 0;
			std::cin >> c >> d;
			cartesian_integers(immediate, c, d);
			immediate.print();
		}
		else//when an unexpected command is entered
		{
			std::cout << "Error: illegal command" << std::endl;
		}

#pragma endregion

		//ignor the rest of the input stream
		//in case the user enters additional parameters
		std::cin.ignore(256, '\n');

	}

}

//all functions------------------------------------------------
//all functions passing by reference, nothing is returned
#pragma region Functions

//set a, b and the bounds of inter, and initialize the interval
//inter: the interval to be entered
//a: the lower bound
//b: the upper bound
//only enters if the lower bound is samller then the upper bound
//outputs error message when invalid
void enter(interval &inter, double a, double b)
{
	if (a <= b)
	{		
		inter.equal(a, b);
		inter.Empty = false;
	}
	else
	{
		std::cout << "Error:invalid interval as " << a << " > " << b << std::endl;
		//inter.clear();
	}
}

//negate the interval
//inter: the interval
//multiply the two ends and switch them
void negate(interval &inter)
{
	if (!inter.Empty)
	{
		inter.equal(-inter.B, -inter.A);
	}
}

//invert the interval
//inter: the interval
//devide two ends and swap them
//output error message instead when 0 is i nthe interval
void invert(interval &inter)
{
	if (!inter.Empty)
	{
		if (inter.A <= 0 && inter.B >= 0)
		{
			std::cout << "Error: division by zero" << std::endl;
			inter.clear();
		}
		else
		{
			inter.equal(1 / inter.B, 1 / inter.A);
		}
	}
}

//assign the value of an interval to another
//inter: the interval to be assigned
//obj: the interval which is assigning to
//used for both ms and mr
void assign(interval &inter, interval &obj)
{
	if (!obj.Empty)
	{
		inter.equal(obj);
	}
}

//add the two interval and stored in inter
//inter: the interval to be stored
//obj: the other interval
//only works when both intervals are initialized
void m_plus(interval &inter, interval &obj)
{
	if (!obj.Empty && !inter.Empty)
	{
		inter.A += obj.A;
		inter.B += obj.B;
	}
}

//same as m_plus but it is subtracting the two intervals
void m_minus(interval &inter, interval &obj)
{
	if (!obj.Empty && !inter.Empty)
	{
		inter.A -= obj.A;
		inter.B -= obj.B;
	}
}

//add c to a and d to b
//inter: the interval
//c: the lower bound
//d: the upper bound
//c has to be less then or equal to d
//otherwise will output error message
void value_add(interval &inter, double c, double d)
{
	if (c > d)
	{
		std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
	}
	else
	{
		if (!inter.Empty)
		{
			inter.A += c;
			inter.B += d;
		}
	}
}

//same as above but subtract
void value_minus(interval &inter, double c, double d)
{
	if (c > d)
	{
		std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
	}
	else 
	{
		if (!inter.Empty)
		{
			inter.A -= c;
			inter.B -= d;
		}
	}
}

//multiplys the two interval
//inter: the first interval
//c: lower bounds of the second interval
//d: upper bounds of the second interval
//again c has to be not greater the d
//refer to project for details
void value_multiply(interval &inter, double c, double d)
{
	if (c > d)
	{
		std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
	}
	else if (!inter.Empty)
	{
		//using std functions to find the min and max
		inter.equal(std::fmin(std::fmin(inter.A * c, inter.A * d), std::fmin(inter.B * c, inter.B * d)),
				    std::fmax(std::fmax(inter.A * c, inter.A * d), std::fmax(inter.B * c, inter.B * d)));
	}
}

//same as above but dividing
void value_divide(interval &inter, double c, double d)
{
	if (c > d)
	{
		std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
	}
	else if(!inter.Empty)
	{
		if (c <= 0 && d >= 0)
		{
			std::cout << "Error: division by zero" << std::endl;
			inter.clear();
		}
		else
		{
			inter.equal(std::fmin(std::fmin(inter.A / c, inter.A / d), std::fmin(inter.B / c, inter.B / d)),
						std::fmax(std::fmax(inter.A / c, inter.A / d), std::fmax(inter.B / c, inter.B / d)));
		}
	}
}

//the addtional function for scalar operations
//reverse of scalar_divide
//inter: the interval
//c: the scalar
//error message when 0 is in the interval
void scalar_divide_by(interval &inter, double c)
{
	if (inter.A <= 0 && inter.B >= 0)
	{
		std::cout << "Error: division by zero" << std::endl;
		inter.clear();
	}
	else if(!inter.Empty)
	{
		if (c >= 0)
		{
			inter.equal(c / inter.A, c / inter.B);
		}
		else
		{
			inter.equal(c / inter.B, c / inter.A);
		}
	}	
}

//finds the intersecting interval for two intervals
//inter: the first interval
//c: lower bounds of the second interval
//d: upper bounds of the second interval
//uninitialize inter if no intersection
void intersect(interval &inter, double c, double d)
{
	if (c > d)
	{
		std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
	}
	else if (!inter.Empty)
	{
		if ((d < inter.A) || (c > inter.B))
		{
			//when there is no intersection
			inter.clear();
		}
		else
		{
			//formula for intersecting interval
			inter.equal(std::fmax(inter.A, c), std::fmin(inter.B, d));
		}
	}
}

//output all the integers within the interval
//inter: the interval
//outputs nothing if contains no intergers
void integers(interval inter)
{
	if (!inter.Empty)
	{

		//flag for the first output
		//this to prevent outputing comma after the last output
		bool first = true;

		for (int i = std::ceil(inter.A); i <= inter.B; ++i)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				std::cout << ", ";
			}
			std::cout << i ;
		}

		std::cout << std::endl;
	}
}


//output all the integer cartesian products within the interval
//inter: the interval
//c: lower bounds of the second interval
//d: upper bounds of the second interval
//outputs nothing if contains no intergers
void cartesian_integers(interval &inter, double c, double d)
{
	if (c > d)
	{
		std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
	}
	else if (!inter.Empty)
	{

		bool first = true;

		for (int i = std::ceil(inter.A); i <= inter.B; ++i)
		{
			for (int j = std::ceil(c); j <= d; ++j)
			{
				if (first)
				{
					first = false;
				}
				else
				{
					std::cout << ", ";
				}
				std::cout << "(" << i << "," << j << ")";
			}
		}

		std::cout << std::endl;
	}
}
//end of functions-----------------------------------------------
#pragma endregion
