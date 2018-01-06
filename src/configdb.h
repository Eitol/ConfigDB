#ifndef _CONFIG_DB__
#define _CONFIG_DB__

#include <EEPROM.h>
#include <Arduino.h>

/**
    If the first segment of the config is the PI number then a
    valid config is stored in the EEPROM
*/
double VALID_CONFIG_ID = (double)PI;

template <class T>
class ConfigDB
{
  public:
    /**
       @param startAddr: address of the EEPROM where the
                         configuration data is stored.
    */
    ConfigDB(int startAddr = 0)
    {
        this->_startAddr = startAddr;
        this->_startConfigAddr = startAddr + sizeof(VALID_CONFIG_ID);
        EEPROM.begin(sizeof(T) + sizeof(VALID_CONFIG_ID));
    }

    /**
       If there is no stored configuration then save one using the default
       values of the Config class

       @return true if save defaults config, false otherwise
    */
    bool storeDefaultIfNotLoad(T defaultValue)
    {
        if (!isValidConfigStored())
        {
            this->save(defaultValue);
            return false;
        }
        return true;
    }

    /**
       Save config in the EEPROM
    */
    void save(T cfg)
    {
        EEPROM.put(this->_startAddr, VALID_CONFIG_ID);
        EEPROM.put(this->_startConfigAddr, cfg);
        EEPROM.commit();
    }

    /**
       Load config from the EEPROM
    */
    T load()
    {
        T tmpCfg;
        EEPROM.get(this->_startConfigAddr, tmpCfg);
        return tmpCfg;
    }

    /**
       clear the configuration (set to zeroes)
    */
    void clear()
    {
        for (unsigned int i = this->_startAddr; i < (sizeof(T) + sizeof(VALID_CONFIG_ID)); i++)
        {
            EEPROM.write(i, 0);
        }
        EEPROM.commit();
    }

    /**
       Check if a valid configuration is stores in the segment of EEPROM
    */
    bool isValidConfigStored()
    {
        double firstData;
        EEPROM.get(this->_startAddr, firstData);
        return firstData == VALID_CONFIG_ID;
    }

    /**
       Get the start address of the config in EEPROM
    */
    int getStartAddr()
    {
        return this->_startAddr;
    }

    /**
       Get the last address of the config in EEPROM.
    */
    int getEndAddr()
    {
        return this->_startConfigAddr + sizeof(T);
    }

  private:
    unsigned int _startAddr;
    unsigned int _startConfigAddr;
};

#endif