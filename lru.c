#include <stdio.h>

int n, nf;          // Number of pages and number of frames
int in[100];        // Page reference sequence
int p[50];          // Frames
int pgfaultcnt = 0; // Page fault counter

// Function to get input from the user
void getData()
{
    printf("\nEnter length of page reference sequence: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &in[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &nf);
}

// Function to initialize the frames and reset page fault count
void initialize()
{
    pgfaultcnt = 0; // Reset page fault counter
    for (int i = 0; i < nf; i++)
    {
        p[i] = -1; // Use -1 to indicate empty frames
    }
}

// Function to check if a page is already in frames
int isHit(int data)
{
    for (int j = 0; j < nf; j++)
    {
        if (p[j] == data)
        {
            return 1; // Page hit
        }
    }
    return 0; // Page miss
}

// Function to display current frames with incoming value
void dispFrames(int incoming)
{
    printf(" Incoming: %d | ", incoming);
    for (int k = 0; k < nf; k++)
    {
        if (p[k] != -1)
            printf(" %d  |", p[k]);
        else
            printf(" -  |"); // Indicate empty frame
    }
    printf("\n");
}

// Function to display the total number of page faults
void dispPgFaultCnt()
{
    printf("Total number of page faults: %d\n", pgfaultcnt);
}

// LRU page replacement algorithm
void lru()
{
    initialize();
    int least[50]; // Last used index array
    printf("\nFrames:\n");
    printf(" F1  F2  F3 \n");
    for (int i = 0; i < n; i++)
    {
        if (isHit(in[i]) == 0)
        { // Page miss
            for (int j = 0; j < nf; j++)
            {
                least[j] = -1; // Initialize last used index
                for (int k = i - 1; k >= 0; k--)
                {
                    if (p[j] == in[k])
                    {
                        least[j] = k; // Last used index
                        break;
                    }
                }
            }
            // Find the page that was least recently used
            int min = n + 1, repindex = 0; // Use n + 1 as an indicator for empty
            for (int j = 0; j < nf; j++)
            {
                if (least[j] < min)
                {
                    min = least[j];
                    repindex = j;
                }
            }
            p[repindex] = in[i]; // Replace the page
            pgfaultcnt++;
        }
        dispFrames(in[i]); // Display current frame state
    }
    dispPgFaultCnt();
}

// Main function
int main()
{
    int choice;
    while (1)
    {
        printf("\nPage Replacement Algorithms\n");
        printf("1. Enter data\n");
        printf("2. LRU\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            getData();
            break;
        case 2:
            lru();
            break;
        default:
            return 0; // Exit the program
        }
    }
}
