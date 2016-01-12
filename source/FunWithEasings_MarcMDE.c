/*******************************************************************************************
*
*   FunWithEasings_v1.1
*   Simple and funny C easings visualizer
*   Created by Marc Montagut @MarcMDE   
*
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
********************************************************************************************/

#include "raylib.h"
#include "ceasings.h"

#define JWHITE (Color){ 250, 237, 230, 255 } // Important color.
#define GHOSTSNUMBER 40 //  Define Ghosts number.

typedef enum 
{
    LINEAR=0,
    QUAD,
    CUBIC,
    QUART,
    QUINT,
    SINE,
    CIRC,
    EXPO,
    ELASTIC,
    BACK,
    BOUNCE
}Easings;

typedef enum
{ 
    IN=0,
    OUT,
    INOUT
}EasingsModes;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 130;
    
    //  Easings enums
    Easings easingType = LINEAR;
    EasingsModes easingMode = IN;
    
    //  Easings Texts
    const char easingsText[11][15] = 
    {
        {"Linear"},
        {"Quad"},
        {"Cubic"},
        {"Quart"},
        {"Quint"},
        {"Sine"},
        {"Circular"},
        {"Expo"},
        {"Elastic"},
        {"Back"},
        {"Bounce"}
    };
    
    //  Easings "modes" texts
    const char easingsModeText[3][6] =
    {
        {"In"},
        {"Out"},
        {"InOut"}
    };
    
    //  Top background rectangle
    Rectangle topRect = {0, 0, screenWidth, 40};
    //  Main Rectangle
    Rectangle rect = {200, topRect.height, 50, 50};
    //  Main Rectangle Color
    Color rectColor = RED;
    //  Ghosts Color
    Color ghostsColor = rectColor;
    ghostsColor.a = 51;
    //  Start Rectangle Background
    Rectangle startRect = {rect.x-5, rect.y, 5, rect.height};
    //  Main Rectangle start position
    Vector2 sourcePosition = {rect.x, rect.y};
    //  Main Rectangle target position
    Vector2 targetPosition = {screenWidth-rect.width, rect.y};
    //  Ghost Rectangles array
    Rectangle ghostRecs[GHOSTSNUMBER];
    //  Ghost Rectangles active bool array
    bool ghostsActive[GHOSTSNUMBER];
    //  Show/Update ghosts bool
    bool ghosts = 1;
    //  Ghosts counter
    int currentGhost = 0;
    //  Ghost Rectangles initialitzation
    for (int i=0; i<GHOSTSNUMBER; i++)
    {
        ghostRecs[i] = rect;
        ghostsActive[i] = 0;
    }
    //  Bot background Rectangle
    Rectangle botRect = {0, topRect.height+rect.height, screenWidth, 40};
    
    //  Easing Variables
    int framesCounter = 0; 
    int duration = 120;
    
    //  Alpha value, used on interface alpha "anim"
    float interfaceAlpha = 0;
    //  Interface Easing Variables
    int interfaceFramesCounter = 0;
    int interfaceDuration = 30;
    // FadeIn/Out interface bool
    bool isInterfaceIn = 0;
    
    //  Check if is easing finished
    bool easingFinished = 0;
    //  Just a fun joke
    bool saitamaMeetsRay = 0;

    InitWindow(screenWidth, screenHeight, "raylib_FunWithEasings_@MarcMDE_v0.1");
    //--------------------------------------------------------------------------------------
    
    //  Textures loading
    Texture2D profileLogo = LoadTexture("resources/MarcMDE_Perturbing_Profile.png");
    Texture2D barLogo = LoadTexture("resources/PixelBar_Logo.png");
    
    //  Audio Device Initialization
    InitAudioDevice();
    
    //  Audio Loading
    Sound opmAudio = LoadSound("resources/OPM_MainTheme.ogg");
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        //  Joke activation
        if (IsKeyPressed('R')) 
        {
            saitamaMeetsRay = !saitamaMeetsRay;
            if (saitamaMeetsRay) PlaySound(opmAudio);
            else StopSound(opmAudio);
        }
        
        //  Random Color
        if (IsKeyDown('C')) rectColor = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
        
        //  Active/Deactive ghosts
        if (IsKeyPressed('G'))  ghosts = !ghosts;
        
        //  Reset Easing and Ghosts. Set easing as unfinished
        if (IsKeyPressed(KEY_SPACE))    
        {
            framesCounter = 0;
            currentGhost = 0;
            for (int i=0; i<GHOSTSNUMBER; i++)
            {
                ghostsActive[i] = 0;
            }
            easingFinished = 0;
        }
        
        //  Switch easing type
        if (IsKeyPressed(KEY_RIGHT))
        {
            if (easingType<10) easingType++;
            else easingType = 0;
        }
        else if (IsKeyPressed(KEY_LEFT))
        {
            if (easingType>0) easingType--;
            else easingType = 10;
        }
        
        //  Switch easing "mode"
        if (IsKeyPressed(KEY_UP))
        {
            if (easingMode<2) easingMode++;
            else easingMode = 0;
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            if (easingMode>0) easingMode--;
            else easingMode = 2;
        }
        
        //  Increase/Decrease easing duration (if the easing is finished)
        if (easingFinished)
        {
            //  Using GHOSTSNUMBER multiples for exact time compatibility.
            if (IsKeyPressed('D'))
            {
                if (duration<GHOSTSNUMBER*12) duration+=GHOSTSNUMBER;
            }
            else if (IsKeyPressed('A'))
            {
                if (duration>GHOSTSNUMBER) duration-=GHOSTSNUMBER;
            }
        }
        
        //  Main Easing Anim. Easing selection.
        if (framesCounter<=duration && !easingFinished)
        {
            switch(easingType)
            {
                case LINEAR:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = Linear(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = Linear(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = Linear(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case QUAD:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = QuadEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = QuadEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = QuadEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case CUBIC:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = CubicEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = CubicEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = CubicEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case QUART:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = QuartEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = QuartEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = QuartEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case QUINT:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = QuintEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = QuintEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = QuintEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case SINE:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = SineEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = SineEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = SineEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case CIRC:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = CircEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = CircEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = CircEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case EXPO:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = ExpoEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = ExpoEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = ExpoEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case ELASTIC:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = ElasticEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = ElasticEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = ElasticEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case BACK:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = BackEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = BackEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = BackEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;
                case BOUNCE:
                    switch(easingMode)
                    {
                        case IN:
                            rect.x = BounceEaseIn(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case OUT:
                            rect.x = BounceEaseOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                        case INOUT:
                            rect.x = BounceEaseInOut(framesCounter, sourcePosition.x, targetPosition.x-sourcePosition.x, duration);
                            break;
                    }
                    break;         
            }
            
            //  Ghosts updating
            if (ghosts && framesCounter%(duration/GHOSTSNUMBER)==0)
            {
                if (!ghostsActive[currentGhost])
                {
                    ghostRecs[currentGhost] = rect;
                    ghostsActive[currentGhost] = 1;
                    currentGhost++;
                }
            }
            
            framesCounter++;
        }
        else    easingFinished = 1;
        
        //  Interface easing. Alpha anim.
        if (interfaceFramesCounter<=interfaceDuration)
        {
            if (isInterfaceIn)
            {
                interfaceAlpha = CircEaseOut(interfaceFramesCounter, 0.2f, 1, interfaceDuration);
            }
            else
            {
                interfaceAlpha = QuadEaseIn(interfaceFramesCounter, 1, -0.8f, interfaceDuration);
            }
            interfaceFramesCounter++;
        }
        else
        {
            //  Alpha fade switch
            isInterfaceIn = !isInterfaceIn;
            interfaceFramesCounter = 0;
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            //  Draw joke
            if (saitamaMeetsRay)
            {
                DrawText("RAYTAMA", startRect.x+150, startRect.y+10, 25, Fade(rectColor, interfaceAlpha));
                DrawText("2LinesOfCodeMAN", startRect.x+275, startRect.y+13, 20, Fade(rectColor, interfaceAlpha));
            }
            
            //  Draw active ghosts
            if (ghosts)
            {
                for (int i=0; i<GHOSTSNUMBER; i++)
                {
                    if (ghostsActive[i])    DrawRectangleRec(ghostRecs[i], ghostsColor);
                }
            }
            
            //  Draw Main Rectangle
            DrawRectangleRec(startRect, GRAY);
            
            //  Draw background Rectangles
            DrawRectangleRec(rect, rectColor);
            DrawRectangleRec(topRect, LIGHTGRAY);
            DrawRectangleRec(botRect, JWHITE);
            
            //  Draw on top rectangle (Controls)
            DrawText("(SPACE)", 2, 4, 18, Fade(BLACK, interfaceAlpha));
            DrawText("Play it", 75, 3, 20, BLACK);
            DrawText("(G)", 2, 22, 18, Fade(BLACK, interfaceAlpha));
            DrawText("Ghosts", 30, 20, 20, BLACK);
            DrawText("<", 165, 7, 30, Fade(BLACK, interfaceAlpha));
            DrawText(">", 375, 7, 30, Fade(BLACK, interfaceAlpha));
            DrawText(easingsText[easingType], 190, 7, 30, BLACK);
            DrawText("^", 400, 7, 40, Fade(BLACK, interfaceAlpha));
            DrawText(easingsModeText[easingMode], 420, 7, 30, BLACK);
            DrawText("(A/D)", 520, 12, 20, Fade(BLACK, interfaceAlpha));
            DrawText("Duration:", 585, 7, 30, BLACK);
            DrawText(FormatText("%i", duration), 730, 7, 30, BLACK); 
            
            //  Draw on bot rectangle
            DrawText("@MarcMDE", 60, botRect.y+4, 30, BLACK); 
            DrawTexture(profileLogo, botRect.x+4, botRect.y+4, WHITE);
            DrawTextureEx(barLogo, (Vector2){screenWidth-barLogo.width-10, botRect.y+8}, 0, 1, WHITE);
            DrawRectangle(380, botRect.y, 235, botRect.height, Fade(rectColor, interfaceAlpha));
            DrawText("IzingsArDaKi", 400, botRect.y+4, 30, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    
    //  Unload sounds
    UnloadSound(opmAudio);
    //  Unload textures
    UnloadTexture(barLogo);
    UnloadTexture(profileLogo);
    
    //  Close Audio Device
    CloseAudioDevice();
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}