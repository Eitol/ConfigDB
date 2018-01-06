#include <math.h>
#include <configdb.h>

/** The custom MyConfiguration class  **/
class MyConfiguration
{
  public:
    int intValue;
    float floatValue;
};

ConfigDB<MyConfiguration> configDB;

bool printCfg(MyConfiguration cfg)
{
    Serial.printf("cfg.intValue:%d\n", cfg.intValue);
    Serial.printf("cfg.floatValue:%f\n", cfg.floatValue);
}

void setup()
{
    Serial.begin(9600);

    //                         intValue | floatValue
    MyConfiguration defaultCfg = {0, 9876.543};

    // If the MyConfiguration is not saved then save it with a default value
    bool isPreviusConfigStored = configDB.storeDefaultIfNotLoad(defaultCfg);

    Serial.printf("\nisPreviusConfigStored=%d\n", isPreviusConfigStored); // False

    // Get the Configuration from the eeprom
    MyConfiguration newCfg = configDB.load();
    printCfg(newCfg);

    // Make new config and save
    newCfg.intValue = 1234;
    newCfg.floatValue = EULER;
    configDB.save(newCfg);

    // Get the new MyConfiguration recently saved in the eeprom
    newCfg = configDB.load();
    printCfg(newCfg);

    configDB.clear();    
}

void loop()
{
    // put your main code here, to run repeatedly:
}