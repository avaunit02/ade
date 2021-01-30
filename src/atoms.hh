#pragma once

#include <string>
#include <vector>
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>

struct cached_atom {
    std::string name;
    xcb_atom_t* atom;
    xcb_intern_atom_cookie_t cookie;
};

xcb_atom_t _NET_SUPPORTED;
xcb_atom_t _NET_CURRENT_DESKTOP;
xcb_atom_t _NET_ACTIVE_WINDOW;
xcb_atom_t _NET_WM_NAME;
xcb_atom_t _NET_WM_DESKTOP;
xcb_atom_t _NET_WM_VISIBLE_NAME;
xcb_atom_t _NET_WM_WINDOW_TYPE;
xcb_atom_t _NET_WM_WINDOW_TYPE_DOCK;
xcb_atom_t _NET_WM_WINDOW_TYPE_NORMAL;
xcb_atom_t _NET_WM_PID;
xcb_atom_t _NET_WM_STATE;
xcb_atom_t _NET_WM_STATE_STICKY;
xcb_atom_t _NET_WM_STATE_SKIP_TASKBAR;
xcb_atom_t _NET_WM_STATE_ABOVE;
xcb_atom_t _NET_WM_STATE_MAXIMIZED_VERT;
xcb_atom_t _NET_WM_STRUT;
xcb_atom_t _NET_WM_STRUT_PARTIAL;
xcb_atom_t WM_PROTOCOLS;
xcb_atom_t WM_DELETE_WINDOW;
xcb_atom_t _XEMBED;
xcb_atom_t _XEMBED_INFO;
xcb_atom_t MANAGER;
xcb_atom_t WM_STATE;
xcb_atom_t _NET_SYSTEM_TRAY_OPCODE;
xcb_atom_t _NET_SYSTEM_TRAY_ORIENTATION;
xcb_atom_t _NET_SYSTEM_TRAY_VISUAL;
xcb_atom_t _NET_SYSTEM_TRAY_COLORS;
xcb_atom_t WM_TAKE_FOCUS;
xcb_atom_t Backlight;
xcb_atom_t BACKLIGHT;
xcb_atom_t _XROOTPMAP_ID;
xcb_atom_t _XSETROOT_ID;
xcb_atom_t ESETROOT_PMAP_ID;
xcb_atom_t _COMPTON_SHADOW;
xcb_atom_t _NET_WM_WINDOW_OPACITY;
xcb_atom_t WM_HINTS;

std::vector<cached_atom> cached_atoms = {
    {"_NET_SUPPORTED", &_NET_SUPPORTED},
    {"_NET_CURRENT_DESKTOP", &_NET_CURRENT_DESKTOP},
    {"_NET_ACTIVE_WINDOW", &_NET_ACTIVE_WINDOW},
    {"_NET_WM_NAME", &_NET_WM_NAME},
    {"_NET_WM_DESKTOP", &_NET_WM_DESKTOP},
    {"_NET_WM_VISIBLE_NAME", &_NET_WM_VISIBLE_NAME},
    {"_NET_WM_WINDOW_TYPE", &_NET_WM_WINDOW_TYPE},
    {"_NET_WM_WINDOW_TYPE_DOCK", &_NET_WM_WINDOW_TYPE_DOCK},
    {"_NET_WM_WINDOW_TYPE_NORMAL", &_NET_WM_WINDOW_TYPE_NORMAL},
    {"_NET_WM_PID", &_NET_WM_PID},
    {"_NET_WM_STATE", &_NET_WM_STATE},
    {"_NET_WM_STATE_STICKY", &_NET_WM_STATE_STICKY},
    {"_NET_WM_STATE_SKIP_TASKBAR", &_NET_WM_STATE_SKIP_TASKBAR},
    {"_NET_WM_STATE_ABOVE", &_NET_WM_STATE_ABOVE},
    {"_NET_WM_STATE_MAXIMIZED_VERT", &_NET_WM_STATE_MAXIMIZED_VERT},
    {"_NET_WM_STRUT", &_NET_WM_STRUT},
    {"_NET_WM_STRUT_PARTIAL", &_NET_WM_STRUT_PARTIAL},
    {"WM_PROTOCOLS", &WM_PROTOCOLS},
    {"WM_DELETE_WINDOW", &WM_DELETE_WINDOW},
    {"_XEMBED", &_XEMBED},
    {"_XEMBED_INFO", &_XEMBED_INFO},
    {"MANAGER", &MANAGER},
    {"WM_STATE", &WM_STATE},
    {"_NET_SYSTEM_TRAY_OPCODE", &_NET_SYSTEM_TRAY_OPCODE},
    {"_NET_SYSTEM_TRAY_ORIENTATION", &_NET_SYSTEM_TRAY_ORIENTATION},
    {"_NET_SYSTEM_TRAY_VISUAL", &_NET_SYSTEM_TRAY_VISUAL},
    {"_NET_SYSTEM_TRAY_COLORS", &_NET_SYSTEM_TRAY_COLORS},
    {"WM_TAKE_FOCUS", &WM_TAKE_FOCUS},
    {"Backlight", &Backlight},
    {"BACKLIGHT", &BACKLIGHT},
    {"_XROOTPMAP_ID", &_XROOTPMAP_ID},
    {"_XSETROOT_ID", &_XSETROOT_ID},
    {"ESETROOT_PMAP_ID", &ESETROOT_PMAP_ID},
    {"_COMPTON_SHADOW", &_COMPTON_SHADOW},
    {"_NET_WM_WINDOW_OPACITY", &_NET_WM_WINDOW_OPACITY},
    {"WM_HINTS", &WM_HINTS},
};

void cache_atoms(xcb_connection_t* connection) {
    for (auto& cached_atom: cached_atoms) {
        cached_atom.cookie = xcb_intern_atom(connection, false, cached_atom.name.length(), cached_atom.name.c_str());
    }
    for (auto& cached_atom: cached_atoms) {
        xcb_intern_atom_reply_t* reply = xcb_intern_atom_reply(connection, cached_atom.cookie, nullptr);
        if (reply) {
            *cached_atom.atom = reply->atom;
        }
        free(reply);
    }
}
