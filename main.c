#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define BALL_BASE_VAL 10
#define INPUT_BUFFER 256

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
    PokeNode* Phead; 
    char* showcase;   
    char* username;
    char  id[9];
    int xp;
} Player;

/* [FUNCTIONAL PROTOTYPES]*/

void welcome(char* version);
unsigned short int get_menu(Player* player);
Player* get_player();
void _init_pokemons_list(Pokemon* p_pokemons);
Ball* create_pokeball(char* type, unsigned short int modifier);
BallNode* _init_ball_llist();


/* 
===== TO DO ====
1 : implement catching
2 : implement showcase

*/

int main() {
    Player* player = malloc(sizeof(Player));
    Pokemon pokemons[20];
    Pokemon* p_pokemons = &pokemons[0];
    

    char* version = "0.0.1v";
    system("cls");
    welcome(version);
    
    player = get_player();
    player->Bhead = _init_ball_llist();

    printf("\n ==== HERE ARE YOUR STARTING BALLS ==== \n");
    int ball_inv_index = 1;
    while(player->Bhead != NULL) {
        printf("%d : %s \n", ball_inv_index, player->Bhead->data->type);
        player->Bhead = player->Bhead->next;
        ball_inv_index++;
    }
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
                
                 _init_pokemons_list(p_pokemons);
                 
                
                getch();
            break;
            case 2 :
                printf("Showcase");
                getch(); 
            break;
            case 3 :
                printf("Thanks for playing!");
                getch();
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
    printf("\n === POKEMON C ===\t\t\tUSER { username : %s, id : %s, xp : %d, showcase : TBA }\n ", player->username, player->id, player->xp);
    printf("1 : CATCH \n 2 : SHOWCASE \n 3 : EXIT \n");
    scanf("%hu", &option);

    return option;

}

Player* get_player() {
   srand(time(NULL));
   Player* new_player = malloc(sizeof(Player));
   new_player->xp = 0;
   new_player->Bhead = NULL;
   new_player->Phead = NULL;
   
   char input[INPUT_BUFFER];

   printf("\n What is your username : \n");
   char* p_input = fgets(input, INPUT_BUFFER, stdin);
   strtok(p_input, "\n");
   new_player->username = malloc(strlen(p_input) + 1);
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

    const unsigned short int LEGENDARY_CONST = 10;
    const unsigned short int NORMAL_CONST = 5;
    const unsigned short int LEGENDARY_MIN = 7; 
    const unsigned short int LEGENDARY_MAX = 10;
    const unsigned short int NORMAL_MIN_MAX_RANGE = 11;

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

    for(int i = 0; i < 20; i++) {
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
        return NULL;
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
    
    BallNode* tmp = head;

    return head;

}

