/***************************************************************
 * Name:      Costum_dialog_box_doings_Main.h
 * Purpose:   Defines Application Frame
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-23
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/

#ifndef COSTUM_DIALOG_BOX_DOINGS_MAIN_H
#define COSTUM_DIALOG_BOX_DOINGS_MAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "Costum_dialog_box_doings_App.h"
#include "Projectile Motion/Projectile_GUI_main.h"
#include <wx/sizer.h>
#include "sk_Register_dialog.h"

class Costum_dialog_box_doings_Frame: public wxFrame
{
    public:
        Costum_dialog_box_doings_Frame(wxFrame *frame, const wxString& title);
        ~Costum_dialog_box_doings_Frame();

        void ShowDialog(wxCommandEvent& event);

        enum IDs{Invoke=45,Main_ID};

    private:
        DECLARE_EVENT_TABLE()
};


#endif // COSTUM_DIALOG_BOX_DOINGS_MAIN_H
