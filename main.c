#include <conio.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#define BALL_BASE_VAL 10
#define INPUT_BUFFER 256
#define NUM_OF_POKEMONS 20

typedef struct Ball
{
    char *type;
    unsigned short int modifier;     // based on type 1.5 , 3 , 5 , 10
    unsigned short int catch_chance; // base * modifier
} Ball;

typedef struct BallNode
{
    Ball *data;
    struct BallNode *next;
} BallNode;

typedef struct Pokemon
{
    char *name;
    char *type;
    bool is_legendary;
    unsigned short int catch_difficulty; // 10 - 100 , if ball catch_chance >=
                                         // catch_difficulty ? success : fail
} Pokemon;

typedef struct PokeNode
{
    Pokemon *data;
    struct PokeNode *next;
} PokeNode;

typedef struct Player
{
    BallNode *Bhead; // [ball1 -> ball2 -> NULL]
    PokeNode *Phead; // linked list of the pokemons the player has
    char *showcase;
    char *username;
    char id[9];
    unsigned short int xp;
    unsigned short int points;
} Player;

//[ENUMS]
enum Colors
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    AQUA = 3,
    RED = 4,
    PURPLE = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 0xA,  // 0xA is equivalent to 10 in decimal
    LIGHT_AQUA = 0xB,   // 0xB is equivalent to 11 in decimal
    LIGHT_RED = 0xC,    // 0xC is equivalent to 12 in decimal
    LIGHT_PURPLE = 0xD, // 0xD is equivalent to 13 in decimal
    LIGHT_YELLOW = 0xE, // 0xE is equivalent to 14 in decimal
    BRIGHT_WHITE = 0xF, // 0xF is equivalent to 15 in decimal
    DEFAULT = 0x07
};

// EXIT CODES
const unsigned short int EXIT_MALLOC_FAILURE = 2;

//[HANDLERS]
HANDLE hc;

/* [FUNCTIONAL PROTOTYPES]*/

// [displays / menu]
void welcome(char *version);
unsigned short int get_menu(Player *player);
void disp_inv_ball_list(BallNode *head);
void disp_walking();
void disp_pokemon(Pokemon *pokemon, unsigned short int index);
void disp_shop(Player *player)
{
    printf("=== ITEM SHOP === \n [ YOU HAVE %hu POINTS ]\n", player->points);
    printf("!! COMING SOON !!");

    // printf("1 : BUY MORE BALLS \n");
}

void style_printf_encountered(WORD text_color, Pokemon *pokemon);

//[input function]
Player *get_player();

//[constructors]
Ball *create_pokeball(char *type, unsigned short int modifier);

//[initializers]
void _init_pokemons_list(Pokemon *p_pokemons);
BallNode *_init_ball_llist();

//[generators]
Pokemon *gen_rand_pokemon(Pokemon *p_pokemons, unsigned short int size);

//[actions]
Ball *choose_ball(Player *player, int *ball_option);
PokeNode *add_to_pokedex(Pokemon *pokemon, PokeNode *head);
void add_to_showcase(Player *player, int showcase_option);
BallNode *remove_ball(Player *player, int ball_option);
void throw_ball(Ball *chosen_ball, Pokemon *random_pokemon, Player *player);

//[DEALLOCATORS]
void free_pokedex(Player *player);
void free_pokeballs(Player *player);

/*
===== TO DO ====
1 : refactor and dry up code
2 : implement store
*/

int main()
{
    hc = GetStdHandle(STD_OUTPUT_HANDLE);
    Player *player = malloc(sizeof(Player));

    if (player == NULL)
    {
        fprintf(stderr, "ERROR :: MEM ALLOC FAILED FOR PLAYER \n");
        free(player);
        exit(EXIT_MALLOC_FAILURE);
    }

    player->showcase = NULL;
    Pokemon pokemons[NUM_OF_POKEMONS];
    Pokemon *p_pokemons = &pokemons[0];
    bool _has_init = false;

    char *version = "v0.0.0-unreleased";
    system("cls");
    welcome(version);

    player = get_player();
    player->Bhead = _init_ball_llist();
    SetConsoleTextAttribute(hc, YELLOW);
    printf("\n ==== HERE ARE YOUR STARTING BALLS ==== \n");
    disp_inv_ball_list(player->Bhead);

    player->Phead = NULL;

    printf("press any key to go to the menu...");
    getch();
    unsigned short int menu_option = 0;
    const unsigned short int MENU_EXIT = 4;

    while (menu_option != MENU_EXIT)
    {
        system("cls");
        fflush(stdin);

        menu_option = get_menu(player);
        switch (menu_option)
        {
        case 1:
            if (!_has_init)
            {
                _init_pokemons_list(p_pokemons);
                _has_init = true;
            }
            disp_walking();
            Pokemon *random_pokemon =
                gen_rand_pokemon(p_pokemons, NUM_OF_POKEMONS);
            if (random_pokemon->is_legendary)
            {
                style_printf_encountered(YELLOW, random_pokemon);
            }
            else
            {
                style_printf_encountered(LIGHT_AQUA, random_pokemon);
            }

            if (player->Bhead == NULL)
            {
                printf(
                    ":: YOU DO NOT HAVE ANY POKEBALLS VISIT THE STORE TO "
                    "BUY MORE :: \n");
                break;
            }
            int catch_option = 0;
            printf("[1] catch [2] run\n");
            scanf("%d", &catch_option);
            switch (catch_option)
            {
            case 1:
                printf("\n=== CHOOSE A BALL TO USE ===\n");
                int ball_option = 0;
                Ball *chosen_ball = choose_ball(player, &ball_option);

                int action = 0;
                printf("[1] throw ball [2] change ball [3] run \n");
                scanf("%d", &action);
                while (action == 2)
                {
                    chosen_ball = choose_ball(player, &ball_option);
                    printf("[1] throw ball [2] change ball [3] run");
                    scanf("%d", &action);
                }

                if (action == 1)
                {
                    throw_ball(chosen_ball, random_pokemon, player);
                    player->Bhead = remove_ball(player, ball_option);
                }
                else if (action == 3)
                {
                    SetConsoleTextAttribute(hc,
                                            RED | FOREGROUND_INTENSITY);
                    printf("** YOU RAN AWAY :: POKEMON FLED **\n");
                    SetConsoleTextAttribute(hc, DEFAULT);
                    printf("press any key to go to the menu...");
                }

                getch();
                break;
            case 2:
                SetConsoleTextAttribute(hc, RED | FOREGROUND_INTENSITY);
                printf("** YOU RAN AWAY :: POKEMON FLED **");
                SetConsoleTextAttribute(hc, DEFAULT);
                getch();
                break;
            default:
                printf("Invalid option try again : ");
                break;
            }

            getch();
            break;
        case 2:
            printf("\n === SHOWCASE === \n");
            printf("[ CHOOSE A POKEMON ] \n");

            if (player->Phead == NULL)
            {
                SetConsoleTextAttribute(hc, RED | FOREGROUND_INTENSITY);
                printf(":: NO POKEMONS IN POKEDEX CURRENTLY :: \n");
                SetConsoleTextAttribute(hc, DEFAULT);
            }
            else
            {
                int showcase_index = 1;
                PokeNode *tmp = player->Phead;
                int showcase_choice = 0;

                while (tmp != NULL)
                {
                    disp_pokemon(tmp->data, showcase_index);
                    tmp = tmp->next;
                    showcase_index++;
                }

                printf("ENTER A POKEMON NUMBER TO SHOWCASE : ");
                scanf("%d", &showcase_choice);
                while (showcase_choice >= showcase_index)
                {
                    SetConsoleTextAttribute(hc, RED | FOREGROUND_INTENSITY);
                    printf(":: ERROR CHOICE OUT OF RANGE RE-ENTER \n");
                    SetConsoleTextAttribute(hc, DEFAULT);
                    scanf("%d", &showcase_choice);
                }

                add_to_showcase(player, showcase_choice);
            }

            getch();
            break;
        case 3:
            disp_shop(player);
            getch();
            break;
        case 4:
            free_pokedex(player);
            free_pokeballs(player);
            player->Phead = NULL;
            player->Bhead = NULL;
            free(player->showcase);
            free(player->username);

            free(player);
            printf("Thanks for playing!");

            break;
        default:
        {
            printf("Invalid option try again : ");
            getch();
        }
        }
    }

    return 0;
}

void welcome(char *version)
{
    printf("====== WELCOME TO POKEMON C %s ====== \n", version);
    printf("Pokemon C is a pokemon simulator\n");
    printf("[] catch pokemons\n[] showcase your pokemons\n");
    printf("press any key to begin ...");
    getch();
}

unsigned short int get_menu(Player *player)
{
    unsigned short int option = 0;
    printf("\n === POKEMON C ===\t\t\t");
    SetConsoleTextAttribute(hc, BLUE | FOREGROUND_INTENSITY);
    printf(
        "USER { username : %s, id : %s, xp : %hu, points : %hu, showcase : %s "
        "}\n ",
        player->username, player->id, player->xp, player->points,
        player->showcase);
    SetConsoleTextAttribute(hc, BRIGHT_WHITE | FOREGROUND_INTENSITY);
    printf("1 : CATCH \n 2 : SHOWCASE \n 3 : ITEM SHOP \n 4 : EXIT \n");
    SetConsoleTextAttribute(hc, DEFAULT);
    scanf("%hu", &option);
    return option;
}

Player *get_player()
{
    srand(time(NULL));
    Player *new_player = malloc(sizeof(Player));

    if (new_player == NULL)
    {
        fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER");
        free(new_player);
        exit(EXIT_MALLOC_FAILURE);
    }

    new_player->xp = 0;
    new_player->Bhead = NULL;
    new_player->Phead = NULL;
    new_player->showcase = malloc(4);
    new_player->points = 0;

    if (new_player->showcase == NULL)
    {
        fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER->SHOWCASE");
        free(new_player->showcase);
        exit(EXIT_MALLOC_FAILURE);
    }
    strcpy(new_player->showcase, "TBA");

    char input[INPUT_BUFFER];

    printf("\n\n\n\n What is your username : \n");
    char *p_input = fgets(input, INPUT_BUFFER, stdin);
    strtok(p_input, "\n");
    new_player->username = malloc(strlen(p_input) + 1);
    if (new_player->username == NULL)
    {
        fprintf(stderr, "ERROR :: MALLOC FAILED FOR NEW_PLAYER->USERNAME");
        free(new_player->username);
        exit(EXIT_MALLOC_FAILURE);
    }
    strcpy(new_player->username, p_input);

    char uuid[9];
    const unsigned short int MIN_ASCII_NUMBER = 48;
    const unsigned short int MAX_ASCII_NUMBER = 57;
    const unsigned short int MIN_ASCII_LLETTER = 97;
    const unsigned short int MAX_ASCII_LLETTER = 122;

    for (int i = 0; i < 8; i++)
    {
        int rand_code;
        if (i % 2 == 0)
        {
            rand_code = rand() % (MAX_ASCII_NUMBER - MIN_ASCII_NUMBER) +
                        MIN_ASCII_NUMBER;
        }
        else
        {
            rand_code = rand() % (MAX_ASCII_LLETTER - MIN_ASCII_LLETTER) +
                        MIN_ASCII_LLETTER;
        }
        uuid[i] = (char)rand_code;
    }

    strcpy(new_player->id, uuid);
    SetConsoleTextAttribute(hc, BLUE | FOREGROUND_INTENSITY);
    printf("USER : %s \n", new_player->username);
    printf("YOUR UUID : %s \n", new_player->id);
    printf("XP : %hu \n", new_player->xp);
    printf("POINTS : %hu ", new_player->points);
    SetConsoleTextAttribute(hc, DEFAULT);
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

void _init_pokemons_list(Pokemon *p_pokemons)
{
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
    const unsigned short int NORMAL_MIN_RANGE = 1;
    const unsigned short int NORMAL_MAX_RANGE = 11;

    for (int i = 0; i < NUM_OF_POKEMONS; i++)
    {
        unsigned short int rand_mult;
        if (p_pokemons[i].is_legendary)
        {
            rand_mult =
                LEGENDARY_CONST *
                (rand() % (LEGENDARY_MAX - LEGENDARY_MIN) + LEGENDARY_MIN);
            p_pokemons[i].catch_difficulty = rand_mult;
        }
        else if (!p_pokemons[i].is_legendary)
        {
            rand_mult =
                NORMAL_CONST * (rand() % (NORMAL_MAX_RANGE - NORMAL_MIN_RANGE) +
                                NORMAL_MIN_RANGE);
            p_pokemons[i].catch_difficulty = rand_mult;
        }
    }
}

Ball *create_pokeball(char *type, unsigned short int modifier)
{
    Ball *new_ball = malloc(sizeof(Ball));
    new_ball->type = malloc(strlen(type) + 1);

    if (new_ball == NULL || new_ball->type == NULL)
    {
        fprintf(stderr, "Failed mallocation for new_ball");
        free(new_ball->type);
        free(new_ball);
        exit(EXIT_MALLOC_FAILURE);
    }

    strcpy(new_ball->type, type);
    new_ball->catch_chance = BALL_BASE_VAL * modifier;
    return new_ball;
}

BallNode *_init_ball_llist()
{
    BallNode *head = malloc(sizeof(BallNode));
    BallNode *first_node = malloc(sizeof(BallNode));
    BallNode *second_node = malloc(sizeof(BallNode));
    BallNode *third_node = malloc(sizeof(BallNode));

    if (head == NULL || first_node == NULL || second_node == NULL ||
        third_node == NULL)
    {
        fprintf(stderr, "ERROR :: MALLOC FAILED FOR _INIT_BALL_LLIST");
        free(head);
        free(first_node);
        free(second_node);
        free(third_node);
        exit(EXIT_MALLOC_FAILURE);
    }

    Ball *starter_pokeball = create_pokeball("pokeball", 1.5);
    Ball *starter_greatball = create_pokeball("greatball", 3);
    Ball *starter_ultraball = create_pokeball("ultraball", 5);
    Ball *starter_masterball = create_pokeball("masterball", 10);

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

void disp_inv_ball_list(BallNode *head)
{
    int ball_inv_amount = 1;
    int _iter = 1;

    while (head != NULL)
    {
        SetConsoleTextAttribute(hc, BRIGHT_WHITE | FOREGROUND_INTENSITY);
        printf("%d : %d x %s \n", _iter, ball_inv_amount, head->data->type);
        head = head->next;
        _iter++;
    }
    SetConsoleTextAttribute(hc, DEFAULT);
}

Pokemon *gen_rand_pokemon(Pokemon *p_pokemons, unsigned short int size)
{
    unsigned short int random_index = rand() % size;
    while ((p_pokemons + random_index)->is_legendary)
    {
        const unsigned short int LEGENDARY_THRESHOLD = 100;
        unsigned short int max = 1000;
        unsigned short int curtail_randomizer = rand() % max;
        if (curtail_randomizer <= LEGENDARY_THRESHOLD)
        {
            return p_pokemons + random_index;
        }
        else
        {
            random_index = rand() % size;
        }
    }
    return p_pokemons + random_index;
}

void disp_walking()
{
    const unsigned short int MAX_SLEEP_INTERVAL = 4;
    unsigned short int random_sleep_interval = rand() % MAX_SLEEP_INTERVAL;
    bool _done_walking = false;
    while (!_done_walking)
    {
        sleep(1);
        printf("Walking... \n");
        sleep(1);
        printf("Walking... \n");
        sleep(MAX_SLEEP_INTERVAL);
        _done_walking = true;
    }
}

Ball *choose_ball(Player *player, int *ball_option)
{
    disp_inv_ball_list(player->Bhead);
    int option = 0;
    scanf("%d", &option);

    BallNode *curr_ball = player->Bhead;
    int _iter = 1;
    while (_iter != option)
    {
        curr_ball = curr_ball->next;
        _iter++;
    }

    *ball_option = option;
    printf("** You chose a %s with a catch chance of %hu ** \n",
           curr_ball->data->type, curr_ball->data->catch_chance);
    return curr_ball->data;
}

PokeNode *add_to_pokedex(Pokemon *pokemon, PokeNode *head)
{
    PokeNode *new_node = malloc(sizeof(PokeNode));
    new_node->data = pokemon;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        PokeNode *tmp = malloc(sizeof(PokeNode));
        tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
    }
    return head;
}

void disp_pokemon(Pokemon *pokemon, unsigned short int index)
{
    printf("\n POKEMON %d { NAME : %s , TYPE : %s } \n", index, pokemon->name,
           pokemon->type);
};

void add_to_showcase(Player *player, int showcase_option)
{
    int _iter = 1;
    PokeNode *tmp = player->Phead;
    printf("SHOWCASE OPT: %d", showcase_option);
    while (_iter != showcase_option)
    {
        tmp = tmp->next;
        _iter++;
    }

    free(player->showcase); // Free existing showcase memory if it exists
    player->showcase = strdup(tmp->data->name);
    if (player->showcase == NULL)
    {
        fprintf(stderr, "Memory allocation failed for showcase");
        exit(EXIT_MALLOC_FAILURE);
    }
}

void free_pokedex(Player *player)
{
    PokeNode *tmp = player->Phead;
    while (tmp != NULL)
    {
        free(tmp->data->name);
        free(tmp->data->type);
        tmp = tmp->next;
    }
}

void free_pokeballs(Player *player)
{
    BallNode *tmp = player->Bhead;
    while (tmp != NULL)
    {
        free(tmp->data->type);
        tmp = tmp->next;
    }
}

BallNode *remove_ball(Player *player, int ball_option)
{
    BallNode *curr = player->Bhead;
    BallNode *prev = player->Bhead;

    if (ball_option != 1)
    {
        int _iter = 1;
        while (_iter != ball_option - 1)
        {
            prev = prev->next;
            _iter++;
        }

        _iter = 1;
        while (_iter != ball_option)
        {
            curr = curr->next;
            _iter++;
        }

        prev->next = curr->next;
        curr->next = NULL;
        free(curr);
    }
    else if (ball_option == 1)
    {
        curr = curr->next;
        prev->next = NULL;
        free(prev);
        player->Bhead = curr;
    }

    return player->Bhead;
}

void throw_ball(Ball *chosen_ball, Pokemon *random_pokemon, Player *player)
{
    if (chosen_ball->catch_chance >= random_pokemon->catch_difficulty)
    {
        player->Phead = add_to_pokedex(random_pokemon, player->Phead);
        unsigned short int previous_xp = player->xp;
        unsigned short int previous_points = player->points;
        if (player->xp == 0)
        {
            player->xp += random_pokemon->catch_difficulty + player->xp;
            player->points += random_pokemon->catch_difficulty + player->points;
        }
        else
        {
            player->xp +=
                random_pokemon->catch_difficulty * floor(player->xp / 2);
            player->points +=
                random_pokemon->catch_difficulty + player->points + 50;
        }

        SetConsoleTextAttribute(hc, 0xF | FOREGROUND_INTENSITY);
        printf(
            " ** YOU CAUGHT %s ** POKEMON { NAME : %s , TYPE : %s } HAS BEEN "
            "ADDED TO YOUR POKEDEX \n ",
            random_pokemon->name, random_pokemon->name, random_pokemon->type);
        SetConsoleTextAttribute(hc, 0x07);

        SetConsoleTextAttribute(hc, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("YOU GAINED %hu XP and %hu points!",
               abs(player->xp - previous_xp),
               abs(player->points - previous_points));
        SetConsoleTextAttribute(hc, 0x07);
    }
    else
    {
        printf("~~ MISSED ~~");
        // re throw or pokemon flees
    }
}

void style_printf_encountered(WORD text_color, Pokemon *pokemon)
{
    SetConsoleTextAttribute(hc, text_color | FOREGROUND_INTENSITY);
    printf("** YOU ENCOUNTERED : %s **\n", pokemon->name);
    SetConsoleTextAttribute(hc, DEFAULT);
}
