/*
 * GccApplication1.c
 *
 * Created: 2/18/2018 5:02:55 PM
 * Author : Eilat
 */ 

#include <avr/io.h>
#include <stdio.h>

int main()
{
    int i, num, sumGood, sumBad;
	num = 36;				//first num to check is 37
	sumBad = 0;				//initialize running sum
	sumGood = 0;			//initialize running sum
    for (i = 0; i<300; i++)	//set loop to count 300 numbers
    {
		num++;
		if (num % 5 == 0)		//if rem is 0, divisible by 5
			sumGood = sumGood + num;	//add to good running sum
		else
			sumBad = sumBad + num;		//if rem is different than 0, not divisible by 5
		
		if (num > 254)			//rests back to one when reaches 255
			num = 0;
	 }
	printf("Sum of numbers divisible by 5 is %d \n",sumGood);
	printf("Sum of numbers that not divisible by 5 is %d \n",sumBad);
	return 0;
}

