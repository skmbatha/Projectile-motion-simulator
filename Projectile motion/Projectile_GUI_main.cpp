#include "Projectile_GUI_main.h"

IMPLEMENT_CLASS(Projectile_GUI,wxDialog)

///event table
BEGIN_EVENT_TABLE(Projectile_GUI,wxDialog)

    EVT_PAINT(Projectile_GUI::paint)
    EVT_SIZE(Projectile_GUI::Resize_handler)
    EVT_UPDATE_UI(wxID_vACC,Projectile_GUI::UI_Update)

    EVT_TEXT(wxID_vACC,Projectile_GUI::SetAcceleration)
    EVT_TEXT(wxID_vVEL,Projectile_GUI::SetVelocity)
    EVT_TEXT(wxID_vTIM,Projectile_GUI::SetTime)
    EVT_TEXT(wxID_vANG,Projectile_GUI::SetAngle)
    EVT_TEXT(wxID_vVMX,Projectile_GUI::SetVMax)
    EVT_TEXT(wxID_vHMX,Projectile_GUI::SetHMax)

    EVT_BUTTON(ID_NEXT,Projectile_GUI::step_play)
    EVT_BUTTON(ID_PREV,Projectile_GUI::step_play)
    EVT_BUTTON(ID_PLAY,Projectile_GUI::play_whole)
    EVT_BUTTON(ID_PAUSE,Projectile_GUI::play_whole)
    EVT_BUTTON(ID_RESET,Projectile_GUI::ResetDContext)

END_EVENT_TABLE()

///functions


Projectile_GUI::Projectile_GUI()///Constructor
{

}

Projectile_GUI::Projectile_GUI(wxWindow* parent,///Deafault  (wxWidgets kind)
                               wxWindowID id, const wxString& caption,
                               const wxPoint& pos, const wxSize& size, long style)
{
    Create(parent,id,caption,wxPoint(150,50),wxSize(1000,700),style);///create the wxDialog box
    ///****************************************************************
    ///*                    Sizers Initialise                         *
    ///****************************************************************

    //wxBoxSizer *GlobalSizer=new wxBoxSizer(wxVERTICAL);

    ///****************************************************************
    ///*                     Windows +(spli)                          *
    ///****************************************************************

    wxSplitterWindow *splitter=new wxSplitterWindow(this, wxID_ANY,wxPoint(0,0),wxSize(1000,700), wxSP_3D);
    Splitter_ptr=splitter;
    wxWindow *leftwindow= new wxWindow(splitter,wxID_ANY,wxPoint(0,0),wxDefaultSize,wxRAISED_BORDER);
    wxPanel *rightwindow= new wxPanel(splitter,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxRAISED_BORDER);

    splitter->Initialize(leftwindow);//you need this or esle nothing will show
    splitter->Initialize(rightwindow);//same here
    splitter->SetMinimumPaneSize(20);//cannot be minimised smaller than this

    int width,height;
    this->GetSize(&width,&height);

    splitter->SplitVertically( leftwindow, rightwindow,(width-width/4)+20);//split the two windows
    splitter->SetSashInvisible(true);

    int width2,height2;
    splitter->GetSize(&width2,&height2);
    wxSize *size_l=new wxSize(width2,height2);
    splitter->SetMinSize(*size_l);

    ///set min for right window
    int width1,height1;
    rightwindow->GetSize(&width1,&height1);
    wxSize *size_r=new wxSize(100,height1);
    rightwindow->SetMinSize(*size_r);

    ///===================================================================================================

    wxClientDC *Main_field=new wxClientDC(leftwindow);///all drawings done here
    Main_field_ptr=Main_field;

    wxColour *Costum_b_Colour=new wxColour(160,160,152);///costum color (Background)
    wxColour *Costum_text_Colour=new wxColour(16,24,24);///costum color (Background)...dark blue

    ///Initialise the windows dimensions
    max_vertical=150;
    max_horizontal=500;

    Initialise_motion_varibales();

    ///THIS INITIALISZS THE MATH PROFILE OBJECT
    Projectile_math *Math=new Projectile_math(-9.81,GetScaleFactor(Main_field,max_vertical,max_horizontal).x_factor,GetScaleFactor(Main_field,max_vertical,max_horizontal).y_factor);
    Main_temp=Math;

    ///I (initlialise with position information)

    ///CALL FOR A FUNCTION TO DRAW THE BACKGROUND
    Draw_Background(*Main_field,GetScaleFactor(Main_field,max_vertical,max_horizontal),*Costum_b_Colour,*Costum_text_Colour);

    double x_distance_value;
    double y_distance_value;

    ///CALCULATE AND OBTAIN THE X AND Y VALUES DEPENDING ON TIME,ANGLE IN THE FUNCTION
    x_distance_value=Math->X_distance(time,Math->DegreesToRad(angle_degrees),initial_velocity);
    y_distance_value=Math->Y_distance(time,Math->DegreesToRad(angle_degrees),initial_velocity);

    Add_control_GUI(*size_r);///Add controls on the right window

}

Projectile_GUI::~Projectile_GUI()///Destructor
{
    delete this;
}

void Projectile_GUI::SetVelocity(wxCommandEvent & event)
{
    wxString value=event.GetString();
    value.ToDouble(&initial_velocity);
}
void Projectile_GUI::SetAcceleration(wxCommandEvent & event)
{
    wxString value=event.GetString();
    value.ToDouble(&acceleration);
}
void Projectile_GUI::SetTime(wxCommandEvent & event)
{
    wxString value=event.GetString();
    value.ToDouble(&time);
}
void Projectile_GUI::SetAngle(wxCommandEvent & event)
{
    wxString value=event.GetString();
    value.ToDouble(&angle_degrees);
}

void Projectile_GUI::SetVMax(wxCommandEvent & event)
{
    wxString value=event.GetString();
    value.ToLong(&max_vertical);
    Main_field_ptr->Clear();
    wxPaintEvent e;
    paint(e);
}

void Projectile_GUI::SetHMax(wxCommandEvent & event)
{
    wxString value=event.GetString();
    value.ToLong(&max_horizontal);
    Main_field_ptr->Clear();
    wxPaintEvent e;
    paint(e);
}

void Projectile_GUI::ResetDContext(wxCommandEvent & event)
{
    Main_field_ptr->Clear();
    time=0;

    wxPaintEvent e;
    paint(e);
}

void Projectile_GUI::Show_Markers(void)///Shows text information on the DC
{
    ///Implementation
}

void Projectile_GUI::Bounce_Handler(void)///bounce object
{
    double milli;
    double sec;

    wxDateTime(time_t);
    wxDateTime time = wxDateTime::UNow();
    milli=(double)time.GetMillisecond();
    sec=(double)time.GetSecond();

    initial_time=sec+(milli/1000);

    initial_velocity=Main_temp->GetCurrentVelocity()-velocity_energy_loss;
    angle_degrees=-1*(Main_temp->GetCurrentAngle());
    Main_temp->SetCurrentYDistance(0);
    time=NULL;
    play=true;
    expand=true;

    Horizontal_length+=Main_temp->GetCurrentXDistance();
    wxUpdateUIEvent ev;
    UI_Update(ev);
}

void Projectile_GUI::UpdateGUI()
{

    wxStaticText *ang=(wxStaticText*)FindWindow(wxID_CANG);
    wxStaticText *vel=(wxStaticText*)FindWindow(wxID_CVEL);
    wxStaticText *tim=(wxStaticText*)FindWindow(wxID_CTIM);


//acc->SetValue(wxString::Format(_("%f"),Main_temp->GetCurrentAcceleration()));
    wxString val=_("Vel:     ")+wxString::Format(_("%f"),Main_temp->GetCurrentVelocity());
    vel->SetLabel(val);
    val=_("Tim:   ")+wxString::Format(_("%f"),Main_temp->GetCurrentTime());
    tim->SetLabel(val);
    val=_("Ang:   ")+wxString::Format(_("%f"),Main_temp->GetCurrentAngle());
    ang->SetLabel(val);
}

void Projectile_GUI::Add_control_GUI(wxSize &size_j)
{
    wxPanel *right_window=(wxPanel*)Splitter_ptr->GetWindow2();

    wxStaticText *TITLE=new wxStaticText(right_window,wxID_ANY,_("CONTROLS"),wxPoint(40,5),wxDefaultSize);
    TITLE->SetFont(wxFont(12,74, 90, 90, true, wxT("Arial")));///will come back to this

    signed int s=20,s2=165,e=-20,e2=40,a=100;

    wxStaticText *Acc=new wxStaticText(right_window,wxID_ACC,_("Acceler: \n(m.s^2)"),wxPoint(5,30+s),wxDefaultSize);
    wxStaticText *Vel=new wxStaticText(right_window,wxID_VEL,_("Velocit: \n(m.s^1)"),wxPoint(5,70+s),wxDefaultSize);
    wxStaticText *Tim=new wxStaticText(right_window,wxID_TIM,_("Time   : \n(Sec)"),wxPoint(5,110+s),wxDefaultSize);
    wxStaticText *Ang=new wxStaticText(right_window,wxID_ANG,_("Angle  : \n(Deg)"),wxPoint(5,150+s),wxDefaultSize);
    wxStaticText *VMx=new wxStaticText(right_window,wxID_VMX,_("V Max  : \n(m)"),wxPoint(5,190+s),wxDefaultSize);
    wxStaticText *HMx=new wxStaticText(right_window,wxID_HMX,_("H Max  : \n(m)"),wxPoint(5,230+s),wxDefaultSize);
    wxStaticText *Tra=new wxStaticText(right_window,wxID_TRA,_("Show trace   : "),wxPoint(5,270+s),wxDefaultSize);

    wxTextCtrl *V_Acc=new wxTextCtrl(right_window,wxID_vACC,wxEmptyString,wxPoint(60,35+s),wxDefaultSize);
    wxTextCtrl *V_Vel=new wxTextCtrl(right_window,wxID_vVEL,wxEmptyString,wxPoint(60,75+s),wxDefaultSize);
    wxTextCtrl *V_Tim=new wxTextCtrl(right_window,wxID_vTIM,wxEmptyString,wxPoint(60,115+s),wxDefaultSize);
    wxTextCtrl *V_Ang=new wxTextCtrl(right_window,wxID_vANG,wxEmptyString,wxPoint(60,155+s),wxDefaultSize);
    wxTextCtrl *V_VMx=new wxTextCtrl(right_window,wxID_vVMX,wxEmptyString,wxPoint(60,195+s),wxDefaultSize);
    wxTextCtrl *V_HMx=new wxTextCtrl(right_window,wxID_vHMX,wxEmptyString,wxPoint(60,235+s),wxDefaultSize);
    wxCheckBox *checkBox = new wxCheckBox(right_window, ID_CHECKBOX,wxEmptyString,wxPoint(90,270+s), wxDefaultSize);
    checkBox->SetValue(true);

    wxStaticText *TITLE2=new wxStaticText(right_window,wxID_ANY,_("- - - - - - - - - - - - - - - - - - - - -"),wxPoint(5,210+a),wxDefaultSize);
    TITLE2->SetFont(wxFont(10,74, 90, 90,false, wxT("Arial")));///will come back to this
    wxStaticText *CAcc=new wxStaticText(right_window,wxID_CANG,_("Ang: "),wxPoint(5,200+e2+a),wxDefaultSize);
    wxStaticText *CVel=new wxStaticText(right_window,wxID_CVEL,_("Vel: "),wxPoint(5,225+e2+a),wxDefaultSize);
    wxStaticText *CTim=new wxStaticText(right_window,wxID_CTIM,_("Tim: "),wxPoint(5,250+e2+a),wxDefaultSize);

    wxStaticText *TITLE3=new wxStaticText(right_window,wxID_ANY,_("- - - - - - - - - - - - - - - - - - - - -"),wxPoint(5,320+a),wxDefaultSize);
    TITLE3->SetFont(wxFont(10,74, 90, 90,false, wxT("Arial")));///will come back to this
    wxButton *PLAY=new wxButton(right_window,ID_PLAY,_("Simulate"),wxPoint(10,190+s2+a),wxSize(176+e,26));
    wxButton *PAUSE=new wxButton(right_window,ID_PAUSE,_("Pause"),wxPoint(10,230+s2+a),wxSize(176+e,26));
    wxButton *PREV=new wxButton(right_window,ID_PREV,_("Prev"),wxPoint(10,270+s2+a),wxSize(176+e,26));
    wxButton *NEXT=new wxButton(right_window,ID_NEXT,_("Next"),wxPoint(10,310+s2+a),wxSize(176+e,26));
    wxButton *INFO=new wxButton(right_window,ID_INFO,_("Sim_Info"),wxPoint(10,350+s2+a),wxSize(97+e,26));
    wxButton *RESET=new wxButton(right_window,ID_RESET,_("Reset DC"),wxPoint(89,350+s2+a),wxSize(97+e,26));

    FindWindow(wxID_vACC)->SetValidator(wxGenericValidator(&acceleration));
    FindWindow(wxID_vVEL)->SetValidator(wxGenericValidator(&initial_velocity));
    FindWindow(wxID_vTIM)->SetValidator(wxGenericValidator(&time));
    FindWindow(wxID_vANG)->SetValidator(wxGenericValidator(&angle_degrees));

///======================================= SIZERS ==========================================
    /*
    wxBoxSizer *GlobalControlSizer=new wxBoxSizer(wxVERTICAL);
    GlobalControlSizer->SetMinSize(size_j);

    wxColour *KatCostum=new wxColour(120,112,112);///
    right_window->SetBackgroundColour(*KatCostum);///Set the Dialog's background color

    wxBoxSizer *ACCE=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *VELO=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *TIME=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *ANGL=new wxBoxSizer(wxHORIZONTAL);

    GlobalControlSizer->Add(TITLE);
    GlobalControlSizer->Add(1,20);///Add space

    GlobalControlSizer->Add(ACCE);
    ACCE->Add(Acc);
    ACCE->Add(V_Acc);

    GlobalControlSizer->Add(VELO);
    ACCE->Add(Vel);
    ACCE->Add(V_Vel);

    GlobalControlSizer->Add(TIME);
    ACCE->Add(Tim);
    ACCE->Add(V_Tim);

    GlobalControlSizer->Add(ANGL);
    ACCE->Add(Ang);
    ACCE->Add(V_Ang);

    GlobalControlSizer->Add(1,20);///Add space

    GlobalControlSizer->Add(PLAY);
    GlobalControlSizer->Add(PAUSE);
    GlobalControlSizer->Add(INFO);

    wxBoxSizer *NextPrev=new wxBoxSizer(wxHORIZONTAL);
    GlobalControlSizer->Add(NextPrev);
    NextPrev->Add(PREV);
    NextPrev->Add(NEXT);

    ///ACTIVATE SIZERS
    SetSizer(GlobalControlSizer);///Set this as th default sizer
    GlobalControlSizer->Fit(right_window);///Make the top sizer to fit around all the inside controls
    //GlobalControlSizer->SetSizeHints(right_window);///assign this window to the
    */
}

void Projectile_GUI::UI_Update(wxUpdateUIEvent & event)
{

    if(resized)
    {
        ///needs multi threading
        wxPaintEvent e;
        paint(e);
    }

    if(play==true)
    {
        double milli;
        double sec;
        double prev_time=0;
        bool once=true,fix=false;
        int DELAY=0;
        projected=true;

        do
        {
            wxDateTime time2 = wxDateTime::UNow();
            milli=(double)time2.GetMillisecond();
            sec=(double)time2.GetSecond();

///================TIME CTRL================
            if(sec==0 && once==true)
            {
                prev_time=60-initial_time;
                once=false;
                fix=true;
                DELAY=0;
            }

            if(sec==0 && once==false && DELAY>3000)
            {
                prev_time+=60;
                DELAY=0;
            }

            if(fix)
            {
                time=((sec+(milli/1000)));
                time+=prev_time;
            }
            else
            {
                time=((sec+(milli/1000)));
                time-=initial_time;
            }

///=========================================

            wxPaintEvent e;
            paint(e);

///reduce read speed
            for(int i=0; i<1000; i++)
            {
                for(int j=0; j<100; j++)
                {}
            }
            DELAY++;
        }
        while(Main_temp->GetCurrentYDistance()>0.1 && pause==false);
///================================end of while====================

        DELAY=0;
        prev_time=0;
        once=true;///changed
        play=false;
        fix=false;

        if(bounce==false)
            time=0;
    }
}

void Projectile_GUI::Resize_handler(wxSizeEvent &event)
{
    resized=true;///fLAG FOR SIGNALING THAT THE DC WAS RESIZED
}

void Projectile_GUI::paint(wxPaintEvent& event)///PAINT ON THE DC
{

    ///If window was resized,clear the dc object buffer
    if(resized==true)
    {
        int width,height;
        this->GetSize(&width,&height);
        Splitter_ptr->SetSize(width,height-40);
        Splitter_ptr->SetSashPosition((width-200),true);

        Main_field_ptr->Clear();
        resized=false;
    }

    ///========================================PRINT THE BACKGROUND==============================
    wxColour *Costum_b_Colour=new wxColour(160,160,152);///costum color (Background)
    wxColour *Costum_text_Colour=new wxColour(16,24,24);///costum color (Background)...dark blue

    ///CALL FOR A FUNCTION TO DRAW THE BACKGROUND
    Scale ScalePoint;
    ScalePoint=GetScaleFactor(Main_field_ptr,max_vertical,max_horizontal);

    Draw_Background(*Main_field_ptr,ScalePoint,*Costum_b_Colour,*Costum_text_Colour);

    ///======================================MATHEMATICAL CALCULATIONS============================
    double x_distance_value;
    double y_distance_value;

    ///CALCULATE AND OBTAIN THE X AND Y VALUES DEPENDING ON TIME,ANGLE IN THE FUNCTION
    x_distance_value=Main_temp->X_distance(time,Main_temp->DegreesToRad(angle_degrees),initial_velocity);
    y_distance_value=Main_temp->Y_distance(time,Main_temp->DegreesToRad(angle_degrees),initial_velocity);

    ///====================================== PROECTILE PRINTING==================================

    UpdateGUI();///Show the current projectile info

    if(y_distance_value<0 && bounce==false)
    {
        wxMessageBox(_("Bounce is not activated\nand OBJECT touched the\nground(min height)."));
        time=0;
        return;
    }

    if(y_distance_value<0.1 && bounce==true && projected==true)
    {
        if((Main_temp->GetCurrentVelocity())<2)
        {
            projected=false;
            play=false;
            Horizontal_length=0;
            expand=false;
            wxMessageBox(_("Done!"));
            time=0;///reset the local time
            return;
        }
        else
        {
            Bounce_Handler();
        }
    }


    wxColour *Costum_object_color= new wxColour(144,24,24);///Red
    Draw_Projectile(*Main_field_ptr,GetScaleFactor(Main_field_ptr,max_vertical,max_horizontal),
                    *Costum_object_color,x_distance_value,y_distance_value);
}

bool Projectile_GUI::Initialise_motion_varibales()
{
    ///motion
    time=0;///In seconds
    initial_velocity=40;///Metres per second...zero
    angle_degrees=60;
    acceleration=9.81;
    velocity_energy_loss=10;
    Horizontal_length=0;

    ///GUI
    v=10;
    h=16;
    vertical_offset=36;
    horizontal_offset=26;
    bounce=true;
    pause=false;
    play=false;
    expand=false;
    projected=false;///went to the auto sim while loop
}

bool Projectile_GUI::Draw_Background(wxDC &pane,Scale  scaling_factor,wxColor &b_color,wxColor &text_color)///Construct the background
{
    wxBrush *brush=new wxBrush(b_color);
    Main_field_ptr->SetBackground(*brush);
    b_colour_ptr=&b_color;
    ///========================================LABELLING================================

    int width,height;///get the size of the window pane
    pane.GetSize(&width,&height);

    ///number of labels
    if(width<500 && height<400)
    {
        v=10;
        h=16;
    }
    else if(width>500 && height>400 && width<900 && height<720)
    {
        v=15;
        h=24;
    }
    else
    {
        v=20;
        h=32;
    }

    ///other values
    int height_scale_factor=(height-vertical_offset)/v;///Vertical increase scale

    int vertical_label=max_vertical/v;
    wxString label;

    ///for label spacing(position offset)
    wxInt16 buf;
    wxInt8 label_length;

    for(wxInt8 cntr=0; cntr<(v+1); cntr++)
    {
        ///Calculation for number length(for spacing)
        buf=(wxInt16)vertical_label*cntr;
        label_length=0;

        while(buf>0)
        {
            buf/=10;
            label_length+=1;
        }

        label=wxString::Format(wxT("%d"),vertical_label*cntr);

        if(label_length==1 || !label_length)
            pane.DrawText(label+wxT("     --"),wxPoint(5,(height-height_scale_factor*cntr)-vertical_offset));
        else if(label_length==2)
            pane.DrawText(label+wxT("   --"),wxPoint(5,(height-height_scale_factor*cntr)-vertical_offset));
        else
            pane.DrawText(label+wxT(" --"),wxPoint(5,(height-height_scale_factor*cntr)-vertical_offset));
    }

    ///horizontal labeling

    int horizontal_label=max_horizontal/(h);
    int width_scale_factor=(width-horizontal_offset)/(h);///Vertical increase scale

    for(wxInt8 cntr=0; cntr<(h); cntr++)
    {
        label=wxString::Format(wxT("%d"),horizontal_label*cntr);
        pane.DrawText(wxT("|"),wxPoint(10+horizontal_offset+(width_scale_factor*cntr),height-30));
        pane.DrawText(label,wxPoint(10+horizontal_offset+(width_scale_factor*cntr),height-15));
    }


    ///========================================CARTESIAN PLANE LINES================================



}

bool Projectile_GUI::Draw_Projectile(wxDC &pane,Scale scaling_factor,wxColor Projectile_color,double X_val,double Y_val)///
{
    int width,height;
    Main_field_ptr->GetSize(&width,&height);

    int x_point;
    int y_point;

    if(expand)
        X_val+=Horizontal_length;

    x_point=(int)((scaling_factor.x_factor*X_val)+vertical_offset);
    y_point=(int)((scaling_factor.y_factor*Y_val)+horizontal_offset);

    static int x_point_prev=x_point;
    static int y_point_prev=y_point;

    ///Clear previous ball trace
    wxCheckBox *Temp=(wxCheckBox*)FindWindow(ID_CHECKBOX);
    if(Temp->GetValue()==false)
    {
        wxPen *pen=new wxPen(*b_colour_ptr,2);
        wxBrush *brush=new wxBrush(*b_colour_ptr);
        pane.SetPen(*pen);
        pane.SetBrush(*brush);
        pane.DrawCircle((wxCoord)x_point_prev,(wxCoord)(height-y_point_prev),10);
    }

    ///Print ball(current)
    wxPen *pen=new wxPen(Projectile_color,2);
    pane.SetPen(*pen);
    pane.DrawCircle((wxCoord)x_point,(wxCoord)(height-y_point),10);

    ///save in prev for next cicle
    x_point_prev=x_point;
    y_point_prev=y_point;

}

Scale Projectile_GUI::GetScaleFactor(wxDC *pane,int max_height,int max_x_displacement)///calculate scale factor
{
    ///NOTE THAT A DIFFERENT RTECHNIQUE IS USED IN LABELLING

    Scale Temp;///Temporary Scale object
    int width,height;///get the size of the window pane
    Main_field_ptr->GetSize(&width,&height);

    Temp.y_factor=((height-vertical_offset));
    Temp.y_factor/=max_height;

    Temp.x_factor=((width-horizontal_offset));
    Temp.x_factor/=max_x_displacement;

    return Temp;
}

void Projectile_GUI::play_whole(wxCommandEvent &event)///play the whole motion timely
{
    double milli;
    double sec;

    if(event.GetId()==ID_PLAY)
    {
        wxDateTime(time_t);
        wxDateTime time = wxDateTime::UNow();
        milli=(double)time.GetMillisecond();
        sec=(double)time.GetSecond();

        play=true;
        initial_time=sec+(milli/1000);
    }
    else
    {
        pause=true;
    }

}

void Projectile_GUI::step_play(wxCommandEvent & event)///play the motion controllably using PREVIOUS AND NEXT buttons
{
    if(event.GetId()==ID_NEXT)///next
    {
        time+=0.2;
        wxPaintEvent Evt;
        paint(Evt);
    }
    else///previous
    {
        if(time>0)
        {
            time-=0.2;
            wxPaintEvent Evt;
            paint(Evt);
        }
        else
        {
            wxMessageBox(_("Minimum time\nreached!"));
        }
    }

}
