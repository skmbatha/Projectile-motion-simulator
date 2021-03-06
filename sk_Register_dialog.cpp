#include "sk_Register_dialog.h"


IMPLEMENT_CLASS(sk_RegisterDialog,wxDialog)

BEGIN_EVENT_TABLE(sk_RegisterDialog,wxDialog)

EVT_UPDATE_UI(ID_SERVERPIN,sk_RegisterDialog::Update_Controls)
EVT_BUTTON(ID_CLEAR,sk_RegisterDialog::Clear)
EVT_BUTTON(ID_ACCEPT,sk_RegisterDialog::Accept)
EVT_BUTTON(ID_REQUEST,sk_RegisterDialog::SetIDAccess)
EVT_BUTTON(wxID_HELP,sk_RegisterDialog::Help)

EVT_TEXT(ID_NAME,sk_RegisterDialog::SetName)
EVT_TEXT(ID_USERNAME,sk_RegisterDialog::SetUsername)
EVT_TEXT(ID_PASS,sk_RegisterDialog::SetPassword)
EVT_TEXT(ID_PASSCONF,sk_RegisterDialog::SetPasswordConfirmation)
EVT_TEXT(ID_EMAILADDR,sk_RegisterDialog::SetEmailAddr)
EVT_TEXT(ID_PHONENO1,sk_RegisterDialog::SetPhoneNo1)
EVT_TEXT(ID_PHONENO2,sk_RegisterDialog::SetPhoneNo2)
EVT_TEXT(ID_TELNO,sk_RegisterDialog::SetTelNo)
EVT_TEXT(ID_WORKNO,sk_RegisterDialog::SetWorkNo)
EVT_TEXT(ID_HOMEADDR,sk_RegisterDialog::SetHomeAddr)
EVT_TEXT(ID_CSID,sk_RegisterDialog::SetCSID)
EVT_TEXT(ID_SERVERPIN,sk_RegisterDialog::UpdateServerPin)
EVT_TEXT(ID_SERVERIP,sk_RegisterDialog::SetServerIpAddr)
EVT_TEXT(ID_PERSONALID,sk_RegisterDialog::SetPersonalIDNumber)

END_EVENT_TABLE()

sk_RegisterDialog::sk_RegisterDialog()///Empty Constructor for  Init()
{
  Init_Variables();///Initialise the varibles
}

sk_RegisterDialog::sk_RegisterDialog(wxWindow* parent,///Deafault Constructor
wxWindowID id, const wxString& caption,
const wxPoint& pos, const wxSize& size, long style )
{
  Init_Variables();///Initialise the varibles

  SetExtraStyle(wxWS_EX_BLOCK_EVENTS|wxDIALOG_EX_CONTEXTHELP);///Extra Styles for the dialog box
  wxDialog::Create(parent,id,caption,pos,size,style);///Create and initialise dialog box object

  Display_Controls();///Create and display all window controls + sizers
  Init_DialogHelp();///Set help Tips

  ///CREATE VALIDATORS FOR ALL CONTROLS(feedback to GUI)
  FindWindow(ID_SERVERIP)->SetValidator(wxGenericValidator(&ServerIpAddress));
  FindWindow(ID_IDACCESS)->SetValidator(wxGenericValidator(&IdAccess));
  FindWindow(ID_CSID)->SetValidator(wxGenericValidator(&CentralStationID));
  FindWindow(ID_PERSONALID)->SetValidator(wxGenericValidator(&PersonalIDNumber));
  FindWindow(ID_HOMEADDR)->SetValidator(wxGenericValidator(&HomeAddress));
  FindWindow(ID_WORKNO)->SetValidator(wxGenericValidator(&WorkNo));
  FindWindow(ID_PHONENO2)->SetValidator(wxGenericValidator(&PhoneNo2));
  FindWindow(ID_PHONENO1)->SetValidator(wxGenericValidator(&PhoneNo1));
  FindWindow(ID_EMAILADDR)->SetValidator(wxGenericValidator(&EmailAddress));
  FindWindow(ID_PASSCONF)->SetValidator(wxGenericValidator(&PasswordConfirmation));
  FindWindow(ID_PASS)->SetValidator(wxGenericValidator(&Password));
  FindWindow(ID_USERNAME)->SetValidator(wxGenericValidator(&Username));
  FindWindow(ID_NAME)->SetValidator(wxGenericValidator(&Name));

  wxTextCtrl *Temp=(wxTextCtrl*)FindWindow(ID_IDACCESS);///Just disable access to teh ID(CLIENT) text control
  Temp->Enable(false);
}

sk_RegisterDialog::~sk_RegisterDialog()///Destructor
{
 delete this;
}

///MAIN CONTROL FUNCTIONS

void sk_RegisterDialog::Init_Variables()
{
         ServerIpAddress=DEFAULT_SERVER_IP_ADDRESS;
         AllowAccess=false;

         IdAccess=_("Admin-43er-76mh-4t56");///Temp
         CentralStationID=_("CSID-45uh-kj87-sd6g");///Temp

}
void sk_RegisterDialog::Display_Controls()
{
    ///LABLES
    //wxStaticText *TITLE=new wxStaticText(this,wxID_ANY,_("    PLEASE ENTER YOUR REGISTRATION DETAILS BELOW:"),wxDefaultPosition,wxDefaultSize);
    //TITLE->SetFont(wxFont(12,74, 90, 90, false, wxT("Arial")));///will come back to this

    wxStaticText *L_NAME=new wxStaticText(this,wxID_ANY,_("Name* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_USERNAME=new wxStaticText(this,wxID_ANY,_("Username : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_PASS=new wxStaticText(this,wxID_ANY,_("Password : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_PASSCONF=new wxStaticText(this,wxID_ANY,_("Confirm Password : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_EMAILADDR=new wxStaticText(this,wxID_ANY,_("Email Address* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_PHONENO1=new wxStaticText(this,wxID_ANY,_("Phone Number(1st)* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_PHONENO2=new wxStaticText(this,wxID_ANY,_("Alternative Phone no : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_TELNO=new wxStaticText(this,wxID_ANY,_("Telephone Number : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_WORKNO=new wxStaticText(this,wxID_ANY,_("Work Number : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_HOMEADDR=new wxStaticText(this,wxID_ANY,_("Residential Address* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_CSID=new wxStaticText(this,wxID_ANY,_("Central S_ID* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_USERID=new wxStaticText(this,wxID_ANY,_("User ID* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_USERIDREQUEST=new wxStaticText(this,wxID_ANY,_("Request User ID* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_SERVERIP=new wxStaticText(this,wxID_ANY,_("Server IP Address* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_PERSONALIDNUM=new wxStaticText(this,wxID_ANY,_("Personal ID Number* : "),wxDefaultPosition,wxDefaultSize);
    wxStaticText *L_SERVERTECHPIN=new wxStaticText(this,wxID_ANY,_("Enter SuperUser Pass : "),wxDefaultPosition,wxDefaultSize);

    ///TEXT BOXES
    wxTextCtrl *NAME=new wxTextCtrl(this,ID_NAME,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *USERNAME=new wxTextCtrl(this,ID_USERNAME,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *PASS=new wxTextCtrl(this,ID_PASS,wxEmptyString,wxDefaultPosition,wxSize(127,23),wxTE_PASSWORD);
    wxTextCtrl *PASSCONF=new wxTextCtrl(this,ID_PASSCONF,wxEmptyString,wxDefaultPosition,wxSize(127,23),wxTE_PASSWORD);
    wxTextCtrl *EMAILADDR=new wxTextCtrl(this,ID_EMAILADDR,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *PHONENO1=new wxTextCtrl(this,ID_PHONENO1,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *PHONENO2=new wxTextCtrl(this,ID_PHONENO2,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *TELNO=new wxTextCtrl(this,ID_TELNO,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *WORKNO=new wxTextCtrl(this,ID_WORKNO,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *HOMEADDR=new wxTextCtrl(this,ID_HOMEADDR,wxEmptyString,wxDefaultPosition,wxSize(127,70),wxTE_MULTILINE);
    wxTextCtrl *IDACCESS=new wxTextCtrl(this,ID_IDACCESS,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *CSID=new wxTextCtrl(this,ID_CSID,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *PERSONALIDNUM=new wxTextCtrl(this,ID_PERSONALID,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *SERVERIP=new wxTextCtrl(this,ID_SERVERIP,wxEmptyString,wxDefaultPosition,wxSize(127,23));
    wxTextCtrl *SERVERTECHPIN=new wxTextCtrl(this,ID_SERVERPIN,wxEmptyString,wxDefaultPosition,wxSize(127,23),wxTE_PASSWORD);

    wxButton *ACCEPT=new wxButton(this,ID_ACCEPT,_("Accept"),wxDefaultPosition,wxDefaultSize);
    wxButton *CLEAR=new wxButton(this,ID_CLEAR,_("Clear"),wxDefaultPosition,wxDefaultSize);
    wxButton *IDREQUEST=new wxButton(this,ID_REQUEST,_("Request ID"),wxDefaultPosition,wxDefaultSize);

    ACCEPT->SetDefault();///Set as ENTER Default

    ///------------------------IMPLEMENT SIZERS------------------------------------

    wxBoxSizer *GlobalSizer=new wxBoxSizer(wxVERTICAL);
    //GlobalSizer->SetMinSize(400,300);

    //wxColour *KatCostum=new wxColour(224,216,216);///Brownish
    wxColour *KatCostum=new wxColour(52,185,185);///
    this->SetBackgroundColour(*KatCostum);///Set the Dialog's background color

    ///TITLE GOES HERE
    //wxBoxSizer *TitleBox=new wxBoxSizer(wxHORIZONTAL);
    //TitleBox->Add(TITLE,0,wxALIGN_CENTER);

          ///ADD TITLE DETAILS
          //GlobalSizer->Add(100,10);///just a space between outer boundry and title box
          //GlobalSizer->Add(TitleBox);///add title box
          GlobalSizer->Add(100,20);///a space between title box and left = right boxes

    ///MAIN CONTROLS
    wxBoxSizer *RightLeftContainer=new wxBoxSizer(wxHORIZONTAL);///Contans main controls
    wxBoxSizer *LeftContainer=new wxBoxSizer(wxHORIZONTAL);///Contans Left
    wxBoxSizer *RightContainer=new wxBoxSizer(wxHORIZONTAL);///Contans Right

          ///ADD BOXES INSIDE THE LEFTRIGHT CONTAINER
          GlobalSizer->Add(RightLeftContainer);

          RightLeftContainer->Add(20,10);///Space between left margin and left label
          RightLeftContainer->Add(LeftContainer);
          RightLeftContainer->Add(30,10);///Vertical line between the two Left and right
          RightLeftContainer->Add(RightContainer);
          RightLeftContainer->Add(20,10);///Space between the right entry and margin

          ///ADD BOXES FOR LEFT AND RIGHT
          ///---------------------LEFT-----------------------
          wxBoxSizer *LeftLabelContainer=new wxBoxSizer(wxVERTICAL);///Contans Left
          wxBoxSizer *LeftFillContainer=new wxBoxSizer(wxVERTICAL);///Contans Right

          LeftContainer->Add(LeftLabelContainer);
          LeftContainer->Add(15,0);
          LeftContainer->Add(LeftFillContainer);

          int text_align=13;
          LeftLabelContainer->Add(L_NAME);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_USERNAME);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_PASS);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_PASSCONF);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_EMAILADDR);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_PHONENO1);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_PHONENO2);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_TELNO);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_WORKNO);
          LeftLabelContainer->Add(0,text_align);
          LeftLabelContainer->Add(L_HOMEADDR);
          LeftLabelContainer->Add(0,text_align);

          LeftFillContainer->Add(NAME);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(USERNAME);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(PASS);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(PASSCONF);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(EMAILADDR);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(PHONENO1);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(PHONENO2);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(TELNO);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(WORKNO);
          LeftFillContainer->Add(0,5);
          LeftFillContainer->Add(HOMEADDR);
          LeftFillContainer->Add(0,5);

///---------------------RIGHT-----------------------
          wxBoxSizer *RightLabelContainer=new wxBoxSizer(wxVERTICAL);///Contans Left
          wxBoxSizer *RightFillContainer=new wxBoxSizer(wxVERTICAL);///Contans Right

          RightContainer->Add(RightLabelContainer);
          RightContainer->Add(15,0);
          RightContainer->Add(RightFillContainer);

          RightLabelContainer->Add(L_USERID);
          RightLabelContainer->Add(0,text_align);
          RightLabelContainer->Add(L_USERIDREQUEST);
          RightLabelContainer->Add(0,text_align);
          RightLabelContainer->Add(L_SERVERTECHPIN);
          RightLabelContainer->Add(0,text_align);
          RightLabelContainer->Add(L_CSID);
          RightLabelContainer->Add(0,text_align);
          RightLabelContainer->Add(L_SERVERIP);
          RightLabelContainer->Add(0,text_align);
          RightLabelContainer->Add(L_PERSONALIDNUM);
          RightLabelContainer->Add(0,text_align);


          RightFillContainer->Add(IDACCESS);
          RightFillContainer->Add(0,5);
          RightFillContainer->Add(IDREQUEST);
          RightFillContainer->Add(0,5);
          RightFillContainer->Add(SERVERTECHPIN);
          RightFillContainer->Add(0,5);
          RightFillContainer->Add(CSID);
          RightFillContainer->Add(0,5);
          RightFillContainer->Add(SERVERIP);
          RightFillContainer->Add(0,5);
          RightFillContainer->Add(PERSONALIDNUM);
          RightFillContainer->Add(0,5);

    ///------------------------------END----------------------------

    ///ADD A STATIC LINE
    wxStaticLine* staticLine = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxSize(594,-1));
    GlobalSizer->Add(staticLine);

    wxBoxSizer *BottomButtonContainer=new wxBoxSizer(wxHORIZONTAL);///Contans accept and clear controls
    GlobalSizer->Add(BottomButtonContainer);///Add bottom box to Global sizer


          ///ADD BUTTONS TO THE  BOTTOM BOX

          //Just for space
          BottomButtonContainer->Add(new wxStaticText(this,wxID_ANY,_("                               ")));
          BottomButtonContainer->Add(new wxStaticText(this,wxID_ANY,_("                                ")));
          BottomButtonContainer->Add(new wxStaticText(this,wxID_ANY,_("                                ")));
          BottomButtonContainer->Add(new wxStaticText(this,wxID_ANY,_("                                ")));
          //Just for space

          BottomButtonContainer->Add(ACCEPT,0,wxALL,4);
          BottomButtonContainer->Add(CLEAR,0,wxALL,4);
          BottomButtonContainer->Add(20,10);


    ///ACTIVATE THE SIZERS

    SetSizer(GlobalSizer);///Set this as th default sizer
    GlobalSizer->Fit(this);///Make the top sizer to fit around all the inside controls
    GlobalSizer->SetSizeHints(this);///assign this window to the

}

void sk_RegisterDialog::Update_Controls(wxUpdateUIEvent& event)
{
 if(ServerPin.Cmp(SERVER_SUPERUSER_PASSWORD)==0)
 {
     AllowAccess=true;
     wxTextCtrl *Temp=(wxTextCtrl*)FindWindow(ID_SERVERIP);
     Temp->Enable(true);
     wxTextCtrl *Temp2=(wxTextCtrl*)FindWindow(ID_CSID);
     Temp2->Enable(true);
 }else
 {
     wxTextCtrl *Temp=(wxTextCtrl*)FindWindow(ID_SERVERIP);
     Temp->Enable(false);
     wxTextCtrl *Temp2=(wxTextCtrl*)FindWindow(ID_CSID);
     Temp2->Enable(false);
 }

 if(Name.Cmp(_(""))==0 || EmailAddress.Cmp(_(""))==0  || PhoneNo1.Cmp(_(""))==0 || IdAccess.Cmp(_(""))==0 || CentralStationID.Cmp(_(""))==0|| PersonalIDNumber.Cmp(_(""))==0|| HomeAddress.Cmp(_(""))==0)
 {
       wxTextCtrl *Temp=(wxTextCtrl*)FindWindow(ID_ACCEPT);
       Temp->Enable(false);
 }else
 {
       wxTextCtrl *Temp=(wxTextCtrl*)FindWindow(ID_ACCEPT);
       Temp->Enable(true);
 }

}

void sk_RegisterDialog::Accept(wxCommandEvent &event)
{
    if(Password.Cmp(PasswordConfirmation)==0)
    {
    if(this->IsModal())
    {
        EndModal(wxID_OK);
    }else
    {
        this->SetReturnCode(wxID_OK);
        delete this;
    }}else
    {
        wxMessageBox(_("Your Password and Confirmation Password\nare not the same\n\nNOTE:Please fix!"));
        wxTextCtrl *field1=(wxTextCtrl*)FindWindow(ID_PASS);
        wxTextCtrl *field2=(wxTextCtrl*)FindWindow(ID_PASSCONF);

        field1->Clear();
        field2->Clear();
    }
}

void sk_RegisterDialog::Clear(wxCommandEvent &event)///Clear all the entries
{
         Name.Clear();
         Username.Clear();
         Password.Clear();
         PasswordConfirmation.Clear();
         EmailAddress.Clear();
         PhoneNo1.Clear();
         PhoneNo2.Clear();
         TelNo.Clear();
         WorkNo.Clear();
         HomeAddress.Clear();
         PersonalIDNumber.Clear();

  wxTextCtrl *c3=(wxTextCtrl*)FindWindow(ID_TELNO);
  c3->Clear();
  wxTextCtrl *c4=(wxTextCtrl*)FindWindow(ID_PERSONALID);
  c4->Clear();
  wxTextCtrl *c5=(wxTextCtrl*)FindWindow(ID_HOMEADDR);
  c5->Clear();
  wxTextCtrl *c6=(wxTextCtrl*)FindWindow(ID_WORKNO);
  c6->Clear();
  wxTextCtrl *c7=(wxTextCtrl*)FindWindow(ID_PHONENO2);
  c7->Clear();
  wxTextCtrl *c8=(wxTextCtrl*)FindWindow(ID_PHONENO1);
  c8->Clear();
  wxTextCtrl *c9=(wxTextCtrl*)FindWindow(ID_EMAILADDR);
  c9->Clear();
  wxTextCtrl *c10=(wxTextCtrl*)FindWindow(ID_PASSCONF);
  c10->Clear();
  wxTextCtrl *c11=(wxTextCtrl*)FindWindow(ID_PASS);
  c11->Clear();
  wxTextCtrl *c12=(wxTextCtrl*)FindWindow(ID_USERNAME);
  c12->Clear();
  wxTextCtrl *c13=(wxTextCtrl*)FindWindow(ID_NAME);
  c13->Clear();
  wxTextCtrl *c14=(wxTextCtrl*)FindWindow(ID_SERVERPIN);
  c14->Clear();
}

void sk_RegisterDialog::Help(wxCommandEvent &event)///On Help
{
    wxMessageBox(_("INFO"));
}

void sk_RegisterDialog::Init_DialogHelp()
{

    FindWindow(ID_NAME)->SetToolTip(_("Enter your name(Full names.)"));
    FindWindow(ID_USERNAME)->SetToolTip(_("This is going to be used\nthe next time you login."));
    FindWindow(ID_PASS)->SetToolTip(_("Set your login password."));
    FindWindow(ID_PASSCONF)->SetToolTip(_("Confirm your password."));
    FindWindow(ID_EMAILADDR)->SetToolTip(_("Enter your email address."));
    FindWindow(ID_PHONENO1)->SetToolTip(_("Enter your main mobile number."));
    FindWindow(ID_PHONENO2)->SetToolTip(_("Enter your Next of Kin or\nalternative mobile number."));
    FindWindow(ID_TELNO)->SetToolTip(_("Enter your Home Telephone number."));
    FindWindow(ID_WORKNO)->SetToolTip(_("Enter your work number"));
    FindWindow(ID_HOMEADDR)->SetToolTip(_("This will be used in case of emergencies\nand other location related matters"));
    FindWindow(ID_IDACCESS)->SetToolTip(_("This is your unique user registration ID.\nThe Admin and added guest will use this to\ngain access to the Central Station."));
    FindWindow(ID_REQUEST)->SetToolTip(_("Press this button to retrieve a server delegated\nunique registration user code."));
    FindWindow(ID_SERVERPIN)->SetToolTip(_("This is a techinical password,only if its correctly\nentered will the system allow for the modification\nof the Central Station ID and server IP_Address."));
    FindWindow(ID_CSID)->SetToolTip(_("Set the Central Station ID(once set \ncan only be changed by KESS)"));
    FindWindow(ID_SERVERIP)->SetToolTip(_("Set the Server IP_Address(factory set)\nNOTE:This can only be changed by the Seervice Provider."));
    FindWindow(ID_PERSONALID)->SetToolTip(_("Enter your personal Identity  Numeber(ID)"));
}

///SET AND GET FUNCTIONS IMPLEMENTANTION

///------------------------------SET METHODS--------------------------------

void sk_RegisterDialog::SetName(wxCommandEvent &event)
{
Name=event.GetString();
return;
}

void sk_RegisterDialog::SetUsername(wxCommandEvent &event)
{
Username=event.GetString();
return;
}

void sk_RegisterDialog::SetPassword(wxCommandEvent &event)
{
Password=event.GetString();
return;
}

void sk_RegisterDialog::SetPasswordConfirmation(wxCommandEvent &event)
{
PasswordConfirmation=event.GetString();
return;
}

void sk_RegisterDialog::SetEmailAddr(wxCommandEvent &event)
{
EmailAddress=event.GetString();
return;
}

void sk_RegisterDialog::SetPhoneNo1(wxCommandEvent &event)
{
PhoneNo1=event.GetString();
return;
}

void sk_RegisterDialog::SetPhoneNo2(wxCommandEvent &event)
{
PhoneNo2=event.GetString();
return;
}

void sk_RegisterDialog::SetTelNo(wxCommandEvent &event)
{
TelNo=event.GetString();
return;
}

void sk_RegisterDialog::SetWorkNo(wxCommandEvent &event)
{
WorkNo=event.GetString();
return;
}

void sk_RegisterDialog::SetHomeAddr(wxCommandEvent &event)
{
HomeAddress=event.GetString();
return;
}

void sk_RegisterDialog::SetIDAccess(wxCommandEvent &event)///whenn the request button is pressed this is used to update the AdminID Variable
{

  ///RETRIEVE DATA FROM THE SERVER AND ASSIGN TO THE VARIABLE(Temp)
}

void sk_RegisterDialog::SetCSID(wxCommandEvent &event)///Used to set the central station's IP_Addr
{
CentralStationID=event.GetString();
return;
}

void sk_RegisterDialog::SetServerIpAddr(wxCommandEvent &event)///Allow to set only if the system  password is entred
{
ServerIpAddress=event.GetString();
return;
}

void sk_RegisterDialog::UpdateServerPin(wxCommandEvent &event)///Allow to set only if the system  password is entred
{
ServerPin=event.GetString();
return;
}

void sk_RegisterDialog::SetPersonalIDNumber(wxCommandEvent &event)///Set ID number
{
PersonalIDNumber=event.GetString();
return;
}

///------------------------------GET METHODS--------------------------------

wxString sk_RegisterDialog::GetName()
{
return Name;
}

wxString sk_RegisterDialog::GetUsername()
{
return Username;
}

wxString sk_RegisterDialog::GetPassword()
{
return Password;
}

wxString sk_RegisterDialog::GetPasswordConfirmation()
{
return PasswordConfirmation;
}

wxString sk_RegisterDialog::GetEmailAddr()
{
return EmailAddress;
}

wxString sk_RegisterDialog::GetPhoneNo1()
{
return PhoneNo1;
}

wxString sk_RegisterDialog::GetPhoneNo2()
{
return PhoneNo2;
}

wxString sk_RegisterDialog::GetTelNo()
{
return TelNo;
}

wxString sk_RegisterDialog::GetWorkNo()
{
return WorkNo;
}

wxString sk_RegisterDialog::GetHomeAddr()
{
return HomeAddress;
}

wxString sk_RegisterDialog::GetIDAccess()
{
return IdAccess;
}

wxString sk_RegisterDialog::GetCSID()
{
return CentralStationID;
}

wxString sk_RegisterDialog::GetServerIpAddr()
{
return ServerIpAddress;
}

wxString sk_RegisterDialog::GetPersonalIDNumber()
{
return PersonalIDNumber;
}

