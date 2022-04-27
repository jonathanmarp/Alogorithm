#ifndef MACRO_H
#define MACRO_H

/* Render */
// For clear window and call update
#define RenderClear(render) \
	/* Clear window  */             \
	SDL_RenderClear(render);

// For present or showing into window
#define RenderShow(render)     \
	/* Present window */       \
	SDL_RenderPresent(render); \

#endif // MACRO_H