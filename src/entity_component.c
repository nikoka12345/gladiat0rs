#define MAX_ENTITIES 300

typedef struct entity
{
    int id;
    int destroyed;
    char type[200];
    
    //indices of components
    int position_index;
    int velocity_index;
    int collision_index;
    int ai_index;
    int sprite_index;
    int animation_index;
    int stat_index;
}entity;

static entity entities[MAX_ENTITIES];

static
void init_entities()
{
    for(int i=0;i<MAX_ENTITIES;i++)
    {
        entities[i].id = -1;
        entities[i].destroyed = false;
        
        //init component indices in arrays
        entities[i].position_index = -1;
        entities[i].velocity_index = -1;
        entities[i].collision_index = -1;
        entities[i].ai_index = -1;
        entities[i].sprite_index = -1;
        entities[i].animation_index = -1;
        entities[i].stat_index = -1;
    }
}

static
int create_entity(char * entity_type)
{
    int i = 0;
    for(i = 0;i<MAX_ENTITIES;i++)
    {
        if(entities[i].id == -1 || entities[i].destroyed == true)
            break;
    }
    entities[i].id = i;
    entities[i].destroyed = false;
    strcpy(entities[i].type, entity_type);
    
    return i;
}

///////////////////COMPONENTS/////////////////////
/*
POSITION
VELOCITY
COLLISION
SPRITE
ANIMATION
AI
STAT
*/

#define MAX_POSITION_COMPONENTS 300
#define MAX_VELOCITY_COMPONENTS 300
#define MAX_POSITION_COMPONENTS 300
#define MAX_COLLISION_COMPONENTS 300
#define MAX_AI_COMPONENTS 300
#define MAX_SPRITE_COMPONENTS 300
#define MAX_ANIMATION_COMPONENTS 300
#define MAX_STAT_COMPONENTS 300


//!-------POSITION-------!//
typedef struct position_component
{
    int entity_id;
    int x,y,w,h;
    int destroyed;
}position_component;

static position_component positions[MAX_POSITION_COMPONENTS];

static
void add_position_component(int entity_id_,int x,int y, int w,int h)
{
    int i = 0;
    for(i = 0;i< MAX_POSITION_COMPONENTS;i++)
    {
        if(positions[i].entity_id == -1 || positions[i].destroyed == true)
            break;
    }
    positions[i].entity_id = entity_id_;
    positions[i].x = x;
    positions[i].y = y;
    positions[i].w = w;
    positions[i].h = h;
    positions[i].destroyed = false;
    
    
    entities[entity_id_].position_index = i;
}

//!-------VELOCITY-------!//
typedef struct velocity_component
{
    int entity_id;
    float dx,dy;
    int destroyed;
}velocity_component;
static velocity_component velocities[MAX_VELOCITY_COMPONENTS];

static
void add_velocity_component(int entity_id_,int dx,int dy)
{
    int i = 0;
    for(i = 0;i< MAX_VELOCITY_COMPONENTS;i++)
    {
        if(velocities[i].entity_id == -1 || velocities[i].destroyed == true)
            break;
    }
    velocities[i].entity_id = entity_id_;
    velocities[i].dx = dx;
    velocities[i].dy = dy;
    velocities[i].destroyed = false;
    
    entities[entity_id_].velocity_index = i;
}

//!-------COLLISION-------!//
typedef struct collision_component
{
    int entity_id;
    int x,y,w,h;
    int dynamic;
    char * type;
    int destroyed;
}collision_component;
static collision_component collisions[MAX_COLLISION_COMPONENTS];


void add_collision_component(int entity_id_,int x,int y, int w,int h,int dynamic,char* type)
{
    int i = 0;
    for(i = 0;i< MAX_COLLISION_COMPONENTS;i++)
    {
        if(collisions[i].entity_id == -1 || collisions[i].destroyed == true)
            break;
    }
    
    collisions[i].entity_id = entity_id_;
    collisions[i].x = x;
    collisions[i].y = y;
    collisions[i].w = w;
    collisions[i].h = h;
    collisions[i].dynamic = dynamic;
    collisions[i].type = type;
    collisions[i].destroyed = false;
    
    entities[entity_id_].collision_index = i;
}

//!-------AI-------!//
typedef struct ai_component
{
    int entity_id;
    int wait_time;
    int attack_time;
    int hit_time;
    int knock_back;
    int ai_type;
    int destroyed;
    
    //For miniboss
    int spin;
    int spin_time;
    int daze_time;
    
}ai_component;
static ai_component ai[MAX_AI_COMPONENTS];


void add_ai_component(int entity_id_,int knock_back,int ai_type)
{
    int i = 0;
    for(i = 0;i< MAX_AI_COMPONENTS;i++)
    {
        if(ai[i].entity_id == -1 || ai[i].destroyed == true)
            break;
    }
    
    ai[i].entity_id = entity_id_;
    ai[i].wait_time = -1;
    ai[i].attack_time = -1;
    ai[i].hit_time = -1;
    ai[i].knock_back = knock_back;
    ai[i].ai_type = ai_type;
    ai[i].destroyed = false;
    
    entities[entity_id_].ai_index = i;
}
//!-------SPRITE-------!//
typedef struct sprite_component
{
    int entity_id;
    SDL_Texture * texture;
    SDL_RendererFlip flip_flags;
    SDL_Rect texture_part;
    int opacity;
    int fade;
    int fade_speed;
    int destroyed;
    int ui_text;
}sprite_component;
static sprite_component sprites[MAX_SPRITE_COMPONENTS];

void add_sprite_component(int entity_id_,SDL_Texture * texture,int fade,int fade_speed,SDL_RendererFlip flip_flags)
{
    
    int i = 0;
    for(i = 0;i< MAX_SPRITE_COMPONENTS;i++)
    {
        if(sprites[i].entity_id == -1 || sprites[i].destroyed == true)
            break;
    }
    
    SDL_Rect fake_part = {-1,-1,-1,-1};
    
    sprites[i].entity_id = entity_id_;
    sprites[i].texture = texture;
    sprites[i].texture_part = fake_part;
    sprites[i].flip_flags = flip_flags;
    sprites[i].opacity = 255;
    sprites[i].fade = fade;
    sprites[i].fade_speed = fade_speed;
    sprites[i].destroyed = false;
    sprites[i].ui_text = false;
    
    entities[entity_id_].sprite_index = i;
}
//!-------ANIMATION-------!//
typedef struct animation_component
{
    int entity_id;
    char animation_name[255];
    int start_time;
    int frame_rate;
    int last_frame;
    SDL_Texture * texture;
    SDL_Rect starting_position;
    int number_of_frames;
    int play_once;
    int done;
    SDL_RendererFlip flip_flags;
    int destroyed;
    int x_off;
    int y_off;
}animation_component;
static animation_component animations[MAX_ANIMATION_COMPONENTS];

void add_animation_component(int entity_id_,char* animation_name,SDL_Texture * texture,SDL_RendererFlip flip_flags,int play_once)
{
    int i = 0;
    for(i = 0;i< MAX_ANIMATION_COMPONENTS;i++)
    {
        if(animations[i].entity_id == -1 || animations[i].destroyed == true)
            break;
    }
    
    animations[i].entity_id = entity_id_;
    strcpy(animations[i].animation_name,animation_name);
    animations[i].texture = texture;
    animations[i].last_frame = 0;
    animations[i].start_time = SDL_GetTicks();
    animations[i].play_once = play_once;
    animations[i].flip_flags = flip_flags;
    animations[i].done = false;
    
    animation_info * temp = head;
    while(strcmp(animation_name,temp->name) != 0 && temp!= NULL)
        temp = temp->next;
    
    if(temp!= NULL)
    {
        animations[i].number_of_frames = temp->number_of_frames;
        animations[i].frame_rate = temp->frame_rate;
        animations[i].starting_position = temp->starting_;
        animations[i].x_off = temp->x_offset;
        animations[i].y_off = temp->y_offset;
    }
    
    animations[i].destroyed = false;
    
    entities[entity_id_].animation_index = i;
}
//!-------STAT-------!//
typedef struct stat_component
{
    int entity_id;
    int max_hp;
    int hp;
    int speed;
    int range_follow;
    int range_attack;
    int can_dmg;
    int dmg;
    int destroyed;
}stat_component;
static stat_component stats[MAX_STAT_COMPONENTS];

void add_stat_component(int entity_id_,int hp,int speed,int dmg,int range_follow,int range_attack)
{
    int i = 0;
    for(i = 0;i< MAX_STAT_COMPONENTS;i++)
    {
        if(stats[i].entity_id == -1 || stats[i].destroyed == true)
            break;
    }
    
    stats[i].entity_id = entity_id_;
    stats[i].max_hp = hp;
    stats[i].hp = hp;
    stats[i].speed = speed;
    stats[i].range_follow = range_follow;
    stats[i].range_attack = range_attack;
    stats[i].can_dmg = false;
    stats[i].dmg = dmg;
    stats[i].destroyed = false;
    
    entities[entity_id_].stat_index = i;
}

//!-------INIT ALL COMPONENTS-------!//
static
void init_components()
{
    //Position
    for(int i = 0;i<MAX_POSITION_COMPONENTS;i++)
    {
        positions[i].entity_id = -1;
        positions[i].x = 0;
        positions[i].y = 0;
        positions[i].w = 0;
        positions[i].h = 0;
        positions[i].destroyed = false;
    }
    
    //Velocity
    for(int i = 0;i< MAX_VELOCITY_COMPONENTS ;i++)
    {
        velocities[i].entity_id = -1;
        velocities[i].dx = 0;
        velocities[i].dy = 0;
        velocities[i].destroyed = false;
    }
    
    //Collision
    for(int i = 0;i<MAX_COLLISION_COMPONENTS;i++)
    {
        collisions[i].entity_id = -1;
        collisions[i].x = 0;
        collisions[i].y = 0;
        collisions[i].w = 0;
        collisions[i].h = 0;
        collisions[i].dynamic = 0;
        collisions[i].type = "";
        collisions[i].destroyed = false;
    }
    //AI
    for(int i = 0;i<MAX_AI_COMPONENTS;i++)
    {
        ai[i].entity_id = -1;
        ai[i].knock_back = false;
        ai[i].ai_type = 1;
        ai[i].destroyed = false;
        
        //For miniboss
        ai[i].spin = -1;
        ai[i].spin_time = -1;
        ai[i].daze_time = -1;
    }
    
    //Sprite
    for(int i = 0;i<MAX_SPRITE_COMPONENTS;i++)
    {
        sprites[i].entity_id = -1;
        sprites[i].texture = NULL;
        sprites[i].flip_flags = SDL_FLIP_NONE;
        sprites[i].opacity = 255;
        sprites[i].fade = false;
        sprites[i].destroyed = false;
    }
    
    //Animation
    for(int i = 0;i<MAX_ANIMATION_COMPONENTS;i++)
    {
        animations[i].entity_id = -1;
        animations[i].texture = NULL;
        animations[i].number_of_frames = 0;
        animations[i].frame_rate = 0;
        animations[i].last_frame = 0;
        animations[i].start_time = 0;
        animations[i].play_once = false;
        animations[i].done = false;
        animations[i].flip_flags = SDL_FLIP_NONE;
        animations[i].destroyed = false;
        animations[i].x_off = 0;
        animations[i].y_off = 0;
    }
    
    //Stat
    for(int i = 0; i < MAX_STAT_COMPONENTS;i++)
    {
        stats[i].entity_id = -1;
        stats[i].max_hp = 0;
        stats[i].hp = 0;
        stats[i].speed = 0;
        stats[i].range_follow = 0;
        stats[i].range_attack = 0;
        stats[i].can_dmg = false;
        stats[i].destroyed = false;
    }
}

void destroy_component(int entity_id_)
{
    entities[entity_id_].destroyed = true;
    
    if(entities[entity_id_].position_index != -1)
        positions[entities[entity_id_].position_index].destroyed = true;
    
    if(entities[entity_id_].velocity_index != -1)
        velocities[entities[entity_id_].velocity_index].destroyed = true;
    
    if(entities[entity_id_].collision_index != -1)
        collisions[entities[entity_id_].collision_index].destroyed = true;
    
    if(entities[entity_id_].ai_index != -1)
        ai[entities[entity_id_].ai_index].destroyed = true;
    
    if(entities[entity_id_].sprite_index != -1)
        sprites[entities[entity_id_].sprite_index].destroyed = true;
    
    if(entities[entity_id_].animation_index != -1)
        animations[entities[entity_id_].animation_index].destroyed = true;
    
    if(entities[entity_id_].stat_index != -1)
        stats[entities[entity_id_].stat_index].destroyed = true;
    
    entities[entity_id_].position_index = -1;
    entities[entity_id_].velocity_index = -1;
    entities[entity_id_].collision_index = -1;
    entities[entity_id_].ai_index = -1;
    entities[entity_id_].sprite_index = -1;
    entities[entity_id_].animation_index = -1;
    entities[entity_id_].stat_index = -1;
}

