/*  tilp - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef GUI_INDEP_H
#define GUI_INDEP_H

/*
  This structure holds the GUI independant functions
*/
struct gui_fncts
{
  /* Display a modal OK dialog box with a title and a message */
  void (*msg_box) (const char *title, char *message);
  
  /* Display a modal dialog box with a title, a message and 1 button.
     The function returns 0 or the button pressed (see defs.h)
  */
  int (*user1_box) (const char *title, char *message,
		    const char *btn1); // 1 button
  int (*user2_box) (const char *title, char *message,
		    const char *btn1, const char *btn2); // 2 buttons
  int (*user3_box) (const char *title, char *message,
		    const char *btn1, const char *btn2, 
		    const char *btn3); // 3 buttons

  /* Display a modal entry dialog box with a title, a message and
   a predefined content.
   It returns NULL if the dbox has been cancelled else it returns
   an allocated string which contains the typed text.
   Think to free the returned buffer when no longer needed !!!
  */
  char* (*dlgbox_entry) (const char *title, const char *message,
			 const char *content);

  /* 
     Display a dialog box with 1 progress bar and a 'Cancel' button.
     If the cancel button is pressed, you should have this in your
     callback: 'info_update.cancel = 1;'
  */
  void (*create_pbar_type1) (const char *title); // 1 pbar
  void (*create_pbar_type2) (const char *title, 
			     char *text);        // 1 label
  void (*create_pbar_type3) (const char *title); // 2 pbars
  void (*create_pbar_type4) (const char *title, 
			     char *text);        // 1 pbar & 1 label
  void (*create_pbar_type5) (const char *title, 
			     char *text);        // 2 pbars & 1 label
  /*
    Destroy (hide) one of the previous pbar dbox.
  */
  void (*destroy_pbar) (void); // destroy pbar(s) & label(s)

};
typedef struct gui_fncts GUI_FNCTS;

extern GUI_FNCTS *gif;

void set_gui_fncts(GUI_FNCTS *gf);

#endif



