#include <iostream>
#include <windows.h>
#include <fstream>
#include <thread>
#include <string>
#include <ShlObj.h>
#include <Lmcons.h>
#include <sstream>
#include <iomanip>
#include <filesystem>
//#include <winsock2.h>
//#include <ws2tcpip.h>

//#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.22000.0\\um\\x64\\ws2_32.lib")

// имя пользователя
std::string getUsername() {
    char username[UNLEN + 1];
    DWORD usernameLength = UNLEN + 1;

    if (GetUserNameA(username, &usernameLength)) {
        return std::string(username);
    }
    else {
        return "Не удалось получить имя пользователя";
    }
}
// имя компьютера
std::string getComputerName() {
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD computerNameLength = MAX_COMPUTERNAME_LENGTH + 1;

    if (GetComputerNameA(computerName, &computerNameLength)) {
        return std::string(computerName);
    }
    else {
        return "Не удалось получить имя компьютера";
    }
}
// имя домен
std::string getDomainName() {
    char domainName[MAX_PATH + 1];
    DWORD domainNameLength = MAX_PATH + 1;

    if (GetComputerNameExA(ComputerNameDnsDomain, domainName, &domainNameLength)) {
        return std::string(domainName);
    }
    else {
        return "Не удалось получить доменное имя";
    }
}



// IP-адрес
//std::string getIPAddress() {
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        return "Ошибка при инициализации Winsock.";
//    }
//
//    char hostName[256];
//    if (gethostname(hostName, sizeof(hostName)) != 0) {
//        WSACleanup();
//        return "Ошибка при получении имени хоста.";
//    }
//
//    addrinfo* result = nullptr;
//    addrinfo* ptr = nullptr;
//    addrinfo hints;
//    ZeroMemory(&hints, sizeof(hints));
//    hints.ai_family = AF_INET;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//
//    if (getaddrinfo(hostName, nullptr, &hints, &result) != 0) {
//        WSACleanup();
//        return "Ошибка при получении информации о хосте.";
//    }
//
//    std::string ipAddress;
//    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
//        sockaddr_in* sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(ptr->ai_addr);
//        char* ip = inet_ntoa(sockaddr_ipv4->sin_addr);
//        ipAddress = ip;
//        break;  // Получаем только первый IP-адрес
//    }
//
//    freeaddrinfo(result);
//    WSACleanup();
//
//    return ipAddress;
//}

void foo() {
    short a = 1;

    while (true) {
        std::ofstream file("example.txt", std::ios::app);

        if (file.is_open()) {
            file << "Username: " + getUsername() + "\nComputerName: " + getComputerName() + 
                "\nDomain: " + getDomainName() << a << std::endl;
            file.close();
            a++;
        }
        else {
            std::cout << "Не удалось открыть файл для записи." << std::endl;
        }
        std::cout << "5 СЕКУНД ПРОШЛО\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void addAutoUpload() {
    WCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);

    HKEY hKey;
    RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);

    RegSetValueExW(hKey, L"MyApp", 0, REG_SZ, (LPBYTE)szPath, (lstrlenW(szPath) + 1) * sizeof(WCHAR));

    RegCloseKey(hKey);
}




int main() {
    setlocale(LC_ALL, "ru");

    //addAutoUpload();
    foo();
    

    return 0;
}
 