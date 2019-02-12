import datetime
import time
import urllib2
import json

today = datetime.date.today()
time = time.strftime("%H:%M:%S")
releases = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases").read()
for release in json.loads(releases):
  name = release['name']
  total = 0
  for asset in release['assets']:
    download_count = asset['download_count']
    print '\"' + name + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"" + asset['name'] + "\"," + str(download_count)
    total = total + download_count
  print '\"' + name + "\",\"" + str(today) + "\",\"" + str(time) + "\",\"total\"," + str(total)
