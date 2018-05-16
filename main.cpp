// ImGui - standalone example application for DirectX 9
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include <d3dx9.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>





using namespace std;
// Data
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            g_d3dpp.BackBufferWidth  = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
            if (hr == D3DERR_INVALIDCALL)
                IM_ASSERT(0);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int main(int, char**)
{
    // Create application window
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, _T("ImGui Example"), NULL };
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindow(_T("ImGui Example"), _T("Cubesat"), WS_OVERLAPPEDWINDOW, 0, 0, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    LPDIRECT3D9 pD3D;
    if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
    {
        UnregisterClass(_T("ImGui Example"), wc.hInstance);
        return 0;
    }
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // Present with vsync

    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // Present without vsync, maximum unthrottled framerate

    // Create the D3DDevice
    if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
    {
        pD3D->Release();
        UnregisterClass(_T("ImGui Example"), wc.hInstance);
        return 0;
    }

    // Setup ImGui binding
    ImGui_ImplDX9_Init(hwnd, g_pd3dDevice);

    // Setup style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    //bool show_app = true;
	bool show_demo_window = false;
	bool Mainwindow = true;
	bool Internal = false;
	bool dpop = false;
	bool timer = true;
	bool right = false;
	bool show_right_click_menu = false;
    ImVec4 clear_color = ImVec4(0.073f, 0.115f, 0.177f, 1.000f); //RGBA colour for screen. place holder picture me asap. i still need music.
	
	
    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
    while (msg.message != WM_QUIT)
    {
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }									   ///////////////////////////////////////////
        ImGui_ImplDX9_NewFrame();             // IT ALL STARTS HERE
		
		if(ImGui::IsMouseClicked( 1,false))
		{
				
				ImVec2 base_pos = ImGui::GetMousePos();
				ImGui::SetNextWindowPos(ImVec2(base_pos.x,base_pos.y));
			    
		}
		if(ImGui::IsMouseClicked( 1,true))
		{
				static ImGuiOnceUponAFrame fourth;
				if (fourth)
				{
					show_right_click_menu = true;
				}
		}
		if(ImGui::IsMouseClicked( 0,true))
		{
				static ImGuiOnceUponAFrame fourth;
				if (fourth)
				{
					show_right_click_menu = false;
				}
		}
		if(ImGui::IsMouseDoubleClicked( 1))
		{
				static ImGuiOnceUponAFrame fourth;
				if (fourth)
				{
					show_right_click_menu = false;;
				}
		}

		static char right_click_selection[40];
		static int right_menu_selection = -1;
		float rate = 7.0f;
		float recharge = 0.2;
		float discharge = 0.05;
		float drain = 0.0f;
		float receving = 18.6f;
		float microssd = 0.8;
		float ssd1 = 0.4;
		float dataS = 1.0;
		float download = 0.0;
		static int pushd = 0;
		static int datab = 0;
		static int Cells = 1;
        static int Dish = 0;
        static int Rx = 0;
        static int Tx = 0;
        static int Startsetup = 1;
		static int Batteryrandom = 0;
		static int downloads = 0;
		static int drives = 0;
		static int warn = 0;
		static int SC = 0;
		static int CK = 0;
		static int RCK = 0;
		float ssd2 = 1.28f;
		
		if (Mainwindow)
		{
			ImGui::SetNextWindowPos(ImVec2(100, 80));    
			ImGui::SetNextWindowSize(ImVec2(800,500)); 
			ImGui::Begin("###Mainwindow", &Mainwindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("####Data_r", ImVec2(785,100), true);
            ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Payloads Acquired");
            ImGui::Separator();
            if (datab >= 1){ImGui::Text("DATA Block downloaded");}
            if (datab >= 2){ImGui::SameLine(200);ImGui::Text("DATA Block downloaded");}
            if (datab >= 3){ImGui::SameLine(400);ImGui::Text("DATA Block downloaded");}
            if (datab >= 4){ImGui::SameLine(600);ImGui::Text("DATA Block downloaded");}
            if (datab >= 5){ImGui::Text("DATA Block downloaded");}
            if (datab >= 6){ImGui::SameLine(200);ImGui::Text("DATA Block downloaded");}
            if (datab >= 7){ImGui::SameLine(400);ImGui::Text("DATA Block downloaded");}
            if (datab >= 8){ImGui::SameLine(600);ImGui::Text("DATA Block downloaded");}
            if (datab >= 9){ImGui::Text("DATA Block downloaded");}
            if (datab >= 10){ImGui::SameLine(200);ImGui::Text("DATA Block downloaded");}
            if (datab >= 11){ImGui::SameLine(400);ImGui::Text("DATA Block downloaded");}
            if (datab >= 12){ImGui::SameLine(600);ImGui::Text("DATA Block downloaded");}
            
			
			ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::Text("");
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("####INPUT", ImVec2(500,300), true);
            ImGui::PushItemWidth(100);
            ImGui::Text("	Commands");ImGui::SameLine(180);ImGui::Text("Effect.");ImGui::SameLine(425);ImGui::Text("OFF / ON");
            ImGui::Separator();
            ImGui::Text("");
            ImGui::Text("Deploy Solar Cells");ImGui::SameLine(160);ImGui::Text("- Will DISABLE Antenna dish.");ImGui::SameLine(400);ImGui::SliderInt("#####cells", &Cells, 0, 1);
            ImGui::Text("Deploy Antenna dish");ImGui::SameLine(160);ImGui::Text("- Will DISABLE Solar cells.");ImGui::SameLine(400);ImGui::SliderInt("###Dish", &Dish, 0, 1);
            ImGui::Text("Antenna Transmit");ImGui::SameLine(160);ImGui::Text("- Will DISABLE Antenna receive.");ImGui::SameLine(400);ImGui::SliderInt("###transmit", &Tx, 0, 1);
            ImGui::Text("Antenna Receive");ImGui::SameLine(160);ImGui::Text("- Will DISABLE Antenna Transmit.");ImGui::SameLine(400);ImGui::SliderInt("###receive", &Rx, 0, 1);
            ImGui::Text("Collect science DATA");ImGui::SameLine(160);ImGui::Text("- Will DISABLE ALL.");ImGui::SameLine(400);ImGui::SliderInt("###science", &SC, 0, 1);
			ImGui::Text("Push DATA to PAYLOAD");ImGui::SameLine(160);ImGui::Text("- Push DATA from SSD1 TO SSD2.");ImGui::SameLine(400);ImGui::SliderInt("###pushd", &pushd, 0, 1);
			ImGui::PopItemWidth();
            ImGui::EndChild();
            ImGui::PopStyleVar();
			ImGui::SameLine();
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("####OUTPUT", ImVec2(275,300), true);
            ImGui::Text("				Status");
            ImGui::Separator();
            ImGui::Text("");
            if (Cells == 0)
            	{
            		recharge = 0.0f;
            		ImGui::Text("Retracted", recharge);
            		ImGui::Separator();
				}
			if (Cells == 1)
            	{
            		
            		ImGui::Text("Deployed", recharge);
            		ImGui::Separator();
            		Dish = 0;
            		Tx = 0;
            		Rx = 0;
				}
            
            if (Dish == 1)
            	{
            		ImGui::Text("Click for internal status -");ImGui::SameLine();
					if (ImGui::SmallButton("PING")) {Internal = true; };
					ImGui::Separator();
					discharge = discharge + 0.07f;
					Cells = 0;
				}
			if (Tx == 1)
            	{
            		ImGui::Text("Transmitting %f kBs", rate);
            		ImGui::Separator();
            		Cells = 0;
            		Rx = 0;
            		Dish = 1;
            		discharge = discharge + 0.4f;
				}	
			if (Rx == 1)
            	{
            		ImGui::Text("Receving %f kBs", receving);
            		ImGui::Separator();
            		Cells = 0;
            		Tx = 0;
            		Dish = 1;
            		discharge = discharge + 0.2f;
            		
				}
			if (SC == 1)
            	{
            		ImGui::Text("Collecting DATA");
            		ImGui::Separator();
            		Cells = 0;
            		Rx = 0;
            		Tx = 0;
            		Dish = 1;
            		discharge = discharge + 0.8f - recharge;
            		
				}
			if (pushd == 1)	
				{
					ImGui::Text("Moving DATA");
					ImGui::Separator();
					Cells = 0;
            		Rx = 0;
            		Tx = 0;
            		Dish = 1;
            		discharge = discharge + 0.2f;
				}
            ImGui::Text("");
            ImGui::Text("");
            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("####DOWNLOAD", ImVec2(785,56), true);
           	ImGui::Text("File DOWNLOAD - Deploy DISH to TRANSMIT click DOWNLOAD. ");
            ImGui::Separator();
            ImGui::PushItemWidth(100);ImGui::Combo("####dummyme",&drives," \0SSD 2\0", 2);ImGui::PopItemWidth();
            ImGui::SameLine();
            if (ImGui::Button("DOWNLOAD",  ImVec2(120,0)) && Dish == 1 && Tx == 1 && drives == 1)
			{downloads = 1;}
			ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::End();
		}
		
		if (Mainwindow)
		{
			ImGui::SetNextWindowPos(ImVec2(920, 80));    
			ImGui::SetNextWindowSize(ImVec2(250,115)); 
			ImGui::Begin("####Cubesat Battery", &Mainwindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("####Battery", ImVec2(235,100), true, ImGuiWindowFlags_NoScrollbar);
			static float progress = 0.4f, progress_dir = 1.0;
			if (Startsetup == 1)
			{
				
				srand(static_cast<unsigned int>(time(0)));
				int randomNumber = rand();
				Batteryrandom = (randomNumber % 10) + 5;
				if (Batteryrandom == 5){progress = 0.5f;}
				if (Batteryrandom == 6){progress = 0.6f;}
				if (Batteryrandom == 7){progress = 0.7f;}
				if (Batteryrandom == 8){progress = 0.8f;}
				if (Batteryrandom == 9){progress = 0.9f;}
				
				Startsetup = 0;
			}
			if (Cells == 1)
			{
				progress += progress_dir * recharge * ImGui::GetIO().DeltaTime / 60;
			}
			if (Cells == 0)
			{
				progress -= progress_dir * discharge * ImGui::GetIO().DeltaTime / 60;
			}

            ImGui::Text("Battery"); // Colour me
			ImGui::ProgressBar(progress, ImVec2(-1.0f,0.0f));
			ImGui::Text("Status:");
            if (Cells == 1)
            {
            	ImGui::SameLine();ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Charging");
            	ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "%f Amps/s",recharge);
            	warn = 0;
			}
			if (Cells == 0 && progress > 0.20)
            {
            	ImGui::SameLine();ImGui::TextColored(ImVec4(1.0f,1.0f,0.0f,1.0f), "Discharging", discharge);
            	ImGui::TextColored(ImVec4(1.0f,1.0f,0.0f,1.0f), "%f Amps/s", discharge);
            	warn = 0;
			}
            if (Cells == 0 && progress < 0.20)
            {
            	ImGui::SameLine();ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "Emergency", discharge);
            	ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "%f Amps/s", discharge);
            	warn = 1;
			}
			 if (Cells == 0 && progress < 0.05)
            {
            	Cells = 1;
            	Dish = 0;
            	Rx = 0;
            	Tx = 0;
            	SC = 0;
            	pushd = 0;
			}
			
            ImGui::EndChild();
            ImGui::PopStyleVar();
			ImGui::End();
		}
		if (Mainwindow)
		{
			ImGui::SetNextWindowPos(ImVec2(920, 210));    
			ImGui::SetNextWindowSize(ImVec2(250,370)); 
			ImGui::Begin("####Cubesat Status", &Mainwindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::Text("		   DATA STORAGE");
			ImGui::Separator();
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("####OS", ImVec2(235,105), true);
			static float progressos = 0.82f, progressos_dir = 1.0;
            
            //progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
                
            

            ImGui::Text("Micro-Controller SSD"); // Colour me
			ImGui::ProgressBar(progressos, ImVec2(-1.0f,0.0f));
            ImGui::Text("Status:");
            if (warn == 0)
            {
            	ImGui::SameLine();ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Heart beat stable");
            }
            if (warn == 1)
            {
            	ImGui::SameLine();ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "Low power mode");
            	ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "CPU/Data rates halfed");
            	ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "");
            	
				rate = rate /2;
			}
            ImGui::EndChild();
            ImGui::PopStyleVar();
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("####SSD", ImVec2(235,105), true);
			static float progressssd1 = 0.21f, progressssd1_dir = 1.1;
            
                //progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
                
            

            ImGui::Text("(SSD 1) Additional space"); // Colour me
			ImGui::ProgressBar(progressssd1, ImVec2(-1.0f,0.0f));
			ImGui::Text("Status:");
			if (SC == 1 && progressssd1 < 1.0)
			{
				progressssd1 += progressssd1_dir * rate * ImGui::GetIO().DeltaTime / 60;
				ImGui::SameLine();ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Collecting");
			}
			static float compress = 0.0, compressf = 1.1;
            if (progressssd1 >= 1.0)
            {
            	SC = 0;
            	if (CK == 0)
            	{
				
            	compress += compressf * ImGui::GetIO().DeltaTime;
				}
				if (compress >= 1.0)
				{
					
					CK = 1;
					ImGui::SameLine();ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Converting Completed");
				}
            	
			}
			if (Dish == 1 && RCK == 1)
				{
					progressssd1 -= progressssd1_dir * rate * ImGui::GetIO().DeltaTime / 60;
					ImGui::SameLine();ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Moving DATA");
					compress -= compressf * rate * ImGui::GetIO().DeltaTime / 60;
					
			
				}
			if (progressssd1 <= 0.0)
			{
				RCK = 0;
			}
            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("####Scientific Data", ImVec2(235,105), true);
			static float progresssd = 1.0f, progresssd_dir = 1.1;
            
            
                

            ImGui::Text("(SSD 2) Payload DATA"); // Colour me
			ImGui::ProgressBar(progresssd, ImVec2(-1.0f,0.0f));
            ImGui::Text("Status:");
            if (downloads == 1 && Dish == 1 && Tx == 1 && drives == 1 && progresssd > 0.00f)
            {
            	progresssd -= progresssd_dir * rate * ImGui::GetIO().DeltaTime / 60;
        		ImGui::SameLine();ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Downloading");
        		if (progresssd <= 0.0)
        		{
        			datab = datab +1;
				}
			}
			if (Dish == 1 && CK == 1 && pushd == 1)
			{
				progresssd += progresssd_dir * rate * ImGui::GetIO().DeltaTime / 60;
        		ImGui::SameLine();ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Receiving");
        		RCK = 1;
        		
        		
        		
			}
			if (progresssd <= 0.0 && RCK == 1)
			{
				CK = 0;
				pushd = 0;	
			}
//			if (progresssd >= 1.0 && RCK == 1)
//			{
//				ImGui::SameLine();ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Received");
//				ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Ready to download");
//			}
            ImGui::EndChild();
            ImGui::PopStyleVar();
			ImGui::End();
		}
		if (Internal)
		{
			ImGui::Begin("Internal report.", &Internal);
			
			ImGui::End();		
		}	
        if (timer)
        {
        	ImGui::SetNextWindowPos(ImVec2(400, 25));    
			ImGui::SetNextWindowSize(ImVec2(300,50)); 
			ImGui::Begin("###timer", &timer, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			float time = 0.0;
			int mins = 0;
			float reset = 0;
			time = ImGui::GetTime();
			while (time < ImGui::GetTime())
			{
				time += 1.0f / 60;
				
			}
			
			
			
			ImGui::Text(" Seconds %f", time);
			ImGui::End();
		}
		if(show_right_click_menu)
		{
		
			ImVec2 base_pos = ImGui::GetMousePos();
			ImGui::SetNextWindowPos(ImVec2(base_pos.x,base_pos.y),ImGuiCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(100,63));
			ImGui::Begin("###rightmenu", &show_right_click_menu,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
			ImGui::BeginChild("####rightmenu", ImVec2(-1,-1), true,ImGuiWindowFlags_NoScrollbar);
            sprintf(right_click_selection, "  Copy", 1);
            if (ImGui::Selectable(right_click_selection, right_menu_selection == 1 )){right_menu_selection = 1; ImGui::LogToClipboard();} 
            ImGui::Separator();
			sprintf(right_click_selection, "  Paste", 2);
            if (ImGui::Selectable(right_click_selection, right_menu_selection == 2 )){right_menu_selection = 2;} 
   			
			
			ImGui::EndChild();
			ImGui::End();
			
		}
        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*255.0f), (int)(clear_color.y*255.0f), (int)(clear_color.z*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            g_pd3dDevice->Reset(&g_d3dpp);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
    }
	Shutdown:
    ImGui_ImplDX9_Shutdown();
    if (g_pd3dDevice) g_pd3dDevice->Release();
    if (pD3D) pD3D->Release();
    UnregisterClass(_T("ImGui Example"), wc.hInstance);

    return 0;
}
