#ifndef LCD_H
#define LCD_H

#define LCD_FISICO

void lcd_init( void );
void lcd_clr( void );
void lcd_print( unsigned char lin, unsigned char col, const char * str );
void lcd_put( unsigned char c );
void lcd_num(  unsigned char lin, unsigned char col,
                    int num, unsigned char tam );

void lcd_lincol( unsigned char lin, unsigned char col);

#endif