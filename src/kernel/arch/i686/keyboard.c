#include "keyboard.h"
#include "irq.h"
#include "io.h"
#include <stdbool.h>

#define KEYBOARD_PORT           0x60

#define UNKNOWN                  0xFFFFFFFF
#define ESC                     (0xFFFFFFFF - 1)
#define CTRL                    (0xFFFFFFFF - 2)
#define LSHFT                   (0xFFFFFFFF - 3)
#define RSHFT                   (0xFFFFFFFF - 4)
#define ALT                     (0xFFFFFFFF - 5)
#define F1                      (0xFFFFFFFF - 6)
#define F2                      (0xFFFFFFFF - 7)
#define F3                      (0xFFFFFFFF - 8)
#define F4                      (0xFFFFFFFF - 9)
#define F5                      (0xFFFFFFFF - 10)
#define F6                      (0xFFFFFFFF - 11)
#define F7                      (0xFFFFFFFF - 12)
#define F8                      (0xFFFFFFFF - 13)
#define F9                      (0xFFFFFFFF - 14)
#define F10                     (0xFFFFFFFF - 15)
#define F11                     (0xFFFFFFFF - 16)
#define F12                     (0xFFFFFFFF - 17)
#define SCRLCK                  (0xFFFFFFFF - 18)
#define HOME                    (0xFFFFFFFF - 19)
#define UP                      (0xFFFFFFFF - 20)
#define LEFT                    (0xFFFFFFFF - 21)
#define RIGHT                   (0xFFFFFFFF - 22)
#define DOWN                    (0xFFFFFFFF - 23)
#define PGUP                    (0xFFFFFFFF - 24)
#define PGDOWN                  (0xFFFFFFFF - 25)
#define END                     (0xFFFFFFFF - 26)
#define INS                     (0xFFFFFFFF - 27)
#define DEL                     (0xFFFFFFFF - 28)
#define CAPS                    (0xFFFFFFFF - 29)
#define NONE                    (0xFFFFFFFF - 30)
#define ALTGR                   (0xFFFFFFFF - 31)
#define NUMLCK                  (0xFFFFFFFF - 32)

const uint32_t g_LowerCase[128] = {
UNKNOWN,ESC,'1','2','3','4','5','6','7','8',
'9','0','-','=','\b','\t','q','w','e','r',
't','y','u','i','o','p','[',']','\n',CTRL,
'a','s','d','f','g','h','j','k','l',';',
'\'','`',LSHFT,'\\','z','x','c','v','b','n','m',',',
'.','/',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,
'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

const uint32_t g_UpperCase[128] = {
    UNKNOWN,ESC,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q','W','E','R',
'T','Y','U','I','O','P','{','}','\n',CTRL,'A','S','D','F','G','H','J','K','L',':','"','~',LSHFT,'|','Z','X','C',
'V','B','N','M','<','>','?',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',
LEFT,UNKNOWN,RIGHT,'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};


bool g_CapsOn = false;
bool g_CapsLock = false;

void i686_Keyboard_Handler(Registers* req);

void i686_Keyboard_Initialize()
{
    i686_IRQ_RegisterHandler(1, i686_Keyboard_Handler);
}

void i686_Keyboard_Handler(Registers* req)
{
    uint8_t scancode = i686_inb(KEYBOARD_PORT) & 0x7F;
    uint8_t state = i686_inb(KEYBOARD_PORT) & 0x80;

    
    switch(scancode){
        case 1:
        case 29:
        case 56:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 87:
        case 88:
            break;
        case 42:
            //shift key
            if (state == 0){
                g_CapsOn = true;
            }else{
                g_CapsOn = false;
            }
            break;
        case 58:
            if (!g_CapsLock && state == 0){
                g_CapsLock = true;
            }else if (g_CapsLock && state == 0){
                g_CapsLock = false;
            }
            break;
        default:
            if (state == 0){
                if (g_CapsOn || g_CapsLock){
                    printf("%c", g_UpperCase[scancode]);
                }else{
                    printf("%c", g_LowerCase[scancode]);
                }
            }
            
    }
}
