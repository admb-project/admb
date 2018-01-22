import datetime
import time
import urllib2
import json
from array import array

#To get ids, go to https://api.github.com/repos/admb-project/admb/releases
ids = array("i", [9329819])

print datetime.date.today()
print time.strftime("%H:%M:%S")

for id in ids:
  data = urllib2.urlopen("https://api.github.com/repos/admb-project/adstudio/releases/{}".format(id)).read()
  jsondata = json.loads(data)
  assets = jsondata['assets']
  for o in assets:
    print o['browser_download_url'] + ': ' + str(o['download_count'])
