#include "Sounds.h"

irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();

void Sounds::playStartSound() {
    SoundEngine->play2D("/home/chris/CLionProjects/Chess/assets/start.wav");
}

void Sounds::playMoveSound() {
    SoundEngine->play2D("/home/chris/CLionProjects/Chess/assets/move.wav");
}

void Sounds::playCaptureSound() {
    SoundEngine->play2D("/home/chris/CLionProjects/Chess/assets/capture.wav");
}

void Sounds::playCheckSound() {
    SoundEngine->play2D("/home/chris/CLionProjects/Chess/assets/check.wav");
}

void Sounds::playCastleSound() {
    SoundEngine->play2D("/home/chris/CLionProjects/Chess/assets/castle.wav");
}

void Sounds::playCheckmateSound() {
    SoundEngine->play2D("/home/chris/CLionProjects/Chess/assets/checkmate.wav");
}
