#define FPS 60
#define FRAME_DELAY 1000 / FPS
#define RELEASE 1

//SDL stuff
typedef struct _sdl
{
                SDL_Renderer * renderer;
                SDL_Window * window;
                SDL_Event e;
                SDL_Texture * m_texture;
	SDL_Rect m_rect;
                int muted;
}_sdl;

//Game global stuff
enum game_state{MAIN_MENU,PLAY,PAUSE_MENU,DEAD};
typedef struct game
{
                int running;
                enum game_state state;
                SDL_Rect camera;
}game;

///!---INIT---!//
static game g = {true,MAIN_MENU,{0,0,640,480}};
static _sdl s = {NULL,NULL};

//Player stuff
static int player_id = 0;
enum direction {UP,DOWN,LEFT,RIGHT,NONE};
static int player_shoot = false;
static enum direction shoot_direction = NONE;
static int pressed_up = false, pressed_down = false,pressed_left = false,pressed_right = false;
static int dead_timer = -1;

//Spawner
static int factor = 0;
static enemies_alive = 0;
static int level = 0;
static int xp = 0;
static int xp_required = 100;

//Kills and level
static int swordsman_killed = 0;
static int biggie_killed = 0;
static int christian_killed = 0;
static int axe_man_killed = 0;
static int miniboss_killed = 0;

static SDL_Rect swordsman_figure = {0,0,35,35};
static SDL_Rect biggie_figure = {0,0,45,45};
static SDL_Rect christian_figure = {0,0,35,35};
static SDL_Rect axe_man_figure = {0,0,40,40};
static SDL_Rect miniboss_figure = {0,0,32,32};

static SDL_Texture * swordsman_score = NULL;
static SDL_Texture * biggie_score = NULL;
static SDL_Texture * christian_score = NULL;
static SDL_Texture * axe_man_score = NULL;
static SDL_Texture * miniboss_score = NULL;
static SDL_Texture * level_score = NULL;

static SDL_Rect s_score = {0,0,0,0};
static SDL_Rect b_score = {0,0,0,0};
static SDL_Rect c_score = {0,0,0,0};
static SDL_Rect a_score = {0,0,0,0};
static SDL_Rect m_score = {0,0,0,0};
static SDL_Rect level_rect = {260,70,0,0};

//Power info
static int killed = 0;
static const int goals[9] = {8,10,14,6,9,11,20,0,0};
static int current_goal = 8;
static int current_index = 0;
static int power_text;
static int goal_text;
static int max_lvl = false;
static int hp_text = 0;
static int lvl_text = 0;

//Main menu stuff
static int options = false;
static int menu_cursor_position = 0;
static int options_cursor_position = 0;
static int changing_volume = false;
static int fullscreen = true;
static int max_volume = 128;
static int volume = 128;

static SDL_Rect play_rect = {0,0,0,0};
static SDL_Rect options_rect = {0,0,0,0};
static SDL_Rect exit_rect = {0,0,0,0};
static SDL_Rect cursor_rect = {0,0,0,0};
static SDL_Texture *play_texture = NULL;
static SDL_Texture *options_texture = NULL;
static SDL_Texture *exit_texture = NULL;
static SDL_Texture *cursor_texture = NULL;

static SDL_Rect volume_rect = {0,0,0,0};
static SDL_Rect fullscreen_rect = {0,0,0,0};
static SDL_Rect back_rect = {0,0,0,0};
static SDL_Rect on_rect = {0,0,0,0};
static SDL_Rect off_rect = {0,0,0,0};
static SDL_Texture *volume_texture = NULL;
static SDL_Texture *fullscreen_texture = NULL;
static SDL_Texture *on_texture = NULL;
static SDL_Texture *off_texture = NULL;
static SDL_Texture *back_texture = NULL;
//Options stuff
static int pause_options = false;
static int pause_cursor_position = 0;
static int pause_options_cursor_position = 0;
static SDL_Rect resume_rect = {0,0,0,0};
static SDL_Rect pause_options_rect = {0,0,0,0};
static SDL_Rect main_menu_rect = {0,0,0,0};
static SDL_Texture *resume_texture = NULL;
static SDL_Texture *main_menu_texture = NULL;
//dead screen stuff
static int dead_cursor_position = 0;
static SDL_Rect retry_rect = {0,0,0,0};
static SDL_Rect dead_main_menu_rect = {0,0,0,0};
static SDL_Rect dead_exit_rect = {0,0,0,0};
static SDL_Texture *retry_texture = NULL;


//Testing
static int enemy_to_spawn = 1;
static int to_run = 1;

//Screen shake
static int shake_timer = 0;
enum ss_amount{SMALL,MEDIUM,BIG,NO};
static enum ss_amount amount = NO;

///!---ANIMATIONS AND TEXTURES---!///
typedef struct animation_info
{
                char name[255];
                SDL_Rect starting_;
                int number_of_frames;
                int frame_rate;
                int x_offset;
                int y_offset;
                struct animation_info* next;
}animation_info;

static animation_info* head = NULL;

//Textures
static SDL_Texture * arrow_h = NULL;
static SDL_Texture * arrow_v = NULL;
static SDL_Texture *arena_texture = NULL;
static SDL_Texture *bigger_arena_texture = NULL;
static SDL_Texture *player_texture = NULL;
static SDL_Texture *swordsman_texture = NULL;
static SDL_Texture *biggie_texture = NULL;
static SDL_Texture *christian_texture = NULL;
static SDL_Texture *axe_man_texture = NULL;
static SDL_Texture* miniboss_texture = NULL;
static SDL_Texture* ui_face = NULL;

//Sounds
static Mix_Music *main_menu_music = NULL;
static Mix_Music *main_theme = NULL;
static Mix_Music *death_theme = NULL;
static Mix_Chunk *shoot = NULL;
static Mix_Chunk *hit = NULL;