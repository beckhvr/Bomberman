#define ELEMENT_SIZE 50
#define PLAYER_HITBOX_SIZE 30
#define PLAYER_SIZE 40

typedef struct s_player_info
{
  int playing;
  int x;
  int y;
  int direction;
  int bombs;
  int cooldown;
  int hp;
} t_player_info;

typedef struct s_container
{
  t_player_info players[4];
   char map[170];
} t_container;

typedef struct s_event
{
  int x;
  int y;
  int direction;
  int bomb;
} t_event;

