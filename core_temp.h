#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 6 


//get core temperature
double get_core_temp()
{

	double temp = 0;
	char buf[MAX_SIZE];
	int fd = 0;
	fd = open(TEMP_PATH,O_RDONLY);
	if(fd<0){
	fprintf(stderr,"failed to open thermal_zone0/temp\n");
	temp=0;
	}
	//read
	if(read(fd,buf,MAX_SIZE)<0){
	fprintf(stderr,"failed to read temp\n");
	temp=0;
	}
	

	temp=atoi(buf)/1000.0;

//	printf("Core temp: %.3f\n",temp);
	close(fd);
	return temp;
}
