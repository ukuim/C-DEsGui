#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define GL_CLAMP_TO_EDGE 0x812F
#include "imgui.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <tchar.h> 
#include <vector>
#include <iostream>
#include <string>  
#include <map>  
#include "jsontool.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

void LoadTexture(const char* path, GLuint* texture, int& w, int& h)
{
    int width, height, channels;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &channels, 4);
    if (data)
    {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        w = width;
        h = height;
    }
}



extern bool show_begin_window;
extern bool show_query_window;

/*
       GLuint texture;
     int w = 0, h = 0;
     LoadTexture("C:\\Users\\Administrator\\Pictures\\1.png", &texture, w, h);
     ImGui::SetCursorPos(ImVec2{ 0, 0 });
     ImGui::Image((void*)(intptr_t)texture, ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
     */

namespace myselfui {
    POINT GetCursorPos()
    {
        POINT p;
        GetCursorPos(&p);
        return p;
    };
    int nWidth = GetSystemMetrics(SM_CXSCREEN);
    int nHeight = GetSystemMetrics(SM_CYSCREEN);
    int current_state = 0;
    std::vector<char*> list = { "1","2","3" };
    int current_ptr = 0;
    char login[256] = u8"测试ing";
    char password[256] = u8"";
    char addname[256] = u8"";
    int addage = 0;

    void body(json& json) {
        /* if (KEY_DOWN(VK_RBUTTON) > 0) {
             SetCursorPos(nWidth / 2, nHeight / 2);
         }*/
        UserData userdata(json);
        ImGui::SetNextWindowPos(ImVec2{ 0, 0 });
        ImGui::SetNextWindowSize({ ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y });
        // 无 padding7v
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        // 无边框
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.6f, 0.75f, 0.93f, 1.0f));

        ImGui::Begin("##body", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
        ImDrawList* draw = ImGui::GetWindowDrawList();
        ImVec2 wpos = ImGui::GetWindowPos();

        draw->AddText(NULL, 18.0f, { wpos.x + 10, wpos.y + 10 }, ImColor(255, 255, 255), u8"guiguigui");
        draw->AddRectFilled({ 0,0 }, { ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y }, 0);
        //下拉列表
        // 设置光标位置为屏幕宽高的80%位置  
        ImGui::SetCursorPos({ ImGui::GetIO().DisplaySize.x / 10 , ImGui::GetIO().DisplaySize.y / 10 * 8 });

        if (ImGui::BeginCombo("Combo", list[current_ptr]))
        {
            for (int i = 0; i < sizeof(list)/sizeof(list[0]); i++)
            {
                if (ImGui::Selectable( list[i] )  )
                {
                    current_ptr = i;
                }
            }
            ImGui::EndCombo();
        }
        int i = 0;
        ImGui::SetCursorPos({ ImGui::GetIO().DisplaySize.x / 10, ImGui::GetIO().DisplaySize.y / 10 });
        if (ImGui::BeginTable("table2", 4, 0, { ImGui::GetIO().DisplaySize.x / 4 * 3,ImGui::GetIO().DisplaySize.y / 2 }) && i < 10)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn(); 
            ImGui::Text(u8"名字");
            ImGui::TableNextColumn();
            ImGui::Text(u8"积分");
            ImGui::TableNextColumn();
            ImGui::Text(u8"id");
            ImGui::TableNextColumn();
            ImGui::Text(u8"操作");
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 0.0f, 0.0f, 0.0f));
            for (auto user : userdata.userdata) {
                char text[100];
                _itoa_s(i, text, 10);
                std::string usernametext = u8"##名字";
                std::string useragetext = u8"##积分";
                std::string userdel = u8"删除";
                userdel.append(user.first.data());

                useragetext.append(text);
                usernametext.append(text);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                char* newname = _strdup(user.second.name.data());
                if (ImGui::InputText(usernametext.data(), newname, 256)) {
                    update_user(json, user.first.data(), newname, user.second.age);
                    write_json("./1.json", json);
                }
                ImGui::TableNextColumn();
                //  ImGui::Text(user.second.name.data());
                if (ImGui::InputInt(useragetext.data(), &user.second.age)) {
                    update_user(json, user.first.data(), user.second.name.data(), user.second.age);
                    write_json("./1.json", json);
                }
                ImGui::TableNextColumn();
                ImGui::Text("%d", i++);
                ImGui::TableNextColumn();
                if (ImGui::Button(userdel.data(), { 100,30 })) {
                    if (MessageBox(NULL, L"确定删除吗？", L"提示", MB_OKCANCEL) == IDOK) {
                        delete_user(json, user.first.data());
                        write_json("./1.json", json);
                    }
                }
            }
            std::string username = "user";
            username.append(std::to_string(i));
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::InputText("##addnames", addname, sizeof(addname));
            ImGui::TableNextColumn();
            ImGui::InputInt("##addages", &addage);
            ImGui::TableNextColumn();
            ImGui::Text("%d", i);
            ImGui::TableNextColumn();
            if (ImGui::Button(u8"添加", { 100,30 })) {
                add_user(json, username, addname, addage);
                write_json("./1.json", json);
            }
            ImGui::PopStyleColor();
            ImGui::EndTable();
        }
        //#fbc2eb ImColor(251, 194, 235, 76)
        //#a6c1ee   ImColor(166,193,242,76);
        //background-image:linear-gradient(0deg,#fbc2eb 0%, #a6c1ee 100%)
        //背景图
        /*
          GLuint texture;
        int w = 0, h = 0;
        LoadTexture("C:\\Users\\Administrator\\Pictures\\1.png", &texture, w, h);
        ImGui::SetCursorPos(ImVec2{ 0, 0 });
        ImGui::Image((void*)(intptr_t)texture, ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
        */
        //登录吖
        ImGui::SetCursorPosX(ImGui::GetIO().DisplaySize.x - ImGui::GetIO().DisplaySize.x / 5);
        ImGui::SetCursorPosY(ImGui::GetIO().DisplaySize.y / 2);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
        ImGui::SetNextItemWidth(ImGui::GetIO().DisplaySize.x / 5 - 30);
        ImGui::InputText("##login", login, sizeof(login));
        ImGui::SetCursorPos(ImVec2{ ImGui::GetIO().DisplaySize.x / 4 * 3, ImGui::GetIO().DisplaySize.y / 2 });
        ImGui::Text(u8"登录吖");
        ImGui::PopStyleVar();
        //密码吖
        ImGui::SetCursorPosX(ImGui::GetIO().DisplaySize.x - ImGui::GetIO().DisplaySize.x / 5);
        ImGui::SetCursorPosY(ImGui::GetIO().DisplaySize.y / 2 + 50);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
        ImGui::SetNextItemWidth(ImGui::GetIO().DisplaySize.x / 5 - 30);
        //ImGui::InputText("##password", password, sizeof(password), ImGuiInputTextFlags_Password);
        ImGui::InputText("##password", password, sizeof(password));
        ImGui::SetCursorPos(ImVec2{ ImGui::GetIO().DisplaySize.x / 4 * 3, ImGui::GetIO().DisplaySize.y / 2 + 50 });
        ImGui::Text(u8"密码吖");
        ImGui::PopStyleVar();
        //按钮吖
        ImGui::SetCursorPosX(ImGui::GetIO().DisplaySize.x / 15 * 14 - 30);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 40);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.0f);
        if (ImGui::Button(u8"按钮", { ImGui::GetIO().DisplaySize.x / 15 , 30 })) {
            current_state = 1;
            show_query_window = true;
        }
        ImGui::PopStyleVar();
        switch (current_state) {
        case 1:
            current_state = 0;
          //  MessageBoxA(NULL, strcmp(password, "我是笨蛋") == 1 ? "没错是笨蛋" : "密码：我是笨蛋", "标题", NULL);
            break;
        default:
            break;
        }
        ImGui::End();
    }

}
