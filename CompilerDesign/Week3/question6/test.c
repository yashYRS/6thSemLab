#include<conio.h>
int main() 
{
	/** Write a C
		program to generate tokens ***
	*/
	int a,b ; 
	a = 10 , b = 20 ; //assignment initialization
	if(a>=b && b<30) //logical
	{
		for(int i = 1 ; i<=10;i++) 
		{
			a = b + 1 ; 
		}
	}
	printf(" A value is ",a);
	printf(" A is of int type");

}