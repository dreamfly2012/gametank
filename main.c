#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int WIDTH = 960;
const int HEIGHT = 640;

const int UP = 0;
const int RIGHT = 90;
const int DOWN = 180;
const int LEFT = 270;


typedef struct{
    float x,y;
    int width,height;
    int direction;
    SDL_Texture *texture;
}Player;

void createPlayer(Player player, SDL_Renderer *render, SDL_Surface *image)
{
    player.texture = SDL_CreateTextureFromSurface(render, image);

    SDL_Rect s_rect, d_rect;

    s_rect.x = 0;
    s_rect.y = 0;
    s_rect.w = 174;
    s_rect.h = 154;

    d_rect.x = player.x;
    d_rect.y = player.y;
    d_rect.w = player.width;
    d_rect.h = player.height;

    SDL_RenderCopyEx(render, player.texture, &s_rect, &d_rect, player.direction, NULL, SDL_FLIP_NONE);
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *render;

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        printf("初始化错误");
        return 1;
    }

    if(!(window = SDL_CreateWindow("tank game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL))){
       printf("创建窗口失败");
       return 1;
    }

    if(!(render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE))){
        printf("渲染器创建失败");
        return 1;
    }

    

    SDL_SetRenderDrawColor(render, 0, 255, 0 ,255);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);

    

    //TODO:渲染图片
    SDL_Surface *image;
    image = IMG_Load("tank.png");
    if(!image){
        printf("Load error:%s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture *texture;
    Player player1,player2;
    player1.x = 200;
    player1.y = 300;
    player1.width = 174 / 2;
    player1.height = 154 / 2;
    player1.direction = LEFT;

    player2.x = 100;
    player2.y = 100;
    player2.width = 174 / 2;
    player2.height = 154 / 2;
    player2.direction = DOWN;

    createPlayer(player1, render, image);
    createPlayer(player2, render, image);
    SDL_RenderPresent(render);






    while(1){
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                printf("事件执行了，我要退出了");
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
             printf("key is pressed");
             SDL_Quit();
             break;
            default:
                break;
            }
        }
        

    }



    SDL_Quit();

    return 0;

}