/*
 * Main app
 */

#include <stdlib.h>
#include <stdio.h>
#include "iU.h"

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

sfShape ** generate_points(char * fn)
{
    sfShape ** tmp = (sfShape**)malloc(600 * sizeof(sfShape*));
    int i = 0, j = 0;
    double res, res2;
    iU_init();
    for (; i <= 600; i++, j++)
    {

        iU_reinit();
        iU_add_variable("x", (i-300.0));
        parse_tree = iU_tokenize(fn);
        iU_gen_parsetables();
        res = iU_calculate_node(iU_gen_parsetree(0, valSize-1));

        if(DEVIDE_BY_ZERO == 1)
        {
            tmp[j] = sfShape_CreateLine(i, 0, i, 600, 1, sfGreen, 0.0, sfGreen);
            continue;
        }

        iU_reinit();
        iU_add_variable("x", (i-300.0+1));
        parse_tree = iU_tokenize(fn);
        iU_gen_parsetables();
        res2 = iU_calculate_node(iU_gen_parsetree(0, valSize-1));

        if(DEVIDE_BY_ZERO == 1)
        {
            tmp[j] = sfShape_CreateLine(i+1, 0, i+1, 600, 1, sfGreen, 0.0, sfGreen);
            continue;
        }

        if(res<0)
            res = abs(res)+300;
        else
            res = 300-res;

        if(res2<0)
            res2 = abs(res2)+300;
        else
            res2 = 300-res2;
        //debugf("f(%f) = %f", (double)i , res);
        tmp[j] = sfShape_CreateLine(i, res, i+1, res2, 1, sfRed, 0.0, sfBlack);
    }
    return tmp;
}

int main()
{

    // Our input
    printf("Enter the function.");
    string ch = (string)malloc(sizeof(char));
    scanf("%s", ch);

    sfWindowSettings Settings = {24, 8, 0};
    sfVideoMode Mode = {600, 600, 32};
    sfRenderWindow* App;
    sfFont* Font;
    sfString* Text;
    sfEvent Event;
    sfColor grid= sfColor_FromRGB(227, 227, 227);

    sfShape * AxeX, *AxeY;

    AxeX = sfShape_CreateLine(300, 0, 300, 600, 2, sfBlack, 0, sfBlack);
    AxeY = sfShape_CreateLine(0, 300, 600, 300, 2, sfBlack, 0, sfBlack);

    /* Create the main window */
    App = sfRenderWindow_Create(Mode, "iU Calculating language", sfResize | sfClose, Settings);
    if (!App)
        return EXIT_FAILURE;
    /* Create a graphical string to display */
    Font = sfFont_CreateFromFile("arial.ttf", 50, NULL);
    if (!Font)
        return EXIT_FAILURE;
    Text = sfString_Create();

    sfString_SetFont(Text, Font);
    sfString_SetFont(Text, Font);
    sfString_SetColor(Text, sfBlack);
    sfString_SetPosition(Text, 0, 540);
    sfString_SetSize(Text, 50);
    sfString_SetText(Text, ch);
    sfShape ** x = generate_points(ch);
    sfShape * tmpLine;

    /* Start the game loop */
    while (sfRenderWindow_IsOpened(App))
    {
        /* Process events */
        while (sfRenderWindow_GetEvent(App, &Event))
        {
            /* Close window : exit */
            if (Event.Type == sfEvtClosed)
                sfRenderWindow_Close(App);
        }

        sfRenderWindow_Clear(App, sfWhite);
        int i;
        //printf("fail");

        for(i = 0; i < 600; i+= 10)
        {
            tmpLine = sfShape_CreateLine(i, 0, i, 600, 1, grid, 0, grid);
            sfRenderWindow_DrawShape(App, tmpLine);
            tmpLine = sfShape_CreateLine(0, i, 600, i, 1, grid, 0, grid);
            sfRenderWindow_DrawShape(App, tmpLine);
        }


        sfRenderWindow_DrawShape(App, AxeX);
        sfRenderWindow_DrawShape(App, AxeY);

        for(i = 0; i <= 600; i ++)
            sfRenderWindow_DrawShape(App, x[i]);

        sfRenderWindow_DrawString(App, Text);

        /* Update the window */
        sfRenderWindow_Display(App);
    }

    /* Cleanup resources */

    sfString_Destroy(Text);
    sfFont_Destroy(Font);

    sfRenderWindow_Destroy(App);

    return EXIT_SUCCESS;
}
