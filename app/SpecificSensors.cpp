/*
 * SpecificSensors.cpp
 *
 *  Created on: 28 ���. 2016 �.
 *      Author: Anakod
 */

#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include "SpecificSensors.h"
#include <Libraries/DHT/DHT.h>


SensorDHT::SensorDHT(String type) :
		Sensor(0)
{
	type.toLowerCase();
	if (type == "dht11")
		this->type = DHT11;
	else if (type == "dht21" || type == "am2301")
		this->type = DHT21;
	else if (type == "dht22")
		this->type = DHT22;
	else
		debugf("UNK DHT!");
}

SensorDHT::~SensorDHT()
{
	delete dht;
}

void SensorDHT::onLoad(JsonObject& data)
{
	dht = new DHT(pins[DFNAME], type);
}

void SensorDHT::onBegin()
{
	//if (!initialized)
	{
		dht->begin();
		initialized = true;
	}
	TempAndHumidity result;
	bool ok = dht->readTempAndHumidity(result);
	if (ok)
	{
		store("temperature", result.temp);
		store("humidity", result.humid);
	}
	else
	{
		debugf("failed read DHT sensor");
		//dht->begin();
	}
}

/////////

void SensorAnalogReader::onBegin()
{
	//int pin = pins[DFNAME];
	store(analogRead(A0));
}

/////////

void SensorButton::onLoad(JsonObject& data)
{
	//auto cb = &SensorButton::onRrepeat;
	//attachInterrupt(pins[DFNAME], Delegate<void()>(cb, (WorkingObject*)this), CHANGE);
}

void SensorButton::onFinish()
{
	int pin = pins[DFNAME];
	bool state = digitalRead(pin);
	store(state);
}
