#pragma once
#include <string>
#include <iostream>
using namespace std;

class Notification {
    string notifID, message, receiverID;
    bool   isRead = false;
public:
    void setDetails(const string& id, const string& msg,
        const string& recv, bool read = false) {
        notifID = id; message = msg; receiverID = recv; isRead = read;
    }
    void display() const {
        cout << "  ID      : " << notifID << "\n"
            << "  Message : " << message << "\n"
            << "  To      : " << receiverID << "\n"
            << "  Status  : " << (isRead ? "Read" : "Unread") << "\n";
    }
    void markRead() { isRead = true;  cout << "  Notification marked as Read.\n"; }
    void markUnread() { isRead = false; cout << "  Notification marked as Unread.\n"; }
};