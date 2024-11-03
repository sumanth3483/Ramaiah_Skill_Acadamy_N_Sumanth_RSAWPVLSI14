int numbers[][8] = {{1,1,1,1,1,1,0},
                   {0,1,1,0,0,0,0}, 
                   {1,1,0,1,1,0,1}, 
                   {1,1,1,1,0,0,1}, 
                   {0,1,1,0,0,1,1},
                   {1,0,1,1,0,1,1},
                   {1,0,1,1,1,1,1},
                   {1,1,1,0,0,0,0},
                   {1,1,1,1,1,1,1},
                   {1,1,1,1,0,1,1}};
 int A;
 int B;
 int C;
 int D;
 int E;
 int F;
 int G;
 int DP;
 int DIG_1;
 int DIG_2;
 int DIG_3;
 int DIG_4;

void sevenSegmentInit(int a, int b, int c, int d, int e, int f, int g, int dp, int d1, int d2, int d3, int d4)
{
  A=a;
  B=b;
  C=c;
  D=d;
  E=e;
  F=f;
  G=g;
  DP=dp;
  DIG_1=d1;
  DIG_2=d2;
  DIG_3=d3;
  DIG_4=d4;
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DIG_1, OUTPUT);
  pinMode(DIG_2, OUTPUT);
  pinMode(DIG_3, OUTPUT);
  pinMode(DIG_4, OUTPUT);
  digitalWrite(DIG_1, HIGH);
  digitalWrite(DIG_2, HIGH);
  digitalWrite(DIG_3, HIGH);
  digitalWrite(DIG_4, HIGH);
}

void selectSegment(int sel=0)
{
  switch(sel)
  {
    case 1:
    digitalWrite(DIG_1, LOW);
    digitalWrite(DIG_2, HIGH);
    digitalWrite(DIG_3, HIGH);
    digitalWrite(DIG_4, HIGH);
    break;
    case 2:
    digitalWrite(DIG_1, HIGH);
    digitalWrite(DIG_2, LOW);
    digitalWrite(DIG_3, HIGH);
    digitalWrite(DIG_4, HIGH);
    break;
    case 3:
    digitalWrite(DIG_1, HIGH);
    digitalWrite(DIG_2, HIGH);
    digitalWrite(DIG_3, LOW);
    digitalWrite(DIG_4, HIGH);
    break;
    case 4:
    digitalWrite(DIG_1, HIGH);
    digitalWrite(DIG_2, HIGH);
    digitalWrite(DIG_3, HIGH);
    digitalWrite(DIG_4, LOW);
  }
}

int getDigit(int num)
{
  num%=10;
  return num;
}

void number(int i)
{
    digitalWrite(A, numbers[i][0]);
    digitalWrite(B, numbers[i][1]);
    digitalWrite(C, numbers[i][2]);
    digitalWrite(D, numbers[i][3]);
    digitalWrite(E, numbers[i][4]);
    digitalWrite(F, numbers[i][5]);
    digitalWrite(G, numbers[i][6]);
    delay(5);
}

void sevenSegmentDisplay(int digit)
{
  switch(digit)
  {
    case 0: number(0);
    break;
    case 1: number(1);
    break;
    case 2: number(2);
    break;
    case 3: number(3);
    break;
    case 4: number(4);
    break;
    case 5: number(5);
    break;
    case 6: number(6);
    break;
    case 7: number(7);
    break;
    case 8: number(8);
    break;
    case 9: number(9);
    break;
  }
}
