//PiVid: Records video when motion is detected. Will prompt user to supply video name and length.

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
	char firstprefix[MAXSIZE] = "raspivid -hf -hf -t ";
	char secondprefix[MAXSIZE] = "omxplayer ";
		
	printf("\nDo you want to name your video first? (Enter Y/N and press ENTER): ");
	scanf("%s", answer1);
	if(strcmp(answer1, A) == 0){
			printf("What do you want to call your video?: ");
			scanf("%s", name);
			strcat(name, ".mp4");
	}
	
	printf("How long do you want to record? (Enter time in milliseconds and press ENTER): ");
	scanf("%s", answer2);
	strcat(firstprefix, answer2);
	strcat(firstprefix, " -o ");
	
	if(digitalRead(SEN) == LOW)
		printf("\nCAMCORDER OFF\nError: Please check wiring OR move away from sensor. \n");
	else
	{
		printf("\nCAMCORDER ON\n1. To record video, stand in front of camcorder. \n2. Your video will record for the specified time. \n3. The video will automatically play after it is finished recording.\n\n");
		for(;;){
			if(digitalRead(SEN) == LOW){
				system(strcat(firstprefix, name));
				break;
			}
		}
	}
	strcat(secondprefix, name);
	printf("Type *%s* and press ENTER to view your video again!\n\n", secondprefix);
	system(secondprefix);
	return(0);
}