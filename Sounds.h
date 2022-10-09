#ifndef CHESS_SOUNDS_H
#define CHESS_SOUNDS_H

#include <irrKlang.h>

class Sounds {
public:
    static void playStartSound();
    static void playMoveSound();
    static void playCaptureSound();
    static void playCheckSound();
    static void playCastleSound();
    static void playCheckmateSound();
};


#endif //CHESS_SOUNDS_H
