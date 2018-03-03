//PiCam: Takes picture when motion is detected. Will prompt user to supply picture name and preview length.

#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string.h>
#define SEN 0
#define MAXSIZE 50
#define A "Y"
#define B "O"

int system(const char *command);

int main()
{
	wiringPiSetup();
	pinMode(SEN, INPUT);
	char answer1[MAXSIZE];
	char answer2[MAXSIZE];
	char name[MAXSIZE] = B;
	char firstprefix[MAXSIZE] = "raspistill -hf -hf -t ";
	char secondprefix[MAXSIZE] = "xdg-open ";
		
	printf("\nDo you want to name your picture first? (Enter Y/N and press ENTER): ");
	scanf("%s", answer1);
	if(strcmp(answer1, A) == 0){
			printf("What do you want to call your video?: ");
			scanf("%s", name);
			strcat(name, ".jpg");
	}
	
	printf("How long do you wish the camera to wait before taking a picture? (Enter time in milliseconds and press ENTER): ");
	scanf("%s", answer2);
	strcat(firstprefix, answer2);
	strcat(firstprefix, " -o ");
	
	if(digitalRead(SEN) == LOW)
		printf("\nCAMERA OFF\nError: Please check wiring OR move away from sensor. \n");
	else
	{
		printf("\nCAMERA ON\n1. To take picture, stand in front of camcorder. \n2. Your picutre will be taken after the specified time. \n3. To view image, enter in the command provided.\n\n");
		for(;;){
			if(digitalRead(SEN) == LOW){
				system(strcat(firstprefix, name));
				break;
			}
		}
	}
	strcat(secondprefix, name);
	printf("Type *%s* and press ENTER to view your picture!\n", secondprefix);
	return(0);
}