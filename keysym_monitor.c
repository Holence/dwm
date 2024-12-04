// written by chatgpt

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    Display *display;
    Window root;
    XEvent event;

    // Open the display
    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }

    // Get the root window
    root = DefaultRootWindow(display);

    // Grab the keyboard
    if (XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime) != GrabSuccess) {
        fprintf(stderr, "Failed to grab the keyboard\n");
        XCloseDisplay(display);
        return 1;
    }

    printf("Press any key to see the corresponding keysym. Press 'q' to quit.\n");

    while (1) {
        // Wait for the next event
        XNextEvent(display, &event);

        if (event.type == KeyPress) {
            // Get the keysym from the keycode
            KeySym keysym = XLookupKeysym(&event.xkey, 0);

            if (keysym == NoSymbol) {
                printf("No keysym found for keycode: %d\n", event.xkey.keycode);
                continue;
            }

            // Print the keysym name
            char *keysym_name = XKeysymToString(keysym);
            if (keysym_name) {
                printf("Key pressed: %s (Keysym: 0x%lx)\n", keysym_name, keysym);

                // Exit on 'q'
                if (strcmp(keysym_name, "q") == 0) {
                    break;
                }
            } else {
                printf("Unknown keysym: 0x%lx\n", keysym);
            }
        }
    }

    // Ungrab the keyboard and close the display
    XUngrabKeyboard(display, CurrentTime);
    XCloseDisplay(display);
    return 0;
}
