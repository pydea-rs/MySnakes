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
void move(unsigned int);
void checkxy();
void cpoint();
void crand();
void Ulose();
void ch2lose(unsigned int,unsigned int);
void sprand();
void dissp();

void main()
{
   srand(time(0));
   linkst();
   start->x = 40;
   start->y = 12;
   end->x = 42;
   end->y = 12;
   crand();
   cout<<"PPT : 000";
	ch = 77;
	while(1)
   {
   	switch(ch)
      {
      	case 77:
         	move(1);break;
         case 80:
         	move(2);break;
         case 72:
         	move(3);break;
         case 75:
         	move(4);break;
   	}
   }
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

void move(unsigned int i)
{
   int t;
   for(t = 0;t < delay;t++);
   if(i == 1)
   	ch2lose(start->x + 1,start->y);
	else if(i == 2)
   	ch2lose(start->x,start->y + 1);
   else if(i == 3)
   	ch2lose(start->x,start->y - 1);
   else if(i == 4)
   	ch2lose(start->x - 1,start->y);
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
         if(i == 1)
      		c->x++;
         else if(i == 2)
				c->y++;
         else if(i == 3)
         	c->y--;
         else if(i == 4)
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
        cout<<"@";
      else if(c == end)
      	cout<<" ";
      else
      	cout<<"O";
      c = c->left;
   }
   char ch2;
   if(kbhit())
   	ch2 = (char)getch();
   if(i == 1 && (ch2 == 72 || ch2 == 80))
   	ch = ch2;
   else if(i == 2 && (ch2 == 77 || ch2 == 75))
		ch = ch2;
   else if(i == 3 && (ch2 == 77 || ch2 == 75))
   	ch = ch2;
   else if(i == 4 && (ch2 == 72 || ch2 == 80))
   	ch = ch2;
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
      putchar(7);
      pe = false;
   }
   else if(start->x == spx && start->y == spy && spcreated == true)
   {
		dissp();
      ppt += sp;
      sp += 5;
      gotoxy(1,1);
      printf("PPT : %.3d",ppt);
      putchar(7);
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
   getch();
   exit(0);
}

void ch2lose(unsigned int xx,unsigned int yy)
{
	char t;
   gettext(xx,yy,xx,yy,&t);
   if(t == 'O')
   	Ulose();
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
