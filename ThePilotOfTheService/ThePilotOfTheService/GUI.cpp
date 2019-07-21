#include "GUI.hpp"
#include "resource.h"
#include <fstream>
#include <sstream>
#include "BotBrain.hpp"

void BlockingGUI::Spawn(HINSTANCE hInst)
{
  DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
}

int BlockingGUI::DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  BotBrain& brain = BotBrain::GetInstance();
  GUIState* state = (GUIState*)GetWindowLong(hWndDlg, GWL_USERDATA);
  char buf[100];
  switch (Msg)
  {
    case WM_DROPFILES:
      wchar_t filename[500];
      DragQueryFileW((HDROP)wParam, 0, filename, 500);
      state->HandleDrop(filename);
      return TRUE;

    case WM_INITDIALOG:
      SetWindowLong(hWndDlg, GWL_USERDATA, (LONG)new GUIState(hWndDlg));
      ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
      ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
      ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
      DragAcceptFiles(hWndDlg, TRUE);
      SetDlgItemText(hWndDlg, TEXT_PAUSE, brain.botactive ? "Bot is ACTIVE" : "Bot is PAUSED");
      //SendDlgItemMessage(hWndDlg, PICTURE_WND, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
      if (brain.autotarget) CheckDlgButton(hWndDlg, C_AUTOTARGET, 1);
      if (brain.autoattack) CheckDlgButton(hWndDlg, C_AUTOATTACK, 1);
      return TRUE;

    case WM_DESTROY:
      delete (GUIState*)GetWindowLong(hWndDlg, GWL_USERDATA);
    //MessageBoxA(0, "DISTROY", (char*)GetWindowLong(hWndDlg, GWL_USERDATA), 0);

    case WM_COMMAND:
      switch (LOWORD(wParam))
      {
        case B_UPGRADE:
          {
            if (!brain.GetWorld().IsIngame())
            {
              MessageBox(hWndDlg, "Wejdz do giery", "NBFR", 0);
              return TRUE;
            }
            GetDlgItemText(hWndDlg, T_UPGRADE, buf, 100);
            unsigned template_id = atoi(buf);
            if (brain.to_enchant.size())
            {
              MessageBox(hWndDlg, "Enchaning aslready in progress! Wait!", "NBFR", 0);
              return TRUE;
            }
            std::vector<unsigned> to_enchant_temp;
            for (const auto& item : brain.backpack.GetInv())
            {
              if (item.second.typeID == template_id)
                to_enchant_temp.push_back(item.first);
            }
            if (to_enchant_temp.size() == 0)
            {
              MessageBox(hWndDlg, "Nie masz takich itemow", "NBFR", 0);
              return TRUE;
            }
            GetDlgItemText(hWndDlg, T_ENCHANT_TYPE, buf, 100);
            unsigned template_enchant = atoi(buf);
            brain.enchant_id = brain.backpack.TemplateIdToObjectId(template_enchant);
            if (!brain.enchant_id)
            {
              MessageBox(hWndDlg, "Nie masz takich enchantow", "NBFR", 0);
              return TRUE;
            }
            if (brain.backpack.GetInv().at(brain.enchant_id).ammount < to_enchant_temp.size())
            {
              MessageBox(hWndDlg, "Niby masz enchanty ale za malo QQ", "NBFR", 0);
              return TRUE;
            }
            brain.to_enchant = std::move(to_enchant_temp);
            break;
          }
        case B_SET_POLYGON:
          if (!brain.GetWorld().IsIngame())
          {
            MessageBox(hWndDlg, "Blad - Musisz byc w grze zebym widzial twoje xy", "NBFR", 0);
            return TRUE;
          }
          //CheckDlgButton(hWndDlg, C_AUTOTARGET, 1);
          GetDlgItemText(hWndDlg, T_POLYGON_RADIUS, buf, 100);
          //Setdialogbkcolor
          if (atoi(buf))
          {
            auto& player = BotBrain::GetInstance().GetWorld().GetPlayer();
            brain.polygon.Reset(6, { player.x, player.y }, atoi(buf), 111);
            MessageBox(hWndDlg, "Ustawilem nowy poligon", "NBFR", 0);
          }
          else
          {
            brain.polygon.Clear();
            MessageBox(hWndDlg, "Removed polygon!", "NBFR", 0);
          }
          return TRUE;

        case IDOK:
          EndDialog(hWndDlg, 0);
          return TRUE;
        case IDOK2:
          brain.autotarget = IsDlgButtonChecked(hWndDlg, C_AUTOTARGET) != 0;
          brain.autoattack = IsDlgButtonChecked(hWndDlg, C_AUTOATTACK) != 0;
          return TRUE;
        case B_PAUSE:
          brain.botactive = !brain.botactive;
          SetDlgItemText(hWndDlg, TEXT_PAUSE, brain.botactive ? "Bot is ACTIVE" : "Bot is PAUSED");
          return TRUE;
          /*case C_AUTOTARGET:
          if (IsDlgButtonChecked(hWndDlg, C_AUTOTARGET))
          MessageBox(hWndDlg, L"C_AUTOTARGET", L"qq", 0);

          return TRUE;*/
      }

      break;
  }

  return FALSE;
}

void BlockingGUI::GUIState::HandleDrop(const wchar_t* filename)
{
  std::fstream file(filename);
  if (!file)
  {
    AddLogLine("Unable to open dragged file\r\n");
    return;
  }

  std::string line;

  while (std::getline(file, line))
  {
    if (line[0] == '#') continue;
    if (line == "ITEM_LIST") return ParseItems(file);
    if (line == "SKILL_LIST") return ParseSkills(file);
    AddLogLine("WRONG FILE HEADER\r\n");
  }

}

void BlockingGUI::GUIState::AddLogLine(const std::string& text)
{
  size_t pos = 0;
  int i = 0;
  while (((pos = log.find('\r', pos + 1)) != std::string::npos) && ++i < 8);
  if (pos != std::string::npos) log.erase(pos + 2);
  //log.append(text);
  log.insert(0, text);
  SetDlgItemText(hWndDlg, T_LOG_WINDOW, log.c_str());
}
/*unsigned int itemId;
  unsigned int reuse;
  unsigned int manaMin;
  unsigned int manaMax;
  unsigned int hpMin;
  unsigned int hpMax;
  bool reqTarget;*/
void BlockingGUI::GUIState::ParseItems(std::fstream& file)
{
  BotBrain& brain = BotBrain::GetInstance();
  std::string line;
  std::vector<BotItem> tempItems;
  while (std::getline(file, line))
  {
    if (line[0] == '#') continue;
    std::stringstream ss(line);
    BotItem tmp;
    ss >> tmp.itemId >> tmp.reuse >> tmp.manaMin >> tmp.manaMax >> tmp.hpMin >> tmp.hpMax >> tmp.reqTarget;
    tmp.lastUse = 0;
    if (!ss.eof())
    {
      AddLogLine(line + " This line couldnt be properly parsed\r\n");
      return;
    }
    tempItems.push_back(tmp);
  }
  AddLogLine("Items updated\r\n");
  AddLogLine((std::to_string(tempItems.size()) + "\r\n").c_str());
  brain.items = std::move(tempItems);
}

void BlockingGUI::GUIState::ParseSkills(std::fstream& file)
{
  BotBrain& brain = BotBrain::GetInstance();
  std::string line;
  std::vector<BotSkill> tempSkills;
  while (std::getline(file, line))
  {
    if (line[0] == '#') continue;
    std::stringstream ss(line);
    BotSkill tmp;
    ss >> tmp.skillId >> tmp.reuse >> tmp.mana >> tmp.hp >> tmp.reqTarget;
    if (!ss.eof())
    {
      AddLogLine(line + " This line couldnt be properly parsed\r\n");
      return;
    }
    tempSkills.push_back(tmp);
  }
  AddLogLine("Skills updated\r\n");
  brain.skills = std::move(tempSkills);
}
