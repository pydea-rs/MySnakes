#include <conio.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <io>

struct bpart
{
   public:
		struct bpart *left;
   	struct bpart *right;
   	int x,px,y,py;
}*start,*end;
typedef struct bpart BPART;

int sp = 15;
int den = 5;
int spx =-1,spy = -1;
int noex = 0;
int ttd = 0;
int ppt = 0,ptx,pty;
int delay = 110000025;
char ch;

bool spcreated = false;
bool pe = false;

void csp();
void check4point();
void linkst();
void move();
void checkxy();
void cpoint();
void crand();
void Ulose();
bool ch4O(unsigned int,unsigned int);
void sprand();
void dissp();
void ChooseDirection();
void CheckForward();

void main()
{
   srand(time(0));
   linkst();
   start->x = 40;
   start->y = 12;
   end->x = 40;
   end->y = 12;
   crand();
   cout<<"PPT : 000";
	ChooseDirection();
	while(1)
		move();
}

void linkst()
{
	start = (BPART *)malloc(sizeof(BPART));
   end = (BPART *)malloc(sizeof(BPART));
   BPART *c = (BPART *)malloc(sizeof(BPART));
   BPART *c2 = (BPART *)malloc(sizeof(BPART));
   BPART *c3 = (BPART *)malloc(sizeof(BPART));
   start->right = NULL;
   start->left = c;
   c->right = start;
   c->left = c2;
   c2->right = c;
   c2->left = c3;
   c3->right = c2;
   c3->left = end;
   end->right = c3;
   end->left = NULL;
   c->x = 41;
   c->y = 12;
}

void move()
{
   int t;
   for(t = 0;t < delay;t++);
   ChooseDirection();
   bool ul = false;
   if(ch == 77)
   	ul = ch4O(start->x + 1,start->y);
	else if(ch == 80)
   	ul = ch4O(start->x,start->y + 1);
   else if(ch == 72)
   	ul = ch4O(start->x,start->y - 1);
   else if(ch == 75)
   	ul = ch4O(start->x - 1,start->y);
   if(ul == true)
   	Ulose();
   if(pe == false)
   {
		cpoint();
      pe = true;
   }
   BPART *c = start;
   while(c != NULL)
   {
   	gotoxy(c->x,c->y);
      c->px = c->x;
      c->py = c->y;
      if(c == start)
      {
         if(ch == 77)
      		c->x++;
         else if(ch == 80)
				c->y++;
         else if(ch == 72)
         	c->y--;
         else if(ch == 75)
         	c->x--;
      }
      else
      {
      	c->x = c->right->px;
         c->y = c->right->py;
      }
      if(c == start)
      	check4point();
      else if(spx == c->x && spy == c->y && spcreated == true)
      {
      	sprand();
         csp();
      }
      if(ptx == c->x && pty == c->y)
      {
      	crand();
         cpoint();
      }
      checkxy();
      gotoxy(c->x,c->y);
      if(c == start)
        cout<<"O";
      else if(c == end)
      	cout<<" ";
      else
      	cout<<"0";
      c = c->left;
   }
   if(spcreated == true)
   {
      gotoxy(78,1);
      printf("%.3d",ttd);
   	ttd--;
   }
   if(ttd == 0 && spcreated == true)
   {
      gotoxy(spx,spy);
      cout<<" ";
      dissp();
   }
}

void checkxy()
{
	BPART *c = start;
   while(c != NULL)
   {
   	if(c->x > 80)
      	c->x = 1;
      else if(c->x < 1)
      	c->x = 80;
      else if(c->y > 24)
      	c->y = 2;
      else if(c->y < 2)
      	c->y = 24;
      c = c->left;
   }
}

void cpoint()
{
   gotoxy(ptx,pty);
   cout<<"x";
}

void crand()
{
	ptx = rand() % 80;
	pty = rand() % 25;
	if(ptx < 1)
   	ptx = 2;
   if(pty <= 1)
   	pty = 2;
}

void check4point()
{
	if(start->x == ptx && start->y == pty)
   {
   	crand();
      BPART *n = (BPART *)malloc(sizeof(BPART));
		n->left = end;
      n->right = end->right;
      end->right->left = n;
      end->right = n;
      ppt += 7;
      delay -= 5;
      noex++;
      if(noex == den)
      {
         sprand();
      	csp();
      }
      gotoxy(1,1);
   	printf("PPT : %.3d",ppt);
      pe = false;
   }
   else if(start->x == spx && start->y == spy && spcreated == true)
   {
		dissp();
      ppt += sp;
      sp += 5;
      gotoxy(1,1);
      printf("PPT : %.3d",ppt);
   }
}

void Ulose()
{
	gotoxy(1,1);
   FILE *f;
   if(!(f = fopen("c:\\windows\\snk.rec","r")))
   {
   	f = fopen("c:\\windows\\snk.rec","w");
      fwrite(&ppt,sizeof(int),1,f);
      cout<<"You Lose!\nYour Record : "<<ppt<<"\nAny Key To Exit...";
      fclose(f);
   }
   else
   {
   	int p;
      fread(&p,sizeof(int),1,f);
      cout<<"You Lose!\nYour Record : "<<ppt<<"\nBest Record : "<<p;
      fclose(f);
      if(ppt > p)
      {
      	cout<<"\nCongratulation!You improved your record.\nAny Key To Exit...";
      	FILE *f2 = fopen("c:\\windows\\snk.rec","w");
         fwrite(&ppt,sizeof(int),1,f2);
         fclose(f2);
      }
      else
      	cout<<"\nAny Key To Exit...";
   }
   getch();
   exit(0);
}

bool ch4O(unsigned int xx,unsigned int yy)
{
	char t;
   gettext(xx,yy,xx,yy,&t);
   if(t == '0')
   	return true;
   return false;
}

void csp()
{
   if(spcreated == true)
   	return;
   gotoxy(spx,spy);
   cout<<"X";
   ttd = 150;
   spcreated = true;
}

void sprand()
{
	spx = rand() % 80;
	spy = rand() % 25;
	if(spx < 1)
   	spx = 2;
   if(spy <= 1)
   	spy = 2;
}

void dissp()
{
	spcreated = false;
   sprand();
   spcreated = false;
   int r2 = rand() % 5;
   den += r2;
   noex = 0;
   gotoxy(78,1);
   cout<<"   ";
}
void ChooseDirection()
{
   const int nxtpx = spcreated == true ? spx : ptx;
   const int nxtpy = spcreated == true ? spy : pty;

   CheckForward();

	if(start->y < nxtpy && ch != 72)
   	ch = 80;
   else if(start->y > nxtpy && ch != 80)
   	ch = 72;
   else if(start->x < nxtpx && ch != 75)
   {
      if((nxtpx - start->x) < ((start->x - 1) + (80 - nxtpx)))
   		ch = ch4O(start->x + 1,start->y) == false ? 77 : 75;
      else
      	ch = ch4O(start->x - 1,start->y) == false ? 75 : 77;
   }
   else if(start->x > nxtpx && ch != 77)
   {
   	if((start->x - nxtpx) < ((nxtpx - 1) + (80 - start->x)))
   		ch = ch4O(start->x - 1,start->y) == false ? 75 : 77;
      else
      	ch = ch4O(start->x + 1,start->y) == false ? 77 : 75;
   }

	CheckForward();
}
void CheckForward()
{
   switch(ch)
   {
   	case 75:
      	if(ch4O(start->x >= 2 ? start->x - 1 : 80,start->y) == true)
         {
         	gotoxy(40,25);
            printf("75 if is true");
         	if(ch4O(start->x,start->y >= 3 ? start->y - 1 : 24) == false)
   				ch = 72;
            else
            	ch = 80;
         }
         break;
   	case 80:
         if(ch4O(start->x,start->y <= 23 ? start->y + 1 : 2) == true)
         {
            gotoxy(40,25);
            printf("80 if is true");
         	if(ch4O(start->x >= 2 ? start->x - 1 : 80,start->y) == false)
   				ch = 75;
            else
            	ch = 77;
         }
         break;
      case 72:
      	if(ch4O(start->x,start->y >= 3 ? start->y - 1 : 24) == true)
         {
            gotoxy(40,25);
            printf("72 if is true");
         	if(ch4O(start->x >= 2 ? start->x - 1 : 80,start->y) == false)
   				ch = 75;
            else
            	ch = 77;
         }
         break;
      case 77:
      	if(ch4O(start->x <= 79 ? start->x + 1 : 1,start->y) == true)
         {
            gotoxy(40,25);
            printf("77 if is true");
         	if(ch4O(start->x,start->y >= 3 ? start->y - 1 : 24) == false)
   				ch = 72;
            else
            	ch = 80;
         }
         break;
   }
}

