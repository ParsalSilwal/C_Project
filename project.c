#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct person{
	char fname[15],lname[15],gender[10],hlth[50];
	int mob,citizen,age;
};

void record(struct person*,FILE*); //Function for the input of personal data 
int dob ();                        //Function for input of birth date & age calculation
void unqcode();                    //Function for unique registration code

int main(){

	system("cls");                  // Clears Output Screen for the main fuction when called next time
	fflush(stdin);                  //Clears the output buffer so that next getchar() doesnt get '\n' when main function recalled
	FILE *cf;
	struct person p;
	int choice;
	long i, j;
	char another;
	cf=fopen("logsss.txt","rb+");

    if (cf == NULL)					 //Error handing for files							
    {
        cf = fopen("logsss.txt","wb+");

        if (cf==NULL)
        {
            printf("Cannot open file");
        }
    }
    
	printf("                                           Government of Nepal\n");
	printf("                                   Ministry of Health & Population\n\n");
	printf("                               COVID-19 Vaccination Campaign Program\n\n");
	printf("  1. Fill Form\n");
	printf("  2. Show Info\n");
	printf("  3. Exit\n\n");
	printf("  Choose One(1 to 3) :- ");
	choice = getchar();                //Take choice for switch function
	
	
	switch(choice){                              
		case '1' :
			cf=fopen("logsss.txt","a+");
			do{	
			system("cls"); 
			printf("                                    Fill up your Form\n\n");
			record(&p,cf);
			printf("\n Add another record Y/N ");
			fflush(stdin);
			another= getchar();
		}while(another == 'y'||another=='Y');  //while loop for multiple input
			fclose(cf);
		main();	
		
			
			
		case '2':
			system("cls");
			cf=fopen("logsss.txt","a+");
			fseek(cf,-1L,2);                     //Sets the file position
			j=ftell(cf);                        //Tell the position of the file
			fclose(cf);
			cf=fopen("logsss.txt","rb+");
			while(ftell(cf) < j){

			fscanf(cf,"%s ",p.fname);          //take input from file cf
			fscanf(cf,"%s ",p.lname);
			fscanf(cf,"%s ",p.gender);
			fscanf(cf,"%d ",&p.age);
			fscanf(cf,"%d ",&p.mob);
			fscanf(cf,"%d ",&p.citizen);
			fscanf(cf,"%s ",p.hlth);
		
			printf("First Name:%s\n",p.fname);   //print on output screen
			printf("Last Name:%s\n",p.lname);		
			printf("Gender:%s\n",p.gender);
			printf("Age:%d\n",p.age);
			printf("Mob no.:%d\n",p.mob);
			printf("Citizenship no.:%d\n",p.citizen);
			printf("Health Status:%s\n\n",p.hlth);

			}
			fclose(cf);
			system("pause");                     //Pause the execution for a while
			main();	                             //Call main function
		
			
		case '3':
			fclose(cf);
			exit(0);
		
		default:
			printf("  !!!!!!!Wrong input!!!!!!!\n");
			system("pause");
			main();	
	}
	return 0;
}  


void record(struct person *m, FILE *pf){
	
	m->age=dob();                                  //Call dob() function for birth date input and assign returning age to a member of struct.
	if(m->age<18){                                //if condition to check age
	printf("Sorry you are under age, you can't be vaccinated.\n");
	system("pause");
	main();
		}
	else
	printf("You are approved for vaccination\n\n");
				
	printf("First Name:-");
	scanf("%s",m->fname);
	printf("Last Name:-");
	scanf("%s",m->lname);
	printf("Gender:-");
	scanf("%s",m->gender);
	printf("Mobile no:-");
	scanf("%d",&m->mob);
	printf("Citizenship No:-");
	scanf("%d",&m->citizen);
	printf("\nMention your recent medical condition i.e. Normal, Heartdisease, Hypertension or others\n");
	scanf("%s",m->hlth);
	printf("\n\nYour are registered ,please go to the nearest Hospital for vaccination with registration code: ");
	unqcode();                                      //Call unqcode() Generate unique registration code
	fprintf(pf,"%s %s %s %d %d %d %s ",m->fname,m->lname,m->gender,m->age,m->mob,m->citizen,m->hlth); //print data in file cf
}
		
int dob(){
	fflush(stdin);
    time_t t;                                        //time_t is time related datatype that holds time since epoch i.e. 1990
    struct tm * currentdate;                         //tm is inbuilt structure in time.h library 
    struct tm birthdate;

    time (&t);                                      //This function returns the time since 00:00:00 UTC, January 1, 1970 
    currentdate = localtime (&t);                   //This function returns time calender time type yr month day
    currentdate->tm_mon = currentdate->tm_mon+ 1;   //In tm structure month is in range 0 to 11.
    currentdate->tm_year = currentdate->tm_year+ 1900; //In tm structure no of yrs is fromm 1990. 
    
    do{
    fflush(stdin);
    printf("Provide your birth date(AD)\n");
    printf("dd: ");
    scanf("%d",&birthdate.tm_mday);
    printf("mm: ");
    scanf("%d",&birthdate.tm_mon);
    printf("yy: ");
    scanf("%d",&birthdate.tm_year);
    printf("\n");
	}while(birthdate.tm_mday>31  || birthdate.tm_mon>12|| birthdate.tm_year>2021 || birthdate.tm_year<1920); // while loop for wrong input
	
	if(birthdate.tm_mday > currentdate->tm_mday){
		currentdate->tm_mday = currentdate->tm_mday+31;
		currentdate->tm_mon = currentdate->tm_mday-1;
	}
	
	if(birthdate.tm_mon > currentdate->tm_mon){
		currentdate->tm_mon = currentdate->tm_mon+12;
		currentdate->tm_year = currentdate->tm_year-1;
	}
	
	int finalyr;
	finalyr = currentdate->tm_year - birthdate.tm_year;	//Subtraction of current yr to birth yr results to age.
	return finalyr;   
}

void unqcode(){
	int i,r;
	char str[8];
	char ch[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
    srand(time(NULL));                              //srand() function ensure that rndom no by rand() would be different everytime.
    for(i=0;i<9;i++){
    	r= rand()%62;                              //rand() function generate random numbers,rand()%n i.e n is the range for random no.
    	str[i]=ch[r];
	}
	printf("%s\n",str);
}
	
		
