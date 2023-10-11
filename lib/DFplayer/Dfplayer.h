#ifndef _DFPLAYER_H
#define _DFPLAYER_H

#include <Arduino.h>
#include "SoftwareSerial.h"
/**
 * SoftwareSerial disables interrupts while transmitting data, so it conflicts with Servo library.
 */
#include "DFRobotDFPlayerMini.h"


namespace DFPLAYER
{
    /// @brief manage DFplayer Mini
    class Dfplayer
    {
    public:
        DFRobotDFPlayerMini dfp;  ///< dfp object
        SoftwareSerial dfpSerial; ///< dfp software serial

    public: // MUST be public to guarantee access of DFP parameters to other objects
        const int m_busyPin{};         ///< DFP busy pin (LOW when busy)
        int m_currentMusic{1};         ///< DFP current music in play
        int m_currentVolume{18};       ///< DFP current volume 0~30
        int m_goodMorningMsg{1};       ///< sequential 'good morning' message
        long m_nStopMsgFiles{};        ///< quantity of 'stop' messages
        long m_nGoodMorningMsgFiles{}; ///< quantity of 'good morning' files
        long m_nMp3Files{};            ///< quantity of mp3 files
        long m_nMenuFiles{};           ///< quantity of menu files
        bool m_radioON{0};             ///< manage radio in continuos mode
        bool m_isPaused{0};            ///< flags radio in pause

    public:
        /// @brief Constructor Dfplayer
        Dfplayer(uint8_t rxPin, uint8_t txPin, int busyPin);

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
        int readBusyPin();

        /// @brief get dfp state
        /// @return 00-playback_finish 01-playing 02-paused 08-sleeping
        int readState();
    };

} // namespace DFPLAYER

#endif //_DFPLAYER_H