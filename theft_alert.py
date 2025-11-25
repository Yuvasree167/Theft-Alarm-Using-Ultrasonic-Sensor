import serial
import smtplib
from email.mime.text import MIMEText
import time

SERIAL_PORT = "COM5"
BAUD_RATE = 9600

SENDER_EMAIL = "yuvasree167@gmail.com"
SENDER_PASSWORD = "kbdqjmexuyxsqndn"
RECEIVER_EMAIL = "muthumani6131@gmail.com"

try:
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)
    print(f"[INFO] Connected to Arduino on {SERIAL_PORT}")
except Exception as e:
    print("[ERROR] Could not connect:", e)
    exit()

print("Listening for alerts...\n")

def send_email():
    msg = MIMEText("Motion detected by your Arduino Theft Alarm System.")
    msg["Subject"] = "⚠ ALERT: Theft Detected"
    msg["From"] = SENDER_EMAIL
    msg["To"] = RECEIVER_EMAIL

    try:
        with smtplib.SMTP_SSL("smtp.gmail.com", 465) as server:
            server.login(SENDER_EMAIL, SENDER_PASSWORD)
            server.send_message(msg)
        print("✅ Email sent!")
    except Exception as e:
        print("❌ Email error:", e)

while True:
    try:
        data = arduino.readline().decode().strip()
        if data == "ALERT":
            print("\n🚨 ALERT received! Sending email...")
            send_email()
    except KeyboardInterrupt:
        print("\nProgram ended.")
        break
