/* Header file of the library for solving the 24 game
 * Author: lem-ma (@Github)
 */

#ifndef __SOLVE24_H__
#define __SOLVE24_H__

/* solve24_tryout:
 * dest: a character array/pointer with at least 8 sizeof(char) allocated
 * Use to store the (internal) answer
 * token: a charater array with at least 4 sizeof(char) allocated
 * such that token[0],token[1],token[2],token[3] are all less than
 * 32 and greater than 0, which are the inputs for the 24 game.
 * returns 0 if the given tokens cannot yield 24
 * return an integer between 1 and 5 if it can yield 24.
 */
int solve24_tryout(char *dest, char *token);

/* solve24_output:
 * dest: a character array/pointer with at least 20 sizeof(char) allocated
 * if you do not want gcc to complain. Enough with 16 sizeof(char)
 * answ: the internal answer, loaded into dest in solve24_tryout
 * mode: the return value (if nonzero) of solve24_tryout
 * returns dest, which has been loaded with
 * the formatted (human-readable) answer
 */
char* solve24_output(char *dest, char *answ, int mode);

#endif
