// THEFT ALARM USING ULTRASONIC SENSOR AND LED ALERT
// Author: Your Name

#define TRIG_PIN 9
#define ECHO_PIN 10
#define ALERT_LED 6
#define INDICATOR_LED 7

int threshold = 30;
unsigned long lastAlert = 0;
unsigned long cooldown = 5000;

void setup()
{
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(ALERT_LED, OUTPUT);
    pinMode(INDICATOR_LED, OUTPUT);
}

void loop()
{
    long distance = readDistance();

    if (distance > 0 && distance < threshold)
    {
        triggerAlert();

        if ((millis() - lastAlert) > cooldown)
        {
            Serial.println("ALERT");
            lastAlert = millis();
        }
    }

    delay(200);
}

long readDistance()
{
    long duration, distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration == 0)
        return -1;

    distance = duration / 58;
    return distance;
}

void triggerAlert()
{
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(ALERT_LED, HIGH);
        digitalWrite(INDICATOR_LED, HIGH);
        delay(200);
        digitalWrite(ALERT_LED, LOW);
        digitalWrite(INDICATOR_LED, LOW);
        delay(200);
    }
}
