typedef struct s_player_info
{
  int playing;
  int x;
  int y;
  int direction;
  int hp;
} t_player_info;

typedef struct s_container
{
  t_player_info players[4];
   char map[1024];
} t_container;

typedef struct s_event
{
  int x;
  int y;
  int direction;
  int bomb;
} t_event;

