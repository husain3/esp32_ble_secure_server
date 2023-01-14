#include <NimBLEDevice.h>

NimBLEServer *pServer;
NimBLEService *pService;
NimBLEAdvertising *pAdvertising;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	Serial.println("Starting NimBLE Server");
	NimBLEDevice::init("NimBLE");

	NimBLEDevice::setPower(ESP_PWR_LVL_P9); /** +9db */

	NimBLEDevice::setSecurityAuth(true, true, true);
	NimBLEDevice::setSecurityPasskey(123456);
	NimBLEDevice::setSecurityIOCap(BLE_HS_IO_DISPLAY_YESNO);

	pServer = NimBLEDevice::createServer();
	pService = pServer->createService("ABCD");

	NimBLECharacteristic *pSecureCharacteristic = pService->createCharacteristic("1235", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::READ_ENC | NIMBLE_PROPERTY::READ_AUTHEN);
	
	pService->start();
	pSecureCharacteristic->setValue("Hello Secure BLE");

	pAdvertising = NimBLEDevice::getAdvertising();
	// Start advertising
	pAdvertising->addServiceUUID("ABCD");
	pAdvertising->setScanResponse(true);
	// pAdvertising->setScanFilter(true, true);

	pAdvertising->start();
}

void loop() {
	// put your main code here, to run repeatedly:
	Serial.println(pServer->getConnectedCount());
}