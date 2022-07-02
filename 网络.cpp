//#include <windows.h>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main(int argc, char** argv) {
    WSADATA wsaData;//
    cout << "服务端:\n";
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

    struct addrinfo  hints, * result;//hints告诉getaddrinfo我的类型，返回到resuit
    //不变组合到36行
    memset(&hints, 0, sizeof(hints));//把内存块设为0
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    // 创建一个结构体来表示IP地址:端口号的组合
    if (getaddrinfo(NULL, "3333", &hints, &result) != 0)
    {
        return 1;
    }

    //绑定组合


    if (bind(S, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
    {

        return 1;
    }

    listen(S, SOMAXCONN);//开始监听是否有连接传入
    //连接准备完成
    sockaddr remote_addr;//客户端的IP地址和端口

    while (1)
    {
        cout << "[正在尝试接受连接]\n";
        SOCKET C = accept(S, &remote_addr, NULL);//接受连接
        if (C == INVALID_SOCKET)
        {
            cout << "\n\n连接失败\n\n";
            continue;
        }
        cout << "\n成功\n\n";

        while (1) {
            string str;
            cout << "\n发送请输入:";

            cin >> str;
            send(C, str.c_str(), str.size(), 0);
            cout << "\n如果接收请按1\n";
            cin >> str;

            

            if ( str== "1")
            {
                str = "";
                str.resize(50);

                int n = recv(C, (char*)str.data(), str.size(), 0);
                if (n == SOCKET_ERROR)
                {
                    cout << "\n接受失败\n";
                }
                cout << "\n接收到:" << str << "\n";
            }
            else
            {
                cout << "\n已跳过接收\n";
            }


          

        }
        
        closesocket(C);
    }

    //---------------------
    WSACleanup();
}