//Functions:

void analogSetup();
char *analogData(char *analogarr[3]);
char analogConvert(char readval);
char calcTemp(char aread);

//pin declerations

int irpin1 = A0; //3 analog IR sensors
int irpin2 = A1;
int irpin3 = A2;
int sustrv = A3; //analog input for suspension travel, not implemented yet

//read variables

char irread1;
char irread2;
char irread3;

char voltage1, voltage2, voltage3;
char temp1, temp2, temp3;