#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Tape initialization
    char input[100];
    char t1[100];
    char t2[100];
    char t3[100];

    for(int i = 0; i < 100; i++) {
        input[i] = '\0';
        t1[i] = '\0';
        t2[i] = '\0';
        t3[i] = '\0';
    }

    t1[0] = 'Z';
    t2[0] = 'Z';
    t3[0] = 'Z';

    // Prompt for string
    printf("Enter a string of characters (a, b, c only): ");
    fgets(input, 100, stdin);

    // Save string length
    int len = strlen(input);

    // Remove trailing newline
    input[len - 1] = '\0';
    len--;

    // Check for characters not in the alphabet {a,b,c}
    for(int i = 0; i < len; i++) {
        if(input[i] != 'a' && input[i] != 'b' && input[i] != 'c' && input[i] != '\0') {
            for(int j = i; j < len; j++) 
                input[j] = input[j+1];
            i--;
        }
    }

    // Algorithm simulation start

    enum state { // TM states
        q0 = 0,
        q1 = 1,
        q2 = 2
    };

    enum accept { // TM accepts the string
        true = 1,
        false = 0
    };

    enum index { // Indexes for the 4 tapes
        in = 0,
        i1 = 0,
        i2 = 0,
        i3 = 0
    };

    struct {
        int curr_state;
        int curr_index[4];
        int is_accepted;
    } config; // Current configuration of the TM

    // Value initialization
    config.curr_state = q0;
    config.is_accepted = false;
    for(int i = 0; i < 4; i++)
        config.curr_index[i] = 0;

    // First step
    if((input[0] == 'a' || input[0] == 'b' || input[0] == 'c') && (t1[0] == 'Z') && (t2[0] == 'Z') && (t3[0] == 'Z')) {
        for(int i = 1; i <=3; i++)
            config.curr_index[i] = 1;
    }

    // Letter count
    while(input[config.curr_index[0]] != '\0') {
        switch(input[config.curr_index[0]]) {
            case 'a':
                t1[config.curr_index[1]] = 'A';
                config.curr_index[1]++;
                break;
            case 'b':
                t2[config.curr_index[2]] = 'B';
                config.curr_index[2]++;
                break;
            case 'c':
                t3[config.curr_index[3]] = 'C';
                config.curr_index[3]++;
                break;
            default:
                printf("The program has encountered an error and it will now terminate.\n");
                return 1;
        }
        config.curr_index[0]++;
    }

    // Once this has finished, we move to the state q1
    config.curr_state = q1;

    // Check number of letters
    while(t1[config.curr_index[1]] != 'Z' && t2[config.curr_index[2]] != 'Z' && t3[config.curr_index[3]] != 'Z') {
        t1[config.curr_index[1]] = '\0';
        t2[config.curr_index[2]] = '\0';
        t3[config.curr_index[3]] = '\0';
        config.curr_index[1]--;
        config.curr_index[2]--;
        config.curr_index[3]--;
    }

    // Check for two tapes reaching the beginning
    if(t1[config.curr_index[1]] != 'Z' && t2[config.curr_index[2]] == 'Z') {
        while(t1[config.curr_index[1]] != 'Z' && t3[config.curr_index[3]] != 'Z') {
            t1[config.curr_index[1]] = '\0';
            t3[config.curr_index[3]] = '\0';
            config.curr_index[1]--;
            config.curr_index[3]--;
        }
    } else if(t1[config.curr_index[1]] != 'Z' && t3[config.curr_index[3]] == 'Z') {
        while(t1[config.curr_index[1]] != 'Z' && t2[config.curr_index[2]] != 'Z') {
            t1[config.curr_index[1]] = '\0';
            t2[config.curr_index[2]] = '\0';
            config.curr_index[1]--;
            config.curr_index[2]--;
        }
    }
    
    // Check result
    if((t1[config.curr_index[1]] == 'Z' && t2[config.curr_index[2]] == 'Z' && t3[config.curr_index[3]] == 'Z') || (t1[config.curr_index[1]] == 'Z' && t2[config.curr_index[2]] == 'Z') || (t1[config.curr_index[1]] == 'Z' && t3[config.curr_index[3]] == 'Z')) {
        config.curr_state = q2;
        config.is_accepted = true;
    }

    if(config.curr_state == q2 && config.is_accepted == true)
        printf("The string %s contains as many 'a's as 'b's or as many 'a's as 'c's.\n", input);
    else
        printf("The string %s does not contain as many 'a's as 'b's or as many 'a's as 'c's.\n", input);

    // End the program
    return 0;
}
