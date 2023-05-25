#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Vistara_Airlines
{
   char Passport_Num[20];
   char Name[20];
   char Start[20];
   char Destination[20];
   char Email[20];
   int Seat_Num;
   struct Vistara_Airlines *following;
};

struct Vistara_Airlines *begin, *stream;

void reservation(int res);
void cancel();
void display();
void save();

int main()
{
   int select;
   int num = 1;

   begin = stream = NULL;

   do
   {
      printf("\n\n\t\t ********************************************************************");
      printf("\n\t\t\t    WELCOME TO VISTARA AIRLINES RESERVATION PORTAL     ");
      printf("\n\t\t ********************************************************************");
      printf("\n\n\n\t\t  Please enter your choice from below (1-4):");
      printf("\n\n\t\t 1. BOOK A SEAT");
      printf("\n\n\t\t 2. CANCEL A BOOKING");
      printf("\n\n\t\t 3. DISPLAY PASSENGER LIST");
      printf("\n\n\t\t 4. SAVE FILE");
      printf("\n\n\n\t\t ENTER YOUR CHOICE: ");
      scanf("%d", &select);
      fflush(stdin);
      system("cls");

      switch (select)
      {
      case 1:
         reservation(num);
         num++;
         break;
      case 2:
         cancel();
         break;
      case 3:
         display();
         break;
      case 4:
         save();
         break;
      default:
         printf("\t <<<---- INVALID CHOICE ---->>>");
         printf("\n\t KINDLY ENTER SELECT FROM NO.1-4");
      }

      getch();
   } while (select != 4);

   return 0;
}

void information()
{
   printf("\t Enter Your Passport Number: ");
   scanf("%s", stream->Passport_Num);
   fflush(stdin);

   printf("\t Enter Your Name: ");
   scanf("%s", stream->Name);
   fflush(stdin);

   printf("\t Enter Your Email Address: ");
   scanf("%s", stream->Email);
   fflush(stdin);

   printf("\n\t Enter The Destination: ");
   scanf("%s", stream->Destination);
   fflush(stdin);
}

void reservation(int res)
{
   stream = begin;

   if (begin == NULL)
   {
      // First traveler
      begin = stream = (struct Vistara_Airlines *)malloc(sizeof(struct Vistara_Airlines));
      information();
      stream->following = NULL;
      printf("\n\t *****SEAT BOOKING SUCCESSFUL!*****");
      printf("\n\n\t Your Seat Number: Seat A-%d", res);
      stream->Seat_Num = res;
      return;
   }
   else if (res > 20) // FULL SEATS
   {
      printf("\n\t\t Seats Full!!!");
      return;
   }
   else
   {
      // Next traveler
      while (stream->following)
         stream = stream->following;

      stream->following = (struct Vistara_Airlines *)malloc(sizeof(struct Vistara_Airlines));
      stream = stream->following;
      information();
      stream->following = NULL;
      printf("\n\t *****SEAT BOOKING SUCCESSFUL!*****");
      printf("\n\t Your Seat Number: Seat A-%d", res);
      stream->Seat_Num = res;
      return;
   }
}

void save()
{
   FILE *fpointer = fopen("Vistara Records.txt", "w");

   if (fpointer == NULL)
   {
      printf("\n Error in opening file!");
      return;
   }

   stream = begin;

   while (stream)
   {
      fprintf(fpointer, "%-6s", stream->Passport_Num);
      fprintf(fpointer, "%-15s", stream->Name);
      fprintf(fpointer, "%-15s", stream->Email);
      fprintf(fpointer, "%-15s", stream->Destination);
      fprintf(fpointer, "\n");

      stream = stream->following;
   }

   printf("\n\n\t Details have been saved to a file (Vistara Records.txt)");
   fclose(fpointer);
}

void display()
{
   stream = begin;

   while (stream)
   {
      printf("\n\n Passport Number : %-6s", stream->Passport_Num);
      printf("\n         Passenger Name : %-15s", stream->Name);
      printf("\n      Email Address: %-15s", stream->Email);
      printf("\n      Seat Number: A-%d", stream->Seat_Num);
      printf("\n     Destination:%-15s", stream->Destination);
      printf("\n\n<<<<----------------------------------------------------->>>>");
      stream = stream->following;
   }
}

void cancel()
{
   stream = begin;

   system("cls");

   char passport[20];

   printf("\n\n Enter Passport Number: ");
   scanf("%s", passport);
   fflush(stdin);

   if (strcmp(begin->Passport_Num, passport) == 0)
   {
      struct Vistara_Airlines *dummy = begin;
      begin = begin->following;
      free(dummy);
      printf("<<<---- Booking Has Been Canceled ---->>>");
      return;
   }

   while (stream->following)
   {
      if (strcmp(stream->following->Passport_Num, passport) == 0)
      {
         struct Vistara_Airlines *dummy = stream->following;
         stream->following = stream->following->following;
         free(dummy);
         printf("<<<---- CANCELED ---->>>");
         getch();
         return;
      }

      stream = stream->following;
   }

   printf("Passport Number is Wrong!!!! Please Check Your Passport.");
}
