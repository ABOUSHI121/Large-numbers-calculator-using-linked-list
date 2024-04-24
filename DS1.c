#include <stdio.h>
#include <stdlib.h>

struct node
{
    int Data;
    struct node *Next;
    struct node *Prev;
};
typedef struct node Node;
int COUNT = 0;//Count of numbers we have
void DeleteList(struct node *L)
{
    struct node *P = (struct node *) malloc(sizeof(struct node)), *temp = (struct node *) malloc(sizeof(struct node));
    P = L;
    L->Next = NULL;

    while (P->Next != NULL)
    {
        temp = P->Next;
        free(P);
        P = temp;
    }

}

struct node *MakeEmpty(struct node *L)
{
    if (L != NULL)
        DeleteList(L);
    L = (struct node *) malloc(sizeof(struct node));

    if (L == NULL)
        printf("Out of memory!\n");

    L->Next = NULL;
    return L;
}

int IsEmpty(struct node *L)
{
    return L->Next == NULL;
}

int IsLast(struct node *P, struct node *L)
{
    return P->Next == NULL;
}

struct node *Find(int X, struct node *L)
{
    struct node *P;
    P = L->Next;

    while (P != NULL && P->Data != X)
        P = P->Next;

    return P;
}

void InsertLast(int X, struct node *L)
{
    struct node *temp, *P = L;

    temp = (struct node *) malloc(sizeof(struct node));
    temp->Data = X;

    while (P->Next != NULL)
        P = P->Next;

    P->Next = temp;

    temp->Next = NULL;
    temp->Prev = P;

}

void InsertFirst(int X, struct node *L)
{
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    temp->Data = X;
    temp->Next = L->Next;
    temp->Prev = L;
    if (L->Next != NULL)
    {
        L->Next->Prev = temp;
    }
    L->Next = temp;
}

Node *FindLast(Node *Num)
{
    Node *temp = (struct node *) malloc(sizeof(struct node));
    temp = Num;
    while (temp->Next != NULL)
    {
        temp = temp->Next;
    }
    return temp;
}//function return pointer to last node
void ZeroCheck(Node *NUM)
{
    Node *Temp1 = (struct node *) malloc(sizeof(struct node));
    Node *Temp = (struct node *) malloc(sizeof(struct node));
    Temp1 = FindLast(NUM);
    while (Temp1->Data == 0&&Temp1->Prev!=NUM)
    {
        Temp = Temp1;
        Temp1 = Temp1->Prev;
        Temp1->Next = NULL;
        free(Temp);
    }
    Temp1->Next = NULL;
}//when a number have zero in his most significant bit like 0542
int size(struct node *L)
{
    struct node *p = L->Next;
    int count = 0;
    while (p != NULL)
    {
        count += 1;
        p = p->Next;
    }
    return count;
}

void PrintList(struct node *L)
{
    struct node *P = FindLast(L);
    if (L->Data == 1)printf("-");
    for (int i = 0; i < size(L); ++i)
    {
        printf("%d", P->Data);
        P = P->Prev;
    }
    printf("\n");
}//edited to print the numbers
int GetCount()
{

    FILE *file;
    int count = 1;//counter for lines
    char C;
    file = fopen("C:\\Users\\hp\\CLionProjects\\untitled99\\sameer.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
    }
    else printf("file opened\n");


    C = getc(file);
    while (C != EOF)
    {
        //count whenever new line is encountered
        if (C == '\n')
        {
            count = count + 1;
        }
        //take next character from file.
        C = getc(file);
    }
    return count;
}//function return the numbers of lines in the file (to make sure that no infinite loop)
void ReadFromFile(
    Node *NUMBERS[])  //in reading i read char by char and flip it to integer and insert it the array of numbers
{
    FILE *file;
    int TempNum;
    int count = GetCount();
    Node *Temp = (struct node *) malloc(sizeof(struct node));
    Temp->Next = NULL;

    // Open file for reading
    file = fopen("C:\\Users\\hp\\CLionProjects\\untitled99\\sameer.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
    }
    else printf("file opened\n");


    char c = getc(file);
    int i = 0;
    for (int j = 0; j < count; ++j)
    {
        int sign = 1;
        while (c != '\n')
        {
            if (c == '-')//sign check
            {
                sign = -1;
                c = getc(file);
            }
            else
            {
                TempNum = atoi(&c);//convert from char to int
                InsertFirst(TempNum, Temp);//insert to Temp, in my code I use the least significant next of header
                c = getc(file);
            }
        }//sign operation
        if (sign == -1)
            Temp->Data = 1;
        else
            Temp->Data = 0;
        NUMBERS[i] = (struct node *) malloc(sizeof(struct node));//numbers point to the data we read
        NUMBERS[i]->Data = Temp->Data;
        NUMBERS[i]->Next = Temp->Next;
        FindLast(NUMBERS[i])->Next = NULL;//to make sure
        Temp->Next = NULL;
        i++;
        COUNT++;
        c = getc(file);
        if (c == EOF)break;
    }

    fclose(file);
}

void findBiggestSize(Node *NUM1, Node *NUM2, Node *L)
{
    int biggestSize;//the answer of add two number of n m digit maximum will be n+1 if m=n
    if (size(NUM1) > size(NUM2))biggestSize = size(NUM1);
    else biggestSize = size(NUM2);
    biggestSize++;

    for (int j = 0; j < biggestSize; ++j)
    {
        InsertLast(0, L);//initially zeros
    }
//    Node *Temp=L;
//    for (int j = 0; j < biggestSize; +j) {
//        Temp=L->Next;
//    }
//    Temp=NULL;
}

int Compare(Node *One, Node *Two)//compare two numbers according to size if the same size return one to avoid overflow
{
    if (size(One) > size(Two))return 1;
    else if (size(Two) > size(One))return 2;
    Node *Temp1 = (struct node *) malloc(sizeof(struct node));
    Node *Temp2 = (struct node *) malloc(sizeof(struct node));
    Temp1 = FindLast(One);
    Temp2 = FindLast(Two);
    //if size equal we compare from MSD to LSD
    while (Temp1->Prev!=One)
    {
        if (Temp1->Data>Temp2->Data)return 1;
        else if (Temp1->Data<Temp2->Data)return 2;
        Temp1=Temp1->Prev;
        Temp2=Temp2->Prev;
    }
    return 1;

}

void minusCheck(Node *L)//if there is minus value after sub or add
{
    Node *temp = L->Next;
    while (L != NULL)
    {
        if (L->Data < 0)
        {
            L->Next->Data--;
            L->Data += 10;
        }
        L = L->Next;

    }
}

void Add(Node *NUMBERS[], Node *SUM)//old add (no using)
{
    int AddDigit;
    Node *Temp1 = (struct node *) malloc(sizeof(struct node));
    Node *Temp2 = (struct node *) malloc(sizeof(struct node));
    Temp1 = NUMBERS[0];
    Temp2 = SUM;
    Temp2->Data = Temp1->Data;
    Temp1 = Temp1->Next;
    Temp2 = Temp2->Next;
    while (Temp1 != NULL)
    {
        Temp2->Data = Temp1->Data;
        Temp1 = Temp1->Next;
        Temp2 = Temp2->Next;
    }
    printf("%d\n", SUM->Data);
    printf("%d\n", NUMBERS[1]->Data);
    PrintList(SUM);
    printf("%d\n", SUM->Data);
    for (int i = 1; i < COUNT; ++i)
    {
        Temp1 = SUM->Next;
        Temp2 = NUMBERS[i]->Next;
        if (SUM->Data == NUMBERS[i]->Data)
        {
            while (Temp2 != NULL)
            {
                AddDigit = Temp1->Data + Temp2->Data;
                if (AddDigit < 10)
                    Temp1->Data = AddDigit;
                else
                {
                    Temp1->Next->Data += 1;
                    Temp1->Data = (AddDigit - 10);
                }
                Temp1 = Temp1->Next;
                Temp2 = Temp2->Next;
            }
        }
        else
        {
            int compareResult = Compare(SUM, NUMBERS[i]);
            if (compareResult == 1)
            {
                while (Temp2 != NULL)
                {
                    AddDigit = Temp1->Data - Temp2->Data;
                    if (AddDigit < 0)
                    {
                        Temp1->Data = AddDigit + 10;
                        Temp1->Next->Data--;
                    }
                    else
                    {
                        Temp1->Data = AddDigit;
                    }
                    Temp1 = Temp1->Next;
                    Temp2 = Temp2->Next;
                }
            }
            else if (compareResult == 2)
            {
                if (SUM->Data == 1)SUM->Data = 0;
                else SUM->Data = 1;
                Temp2 = SUM;
                Temp1 = NUMBERS[i];
                while (Temp2 != NULL)
                {
                    AddDigit = Temp1->Data - Temp2->Data;
                    if (AddDigit < 0)
                    {
                        Temp1->Data = AddDigit + 10;
                        Temp1->Next->Data--;
                    }
                    else
                    {
                        Temp1->Data = AddDigit;
                    }
                    Temp1 = Temp1->Next;
                    Temp2 = Temp2->Next;
                }
            }
            else
            {
                Temp1 = SUM;
                while (Temp1->Next != NULL)
                {
                    Temp1->Next->Data == 0;
                    Temp1 = Temp1->Next;
                }
            }
        }
    }
    minusCheck(SUM);


}

void addTwo(Node *NUM1, Node *NUM2, Node *SUM, int same)
{
    DeleteList(SUM);//make sure that old data gone
    findBiggestSize(NUM1, NUM2, SUM);//overflow sol
    int AddDigit;//temp num that hold result of add two digits
    Node *Temp1 = (struct node *) malloc(sizeof(struct node));
    Node *Temp2 = (struct node *) malloc(sizeof(struct node));
    if (Compare(NUM1, NUM2) == 1)//if NUM1 > NUM2 transfer data of num1 to sum
    {
        Temp1 = NUM1;
        Temp2 = SUM;
        Temp2->Data = Temp1->Data;
        Temp1 = Temp1->Next;
        Temp2 = Temp2->Next;
        while (Temp1 != NULL)
        {
            Temp2->Data = Temp1->Data;
            Temp1 = Temp1->Next;
            Temp2 = Temp2->Next;
        }
        Temp1 = SUM->Next;
        Temp2 = NUM2->Next;
    }
    else if (Compare(NUM1, NUM2) == 2 && same != 1)  //else transfer data of num 2
    {
        Temp1 = NUM2;
        Temp2 = SUM;
        Temp2->Data = Temp1->Data;
        Temp1 = Temp1->Next;
        Temp2 = Temp2->Next;
        while (Temp1 != NULL)
        {
            Temp2->Data = Temp1->Data;
            Temp1 = Temp1->Next;
            Temp2 = Temp2->Next;
        }
        Temp1 = SUM->Next;
        Temp2 = NUM1->Next;
    }

    if (NUM1->Data == NUM2->Data)//same sign normal addition
    {
        while (Temp2 != NULL)
        {
            AddDigit = Temp1->Data + Temp2->Data;
            if (AddDigit < 10)
                Temp1->Data = AddDigit;
            else
            {
                Temp1->Next->Data += 1;
                Temp1->Data = (AddDigit - 10);
            }
            Temp1 = Temp1->Next;
            Temp2 = Temp2->Next;
        }
    }
    else  //different sign sub
    {
        while (Temp2 != NULL)
        {
            AddDigit = Temp1->Data - Temp2->Data;
            if (AddDigit < 0)
            {
                Temp1->Data = AddDigit + 10;
                Temp1->Next->Data--;
            }
            else
            {
                Temp1->Data = AddDigit;
            }
            Temp1 = Temp1->Next;
            Temp2 = Temp2->Next;
        }
    }

    minusCheck(SUM);
    ZeroCheck(SUM);
}

void Sub(Node *NUMBERS[], Node *SUB)//old sub (no use)
{
//sub is the same of mul but i flip the sign of the second number
    int AddDigit;
    Node *Temp1 = (struct node *) malloc(sizeof(struct node));
    Node *Temp2 = (struct node *) malloc(sizeof(struct node));
    Temp1 = NUMBERS[0];
    Temp2 = SUB;
    Temp2->Data = Temp1->Data;
    Temp1 = Temp1->Next;
    Temp2 = Temp2->Next;
    while (Temp1 != NULL)
    {
        Temp2->Data = Temp1->Data;
        Temp1 = Temp1->Next;
        Temp2 = Temp2->Next;
    }
    for (int i = 1; i < COUNT; ++i)
    {
        Temp1 = SUB->Next;
        Temp2 = NUMBERS[i]->Next;
        if (SUB->Data != NUMBERS[i]->Data)
        {
            while (Temp2 != NULL)
            {
                AddDigit = Temp1->Data + Temp2->Data;
                if (AddDigit < 10)
                    Temp1->Data = AddDigit;
                else
                {
                    Temp1->Next->Data += 1;
                    Temp1->Data = (AddDigit - 10);
                }
                Temp1 = Temp1->Next;
                Temp2 = Temp2->Next;
            }
        }
        else
        {
            int compareResult = Compare(SUB, NUMBERS[i]);
            if (compareResult == 1)
            {
                while (Temp2 != NULL)
                {
                    AddDigit = Temp1->Data - Temp2->Data;
                    if (AddDigit < 0)
                    {
                        Temp1->Data = AddDigit + 10;
                        Temp1->Next->Data--;
                    }
                    else
                    {
                        Temp1->Data = AddDigit;
                    }
                    Temp1 = Temp1->Next;
                    Temp2 = Temp2->Next;
                }
            }
            else if (compareResult == 2)
            {
                if (SUB->Data == 1)SUB->Data = 0;
                else SUB->Data = 1;
                Temp2 = SUB;
                Temp1 = NUMBERS[i];
                while (Temp2 != NULL)
                {
                    AddDigit = Temp1->Data - Temp2->Data;
                    if (AddDigit < 0)
                    {
                        Temp1->Data = AddDigit + 10;
                        Temp1->Next->Data--;
                    }
                    else
                    {
                        Temp1->Data = AddDigit;
                    }
                    Temp1 = Temp1->Next;
                    Temp2 = Temp2->Next;
                }
            }
            else
            {
                Temp1 = SUB;
                while (Temp1->Next != NULL)
                {
                    Temp1->Next->Data == 0;
                    Temp1 = Temp1->Next;
                }
            }
        }
    }
    minusCheck(SUB);
}

void SubTwo(Node *NUM1, Node *NUM2, Node *SUB)
{
    DeleteList(SUB);//same of add but with flip the seconde number sign
    findBiggestSize(NUM1, NUM2, SUB);
    Node *Temp1 = (struct node *) malloc(sizeof(struct node));
    Node *Temp2 = (struct node *) malloc(sizeof(struct node));
    Node *Temp3 = (struct node *) malloc(sizeof(struct node));
    Node *Temp4 = (struct node *) malloc(sizeof(struct node));
    findBiggestSize(NUM1, NUM2, Temp1);
    findBiggestSize(NUM1, NUM2, Temp2);
    Temp1->Data = NUM1->Data;
    Temp4 = Temp1;
    Temp3 = Temp3->Next;
    Temp4 = Temp4->Next;
    while (Temp3!= NULL)  //loop to transfer values from first number to temp LL
    {
        Temp4->Data = Temp3->Data;
        Temp3 = Temp3->Next;
        Temp4 = Temp4->Next;
    }
    Temp3 = NUM1;

    Temp3 = NUM2;
    Temp4 = Temp2;
    if (NUM2->Data == 0)Temp2->Data = 1;
    else Temp2->Data = 0;
    Temp3 = NUM2;
    Temp4 = Temp2;
    Temp3 = Temp3->Next;
    Temp4 = Temp4->Next;
    while (Temp3 != NULL)  //transfer
    {
        Temp4->Data = Temp3->Data;
        Temp3 = Temp3->Next;
        Temp4 = Temp4->Next;
    }
    if (Compare(NUM1,NUM2)==1)//to make sure that we delete the smaller number from the bigger
        addTwo(Temp1, Temp2, SUB, 0);
    else
        addTwo(Temp2, Temp1, SUB, 0);
}

void findBiggestSizeMUL(Node *NUM1, Node *NUM2, Node *MUL)
{
    int biggestSize = size(NUM1) + size(NUM2) + 2;//the biggest size of result after mul m digits with n digits is m+n

    for (int j = 0; j < biggestSize; ++j)
    {
        InsertLast(0, MUL);
    }
    FindLast(MUL)->Next=NULL;

}

void MulTwo(Node *NUM1, Node *NUM2, Node *NUMBERS[], Node *MUL)
{
    DeleteList(MUL);
    findBiggestSizeMUL(NUM1, NUM2, MUL);
    Node *Temp1 = (struct node *) malloc(sizeof(struct node));//points to the first number
    Node *Temp2 = (struct node *) malloc(sizeof(struct node));//points to the second number
    Node *Temp3 = (struct node *) malloc(sizeof(struct node));//points to Temp
    Node *Temp4 = (struct node *) malloc(sizeof(struct node));//help to transfer data from MUL to Temp(points to MUL)
    Node *Temp = (struct node *) malloc(sizeof(struct node));//Hold the MUL value to the next addition
    Temp1 = NUM1->Next;
    Temp2 = NUM2->Next;
    Temp->Data = 0;//because the addition in MUL process it is always between positive numbers
    Temp->Next = NULL;
    MUL->Data = 0;//same as above comment
    int AddDigit;//int that hold the value of mul to digits
    findBiggestSizeMUL(NUM1, NUM2, Temp);//to make Temp can hold the biggest possible number of digit
    Node *AddResults = (struct node *) malloc(sizeof(struct node));//node to save the result of mul two digits
    AddResults->Next = NULL;
    for (int j = 0; j < Temp2 != NULL; ++j)//first loop witch depend on the second int
    {
        for (int k = 0; Temp1 != NULL; ++k) //second loop witch depend on the first int
        {

            AddResults->Data = 0;//as what I said addition in mul always positive
            AddDigit = (Temp1->Data) * (Temp2->Data);//two digit mul



            do
            {
                InsertLast((AddDigit % 10), AddResults);
                AddDigit /= 10;//here we save the data,this loop maximum run two times
            }
            while (AddDigit > 0);

            for (int i = 0; i < j + k; ++i)//this loop to add the zeros to our result depend on witch digit we reach
            {
                InsertFirst((0), AddResults);
            }
            addTwo(AddResults, Temp, MUL, 0);//add result and the previous data of mul and save the result in mul
            Temp3 = Temp->Next;//transfer data from MUL to temp
            Temp4 = MUL->Next;
            while (Temp4 != NULL)
            {
                Temp3->Data = Temp4->Data;
                Temp4 = Temp4->Next;
                Temp3 = Temp3->Next;
            }

            DeleteList(AddResults);
            Temp1 = Temp1->Next;
        }
        Temp1 = NUM1->Next;
        Temp2 = Temp2->Next;
    }
    MUL->Data = NUM1->Data ^ NUM2->Data;
    ZeroCheck(MUL);
}

void Div(Node *NUM1, Node *NUM2, Node *DIV, Node *REM)
{
    int i=0;//did not work yet :/
    findBiggestSize(NUM1,NUM2,REM);
    Node *Temp1 = (struct node *) malloc(sizeof(struct node));
    Node *Temp2 = (struct node *) malloc(sizeof(struct node));
    Node *Temp3 = (struct node *) malloc(sizeof(struct node));
    Node *Temp4 = (struct node *) malloc(sizeof(struct node));
    Node *Temp5 = (struct node *) malloc(sizeof(struct node));
    Temp5->Data=0;
    InsertFirst(1,Temp5);
    findBiggestSize(NUM1,NUM2,Temp1);
    findBiggestSize(NUM1,NUM2,Temp2);
    Temp1 = NUM1->Next;
    Temp2 = NUM2->Next;
    if (Compare(NUM1, NUM2) == 2)
    {
        InsertFirst(0, DIV);
        Temp1 = NUM1;
        Temp2 = REM;
        Temp1 = Temp1->Next;
        Temp2 = Temp2->Next;
        while (Temp1 != NULL)
        {
            Temp2->Data = Temp1->Data;
            Temp1 = Temp1->Next;
            Temp2 = Temp2->Next;
        }
    }
    else
    {
        Temp4 = Temp1;
        Temp3=NUM1;
        Temp3 = Temp3->Next;
        Temp4 = Temp4->Next;
        while (Temp3!= NULL)
        {
            Temp4->Data = Temp3->Data;
            Temp3 = Temp3->Next;
            Temp4 = Temp4->Next;
        }
        Temp3 = NUM2;
        Temp4 = Temp2;
        Temp3 = NUM2;
        Temp4 = Temp2;
        Temp3 = Temp3->Next;
        Temp4 = Temp4->Next;
        while (Temp3 != NULL)
        {
            Temp4->Data = Temp3->Data;
            Temp3 = Temp3->Next;
            Temp4 = Temp4->Next;
        }
        Temp1->Data=0;
        Temp2->Data=0;
        DIV->Data=0;
        Temp3->Data=0;
        while (Compare(Temp1,Temp2)==1)
        {
            SubTwo(Temp1,Temp2,Temp3);
            i++;
        }
        REM=Temp1;

    }
    printf("%d",i);
    printf("hi");
    // Node *Temp= (struct node*)malloc(sizeof(struct node));
}

int main()
{
    int NUM1, NUM2;
    Node *NUMBERS[100];//array of linked lists
    int GetData = 0;//flag of data reading
    int operation = 1;//operation user choose
    Node *SUM = (struct node *) malloc(sizeof(struct node));
    Node *SUB = (struct node *) malloc(sizeof(struct node));
    Node *MUL = (struct node *) malloc(sizeof(struct node));
    Node *DIV = (struct node *) malloc(sizeof(struct node));
    Node *REMINDER = (struct node *) malloc(sizeof(struct node));
    REMINDER->Next = NULL;
    SUM->Next = NULL;
    SUB->Next = NULL;
    MUL->Next = NULL;
    DIV->Next = NULL;
    SUM->Data = 0;
    printf("Welcome !\nSelect operation to do please\n1-Read the input file\n");
    printf("2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Exit\n");
    while (operation != 6)
    {
        scanf("%d", &operation);
        if (operation == 1)
        {
            if (GetData == 1)printf("Data was read already\n");
            else
            {
                ReadFromFile(NUMBERS);
                GetData = 1;
            }
            printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Exit\n");

        }
        else if (operation == 2)
        {
            if (GetData == 0)
            {
                printf("data did not read yet\n");
                printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Exit\n");
                continue;
            }
            else
            {
                printf("Select two numbers please\n");
                for (int i = 0; i < COUNT; ++i)
                {
                    PrintList(NUMBERS[i]);
                }
                scanf("%d", &NUM1);
                scanf("%d", &NUM2);
                if(NUM1>COUNT||NUM2>COUNT)
                {
                    printf("out of range\n");
                    printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Exit\n");
                    continue;
                }
                int theSame;
                if (NUM1 == NUM2)
                {
                    theSame = 1;
                }
                addTwo(NUMBERS[NUM1 - 1], NUMBERS[NUM2 - 1], SUM, theSame);
                printf("The sum is : ");
                PrintList(SUM);
                printf("\n");
                printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Print the results\n7-Exit\n");
            }
        }
        else if (operation == 3)
        {
            if (GetData == 0)
            {
                printf("data did not read yet\n");
                printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Print the results\n7-Exit\n");
                continue;
            }
            else
            {
                printf("Select two numbers please\n");
                for (int i = 0; i < COUNT; ++i)
                {
                    PrintList(NUMBERS[i]);
                }
                scanf("%d", &NUM1);
                scanf("%d", &NUM2);
                if(NUM1>COUNT||NUM2>COUNT)
                {
                    printf("out of range\n");
                    printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Exit\n");
                    continue;
                }
                SubTwo(NUMBERS[NUM1 - 1], NUMBERS[NUM2 - 1], SUB);
                printf("The sub is : ");
                PrintList(SUB);
                printf("\n");
                printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Print the results\n7-Exit\n");
            }
        }
        else if (operation == 4)
        {
            if (GetData == 0)
            {
                printf("data did not read yet\n");
                continue;
            }
            else
            {
                printf("Select two numbers please\n");
                for (int i = 0; i < COUNT; ++i)
                {
                    PrintList(NUMBERS[i]);
                }
                scanf("%d", &NUM1);
                scanf("%d", &NUM2);
                if(NUM1>COUNT||NUM2>COUNT)
                {
                    printf("out of range\n");
                    printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Exit\n");
                    continue;
                }
                MulTwo(NUMBERS[NUM1 - 1], NUMBERS[NUM2 - 1], NUMBERS, MUL);
                printf("The MUL is : ");
                PrintList(MUL);
                printf("\n");
                printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Print the results\n7-Exit\n");
            }
        }
        else if (operation == 5)
        {
            if (GetData == 0)
            {
                printf("data did not read yet\n");
                continue;
            }
            else
            {
                printf("Select two numbers please\n");
                for (int i = 0; i < COUNT; ++i)
                {
                    PrintList(NUMBERS[i]);
                }
                scanf("%d", &NUM1);
                scanf("%d", &NUM2);
                if(NUM1>COUNT||NUM2>COUNT)
                {
                    printf("out of range\n");
                    printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Exit\n");
                    continue;
                }
                Div(NUMBERS[NUM1 - 1], NUMBERS[NUM2 - 1], DIV, REMINDER);
                printf("The DIV is : ");
                PrintList(DIV);
                printf("\n");
                printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Print the results\n7-Exit\n");
            }
        }
        else if (operation == 6)
        {
            printf("Bye\n");
            break;
        }
        else
        {
            printf("invalid operation\n");
            printf("Select operation to do please\n1-Read the input file\n2-Add\n3-Subtract\n4-Multiply\n5-Divide\n6-Print the results\n7-Exit\n");
        }
    }
    return 0;
}
