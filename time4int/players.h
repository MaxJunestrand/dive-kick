// Player positions in pixels
float player1Posx, player1Posy;
float player2Posx, player2Posy;

// Player velocities in pixels per frame
float player1dx, player1dy;
float player2dx, player2dy;

// Player acceleration
float player1accx, player1accy;
float player2accx, player2accy;

// Player gravity enabled
char player1enableGrav;
char player2enableGrav;

// Player widths and heights
int player1width;
int player1height;

int player2width;
int player2height;

// Player actions (functions)
void player1BackJump( void );
void player1JumpKick( void );
void player2JumpKick( void );
void player2BackJump( void );

// AI functions
void player2AIAggro( void );
void player2AIDef( void );