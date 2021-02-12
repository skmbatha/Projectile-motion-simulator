#ifndef PROJECTILE_GUI_MAIN_H_INCLUDED
#define PROJECTILE_GUI_MAIN_H_INCLUDED

#include <wx/wx.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <wx/splitter.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/statusbr.h>
#include <wx/colour.h>///import the colout header file
#include <wx/valgen.h>///for data validation

#include "Projectile_Math.h"

struct Scale{
double x_factor;
double y_factor;
};

class Projectile_GUI:public wxDialog{

DECLARE_CLASS(Projectile_GUI)
DECLARE_EVENT_TABLE()

public: Projectile_GUI();///Constructor

        Projectile_GUI(wxWindow* parent,///with variables...wxWidgets kind(native kind of UI)
        wxWindowID id, const wxString& caption,
        const wxPoint& pos, const wxSize& size, long style );

        ~Projectile_GUI();///Destructor

        bool Initialise_motion_varibales();
        bool Draw_Background(wxDC &pane,Scale  scaling_factor,wxColor &b_color,wxColor &text_color);///Construct the background
        bool Draw_Projectile(wxDC &pane,Scale scaling_factor,wxColor Projectile_color,double X_val,double Y_val);///
        void play_whole(wxCommandEvent &event);///play the whole motion timely
        void step_play(wxCommandEvent & event);///play the motion controllably using PREVIOUS AND NEXT buttons
        void paint(wxPaintEvent& event);///PAINT ON THE DC
        void Resize_handler(wxSizeEvent &event);
        void UI_Update(wxUpdateUIEvent & event);
        void Add_control_GUI(wxSize &size_j);
        void Show_Markers(void);///Shows text information on the DC
        void Bounce_Handler(void);///bounce object
        Scale GetScaleFactor(wxDC *pane,int max_height,int max_x_displacement);///calculate scale factor

        void SetVelocity(wxCommandEvent & event);
        void SetAcceleration(wxCommandEvent & event);
        void SetTime(wxCommandEvent & event);
        void SetAngle(wxCommandEvent & event);
        void SetVMax(wxCommandEvent & event);
        void SetHMax(wxCommandEvent & event);
        //void SetStep(wxCommandEvent & event);
        void ResetDContext(wxCommandEvent & event);
        void UpdateGUI();

        enum IDs{
        Main_paint=101,
        ID_Control,
        wxID_ACC,
        wxID_VEL,
        wxID_TIM,
        wxID_ANG,
        wxID_vACC,
        wxID_vVEL,
        wxID_vTIM,
        wxID_vANG,
        ID_PLAY,
        ID_PAUSE,
        ID_PREV,
        ID_NEXT,
        ID_INFO,
        wxID_CVEL,
        wxID_CTIM,
        wxID_CANG,
        wxID_VMX,
        wxID_HMX,
        wxID_TRA,
        wxID_vVMX,
        wxID_vHMX,
        ID_CHECKBOX,
        ID_RESET
        };

        Projectile_math *Main_temp;
        wxFrame *Control_ptr;
        wxClientDC *Main_field_ptr;
        wxSplitterWindow *Splitter_ptr;
        const wxColour *b_colour_ptr;

private:///CLASS GLOBAL VARIABLES(buffer)
        double time;
        double initial_velocity;
        double angle_degrees;
        double acceleration;
        double x_distance;
        double y_distance;
        double initial_time;
        double velocity_energy_loss;

        double Horizontal_length;
        bool expand;


        ///Status variables
        long int max_vertical;
        long int max_horizontal;

        int  vertical_offset;
        int  horizontal_offset;
        bool resized;
        bool show_projectile_tracks_flag;
        bool bounce;
        bool pause;
        bool play;
        bool projected;
        int  v,h;///for label number of number labels

};


#endif // PROJECTILE_GUI_MAIN_H_INCLUDED
