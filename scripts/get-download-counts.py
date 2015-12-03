import datetime
import time
import urllib2
import json

print datetime.date.today()
print time.strftime("%H:%M:%S")

data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/2223621").read()
jsondata = json.loads(data)
assets = jsondata['assets']
for o in assets:
  print o['browser_download_url'] + ': ' + str(o['download_count'])

data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/1355046").read()
jsondata = json.loads(data)
assets = jsondata['assets']
for o in assets:
  print o['browser_download_url'] + ': ' + str(o['download_count'])

data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/1355094").read()
jsondata = json.loads(data)
assets = jsondata['assets']
for o in assets:
  print o['browser_download_url'] + ': ' + str(o['download_count'])

data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/1328565").read()
jsondata = json.loads(data)
assets = jsondata['assets']
for o in assets:
  print o['browser_download_url'] + ': ' + str(o['download_count'])

