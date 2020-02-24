import datetime
import time
import urllib2
import json
from array import array

#To get ids, go to https://api.github.com/repos/admb-project/admb/releases
ids = array("i", [22935357, 9004909, 4944493, 4891577, 2275083, 2223621, 1355046, 1355094, 1328565])

print datetime.date.today()
print time.strftime("%H:%M:%S")

for id in ids:
  data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/{}".format(id)).read()
  jsondata = json.loads(data)
  assets = jsondata['assets']
  for o in assets:
    print o['browser_download_url'] + ': ' + str(o['download_count'])
