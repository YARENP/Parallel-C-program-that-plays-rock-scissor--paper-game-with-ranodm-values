#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>



int countfor0 = 0;//to keep track of process 0 victory
int countfor1 = 0;//to keep track of process 1 victory
int roundcount = 0;
//a program to play-rock-scissor game 0= rock     1 = scissors       paper 2

int compare(int first, int second)
{
//case when process 0 win
    if ((first == 0 && second == 1) || (first == 1 && second == 2) || (first == 2 && second == 0))
    {
        countfor0++;
        return 1;
    }
//case when process 1 win
    if ((first == 0 && second == 2) || (first == 1 && second == 0) || (first == 2 && second == 1))
    {
        countfor1++;
        return 2;
    }
//case when tie
    if (first == second)
        return 0;
    return -1;
}
void result(int win)
{
    if (win == -1)
        printf("Couldnt comopared\n");
    else if (win == 1)
        printf("Process 0 won for this round!!\n");
    else if (win == 2)
        printf("Process 1 won for this round!!!!!\n");
    else if (win == 0)
        printf("Tie\n");
}

int main()
{
    char items[3][10] = {{"ROCK"}, {"SİCCORS"}, {"PAPER"}};
    int comm;
    int my_rank;

    int error = MPI_Init(NULL, NULL);

    if (error != 0)
    {
        printf("\n");
        printf("RANDOM_MPI - Fatal error.\n");
        printf("  MPI_Init returned nonzero ERROR.\n");
        exit(1);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &comm);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int deneme1 = -1;//chosed element
    srand(time(NULL));

    while (1)
    {
        roundcount++;

        if (my_rank == 1)
        {

            int deneme1 = (random()) % 3;
            MPI_Send(&deneme1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            int winner; //to acknwolege process 1 about winner 
            
        }
        else if (my_rank == 0)
        {

            for (int q = 1; q < comm; q++)
            {
                MPI_Recv(&deneme1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            int deneme2 = (random() + random()) % 3;

            printf("\n\nROUND  %d RESULTS : \n********************\n",roundcount);
            printf("Process %d item is : %s\n", my_rank, items[deneme2]);
            printf("Process %d item is : %s\n\n", my_rank + 1, items[deneme1]);

            int win = compare(deneme2, deneme1);
            result(win);
            printf("\nProcess 0 score : %d\n", countfor0);
            printf("Process 1 score : %d\n", countfor1);
            if (countfor0 >= 5)
                break;
            if (countfor1 >= 5)
                break;
        }
    }
    printf("\nGAME OVER\n");
    if(countfor0 == 5)
    printf("Process 0 won the game !!!!!!\n");
    else if(countfor1 == 5)
    printf("Process 1 won the game !!!!!!\n");
    printf("\nThe game has executed succesfully  (ctrl + C to exit)\n");
    MPI_Finalize();
    return 0;
}
