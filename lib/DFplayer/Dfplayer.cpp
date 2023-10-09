
#include "Dfplayer.h"


void Dfplayer::begin()
{
    // wait DFPlayer
    delay(2000);

    // init DFPlayer serial
    dfpSerial.begin(9600);
    
    
    // check DFPlayer connected and SD card inserted
    int tentativa=1;
    while (!dfp.begin(dfpSerial) && tentativa<4) 
    {
        Serial.println(F("SD card error, check connection"));
        //BT.println(F("SD card error, check connection"));
        tentativa++;
        delay(1000);
    }
    if (tentativa == 4 && !dfp.begin(dfpSerial)) 
    {
        Serial.println("DFplayer OFF");
        //BT.println("DFplayer OFF");
    }
    else 
    {
        Serial.println(F("DFPlayer ON ..."));
        //BT.println(F("DFPlayer ON ..."));
    
        // Continue  DFplayer init
        dfp.setTimeOut(500);        ///< Set serial communictaion time out 500ms
        dfp.volume(volumeAtual);    ///<Set volume value (0~30)
        dfp.EQ(DFPLAYER_EQ_NORMAL); ///< set equalizer
        dfp.outputDevice(DFPLAYER_DEVICE_SD);  ///< set SD card output
    

        // check number of "STOP messages"
        nArqvMsgStop=-1;
        int j=0;
        while (nArqvMsgStop == -1 && j < 5)  
        {
            nArqvMsgStop= dfp.readFileCountsInFolder(2);
            j++;
            delay(200);
        }
        if (nArqvMsgStop == -1) nArqvMsgStop=21;
        Serial.print("# of Stop messages: ");Serial.println(nArqvMsgStop);
        //BT.print("# of Stop messages: ");BT.println(nArqvMsgStop);

        // check number of "good morning" messages
        nArqvMsgBomDia=-1;
        j=0;
        while (nArqvMsgBomDia == -1 && j < 5)  
        {
            nArqvMsgBomDia= dfp.readFileCountsInFolder(1);
            j++;
            delay(200);
        }
        if (nArqvMsgBomDia == -1) nArqvMsgBomDia=13;
        Serial.print("# of good morning messages: ");Serial.println(nArqvMsgBomDia);
        //BT.print("# of good morning messages: ");BT.println(nArqvMsgBomDia);
    
        // check number of MP3 musics
        nArqvMp3=-1;
        j=0;
        while (nArqvMp3 == -1 && j < 5)  
        {
            nArqvMp3= dfp.readFileCountsInFolder(3);
            j++;
            delay(200);
        }
        if (nArqvMp3 == -1) nArqvMp3=12;
        Serial.print("# of MP3 musics ");Serial.println(nArqvMp3);
        //BT.print("# of MP3 musics ");BT.println(nArqvMp3);
    
        // check Menu message"
        nArqvMenu=-1;
        j=0;
        while (nArqvMenu == -1 && j < 5)  
        {
            nArqvMenu= dfp.readFileCountsInFolder(4);
            j++;
            delay(200);
        }
        if (nArqvMenu == -1) nArqvMenu=1;
        Serial.print("Menu message: ");Serial.println(nArqvMenu);
        //BT.print("Menu message: ");BT.println(nArqvMenu);
    }
}

void Dfplayer::sendMsgStop() 
{
    bool notBusy{};
    long sustoMsg=random(1,nArqvMsgStop+1);
    
    // if Roberto is listening radio, play Stop message on Advertisement folder
    if (radioON) 
    {       
        dfp.advertise(sustoMsg);
    }
    else 
    {
        notBusy=digitalRead(m_busyPin);
        if (notBusy) 
        {
            dfp.playFolder(2,sustoMsg);
        }
    }
}

void Dfplayer::sendGoodMorning() 
{
    bool notBusy{};
    msgAtual=random(1,nArqvMsgBomDia+1);
    notBusy=digitalRead(m_busyPin);     
    if (notBusy) 
    {
        dfp.playFolder(1,msgAtual);
    }

}

void Dfplayer::setVolume(int vol)
{
    volumeAtual = vol;
}


