
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PHILOSOPHERS 8
#define NUM_TABLE 10

//pthread_mutex_t table_mutex[NUM_TABLE];


int rice=0;
float price=0;
int eating = 0;

int isThereZero(int p[]){
     for(int j=0 ; j<NUM_PHILOSOPHERS ; j++){
        printf("i  : %d\n", p[j]);
        if(p[j] == 0){
            return 1; // sayı bulunmuşsa diğerlerini kontrol etmeden döngüden çıkar
        }
    }
    return 0;
}

// Functions for philosophers
void *philosopher_behaviour(void* id)
{   
    int philosopher_number = *((int*)id);
    int philo[NUM_PHILOSOPHERS]={0,0,0,0,0,0,0,0};

    // Endless loop for philosopher
    while(1){

        // Thinking Section
        srand(time(NULL));
        int thinkingTime = rand() % 4 + 1 ;
        //printf("PID : (%ld)  Philosopher %d is thinking in %d seconds \n", pthread_self(), philosopher_number+1, thinkingTime);
        sleep(thinkingTime);

        while(1){
            if(rice == 2000){
                pthread_exit(NULL);
                continue;
            }
            /*else if(rice == 2000 && isThereZero(philo)==1){
                price = price + 19.90 + 20;
                rice = 0;
            }*/

            rice = rice + 100;
            eating = eating + 1;

            srand(time(NULL));
            int eatingTime = rand() % 4 + 1 ;
            //printf("PID : (%ld)  Philosopher eating %d in %d seconds \n", pthread_self(), philosopher_number+1, eatingTime);

            philo[philosopher_number]=philo[philosopher_number]+1;

            sleep(eatingTime);

            //printf("PID : (%ld)  Philosopher %d finished the eating \n", pthread_self(), philosopher_number+1);
            break;
        }
       // printf("Philosopher %d eat %d times \n", philosopher_number+1, philo[philosopher_number]);

    }


}



int main(){
    char *console[10];

    printf("Filozof grup sayısı >>");
    gets(console);
    printf("%s\n",console);
    uint waitingGroup = atoi(console);

 /*   for (int i=0; i < NUM_TABLE; i++){
        pthread_mutex_init(&table_mutex[i], NULL);
    }*/

    if(waitingGroup>NUM_TABLE){
        while(waitingGroup>0){
            int table = NUM_TABLE;
            if(waitingGroup<NUM_TABLE){
                table=waitingGroup;
            }
            printf("%d %s\n", waitingGroup, "group waiting");
            for (int i = 0; i < table; i++){
                price = 99.90 + 20;
                //pthread_mutex_lock(&table_mutex[i]);
                pthread_t thread_ids[NUM_PHILOSOPHERS];
                int philosopher_numbers[NUM_PHILOSOPHERS];
                int philosopher_eating_counts[NUM_PHILOSOPHERS];

                    // Setting the Philosopher Numbers
                for (int i = 0; i < NUM_PHILOSOPHERS; i++){
                    philosopher_numbers[i] = i;
                    philosopher_eating_counts[i] = 0;
                }

                // Thread Creation
                for (int i = 0; i < NUM_PHILOSOPHERS; i++){
                    pthread_create(&thread_ids[i], NULL, philosopher_behaviour, (void*)&philosopher_numbers[i]); 
                }


                // Wait equivalent
                for (int i = 0; i < NUM_PHILOSOPHERS; i++){
                    pthread_join(thread_ids[i], NULL);
                }
              //  pthread_mutex_unlock(&table_mutex[i]);

                printf("hesap: %.2f\n", i, price);
                printf("eating : %d\n", eating);

                rice = 0;
                price = 0;
                eating = 0;
            }
            waitingGroup = waitingGroup-table;

        }
        


    }else{
        for (int i = 0; i < waitingGroup; i++){
           // pthread_mutex_lock(&table_mutex[i]);
            price = 99.90 + 20;
            pthread_t thread_ids[NUM_PHILOSOPHERS];
            int philosopher_numbers[NUM_PHILOSOPHERS];
            int philosopher_eating_counts[NUM_PHILOSOPHERS];

            // Setting the Philosopher Numbers
            for (int i = 0; i < NUM_PHILOSOPHERS; i++){
                philosopher_numbers[i] = i;
                philosopher_eating_counts[i] = 0;
            }

            // Thread Creation
            for (int i = 0; i < NUM_PHILOSOPHERS; i++){
                pthread_create(&thread_ids[i], NULL, philosopher_behaviour, (void*)&philosopher_numbers[i]); 
            }


            // Wait equivalent
            for (int i = 0; i < NUM_PHILOSOPHERS; i++){
                pthread_join(thread_ids[i], NULL);
            }

           // pthread_mutex_unlock(&table_mutex[i]);

            printf("hesap : %.2f\n", price);
            printf("eating : %d\n", eating);

            rice = 0;
            price = 0;
            eating = 0;

        }
        pthread_exit(NULL);	

    }

   

    exit(0);



        
}