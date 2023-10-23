#ifndef _DFPLAYER_H
#define _DFPLAYER_H

/**
 * SoftwareSerial disables interrupts while transmitting data, so it conflicts with Servo library.
 */
#include "SoftwareSerial.h"
#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"


namespace DFPLAYER
{
    //""""""""""""""""""""""""class

    /// @brief class to manage DFplayer Mini
    class Dfplayer
    {


    //""""""""""""""""""""""""private object composition
    private:
        DFRobotDFPlayerMini dfp;        ///< dfp object
        SoftwareSerial dfpSerial;       ///< dfp software serial

    
    //""""""""""""""""""""""""constructor declaration
    public:
        /// @brief Constructor Dfplayer
        Dfplayer(uint8_t rxPin, uint8_t txPin, int busyPin);



    //""""""""""""""""""""""""public member functions

        /// @brief init DFP
        void begin();

        /// @brief play Stop message
        void playStopMsg();

        /// @brief play Good Morning message
        void playGoodMorningMsg();

        /// @brief set actual volume
        /// @param vol from 0 to 30
        void setVolume(int vol);

        /// @brief read dfp busy pin
        /// @return state of dfp busy pin
        const int readBusyPin();

        /// @brief get dfp state
        /// @return 00-playback_finish 01-playing 02-paused 08-sleeping
        const int readState();

        /// @brief play random music for radio
        void playRandomMusic();

        /// @brief pause music
        void pauseMusic();

        /// @brief start play music
        void startMusic();

        /// @brief pause/start music depends om m_isPaused flag
        void pauseStartMusic();

        /// @brief down volume
        void volumeDown();

        /// @brief up volume
        void volumeUp();

        /// @brief play previous music in mp3 folder
        void playPreviousMusic();

        /// @brief play next music in mp3 folder
        void playNextMusic();

        /// @brief play previous good morning msg in folder 1
        void playPreviousMsg();

        /// @brief play next good morning msg in folder 1
        void playNextMsg();

        /// @brief play menu in folder 4
        void playMenu();

        /// @brief m_radioON getter
        /// @return m_radioON
        bool getRadioON() {
            return m_radioON;
        }

        /// @brief m_radioON setter
        /// @param state state
        void setRadioON(bool state){
            m_radioON = state;
        }

        /// @brief m_isPaused getter
        /// @return m_isPaused
        bool getIsPaused() {
            return m_isPaused;
        }

        /// @brief m_isPaused setter
        /// @param state state
        void setIsPaused(bool state){
            m_isPaused = state;
        }

        /// @brief m_currentMusic getter
        /// @return m_currentMusic
        int getCurrentMusic(){
            return m_currentMusic;
        }

        /// @brief m_currentVolume getter
        /// @return m_currentVolume
        int getCurrentVoulme(){
            return m_currentVolume;
        }

        /// @brief m_currentGoodMorningMsg getter
        /// @return m_currentGoodMorningMsg
        int getCurrentGoodMorningMsg(){
            return m_currentGoodMorningMsg;
        }



    //""""""""""""""""""""""""private data members
    private:
        int m_currentMusic{1};         ///< DFP current music in play
        int m_currentVolume{18};       ///< DFP current volume 0~30
        int m_currentGoodMorningMsg{1};       ///< sequential 'good morning' message
        const int m_busyPin{};         ///< DFP busy pin (LOW when busy)
        long m_nStopMsgFiles{};        ///< quantity of 'stop' messages
        long m_nGoodMorningMsgFiles{}; ///< quantity of 'good morning' files
        long m_nMp3Files{};            ///< quantity of mp3 files
        long m_nMenuFiles{};           ///< quantity of menu files
        bool m_radioON{0};             ///< manage radio in continuos mode
        bool m_isPaused{0};            ///< flags radio in pause
    };

} // namespace DFPLAYER

#endif //_DFPLAYER_H