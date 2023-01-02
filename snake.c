#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

char direction='w';

// Struttura per rappresentare la posizione di un elemento sullo schermo
typedef struct {
  int x;
  int y;
} Pos;



// Struttura per rappresentare il serpente
typedef struct {
  Pos body[WIDTH * HEIGHT]; // corpo del serpente
  int len;                  // lunghezza attuale del serpente
  int dir;                  // direzione corrente (0 = su, 1 = destra, 2 = giù, 3 = sinistra)
} Snake;

// Struttura per rappresentare il cibo
typedef struct {
  Pos pos;  // posizione del cibo
  char sym; // simbolo da disegnare
} Food;

void snake_init(Snake*);
void food_init(Food*);
void snake_draw(Snake*);
void food_draw(Food*); 
void snake_move(Snake*);
void getInput (void*);

// Inizializza il serpente
void snake_init(Snake* s) {
  s->len = 1;
  s->body[0] = (Pos){WIDTH / 2, HEIGHT / 2};
  s->dir = 1;
}

// Inizializza il cibo
void food_init(Food* f) {
  f->pos = (Pos){rand() % WIDTH, rand() % HEIGHT};
  f->sym = 'O';
}

// Disegna il serpente sullo schermo
void snake_draw(Snake* s) {
  system("cls");
  for (int i = 0; i < s->len; i++) {
    Pos pos = s->body[i];
    printf("\033[%d;%dHX", pos.y, pos.x);
  }
}



void food_draw(Food* f) {
  Pos pos = f->pos;
  printf("\033[%d;%dHO", pos.y, pos.x);
}

// Sposta il serpente nella sua direzione corrente
void snake_move(Snake* s) {
  for (int i = s->len - 1; i > 0; i--) {
    s->body[i] = s->body[i - 1];
  }
  Pos head = s->body[0];
  switch (s->dir) {
    case 0: // su
      head.y--;
      break;
    case 1: // destra
      head.x++;
      break;
    case 2: // giù
      head.y++;
      break;
    case 3: // sinistra
      head.x--;
      break;
  }
  s->body[0] = head;
}

// Controlla se il serpente ha colpito un muro o se si è morsicato la coda
bool snake_collision(Snake* s) {
  Pos head = s->body[0];
  
  // Controlla se il serpente ha colpito un muro
  if (head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT) {
    return true;
  }
  
  // Controlla se il serpente si è morsicato la coda
  for (int i = 1; i < s->len; i++) {
    if (head.x == s->body[i].x && head.y == s->body[i].y) {
      return true;
    }
  }
  
  return false;
}

void getInput (void* snake){
  char input;
  while(true){
    input = getchar();
    if(input=='w'||input=='a'||input=='s'||input=='d'){
      direction=input;
    }
  }

}

int main() {
  int delay = 500; // 0.5 secondi
  unsigned int handle;
  srand(time(NULL)); // inizializza il generatore di numeri casuali
  
  // Inizializza il serpente e il cibo
  Snake snake;
  snake_init(&snake);
  Food food;
  food_init(&food);
  handle=_beginthread(&getInput, 0, &snake);
  
  while (true) {
    // Disegna il serpente e il cibo
    bool len=(snake.len==1);
    switch (direction) {
      case 'w':
        if((!len && snake.dir!=2) || len)
          snake.dir = 0;
        break;
      case 'a':
        if((!len && snake.dir!=1) || len)
          snake.dir = 3;
        break;
      case 's':
        if((!len && snake.dir!=0) || len)
          snake.dir = 2;
        break;
      case 'd':
        if((!len && snake.dir!=3) || len)
        snake.dir = 1;
        break;
    }
    snake_draw(&snake);
    food_draw(&food);
    
    
    // Sposta il serpente
    snake_move(&snake);
    
    // Controlla se il serpente ha colpito un muro o se si è morsicato la coda
    if (snake_collision(&snake)) {
      break;
    }
    
    // Controlla se il serpente ha mangiato il cibo
    Pos head = snake.body[0];
    if (head.x == food.pos.x && head.y == food.pos.y) {
      snake.len++;
      food_init(&food);
    }
    Sleep(delay);
  }
  
  // Fine del gioco, mostra un messaggio di game over
  system("cls");
  TerminateThread((HANDLE)handle,0);
  CloseHandle((HANDLE)handle);
  printf("GAME OVER\n");
  Sleep(5000);
  return 0;
}



