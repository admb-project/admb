import datetime
import urllib2
import json

print datetime.date.today()

data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/1355046/assets").read()
for o in json.loads(data):
  print o['name'] + ': ' + str(o['download_count'])

data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/1355094/assets").read()
for o in json.loads(data):
  print o['name'] + ': ' + str(o['download_count'])

data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/1328565/assets").read()
for o in json.loads(data):
  print o['name'] + ': ' + str(o['download_count'])
 
