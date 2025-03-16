#ifndef COLORS_H
#define COLORS_H

#define RGB_F(r, g, b) "\x1b[38;2;"#r";"#g";"#b"m"
#define RGB_B(r, g, b) "\x1b[48;2;"#r";"#g";"#b"m"

#define BLACK_F   "\x1b[30m"
#define RED_F     "\x1b[31m"
#define GREEN_F   "\x1b[32m"
#define YELLOW_F  "\x1b[33m"
#define BLUE_F    "\x1b[34m"
#define MAGENTA_F "\x1b[35m"
#define CYAN_F    "\x1b[36m"
#define WHITE_F   "\x1b[37m"

#define DEFAULT_F "\x1b[39m"

#define BLACK_B   "\x1b[40m"
#define RED_B     "\x1b[41m"
#define GREEN_B   "\x1b[42m"
#define YELLOW_B  "\x1b[43m"
#define BLUE_B    "\x1b[44m"
#define MAGENTA_B "\x1b[45m"
#define CYAN_B    "\x1b[46m"
#define WHITE_B   "\x1b[47m"

#define DEFAULT_B "\x1b[49m"

#endif