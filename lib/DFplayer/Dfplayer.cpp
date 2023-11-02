/*!
 * @file Dfplayer.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	Augusto Sherman
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#include "Dfplayer.h"

// #define _DEBUG

namespace DFPLAYER
{
    //"""""""""""""""""""""" constructor definition

    Dfplayer::Dfplayer(uint8_t rxPin, uint8_t txPin, int busyPin)
        : dfp{}, dfpSerial{rxPin, txPin}, m_busyPin{busyPin}
    {
    }



    //""""""""""""""""""""""

    void Dfplayer::begin()
    {
        // wait DFPlayer
        delay(2000);

        // init DFPlayer serial
        dfpSerial.begin(9600);
        delay(200);

        // assure dfPSerial is listening
        dfpSerial.listen();

        // check DFPlayer connected and SD card inserted
        int tentativa = 1;

        /**
         * dfp.begin MUST TO BE INITIALIZED WITH (dfpSerial,false) to work properly)
         */
        while (!dfp.begin(dfpSerial, false) && tentativa < 4)
        {
            Serial.println(F("SD card error, check connection"));
            // BT.println(F("SD card error, check connection"));
            tentativa++;
            delay(1000);
        }
        if (tentativa == 4 && !dfp.begin(dfpSerial))
        {
            Serial.println("DFplayer OFF");
            // BT.println("DFplayer OFF");
        }
        else
        {
            Serial.println(F("DFPlayer ON ..."));
            // BT.println(F("DFPlayer ON ..."));

            // Continue  DFplayer init
            dfp.setTimeOut(500); ///< Set serial communictaion time out 500ms

            dfp.volume(m_currentVolume); ///< Set volume value (0~30)

            // check initial volume
            Serial.print("m_currentVolume: ");
            Serial.println(dfp.readVolume());

            dfp.EQ(DFPLAYER_EQ_NORMAL); ///< set equalizer
            Serial.print("Equalizer: ");
            Serial.println(dfp.readEQ());

            dfp.outputDevice(DFPLAYER_DEVICE_SD); ///< set SD card output

            // check number of "STOP messages"
            m_nStopMsgFiles = -1;
            int j = 0;
            while (m_nStopMsgFiles == -1 && j < 5)
            {
                m_nStopMsgFiles = dfp.readFileCountsInFolder(2);
                j++;
                delay(200);
            }
            if (m_nStopMsgFiles == -1)
                m_nStopMsgFiles = 21;
            Serial.print(F("n. of Stop messages: "));
            Serial.println(m_nStopMsgFiles);
            // BT.print("# of Stop messages: ");BT.println(nStopMsgFiles);

            // check number of "good morning" messages
            m_nGoodMorningMsgFiles = -1;
            j = 0;
            while (m_nGoodMorningMsgFiles == -1 && j < 5)
            {
                m_nGoodMorningMsgFiles = dfp.readFileCountsInFolder(1);
                j++;
                delay(200);
            }
            if (m_nGoodMorningMsgFiles == -1)
                m_nGoodMorningMsgFiles = 13;
            Serial.print(F("n. of good morning messages: "));
            Serial.println(m_nGoodMorningMsgFiles);
            // BT.print("# of good morning messages: ");BT.println(nGoodMorningMsgFiles);

            // check number of MP3 musics
            m_nMp3Files = -1;
            j = 0;
            while (m_nMp3Files == -1 && j < 5)
            {
                m_nMp3Files = dfp.readFileCountsInFolder(3);
                j++;
                delay(200);
            }
            if (m_nMp3Files == -1)
                m_nMp3Files = 12;
            Serial.print(F("n. of MP3 musics "));
            Serial.println(m_nMp3Files);
            // BT.print("# of MP3 musics ");BT.println(nMp3Files);

            // check Menu message"
            m_nMenuFiles = -1;
            j = 0;
            while (m_nMenuFiles == -1 && j < 5)
            {
                m_nMenuFiles = dfp.readFileCountsInFolder(4);
                j++;
                delay(200);
            }
            if (m_nMenuFiles == -1)
                m_nMenuFiles = 1;
            Serial.print(F("Menu message: "));
            Serial.println(m_nMenuFiles);
            // BT.print("Menu message: ");BT.println(nMenuFiles);
        }
    }

    //""""""""""""""""""""""

    void Dfplayer::playStopMsg()
    {
        int randomStopMsg = random(1, m_nStopMsgFiles + 1);
        bool busy = !digitalRead(m_busyPin);

        // if Roberto is playing music, play Stop message on Advertisement folder
        // if (m_radioON || busy)
        if (m_radioON || busy)
        {
#ifdef _DEBUG
            Serial.print("advertise mode, busyPin = ");
            Serial.print(!busy);
            Serial.print("\tDFP state = ");
            Serial.println(readState());
            delay(100);
#endif
            dfp.advertise(randomStopMsg);
            delay(100);
        }
        else
        {
            dfp.playFolder(2, randomStopMsg);
#ifdef _DEBUG
            Serial.print("normal mode, busyPin = ");
            Serial.print(!busy);
            Serial.print("\tDFP state = ");
            Serial.println(readState());
#endif
        }
    }

    //""""""""""""""""""""""

    void Dfplayer::playGoodMorningMsg()
    {
        uint8_t randomMsg = random(1, m_nGoodMorningMsgFiles + 1);
        bool busy = !digitalRead(m_busyPin);
        if (!busy)
        {
            dfp.playFolder(1, randomMsg);
        }
    }

    //""""""""""""""""""""""

    void Dfplayer::setVolume(int vol)
    {
        m_currentVolume = vol;
        dfp.volume(m_currentVolume);
    }

    //""""""""""""""""""""""

    const int Dfplayer::readBusyPin()
    {
        return digitalRead(m_busyPin);
    }

    //""""""""""""""""""""""

    const int Dfplayer::readState()
    {
        dfpSerial.listen();

        int state = dfp.readState();
        delay(100);

        return state;
    }

    void Dfplayer::playRandomMusic(){
        m_currentMusic = random(1, m_nMp3Files + 1);

        dfp.playMp3Folder(m_currentMusic);
    }

    void Dfplayer::pauseMusic(){
        dfp.pause();
    }

    void Dfplayer::startMusic(){
        dfp.start();
    }

    void Dfplayer::pauseStartMusic(){

        (m_isPaused) ? dfp.start() : dfp.pause();

        m_isPaused = !m_isPaused;

        delay(150);
    }

    void Dfplayer::volumeDown(){
        if (m_currentVolume > 5){
            m_currentVolume--;
            dfp.volumeDown();
        }
    }

    void Dfplayer::volumeUp(){
        if (m_currentVolume < 30)
        {
            m_currentVolume++;
            dfp.volumeUp();
        }
    }

    void Dfplayer::playPreviousMusic(){
        
        (m_currentMusic > 1) ? m_currentMusic-- : m_currentMusic = m_nMp3Files;

        dfp.playMp3Folder(m_currentMusic);
    }

    void Dfplayer::playNextMusic(){

        (m_currentMusic < m_nMp3Files) ? m_currentMusic++ : m_currentMusic = 1;

        dfp.playMp3Folder(m_currentMusic);
    }

    void Dfplayer::playPreviousMsg(){

        (m_currentGoodMorningMsg > 1) ? m_currentGoodMorningMsg-- : m_currentGoodMorningMsg = m_nGoodMorningMsgFiles;

        dfp.playFolder(1,m_currentGoodMorningMsg);
    }

    void Dfplayer::playNextMsg(){

        (m_currentGoodMorningMsg < m_nGoodMorningMsgFiles) ? m_currentGoodMorningMsg++ : m_currentGoodMorningMsg = 1;

         dfp.playFolder(1,m_currentGoodMorningMsg);
    }

    void Dfplayer::playMenu(){
        dfp.playFolder(4, 1);
    }

} // namespace DFPLAYER {
