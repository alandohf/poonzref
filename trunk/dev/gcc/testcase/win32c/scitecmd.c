#include <windows.h>

#include <direct.h>

#include <string>
#include <vector>

char *help =
    "scitecmd [file] options                                    \n"
    "                                                           \n"
    "Command line interface to scite. Opens the specified file  \n"
    "in the current SciTe window.                               \n"
    "                                                           \n"
    "OPTIONS                                                    \n"
    "                                                           \n"
    "  -h          Print this help text.                        \n"
    "  -l line     Go to line number line in the file.          \n"
    "  -f text     Find the text text in the file.              \n"
    "  -i text     Insert text in the file.                     \n"
    "  -n          Create a new empty window.                   \n"
    "  -s          Open a new window with STDIN content.        \n"
    "  -c cmd      Raw scite command.                           \n";

HWND find_target()
{
    HWND target = 0;
    unsigned int SDI = RegisterWindowMessage("SciTEDirectorInterface");
    HWND w = GetWindow(GetDesktopWindow(),GW_CHILD);
    while (w) {
        DWORD res = 0;
        SendMessageTimeout(w, SDI, 0, 0, SMTO_NORMAL, 1000, &res);
        if (res == static_cast<DWORD>(SDI)) {
            return w;
        }
        w = GetWindow(w, GW_HWNDNEXT);
    }
    return 0;
}

std::string encode(const std::string s)
{
    std::string trans;
    for (int i=0; i<int(s.size()); ++i) {
        if (s[i] == '\\') {
            trans.append(2, '\\');
        } else if (s[i] == '\n') {
            trans.append(1,'\\');
            trans.append(1,'n');
        } else {
            trans.append(1,s[i]);
        }
    }
    return trans;
}

#define REQUIRE_ARG if (opt >= argc) goto err

int main(int argc, char **argv)
{
    std::vector<std::string> commands;

    bool force_activate = true;

    int opt = 1;
    while (opt < argc) 
    {
        std::string cmd = argv[opt++];

        if (cmd == "--help" || cmd == "-h") {
            puts(help);
            return 0;
        } else if (cmd == "-l") {
            REQUIRE_ARG;
            std::string arg = argv[opt++];
            std::string command = std::string("goto:") + arg;
            commands.push_back(command);
        } else if (cmd == "-f") {
            REQUIRE_ARG;
            std::string arg = argv[opt++];
            std::string command = std::string("find:") + arg;
            commands.push_back(command);
        } else if (cmd == "-i") {
            REQUIRE_ARG;
            std::string arg = argv[opt++];
            std::string command = std::string("insert:") + encode(arg);
            commands.push_back(command);
        } else if (cmd == "-n") {
            commands.push_back("menucommand:101");
            force_activate = false;
        } else if (cmd == "-s") {
            char buffer[205];
            commands.push_back("menucommand:101");
            force_activate = false;

            while (fgets(buffer, 200, stdin)) {
                commands.push_back( std::string("insert:") + encode(buffer));
            }
        } else if (cmd == "-c") {
            REQUIRE_ARG;
            std::string arg = argv[opt++];
            commands.push_back(arg);
        } else {
            force_activate = false;
            char dir[1005];
            std::string file = cmd;
            std::string path;
            if (file.find(':') == std::string::npos && file[0] != '/' && file[0] != '\\') {
                _getcwd(dir, 1000);
                path = std::string(dir) + "\\" + file;
            } else
                path = file;
            for (int i=0; i<int(path.size()); ++i)
                if (path[i] == '\\')
                    path[i] = '/';
            commands.push_back(std::string("open:" + path));
        }
    }

    if (commands.size() == 0) {
        puts(help);
        return 0;
    }

    if (force_activate) {
        commands.push_back("menucommand:101");
        commands.push_back("menucommand:105");
    }

    HWND w = find_target();
    if (w == 0) {
        puts("Scite not found, trying to start it.");
        ShellExecute(0, "open", "scite.exe", NULL, "c:\\", SW_SHOW);
        int t = 5000;
        while (t > 0 && w == 0) {
            Sleep(50);
            t -= 50;
            w = find_target();
        }
        if (w == 0) {
            puts ("Couldn't start scite, make sure scite.exe is in path.");
            return -1;
        }
    }

    SetForegroundWindow(w);
    std::vector<std::string>::iterator it = commands.begin(), end = commands.end();
    for (; it!=end; ++it) {
        COPYDATASTRUCT cds;
        cds.dwData = 0;
        cds.cbData = (DWORD)it->size();
        cds.lpData = (void *)it->c_str();

        SendMessage(w, WM_COPYDATA, 0, (long)&cds);
    }   
    return 0;

err:
    puts("Error in arguments.");
    puts(help);
    return 1;
}
