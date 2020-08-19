#include <stdio.h>
#include <SDL2/SDL.h>

const int WIDTH = 960;
const int HEIGHT = 640;

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