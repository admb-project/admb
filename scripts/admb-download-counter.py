import json
import urllib2

data = urllib2.urlopen("https://api.github.com/repos/admb-project/admb/releases/1328565/assets").read()
for o in json.loads(data):
  print o['name'] + ': ' + str(o['download_count'])
 
