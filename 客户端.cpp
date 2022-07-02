//#include <windows.h>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main(int argc, char** argv) {
    WSADATA wsaData;//

     //int iResult;//是否成功初始化

                 // 初始化库

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        //printf("WSAStartup failed: %d\n", iResult);
        cout << "\n初始化失败";
        return 1;
    }
    else
    {
        cout << "\n初始化成功";
    }
    //---------------------
    SOCKET S = INVALID_SOCKET;//声名对象S

    S = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建SOCK

    struct addrinfo  hints, * f;//hints告诉getaddrinfo我的类型，返回到resuit
    //不变组合到36行
    memset(&hints, 0, sizeof(hints));//把内存块设为0
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    // 创建一个结构体来表示IP地址:端口号的组合

    cout << "\n\n请输入服务端IP\n";

    string str;
    
    cin >> str;
    
    if (getaddrinfo(str.c_str(), "3333", &hints, &f) != 0)
    {
        return 1;
    }

    //连接

     
     
    if (connect(S, f->ai_addr, (int)f->ai_addrlen)== SOCKET_ERROR) {
        closesocket(S);
       
        cout << "\n\n连接失败\n";
        return 1;
    }

    while (1)
    {
        char ch[50]={0};
        
        string g;
        cout << "\n如果接收请按1\n";
        cin >> g;

        if (g== "1")
        {
            int n = recv(S, ch, sizeof(ch), 0);
            if (n == SOCKET_ERROR)
            {
                cout << "\n接受失败\n";
            }
            cout << "\n接受到:" << ch << endl;
        }
        else
        {
            cout << "\n已跳过接收\n";
        }
        
        
        cout << "\n发送请输入:";
        
        cin >> str;
        send(S, str.c_str(), str.size(), 0);
    }
  

    //---------------------
    WSACleanup();
}