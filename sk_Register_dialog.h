#ifndef SK_REGISTER_DIALOG_H_INCLUDED
#define SK_REGISTER_DIALOG_H_INCLUDED

///MACROS

#define DEFAULT_SERVER_IP_ADDRESS wxT("196.001.235.004")
#define SERVER_SUPERUSER_PASSWORD wxT("Server12345")

///INCLUDES
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/colour.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/valgen.h>///for data validation

class sk_RegisterDialog :public wxDialog{

DECLARE_CLASS(sk_RegisterDialog);
DECLARE_EVENT_TABLE();

public: sk_RegisterDialog();///Empty Constructor for  Init()

        sk_RegisterDialog(wxWindow* parent,///Deafault Constructor
        wxWindowID id, const wxString& caption,
        const wxPoint& pos, const wxSize& size, long style );

        ~sk_RegisterDialog();///Destructor

        ///MAIN CONTROL FUNCTIONS

        void Init_Variables();
        void Display_Controls();
        void Update_Controls(wxUpdateUIEvent& event);
        void Accept(wxCommandEvent &event);
        void Clear(wxCommandEvent &event);///Clear all the entries
        void Help(wxCommandEvent &event);///Id help button is pressed
        void Init_DialogHelp();///When the mouse is houvered over a control with help pressed

        ///GET AND SET METHODS

        void SetName(wxCommandEvent &event);
        void SetUsername(wxCommandEvent &event);
        void SetPassword(wxCommandEvent &event);
        void SetPasswordConfirmation(wxCommandEvent &event);
        void SetEmailAddr(wxCommandEvent &event);
        void SetPhoneNo1(wxCommandEvent &event);
        void SetPhoneNo2(wxCommandEvent &event);
        void SetTelNo(wxCommandEvent &event);
        void SetWorkNo(wxCommandEvent &event);
        void SetHomeAddr(wxCommandEvent &event);
        void SetIDAccess(wxCommandEvent &event);///whenn the request button is pressed this is used to update the AdminID Variable
        void SetCSID(wxCommandEvent &event);///Used to set the central station's IP_Addr

        void SetServerIpAddr(wxCommandEvent &event);///Allow to set only if the system  password is entred
        void UpdateServerPin(wxCommandEvent &event);///Update the entered pin on the system(LIVE)
        void SetPersonalIDNumber(wxCommandEvent &event);///Set ID number

        wxString GetName();
        wxString GetUsername();
        wxString GetPassword();
        wxString GetPasswordConfirmation();
        wxString GetEmailAddr();
        wxString GetPhoneNo1();
        wxString GetPhoneNo2();
        wxString GetTelNo();
        wxString GetWorkNo();
        wxString GetHomeAddr();
        wxString GetIDAccess();
        wxString GetCSID();
        wxString GetServerIpAddr();
        wxString GetPersonalIDNumber();

        ///ENUM IDs for controls

        enum IDs{
        ID_NAME=200,
        ID_USERNAME,
        ID_PASS,
        ID_PASSCONF,
        ID_EMAILADDR,
        ID_PHONENO1,
        ID_PHONENO2,
        ID_TELNO,
        ID_WORKNO,
        ID_HOMEADDR,
        ID_IDACCESS,
        ID_CSID,
        ID_SERVERIP,
        ID_PERSONALID,
        ID_ACCEPT,
        ID_CLEAR,
        ID_SERVERPIN,
        ID_REQUEST
        };

private: wxString Name;
         wxString Username;
         wxString Password;
         wxString PasswordConfirmation;
         wxString EmailAddress;
         wxString PhoneNo1;
         wxString PhoneNo2;
         wxString TelNo;
         wxString WorkNo;
         wxString HomeAddress;
         wxString IdAccess;
         wxString CentralStationID;
         wxString PersonalIDNumber;

         wxString ServerPin;
         wxString ServerIpAddress;
         bool AllowAccess;

};


#endif // SK_REGISTER_DIALOG_H_INCLUDED
