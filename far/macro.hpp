#ifndef __KEYMACRO_HPP__
#define __KEYMACRO_HPP__
/*
macro.hpp

�������

*/

/* Revision: 1.13 23.05.2001 $ */

/*
Modify:
  23.05.2001 SVS
    ! IndexMode - ��������� ������: ������ ������ - ������, ������ - ����������.
  23.05.2001 SVS
    + Sort()
    + IndexMode - ������ ������ �������� � Macros
  16.05.2001 SVS
    + GetCurRecord() - ��� �����
  06.05.2001 DJ
    ! �������� #include
  25.04.2001 SVS
    ! ��� �������� ������ ��� ������ �������� ������� � ������� Check* -
      ������� ����� �������������� ���� :-(
  08.03.2001 SVS
    + ������� MkTextSequence - ������������ ���������� ������������� Sequence
  22.01.2001 SVS
    + ������� MkRegKeyName - ������������ ����� ����� � �������.
  17.01.2001 SVS
    + ������� ��������� ������� ������� � ������� ��� �����������������������:
       int GetIndex(int Key, int Mode);
       int GetRecordSize(int Key, int Mode);
  04.01.2001 SVS
    ! ������� ReadMacros � GetMacroSettings
    + ������� AssignMacroKey
    ! ������� ��������� struct TKeyNames
  26.12.2000 SVS
    + SwitchFlags()
  23.12.2000 SVS
    + int ParseMacroString(struct MacroRecord *CurMacro,char *BufPtr)
    + int PlayKeyMacro(struct MacroRecord *MRec)
    + int PlayKeyMacro(char *KeyBuffer)
  21.12.2000 SVS
    ! ��������� MacroRecord ���������� �� struct.hpp � "�����"
    ! ������� KeyToText ������� �� �������������
  10.09.2000 SVS
    ! ������� ReadMacros ����� �������������� ���������
  25.06.2000 SVS
    ! ���������� Master Copy
    ! ��������� � �������� ���������������� ������
*/
#include "farconst.hpp"

class Panel;

struct MacroRecord
{
  DWORD Flags;
  int   Key;
  int   BufferSize;
  DWORD *Buffer;
};

class KeyMacro
{
  private:
    /* $ 10.09.2000 SVS
      ! ������� ReadMacros ����� �������������� ���������
    */
    class LockScreen *LockScr;

    struct MacroRecord *Macros;
    int MacrosNumber;
    // ��� ������ - � ������� ������� �������� ���...
    // 0 - ��� ������, 1 - ������� ������, 2 - ����� ������� ��������
    int Recording;

    DWORD *RecBuffer;
    int IndexMode[MACRO_LAST][2];
    int RecBufferSize;
    int Executing;
    int ExecMacroPos;
    int ExecKeyPos;
    int InternalInput;
    int Mode;
    int StartMode;
    int StartMacroPos;

    struct MacroRecord *TempMacro; // ��������� ����� ��� 1 �����
    int TempMacroType;             // ��� ����� ������

  private:
    int ReadMacros(int ReadMode, char *Buffer, int BufferSize);
    DWORD AssignMacroKey();
    int GetMacroSettings(int Key,DWORD &Flags);
    void InitVars();
    void ReleaseTempBuffer(); // ������� ��������� �����

    // �� ���������� ������������� ������� ������� MacroRecord
    int ParseMacroString(struct MacroRecord *CurMacro,char *BufPtr);
    DWORD SwitchFlags(DWORD& Flags,DWORD Value);
    static long WINAPI AssignMacroDlgProc(HANDLE hDlg,int Msg,int Param1,long Param2);
    char *MkRegKeyName(int IdxMacro,char *RegKeyName);

    BOOL CheckEditSelected(DWORD CurFlags);
    BOOL CheckPanel(int PanelMode,DWORD CurFlags);
    BOOL CheckCmdLine(int CmdLength,DWORD Flags);
    BOOL CheckFileFolder(Panel *ActivePanel,DWORD CurFlags);
    BOOL CheckAll(DWORD CurFlags);
    void Sort(void);

  public:
    KeyMacro();
    ~KeyMacro();

  public:
    int ProcessKey(int Key);
    int GetKey();
    int PeekKey();

    int  IsRecording() {return(Recording);};
    int  IsExecuting() {return(Executing);};
    void SetMode(int Mode) {KeyMacro::Mode=Mode;};
    int  GetMode() {return(Mode);};

    void RunStartMacro();

    // "������" ��������� ������������� �������
    int PlayKeyMacro(char *KeyBuffer);
    // "������" ������ (�������� �������������)
    int PlayKeyMacro(struct MacroRecord *MRec);

    int  LoadMacros();
    void SaveMacros();

    int GetStartIndex(int Mode) {return IndexMode[Mode<MACRO_LAST?Mode:MACRO_LAST][0];}
    // ������� ��������� ������� ������� ������� � �������
    int GetIndex(int Key, int Mode);
    // ��������� �������, ����������� ��������� ��������
    int GetRecordSize(int Key, int Mode);

    int GetCurRecord(struct MacroRecord* RBuf,int *KeyPos);

    static char* GetSubKey(int Mode);
    static int   GetSubKey(char *Mode);
    static char *MkTextSequence(DWORD *Buffer,int BufferSize);
};

#endif	// __KEYMACRO_HPP__
