#include "input.h"
#include "ctx.h"

void handleInput(int ch)
{
    switch (ch) {
    case 'q':
        ctx.running = false;
        break;
    }
}