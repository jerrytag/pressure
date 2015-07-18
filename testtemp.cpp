#include "core_temp.h"
#include <stdio.h>

int main()
{
	while(1){
	double temp=get_core_temp();
	printf("%f\n",temp);
	}
}