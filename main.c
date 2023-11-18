#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define BALL_BASE_VAL 10
#define INPUT_BUFFER 256
#define NUM_OF_POKEMONS 20

typedef struct Ball {
    char* type;
    unsigned short int modifier; //based on type 1.5 , 3 , 5 , 10
    unsigned short int catch_chance; // base * modifier    
} Ball;

typedef struct BallNode {
    Ball* data;
    struct BallNode* next;
} BallNode;

typedef struct Pokemon {
    char* name;
    char* type;
    bool is_legendary;
    unsigned short int catch_difficulty; // 10 - 100 , if ball catch_chance >= catch_difficulty ? success : fail
} Pokemon;

typedef struct PokeNode {
    Pokemon *data;
    struct PokeNode* next;
} PokeNode;

typedef struct Player {
    BallNode* Bhead; // [ball1 -> ball2 -> NULL]
    PokeNode* Phead; // linked list of the pokemons the player has
    char* showcase;   
    char* username;
    char  id[9];
    int xp;
} Player;

// EXIT CODES 
const unsigned short int EXIT_MALLOC_FAILURE = 2;

/* [FUNCTIONAL PROTOTYPES]*/

 // [displays / menu]
void welcome(char* version);
unsigned short int get_menu(Player* player);
void disp_inv_ball_list(BallNode* head);
void disp_walking();
void disp_pokemon(Pokemon* pokemon, unsigned short int index);

//[input function]
Player* get_player();

//[constructors]
Ball* create_pokeball(char* type, unsigned short int modifier);

//[initializers]
void _init_pokemons_list(Pokemon* p_pokemons);
BallNode* _init_ball_llist();

//[generators]
Pokemon* gen_rand_pokemon(Pokemon* p_pokemons, unsigned short int size);

//[actions]
Ball* choose_ball(BallNode* head, int ball_option);
PokeNode* add_to_pokedex(Pokemon* pokemon, PokeNode* head);
void add_to_showcase(Player* player, int showcase_option);

//[DEALLOCATORS]
void free_pokedex(Player* player);
void free_pokeballs(Player* player);

/* 
===== TO DO ====
1 : refactor and dry up code
*/

int main() {
    Player* player = malloc(sizeof(Player));

    if(player == NULL) {
        fprintf(stderr, "ERROR :: MEM ALLOC FAILED FOR PLAYER \n");
        free(player);
        exit(EXIT_MALLOC_FAILURE);
    }

    player->showcase = NULL;
    Pokemon pokemons[NUM_OF_POKEMONS];
    Pokemon* p_pokemons = &pokemons[0];
    bool _has_init = false;
    

    char* version = "v0.0.2";
    system("cls");
    welcome(version);
    
    player = get_player();
    player->Bhead = _init_ball_llist();
    printf("\n ==== HERE ARE YOUR STARTING BALLS ==== \n");
    disp_inv_ball_list(player->Bhead);
    player->Phead = NULL;

    
    printf("press any key to go to the menu...");
    getch();
    unsigned short int menu_option = 0;
    const unsigned short int MENU_EXIT = 3;
    
    while(menu_option != MENU_EXIT) {
        system("cls");
        fflush(stdin);
        menu_option = get_menu(player);
        switch(menu_option) {
            case 1 :
                if(!_has_init) { 
                    _init_pokemons_list(p_pokemons); 
                    _has_init = true;
                }
                 disp_walking();
                 Pokemon* random_pokemon = gen_rand_pokemon(p_pokemons, NUM_OF_POKEMONS);
                 printf("** YOU ENCOUNTERED : %s **\n", random_pokemon->name);

                 int catch_option = 0;
                 printf("[1] catch [2] run\n");
                 scanf("%d", &catch_option);
                 switch(catch_option) {
                    case 1 :
                        printf("\n=== CHOOSE A BALL TO USE ===\n");
                        disp_inv_ball_list(player->Bhead);
                        int ball_option = 0;
                        scanf("%d", &ball_option);
                        Ball* chosen_ball = choose_ball(player->Bhead, ball_option);
                        printf("** You chose a %s with a catch chance of %hu ** \n", chosen_ball->type, chosen_ball->catch_chance);
                        printf("[1] throw ball [2] change ball [3] run \n");
                        int action = 0;

                        scanf("%d", &action);
                        while(action == 2) {
                            disp_inv_ball_list(player->Bhead);
                            scanf("%d", &ball_option);
                            chosen_ball = choose_ball(player->Bhead, ball_option);
                            printf("** You chose a %s with a catch chance of %hu ** \n", chosen_ball->type, chosen_ball->catch_chance);
                            printf("[1] throw ball [2] change ball [3] run");
                            scanf("%d", &action);
                        }
                        
                        if(action == 1) {
                            //throw
                            if(chosen_ball->catch_chance >= random_pokemon->catch_difficulty) {
                                printf("** YOU CAUGHT %s **", random_pokemon->name);
                                printf("POKEMON { NAME : %s , TYPE : %s } HAS BEEN ADDED TO YOUR POKEDEX \n", random_pokemon->name, random_pokemon->type);
                                player->Phead = add_to_pokedex(random_pokemon, player->Phead);
                                //add to pokedex
                            } else {
                                printf("~~ MISSED ~~");
                                //re throw or pokemon flees
                            }
                        } else if (action == 3) {
                            //run
                        }
                        

                    getch();
                    break;
                    case 2 :
                    printf("** YOU RAN AWAY :: POKEMON FLED **");
                    getch();
                    break;
                    default : printf("Invalid option try again : ");
                    break; 

                   
                 }
                
                getch();
            break;
            case 2 :
                printf("\n === SHOWCASE === \n");
                printf("[ CHOOSE A POKEMON ] \n");
                
                if(player->Phead == NULL) {
                    printf(":: NO POKEMONS IN POKEDEX CURRENTLY :: \n");
                } else {
                    int showcase_index = 1;
                    PokeNode* tmp = player->Phead;
                    int showcase_choice = 0;

                    while(tmp != NULL) {
                        disp_pokemon(tmp->data, showcase_index);
                        tmp = tmp->next;
                        showcase_index++;
                    }

                    printf("ENTER A POKEMON NUMBER TO SHOWCASE : ");
                    scanf("%d", &showcase_choice);
                    while(showcase_choice >= showcase_index) {
                        printf(":: ERROR CHOICE OUT OF RANGE RE-ENTER \n");
                        scanf("%d", &showcase_choice);
                    }
                    
                    add_to_showcase(player, showcase_choice);
                    
                }
               
                getch(); 
            break;
            case 3 :
                free_pokedex(player);
                free_pokeballs(player);
                player->Phead = NULL;
                player->Bhead = NULL;
                free(player->showcase);
                free(player->username);
                
                free(player);
                printf("Thanks for playing!");
                
                
            break;
            default : {
                printf("Invalid option try again : ");
                getch();
            }

        }

    }
    
    
    return 0;

}

void welcome(char* version) {
    printf("====== WELCOME TO POKEMON C %s ====== \n", version);
    printf("Pokemon C is a pokemon simulator\n");
    printf("[] catch pokemons\n[] showcase your pokemons\n");
    printf("press any key to begin ...");
    getch();
}

unsigned short int get_menu(Player* player) {
    unsigned short int option = 0;
    printf("\n === POKEMON C ===\t\t\tUSER { username : %s, id : %s, xp : %d, showcase : %s }\n ", player->username, player->id, player->xp, player->showcase);
    printf("1 : CATCH \n 2 : SHOWCASE \n 3 : EXIT \n");
    scanf("%hu", &option);
    return option;

}

Player* get_player() {
   srand(time(NULL));
   Player* new_player = malloc(sizeof(Player));

   if(new_player == NULL) {
    fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER");
    free(new_player);
    exit(EXIT_MALLOC_FAILURE);
   }

   new_player->xp = 0;
   new_player->Bhead = NULL;
   new_player->Phead = NULL;
   new_player->showcase = malloc(4);

   if(new_player->showcase == NULL) {
    fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER->SHOWCASE");
    free(new_player->showcase);
    exit(EXIT_MALLOC_FAILURE);

   }
   strcpy(new_player->showcase, "TBA");
   
   char input[INPUT_BUFFER];

   printf("\n\n\n\n What is your username : \n");
   char* p_input = fgets(input, INPUT_BUFFER, stdin);
   strtok(p_input, "\n");
   new_player->username = malloc(strlen(p_input) + 1);
   if(new_player->username == NULL) {
    fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER->USERNAME");
    free(new_player->username);
    exit(EXIT_MALLOC_FAILURE);
   }
   strcpy(new_player->username, p_input);
   printf("YOU ENTERED : %s \n", new_player->username);
   
   char uuid[9];
   const unsigned short int MIN_ASCII_NUMBER = 48;
   const unsigned short int MAX_ASCII_NUMBER = 57;
   const unsigned short int MIN_ASCII_LLETTER = 97;
   const unsigned short int MAX_ASCII_LLETTER = 122;
  
   for(int i = 0 ; i < 8; i++) {
    int rand_code;
        if(i % 2 == 0) {
            rand_code = rand() % (MAX_ASCII_NUMBER - MIN_ASCII_NUMBER) + MIN_ASCII_NUMBER;
        } else {
            rand_code = rand() % (MAX_ASCII_LLETTER - MIN_ASCII_LLETTER) + MIN_ASCII_LLETTER;
        }
        uuid[i] = (char)rand_code;
        
   }

   
   strcpy(new_player->id, uuid);
   printf("YOUR UUID : %s \n", new_player->id);
   printf("XP : %d", new_player->xp);
   getch();

   return new_player;
    
}


/* 
 *
 *   if(is_legendary == true) {
 *      catch_difficulty = 10 * 7 || 8 || 9 || 10
 *  } else {
 *      catch_difficulty = 5 * 1 - 10
 *  }
 *
 *   
 */

void _init_pokemons_list(Pokemon* p_pokemons) {

    

    p_pokemons[0].name = "Pikachu";
    p_pokemons[0].type = "Electric";
    p_pokemons[0].is_legendary = false;

    p_pokemons[1].name = "Bulbasaur";
    p_pokemons[1].type = "Grass/Poison";
    p_pokemons[1].is_legendary = false;

    p_pokemons[2].name = "Charmander";
    p_pokemons[2].type = "Fire";
    p_pokemons[2].is_legendary = false;

    p_pokemons[3].name = "Squirtle";
    p_pokemons[3].type = "Water";
    p_pokemons[3].is_legendary = false;

    p_pokemons[4].name = "Jigglypuff";
    p_pokemons[4].type = "Normal/Fairy";
    p_pokemons[4].is_legendary = false;

    p_pokemons[5].name = "Mewtwo";
    p_pokemons[5].type = "Psychic";
    p_pokemons[5].is_legendary = true;

    p_pokemons[6].name = "Snorlax";
    p_pokemons[6].type = "Normal";
    p_pokemons[6].is_legendary = false;

    p_pokemons[7].name = "Eevee";
    p_pokemons[7].type = "Normal";
    p_pokemons[7].is_legendary = false;

    p_pokemons[8].name = "Gyarados";
    p_pokemons[8].type = "Water/Flying";
    p_pokemons[8].is_legendary = false;

    p_pokemons[9].name = "Dragonite";
    p_pokemons[9].type = "Dragon/Flying";
    p_pokemons[9].is_legendary = false;

    p_pokemons[10].name = "Machop";
    p_pokemons[10].type = "Fighting";
    p_pokemons[10].is_legendary = false;

    p_pokemons[11].name = "Alakazam";
    p_pokemons[11].type = "Psychic";
    p_pokemons[11].is_legendary = false;

    p_pokemons[12].name = "Geodude";
    p_pokemons[12].type = "Rock/Ground";
    p_pokemons[12].is_legendary = false;

    p_pokemons[13].name = "Moltres";
    p_pokemons[13].type = "Fire/Flying";
    p_pokemons[13].is_legendary = true;

    p_pokemons[14].name = "Gengar";
    p_pokemons[14].type = "Ghost/Poison";
    p_pokemons[14].is_legendary = false;

    p_pokemons[15].name = "Magikarp";
    p_pokemons[15].type = "Water";
    p_pokemons[15].is_legendary = false;

    p_pokemons[16].name = "Ditto";
    p_pokemons[16].type = "Normal";
    p_pokemons[16].is_legendary = false;

    p_pokemons[17].name = "Rayquaza";
    p_pokemons[17].type = "Dragon/Flying";
    p_pokemons[17].is_legendary = true;

    p_pokemons[18].name = "Psyduck";
    p_pokemons[18].type = "Water";
    p_pokemons[18].is_legendary = false;

    p_pokemons[19].name = "Clefairy";
    p_pokemons[19].type = "Fairy";
    p_pokemons[19].is_legendary = false;

    const unsigned short int LEGENDARY_CONST = 10;
    const unsigned short int NORMAL_CONST = 5;
    const unsigned short int LEGENDARY_MIN = 7; 
    const unsigned short int LEGENDARY_MAX = 10;
    const unsigned short int NORMAL_MIN_MAX_RANGE = 11;

    for(int i = 0; i < NUM_OF_POKEMONS; i++) {
        unsigned short int rand_mult;
        if(p_pokemons[i].is_legendary) {
            rand_mult = LEGENDARY_CONST * (rand() % (LEGENDARY_MAX - LEGENDARY_MIN) + LEGENDARY_MIN);
            p_pokemons[i].catch_difficulty = rand_mult;
        } else if(!p_pokemons[i].is_legendary) {
            rand_mult = NORMAL_CONST * (rand() % NORMAL_MIN_MAX_RANGE);
            p_pokemons[i].catch_difficulty = rand_mult;
        }
    }
   
}

Ball* create_pokeball(char* type, unsigned short int modifier) {
    Ball* new_ball = malloc(sizeof(Ball));
    new_ball->type = malloc(strlen(type) + 1);

    if(new_ball == NULL || new_ball->type == NULL) {
        fprintf(stderr, "Failed mallocation for new_ball");
        free(new_ball->type);
        free(new_ball);
        exit(EXIT_MALLOC_FAILURE);
    }

    strcpy(new_ball->type , type);
    new_ball->catch_chance = BALL_BASE_VAL * modifier;
    return new_ball;
}

BallNode* _init_ball_llist() {
    BallNode* head = malloc(sizeof(BallNode));
    BallNode* first_node = malloc(sizeof(BallNode));
    BallNode* second_node = malloc(sizeof(BallNode));
    BallNode* third_node = malloc(sizeof(BallNode));

    if(head == NULL || first_node == NULL || second_node == NULL || third_node == NULL) {
        fprintf(stderr, "ERROR :: MALLOC FAILED FOR _INIT_BALL_LLIST");
        free(head);
        free(first_node);
        free(second_node);
        free(third_node);
        exit(EXIT_MALLOC_FAILURE);
    }

    Ball* starter_pokeball = create_pokeball("pokeball", 1.5);
    Ball* starter_greatball = create_pokeball("greatball", 3);
    Ball* starter_ultraball = create_pokeball("ultraball", 5);
    Ball* starter_masterball = create_pokeball("masterball", 10);

    head->data = starter_pokeball;
    head->next = first_node;
    first_node->data = starter_greatball;
    first_node->next = second_node;
    second_node->data = starter_ultraball;
    second_node->next = third_node;
    third_node->data = starter_masterball;
    third_node->next = NULL;
    
    return head;

}

void disp_inv_ball_list(BallNode* head) {
    int ball_inv_amount = 1;
    int index = 1;
    while(head != NULL) {
        printf("%d : %d x %s \n", index, ball_inv_amount, head->data->type);
        head = head->next;
        index++;
    }
}

Pokemon* gen_rand_pokemon(Pokemon* p_pokemons, unsigned short int size) {
    unsigned short int random_index = rand() % size;
    while((p_pokemons + random_index)->is_legendary) {
        const unsigned short int LEGENDARY_THRESHOLD = 100;
        unsigned short int max = 1000;
        unsigned short int curtail_randomizer = rand() % max;
        if(curtail_randomizer <= LEGENDARY_THRESHOLD) {
            return p_pokemons + random_index;
        } else {
            random_index = rand() % size;
        }
    }
    return p_pokemons + random_index;
}

void disp_walking() {
    const unsigned short int MAX_SLEEP_INTERVAL = 4;
                 unsigned short int random_sleep_interval = rand() % MAX_SLEEP_INTERVAL;
                 bool _done_walking = false;
                 while(!_done_walking) {
                    sleep(2);
                    printf("Walking... \n");
                    sleep(MAX_SLEEP_INTERVAL);
                    _done_walking = true;
                 }
                 
}


Ball* choose_ball(BallNode* head, int ball_option) {
    BallNode* curr = head;
    int _iter = 1;
    while(_iter != ball_option) {
        curr = curr->next;
        _iter++;
    }

    return curr->data;
}

PokeNode* add_to_pokedex(Pokemon* pokemon, PokeNode* head) {
    PokeNode* new_node = malloc(sizeof(PokeNode));
    new_node->data = pokemon;
    new_node->next = NULL;

    if(head == NULL) {
        head = new_node;
    } else {
        PokeNode* tmp = malloc(sizeof(PokeNode));
        tmp = head;
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_node;


    }
    return head;
}


void disp_pokemon(Pokemon* pokemon, unsigned short int index) {
    printf("\n POKEMON %d { NAME : %s , TYPE : %s } \n", index, pokemon->name, pokemon->type);
};

void add_to_showcase(Player* player, int showcase_option) {
    int _iter = 1;
    PokeNode* tmp = player->Phead;
    printf("SHOWCASE OPT: %d", showcase_option);
    while (_iter != showcase_option) {
        tmp = tmp->next;
        _iter++;
    }
    
    free(player->showcase); // Free existing showcase memory if it exists
    player->showcase = strdup(tmp->data->name);
    if (player->showcase == NULL) {
        fprintf(stderr, "Memory allocation failed for showcase");
        exit(EXIT_MALLOC_FAILURE);
    }

    
}

void free_pokedex(Player* player) {

    PokeNode* tmp = player->Phead;
    if(tmp == NULL) {
        fprintf(stderr, "ERROR :: MEM ALLOC FAILED FOR TMP \n");
        free(tmp);
        exit(EXIT_MALLOC_FAILURE);
    }

    while(tmp != NULL) {
        free(tmp->data->name);
        free(tmp->data->type);
        tmp = tmp->next;
    }
}

void free_pokeballs(Player* player) {
    BallNode* tmp = player->Bhead;

    if(tmp == NULL) {
        fprintf(stderr, "ERROR :: MEM ALLOC FAILED FOR TMP \n");
        free(tmp);
        exit(EXIT_MALLOC_FAILURE);
    }

    while(tmp != NULL) {
        free(tmp->data->type);
        free(tmp->data->catch_chance);
        free(tmp->data->modifier);
        tmp = tmp->next;
    }
}


