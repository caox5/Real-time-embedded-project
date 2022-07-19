import smtplib

#Email Variables
SMTP_SERVER = 'smtp.gmail.com' #Email Server (don't change!)
SMTP_PORT = 587 #Server Port (don't change!)
GMAIL_USERNAME = 'falldetectionrpi@gmail.com' #change this to match your gmail account
GMAIL_PASSWORD = 'Caoxin12345' #change this to match your gmail password

class Emailer:
    def sendmail(self, recipient, subject, content):

#Create Headers
        headers = ["From: " + GMAIL_USERNAME, "Subject: " + subject, "To: " + recipient,
                   "MIME-Version: 1.0", "Content-Type: text/html"]
        headers = "\r\n".join(headers)

#Connect to Gmail Server
        session = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        session.ehlo()
        session.starttls()
        session.ehlo()

#Login to Gmail
        session.login(GMAIL_USERNAME, GMAIL_PASSWORD)

#Send Email and Exit
        session.sendmail(GMAIL_USERNAME, recipient, headers + "\r\n\r\n" + content)
        session.quit

sender = Emailer()

sendTo = 'loowing397@163.com' #Change this to the email you wish to send to (could change)
emailSubject = "Falldetector" #The Subject of the Email (could change)
emailContent = "Fall has been detected!!!" #The Content / Body of the email (could change)

#Sends an email to the "sendTo" address with the specified "emailSubject" as the subject and "emailContent" as the email content.
sender.sendmail(sendTo, emailSubject, emailContent)
